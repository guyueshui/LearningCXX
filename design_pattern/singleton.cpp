// A singleton class
// c.f. https://zhuanlan.zhihu.com/p/37469260

#include <iostream>
#include <mutex>
using namespace std;

std::mutex gm;

/**
 * This is so-called lazy-singleton, since it creates the
 * instance until you ask for it.
 *
 * However, it may cause memory leak, since you have no
 * way to delete the instance you created.
 */
class SingletonV1
{
public:
  static SingletonV1* GetInstance()
  {
    if (pinstance_ == nullptr)
      pinstance_ = new SingletonV1();
    return pinstance_;
  }
private:
  SingletonV1() = default;
  ~SingletonV1() = default;
  SingletonV1(const SingletonV1&) = delete;
  SingletonV1& operator=(const SingletonV1&) = delete;
private: 
  static SingletonV1* pinstance_;
};
// static member initialization
SingletonV1* SingletonV1::pinstance_ = nullptr;

/**
 * This is also a lazy-singleton, but it's thread-safe.
 * It is so-called Double-Checked Locking Pattern (DCL).
 */
class SingletonV2
{
public:
  static SingletonV2* GetInstance()
  {
    if (pinstance_ == nullptr)
    {
      // Attention here: see if >= 2 threads meets here,
      // only one thread can hold the mutex, then create
      // the instance, this is can only occur on your first
      // request on instance, once the instance is created,
      // we can return it immediately.
      std::lock_guard<std::mutex> lk(gm);

      // See why double check here?
      // Cause if >= 2 threads have already run across here,
      // they've waited and finally held the mutex, w/o this
      // check, all of these threads will create a instance,
      // that's not what you want.
      if (pinstance_ == nullptr)  // double check
        pinstance_ = new SingletonV2();
    }
    return pinstance_;
  }
private:
  SingletonV2() = default;
  ~SingletonV2() = default;
  SingletonV2(const SingletonV2&) = delete;
  SingletonV2& operator=(const SingletonV2&) = delete;
private: 
  static SingletonV2* pinstance_;
};
// static member initialization
SingletonV2* SingletonV2::pinstance_ = nullptr;

/**
 * C++11 ensures the mt-safety of local static object. Taking
 * the advantage of this, <<Effective C++>> provides us an elegant
 * implemention of mt-safe singleton.
 */
class SingletonV3
{
public:
  static SingletonV3* GetInstance()
  {
    // Note that instance will be created only at the first time.
    static SingletonV3 instance;
    return &instance;
  }
private:
  SingletonV3() = default;
  ~SingletonV3() = default;
  SingletonV3(const SingletonV3&) = delete;
  SingletonV3& operator=(const SingletonV3&) = delete;
};

/**
 * This is an eager-singleton which create an instance at first,
 * then return it as required.
 *
 * It's mt-safe since the instance initiliazation is before main()
 * function.
 */
class SingletonV4
{
public:
  static SingletonV4* GetInstance()
  {
    return &instance_;
  }
private:
  SingletonV4() = default;
  ~SingletonV4() = default;
  SingletonV4(const SingletonV4&) = delete;
  SingletonV4& operator=(const SingletonV4&) = delete;
private:
  // note that here is not a pointer, since a pointer will not own
  // a memory range by default.
  static SingletonV4 instance_;
};
// initialize the static member
SingletonV4 SingletonV4::instance_;

//============== Notes ==================
/**********************************************************************
Use a Singleton if:
 - If you need to have one and only one object of a type in system
Do not use a Singleton if:
 - If you want to save memory
 - If you want to try something new
 - If you want to show off how much you know
 - Because everyone else is doing it (See cargo cult programmer in wikipedia)
 - In user interface widgets
 - It is supposed to be a cache
 - In strings
 - In Sessions
 - I can go all day long
ow to create the best singleton:
 - The smaller, the better. I am a minimalist
 - Make sure it is thread safe
 - Make sure it is never null
 - Make sure it is created only once
 - Lazy or system initialization? Up to your requirements
 - Sometimes the OS or the JVM creates singletons for you (e.g. in Java every class definition is a singleton)
 - Provide a destructor or somehow figure out how to dispose resources
 - Use little memory
*************************************************************************/
