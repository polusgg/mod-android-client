#include "jni_helpers.h"
#include <jni.h>
#include <string>

JNIEnv* get_thread_jnienv() {
    JNIEnv * thread_env;
    int res = g_jvm->GetEnv((void **)&thread_env, JNI_VERSION_1_6);

    if (res == JNI_EDETACHED) {
        JavaVMAttachArgs args;
        args.version = JNI_VERSION_1_6;
        args.name = nullptr;
        args.group = nullptr;
        g_jvm->AttachCurrentThread(&thread_env, &args);
    }

    return thread_env;
}

std::string stdstring(JNIEnv* env, jstring string)
{
    int strlen = env->GetStringUTFLength(string);
    const char *utf_string = env->GetStringUTFChars(string, nullptr);

    std::string std_string(utf_string, strlen);
    env->ReleaseStringUTFChars(string, utf_string);

    return std_string;
}
