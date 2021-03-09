#pragma once

#include <string>
#include <list>
#include "framework/il2cpp-appdata.h"

struct Il2CppICall {
public:
    void *addr;
    std::string name;
};

namespace services {
    class ICallHelper {

    private:
        ICallHelper() {}

        std::list<Il2CppICall> ICallCache;

    public:
        static ICallHelper& getInstance() {
            // Guaranteed to be destroyed.
            static ICallHelper instance;
            // Instantiated on first use.
            return instance;
        }

        ICallHelper(ICallHelper const&) = delete;
        void operator = (ICallHelper const&) = delete;

        void init();
        void destroy();

        void *ResolveICall(const std::string& name);
    };
}


