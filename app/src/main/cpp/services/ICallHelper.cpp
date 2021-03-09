#include "ICallHelper.h"
#include <string>
#include <cinttypes>
#include "../util/logger.h"

void services::ICallHelper::init() {
    LOGI("[+] Initializing ICallHelper");
    // this->ResolveICall("UnityEngine.ImageConversion::LoadImage");
    // this->ResolveICall("UnityEngine.Sprite::CreateSprite_Injected");
}

void services::ICallHelper::destroy() {
    LOGI("[-] Destroying ICallHelper");

    this->ICallCache.clear();
}

void *services::ICallHelper::ResolveICall(const std::string& name) {
    for (auto& cachedCall : this->ICallCache) {
        if (cachedCall.name == name)
            return cachedCall.addr;
    }

    auto method = (void *) il2cpp_resolve_icall(name.c_str());
    if (method) {
        Il2CppICall call;
        call.addr = method;
        call.name = name;
        this->ICallCache.push_back(call);
        LOGI("[+] Found ICall %s at address: 0x%016" PRIxPTR "\n", name.c_str(), (uintptr_t) method);
    } else {
        LOGW("[-] Could not find ICall %s", name.c_str());
    }
    return (void *) method;
}
