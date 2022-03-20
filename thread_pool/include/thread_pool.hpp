#ifndef WEB_THREAD_POOL_HPP
#define WEB_THREAD_POOL_HPP

#include <template.hpp>

#include <mutex>

class ThreadPool : public Instance<ThreadPool>
{
public:
    ThreadPool();
    void beginThread();

private:
    void coutTest();
    
private:
    std::mutex mtx;
};

#endif