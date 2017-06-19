//
// Created by fanzhengchen on 6/18/17.
//

#include "register.h"

int registerNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *gMethods,
                          int numMethods) {

    jclass cls = env->FindClass(className);
    if (cls == NULL) {
        return JNI_FALSE;
    }

    if (env->RegisterNatives(cls, gMethods, numMethods) < 0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

