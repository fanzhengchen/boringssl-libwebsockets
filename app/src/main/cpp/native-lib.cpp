#include <jni.h>
#include <string>
#include <android/log.h>
#include <openssl/ssl.h>
#include "libwebsockets.h"


static lws_client_connect_info connect_info;
static lws_context_creation_info creation_info;

extern "C"
JNIEXPORT jstring JNICALL
Java_com_fzc_jni_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    c
    __android_log_print(ANDROID_LOG_ERROR, "jni on unload", "%s", "exit");

    return env->NewStringUTF(hello.c_str());
}


