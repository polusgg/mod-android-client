#include <jni.h>
#include <pthread.h>
#include "util/logger.h"
#include "util/helpers.h"
#include "util/jni_helpers.h"
#include "framework/il2cpp-init.h"
#include "services/InnerNetObjManager.h"
#include "patches/patch_manager.h"
#include "services/ICallHelper.h"

uintptr_t il2cpp_base_address;

void *mod_thread(void *) {

    LOGI("[+] Starting execution of mod thread");

    // Side effect to attach JavaVM to this pthread
    get_thread_jnienv();
    il2cpp_base_address = 0;

    // Make sure libil2cpp.so is loaded
    while (il2cpp_base_address == 0) {
        il2cpp_base_address = get_library_address("libil2cpp.so");
    }

    // Initialize all function/struct pointers
    init_il2cpp();
    LOGI("[+] Initialized il2cpp pointers");

    // Initialize Services
    services::InnerNetObjManager::getInstance().init();
    services::ICallHelper::getInstance().init();
    LOGI("[+] Initialized services");

    // Patch all functions
    patch_all();
    LOGI("[+] Patched and detoured functions");

    return nullptr;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_cydon_pggandroid_MainActivity_initMod(
        JNIEnv *env,
        jobject thiz
) {
    env->GetJavaVM(&g_jvm);

    pthread_t pthread;
    pthread_create(&pthread, nullptr, mod_thread, nullptr);
}
