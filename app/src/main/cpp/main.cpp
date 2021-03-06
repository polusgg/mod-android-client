#include <jni.h>
#include <pthread.h>
#include "util/logger.h"
#include "util/helpers.h"
#include "framework/il2cpp-init.h"
#include "services/InnerNetObjManager.h"
#include "patches/patch_manager.h"

uintptr_t il2cpp_base_address;

void *mod_thread(void *) {

    LOGI("Starting execution of mod thread");

    il2cpp_base_address = 0;

    // Make sure libil2cpp.so is loaded
    while (il2cpp_base_address == 0) {
        il2cpp_base_address = get_library_address("libil2cpp.so");
    }

    // Initialize all function/struct pointers
    init_il2cpp();

    // Initialize Services
    services::InnerNetObjManager::getInstance().init();

    // Patch all functions
    patch_all();

    return nullptr;
}

__attribute__((constructor))
static void ctor()
{
    pthread_t pthread;
    pthread_create(&pthread, nullptr, mod_thread, nullptr);
}
