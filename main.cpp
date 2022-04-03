#include <iostream>
#include <string>

#include <socket.hpp>
#include <thread_pool.hpp>

using namespace std;
const int PORT = 9000;
const int OPEN_MAX = 1024;

int test()
{
    std::cout << "hello world" << std::endl;
    return 1;
}

int main(int argc, char** argv)
{
    ThreadPool::get().start();
    std::future<int> ret = ThreadPool::get().run(&test);
    std::cout << ret.get() << std::endl;

    return 0;
}