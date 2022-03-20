#include <socket.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <iostream>
#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <ctype.h>
#include <sys/socket.h>
#include <errno.h>
#include <iostream>

#include <common.hpp>

BasicSocket::BasicSocket()
    : m_domain(AF_INET)
{
    bzero(buf, BUFSIZ);
}

BasicSocket::~BasicSocket()
{
    if(m_sockAddrIn)
    {
        delete m_sockAddrIn;
        m_sockAddrIn = nullptr;
    }
}

void BasicSocket::Socket(int _type, int _protocol)
{
    m_sockfd = socket(m_domain, _type, _protocol);
    if(m_sockfd == -1) 
    {
        Perror("Socket Error");
    }

    m_type = _type;
    m_protocol = _protocol;
}

void BasicSocket::SetSockOpt()
{
    int opt = 1;
    int ret = setsockopt(m_sockfd, SOL_SOCKET, SO_REUSEADDR, (void*)&opt, sizeof(opt));
    if(ret == -1)
    {
        Perror("Set Sock Option Error");
    }
}

void BasicSocket::Bind(struct sockaddr_in& _sockAddrIn)
{
    int ret = bind(m_sockfd, (const sockaddr*)&_sockAddrIn, sizeof(_sockAddrIn));
    if(ret == -1)
    {
        Perror("Bind Error");
    }
    m_sockAddrIn = new struct sockaddr_in(_sockAddrIn);
}

void BasicSocket::Listen(int _num)
{
    int ret = listen(m_sockfd, _num);
    if(ret == -1) 
    {
        Perror("Listen Error");
    }
}

TCPServer::ClientInfo::ClientInfo()
    :clientAddr(new struct sockaddr_in)
{
    
}

TCPServer::TCPServer(int _port)
    : BasicSocket()
{
    //socket
    {
        Socket(SOCK_STREAM, 0);
    }

    //set sock opt
    {
        SetSockOpt();
    }

    //bind
    {
        struct sockaddr_in sockAddr;
        sockAddr.sin_family = m_domain;
        sockAddr.sin_port = htons(_port);
        sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);

        Bind(sockAddr);
    }

    //listen
    {
        Listen();
    }
}

const std::shared_ptr<TCPServer::ClientInfo> TCPServer::Accept()  noexcept
{
    std::shared_ptr<ClientInfo> info(new ClientInfo);

    try
    {
        socklen_t sock_len = sizeof(info->clientAddr);
        while(true)
        {
            info->clientFd = accept(m_sockfd, (struct sockaddr*)info->clientAddr.get(), &sock_len);
            if(info->clientFd == -1)
            {
                if(errno == EINTR) continue;
                if(errno == ECONNRESET) continue;

                Perror("Accpet Error");
            }
            break;
        }
    }
    catch(...)
    {
        return nullptr;
    }

    return info;
}

const std::string TCPServer::Recv(const std::shared_ptr<TCPServer::ClientInfo> _client)
{
    bzero(buf, BUFSIZ);

    while (true)
    {
        int ret = recv(_client->clientFd, buf, BUFSIZ, 0);
        if(ret == -1)
        {
            if(errno == EINTR) continue;
            if(errno == ECONNRESET) continue;

            Perror("Recv Error");
        }
        break;
    }
    
    return buf;
}

const std::string TCPServer::Recv(const std::shared_ptr<TCPServer::ClientInfo> _client, size_t n)
{
    bzero(buf, BUFSIZ);

    size_t left = 0;
    size_t right = n;
    while(left < right)
    {
        int ret = recv(_client->clientFd, buf + left, right - left, 0);
        if(ret == -1)
        {
            if(errno == EINTR) continue;
            if(errno == ECONNRESET) continue;

            Perror("Recv N Error");
        }

        left += ret;
    }

    return buf;
}

const short TCPServer::RecvOne(const std::shared_ptr<TCPServer::ClientInfo> _client, char& c)
{
    static std::string str_buf;
    static size_t left = 0;

    if(str_buf.size() == left)
    {
        left = 0;
        str_buf = Recv(_client);
    }

    if(str_buf.empty()) return 0;
    c = str_buf[left++];
    return 1;
}

const std::string TCPServer::RecvLine(const std::shared_ptr<TCPServer::ClientInfo> _client)
{
    std::string recvMes;
    char c;
    while(true)
    {
        short ret = RecvOne(_client, c);
        if(ret == 1)
        {
            recvMes += c;
            if(c == '\n') break;
        }
        else if(ret == -1)
        {
            throw ;
        }
        else if(ret == 0)
        {
            break;
        }
    }

    return recvMes;
}
    
void TCPServer::Send(const std::shared_ptr<TCPServer::ClientInfo> _client, const std::string& str)
{
    bzero(buf, BUFSIZ);

    strcpy(buf, str.c_str());
    
    size_t cur = 0;
    while(cur < str.size())
    {
        int ret = send(_client->clientFd, buf + cur, str.size() - cur, 0);
        if(ret == -1)
        {
            if(errno == EINTR) continue;
            if(errno == ECONNRESET) continue;

            Perror("Send Error");
        }

        cur += ret;
    }
}