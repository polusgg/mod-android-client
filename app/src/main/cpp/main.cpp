#include <jni.h>
#include <pthread.h>
#include "util/logger.h"

void *mod_thread(void *) {
    return nullptr;
}

extern "C" JNIEXPORT void JNICALL
Java_com_cydon_pggandroid_MainActivity_initMod(
        JNIEnv* env,
        jobject /* this */)
{
    pthread_t pthread;
    pthread_create(&pthread, nullptr, mod_thread, nullptr);
}
