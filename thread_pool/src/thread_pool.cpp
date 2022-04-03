#include <thread_pool.hpp>

#include <iostream>

#include <vector>
#include <queue>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

#include <chrono>

struct ThreadPool::ThreadPoolImpl
{
    std::atomic<bool> finished;
    const size_t max_thread_num = 10;

    //tasks
    std::queue<std::function<void()>> tasks;

    //threads
    std::vector<std::thread> threas;

    //mutex
    std::mutex mtx;
    std::condition_variable cnv;
};

ThreadPool::ThreadPool()
    : Instance<ThreadPool>()
    , PImpl(new ThreadPoolImpl)
{
    PImpl->finished.store(true);
}

ThreadPool::~ThreadPool()
{
    PImpl->finished.store(true);
    PImpl->cnv.notify_all();

    for(size_t i=0 ; i<PImpl->threas.size() ; ++i)
    {
        PImpl->threas[i].join();
    }
}

void ThreadPool::start()
{
    PImpl->finished.store(false);
    for(size_t i=0 ; i<PImpl->max_thread_num ; ++i)
    {
        PImpl->threas.emplace_back(&ThreadPool::workThread, &ThreadPool::get());
    }
}

void ThreadPool::setData(std::function<void()>&& func)
{
    std::unique_lock<std::mutex> lock(PImpl->mtx);
    PImpl->tasks.emplace(func);
    PImpl->cnv.notify_one();
}

void ThreadPool::workThread()
{
    while(!PImpl->finished.load())
    {
        std::unique_lock<std::mutex> lock(PImpl->mtx);
        PImpl->cnv.wait(lock, [this]() { return PImpl->finished.load() || !PImpl->tasks.empty(); });
        if(PImpl->finished.load()) return ;

        std::function<void()> func = PImpl->tasks.front();
        PImpl->tasks.pop();

        lock.unlock();

        func();
    }
}