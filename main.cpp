#include <iostream>
#include <string>

#include <socket.hpp>
#include <thread_pool.hpp>

using namespace std;
const int PORT = 9000;
const int OPEN_MAX = 1024;

int main(int argc, char** argv)
{
    ThreadPool& tp = ThreadPool::get();
    tp.beginThread();

    while(true);

    return 0;
}