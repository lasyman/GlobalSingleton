#pragma once

#include "Singleton.hpp"
#include "DllWrapper.hpp"

class GlobalSingletonContext : public Singleton<GlobalSingletonContext> {
public:
    // singleton manager dynamic library: sgtmgr.dll or (lib)sgtmgr.so
    const std::string SingletonManagerLibrary = "sgtmgr";

    GlobalSingletonContext()
    {
        if (!manager.Load(SingletonManagerLibrary)) {
            std::string except = "The singleton manager library `" +
                SingletonManagerLibrary + "` does not exist!";
#ifdef _WIN32
            throw std::exception(except.c_str());
#else
            throw std::logic_error(except.c_str());
#endif
        }
    }

    template <typename T>
    inline T* Regist()
    {
        bool construct = !(manager.ExecuteFunction<uint32_t(size_t)>(
            "Count", typeid(T).hash_code()) > 0);
        T* instance = manager.ExecuteFunction<T*(size_t, size_t)>(
            "Obtain", typeid(T).hash_code(), sizeof(T));
        if (!instance) {
#ifdef _WIN32
            throw std::exception("The singleton internal fatal!");
#else
            throw std::logic_error("The singleton internal fatal!");
#endif
        }
        if (construct) {
            new(instance) T;
        }
        return instance;
    }

    template <typename T>
    inline void Unregist()
    {
        T* instance = manager.ExecuteFunction<T*(size_t)>(
            "Release", typeid(T).hash_code());
        bool destruct = !(manager.ExecuteFunction<uint32_t(size_t)>(
            "Count", typeid(T).hash_code()) > 0);
        if (instance && destruct) {
            instance->~T();
        }
    }

private:
    DllWrapper manager;
};
