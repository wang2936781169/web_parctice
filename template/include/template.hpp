#ifndef WEB_TEMPLATE_HPP
#define WEB_TEMPLATE_HPP

template<class T>
class NoCopy
{
protected:
    NoCopy() = default;
    ~NoCopy() = default;

private:
    NoCopy& operator=(const NoCopy&);
    NoCopy(const NoCopy&);
};

template <class T>
class Instance : public NoCopy<T>
{
public:
    static T& get() 
    { 
        static T instance; 
        return instance; 
    }

protected:
    Instance() = default;
    ~Instance() = default;
};

#endif