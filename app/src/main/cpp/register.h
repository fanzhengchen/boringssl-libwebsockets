//
// Created by fanzhengchen on 6/18/17.
//

#ifndef BORINGSSL2_REGISTER_H
#define BORINGSSL2_REGISTER_H

#include <jni.h>

int registerNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *gMethods,
                          int numMethods);


#endif //BORINGSSL2_REGISTER_H

