#pragma once
#include <jni.h>
#include <string>

inline JavaVM* g_jvm;

JNIEnv* get_thread_jnienv();

std::string stdstring(JNIEnv* env, jstring string);