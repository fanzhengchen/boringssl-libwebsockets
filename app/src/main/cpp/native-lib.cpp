#include <jni.h>
#include <string>
#include <android/log.h>
#include <openssl/rsa.h>
#include <libwebsockets.h>
#include "register.h"

#define JNIREG_CLASS "mark/com/boringssl/MainActivity"
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, "LwsService", ##__VA_ARGS__)

JavaVM *gJvm = NULL;
JNIEnv *gEnv = NULL;

JNIEXPORT jstring JNICALL jni_stringFromJNI(JNIEnv *, jobject);

const int NUM_OF_METHODS = 1;
static JNINativeMethod methods[NUM_OF_METHODS] = {
        {"stringFromJNI", "()Ljava/lang/String;", (void *)jni_stringFromJNI}
};


JNIEXPORT jstring JNICALL
jni_stringFromJNI(JNIEnv *env, jobject /* this */) {
    std::string hello = "Hello from C++";



    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    jint result = -1;
    gJvm = vm;
    LOGV("jni on load");
    if (vm->GetEnv((void **) &gEnv, JNI_VERSION_1_6) != JNI_OK) {
        return result;
    };
    if (vm->AttachCurrentThread(&gEnv, NULL) < 0) {
        return result;
    };
    if (registerNativeMethods(gEnv, JNIREG_CLASS, methods, NUM_OF_METHODS) != JNI_TRUE) {
        return result;
    }

    result = JNI_VERSION_1_6;
    return result;
}

extern "C"
JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved) {
//    gJvm = NULL;
}

