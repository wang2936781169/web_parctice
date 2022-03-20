#ifndef WEB_SOCKET_HPP
#define WEB_SOCKET_HPP

#include <string>
#include <set>
#include <memory>
#include <iostream>

struct sockaddr_in;

class BasicSocket
{
public:
    const int getSockFd() const { return m_sockfd; }

protected:
    BasicSocket();
    virtual ~BasicSocket();

    void Socket(int _type, int _protocol);
    void SetSockOpt();
    void Bind(struct sockaddr_in& _sockAddrIn);
    void Listen(int _num = 128);

protected:
    int m_domain;
    int m_sockfd;

    char buf[BUFSIZ];

private:
//  socket param
    int m_type;
    int m_protocol;

//  bind param
    struct sockaddr_in* m_sockAddrIn;
};

class TCPServer : public BasicSocket
{
public:
    struct ClientInfo
    {
        ClientInfo();
        int clientFd;
        std::shared_ptr<struct sockaddr_in> clientAddr;
    };

public:
    TCPServer(int _port);

    const std::shared_ptr<ClientInfo> Accept() noexcept;

    const std::string Recv(const std::shared_ptr<ClientInfo> _client);
    const std::string Recv(const std::shared_ptr<ClientInfo> _client, size_t n);
    const short RecvOne(const std::shared_ptr<ClientInfo> _client, char& c);
    const std::string RecvLine(const std::shared_ptr<ClientInfo> _client);

    void Send(const std::shared_ptr<ClientInfo> _client, const std::string& str);

private:
    

};

#endif
