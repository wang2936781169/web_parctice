#ifndef WEB_THREAD_POOL_HPP
#define WEB_THREAD_POOL_HPP

#include <template.hpp>

#include <memory>
#include <future>
#include <functional>

class ThreadPool : public Instance<ThreadPool>
{
    friend Instance<ThreadPool>;

    struct ThreadPoolImpl;

public:
    template<class Func, class ...Args>
#ifdef ThreadReturn
    auto run(Func&& func, Args&& ...args) -> 
        std::future<decltype(std::bind(func, args...)())>
#else
    void run(Func&& func, Args&& ...args)
#endif
    {
#ifdef ThreadReturn
        using ret_type = decltype(std::bind(func, args...)());
        auto packaged = std::make_shared<std::packaged_task<ret_type()>>(
            std::bind(func, args...));
        std::future<ret_type> ret_fu = packaged->get_future();
        setData([packaged] { (*packaged)(); });
        return ret_fu;
#else
        setData(std::bind(func, args...));
#endif
    }

    void start();

private:
    void setData(std::function<void()>&&);

private:
    ThreadPool();
    ~ThreadPool();

private:
    void workThread();
    
private:
    std::unique_ptr<ThreadPoolImpl> PImpl;
};

#endif