#ifndef WEB_TEMPLATE_HPP
#define WEB_TEMPLATE_HPP

template<class T>
class NoCopy
{
protected:
    NoCopy() = default;
    ~NoCopy() = default;

private:
    NoCopy& operator=(const NoCopy&) = delete;
    NoCopy(const NoCopy&) = delete;
};

template<class T>
class Instance : private NoCopy<T>
{
public:
    static T& get() { static T instance; return instance; }

protected:
    Instance() {};
    ~Instance() = default;
};

#endif