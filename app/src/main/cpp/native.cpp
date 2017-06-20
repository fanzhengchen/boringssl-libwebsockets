#include <jni.h>
#include <string>
#include <android/log.h>
#include <libwebsockets.h>
#include "register.h"
#include "native.h"

#define JNI_CLASS "mark/com/boringssl/JNI"
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, "LwsService", ##__VA_ARGS__)
#define BUFFER_SIZE 4096

JavaVM *gJvm = NULL;
JNIEnv *gEnv = NULL;
lws_client_connect_info connect_info;
lws_context_creation_info creation_info;
lws_context *context = NULL;
lws *wsi = NULL;

struct per_session_data {
    int data;
};

static int
callback(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len) {
    LOGV("callback invoke %d", reason);
    return 0;
}

static int
callback2(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len) {
    LOGV("callback2 invoke %d", reason);
    return 0;
}

enum websocket_protocols {
    PROTOCOL_DUMP_INCREMENT = 0,
    PROTOCOL_COUNT
};

const lws_protocols protocols[] = {
        {"dump-increment-protocol", callback, sizeof(per_session_data), BUFFER_SIZE},
        {"http",                    callback2, sizeof(per_session_data), BUFFER_SIZE},
        {NULL, NULL,                          0, 0}
};

const lws_extension exts[] = {
        {"deflate-frame", lws_extension_callback_pm_deflate, "deflate-frame"},
        {NULL, NULL, NULL}
};

void init() {
    lws_context_creation_info &info = creation_info;
    memset(&info, 0, sizeof(info));
    info.port = CONTEXT_PORT_NO_LISTEN;
    info.protocols = protocols;
    info.extensions = exts;
    info.gid = -1;
    info.uid = -1;
    context = lws_create_context(&info);
}

extern "C"
JNIEXPORT jstring JNICALL
JNI_stringFromJni(JNIEnv *env, jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


extern "C"
JNIEXPORT void JNICALL JNI_serviceWebSockets
        (JNIEnv *, jobject) {
    if (context) {
        LOGV("service websockets");
        lws_service(context, 0);
    }
}

extern "C"
JNIEXPORT void JNICALL JNI_connect
        (JNIEnv *, jobject) {

//    gJvm->AttachCurrentThread(&gEnv, NULL);
    init();
    lws_client_connect_info info;
    memset(&info, 0, sizeof(lws_client_connect_info));

    info.port = 20000;
    info.address = "172.16.14.115";
    info.path = "/WebSocket";
    info.context = context;

    info.ssl_connection = 0;
    info.host = "172.16.14.115";
    info.origin = "172.16.14.115";

    info.ietf_version_or_minus_one = -1;
    info.client_exts = exts;
    info.protocol = protocols[1].name;

    wsi = lws_client_connect_via_info(&info);

    if (wsi == NULL) {
        LOGV("connected");
    } else {
        LOGV("not connected");
    }
//    gJvm->DetachCurrentThread();
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

    int num_methods = sizeof(jni_native_methods) / sizeof(JNINativeMethod);

    LOGV("num_methods %d", num_methods);
    if (registerNativeMethods(gEnv, JNI_CLASS, jni_native_methods, num_methods) != JNI_TRUE) {
        return result;
    }

    result = JNI_VERSION_1_6;
    return result;
}

extern "C"
JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved) {
    gJvm = NULL;
}
/*
 * 0xe9b3cd32
 */
