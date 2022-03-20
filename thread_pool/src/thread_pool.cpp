#include <thread_pool.hpp>

#include <iostream>
#include <thread>
#include <chrono>

ThreadPool::ThreadPool()
{
}

void ThreadPool::beginThread()
{
    for(size_t i=0 ; i<10 ; ++i)
    {
        std::thread t(&ThreadPool::coutTest, this);
        t.detach();
    }
}

void ThreadPool::coutTest()
{
    while(true)
    {
        this->mtx.lock();
        {
            std::cout << "test pid = " << std::this_thread::get_id() << std::endl;
        }
        this->mtx.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
