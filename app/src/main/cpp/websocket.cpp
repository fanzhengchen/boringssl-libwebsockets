//
// Created by mark on 17-6-19.
//

#include <jni.h>
#include <android/log.h>
#include "register.h"
#include "websocket.h"

#define JNIREG_CLASS "com/example/WebSocket"

#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, "LwsService", ##__VA_ARGS__)

JavaVM *gJvm = NULL;
JNIEnv *gEnv = NULL;

////////////////////////////////////////////////////
// JNI functions to export:                       //
////////////////////////////////////////////////////

static jclass gLwsServiceCls;
static jobject gLwsServiceObj;
static jmethodID sendMessageId;

static const int MSG_DUMB_INCREMENT_PROTOCOL_COUNTER = 1;
static const int MSG_LWS_CALLBACK_CLIENT_CONNECTION_ERROR = 2;
static const int MSG_LWS_CALLBACK_CLIENT_ESTABLISHED = 3;

static struct lws_context *context = NULL;
static struct lws_context_creation_info info;
static struct lws *wsi = NULL;

static int port = 0;
static int use_ssl = 0;
static int use_ssl_client = 0;
static char address[8192];
static char cgi_path[8192];

static JNINativeMethod methods[] = {
        {"setAddress", "(Ljava/lang/String;ILjava/lang/String;)V", (void *) jni_setAddress},
        {"setUrl",     "(Ljava/lang/String;)V",                    (void *) jni_setUrl},
        {"connect",    "()V",                                      (void *) jni_connect}
};

enum websocket_protocols {
    PROTOCOL_DUMB_INCREMENT = 0,
    PROTOCOL_COUNT
};

struct per_session_data { ;// no data
};

static struct lws_protocols protocols[] = {
        {
                "dumb-increment-protocol",
                callback,
                sizeof(struct per_session_data),
                BUFFER_SIZE,
        },
        {NULL, NULL, 0, 0} // end of list
};

static const struct lws_extension exts[] = {
        {
                "deflate-frame",
                lws_extension_callback_pm_deflate,
                "deflate_frame"
        },
        {NULL, NULL, NULL}
};


static int
callback(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len) {

}
/*
 * Class:     com_example_WebSocket
 * Method:    setAddress
 * Signature: (Ljava/lang/String;ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL jni_setAddress
        (JNIEnv *env, jobject obj, jstring serverAddress, jint serverPort, jstring path) {

    gJvm->AttachCurrentThread(&gEnv, NULL);


    jclass cls = env->GetObjectClass(obj);
    gLwsServiceCls = (jclass) env->NewGlobalRef(cls);
    gLwsServiceObj = env->NewGlobalRef(obj);
    memset(&info, 0, sizeof(info));

    info.port = CONTEXT_PORT_NO_LISTEN;
    info.protocols = protocols;
    info.gid = -1;
    info.uid = -1;

    context = lws_create_context(&info);

    address[0] = 0;
    port = serverPort;
    use_ssl = 0;
    use_ssl_client = 0;
    snprintf(address, sizeof(address), "%s", env->GetStringUTFChars(serverAddress, 0));

    cgi_path[0] = 0;
    snprintf(cgi_path, sizeof(cgi_path), "%s", env->GetStringUTFChars(path, 0));
}

/*
 * Class:     com_example_WebSocket
 * Method:    setUrl
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL jni_setUrl(JNIEnv *, jobject, jstring) {

};

/*
 * Class:     com_example_WebSocket
 * Method:    connect
 * Signature: ()V
 */
JNIEXPORT void JNICALL jni_connect
        (JNIEnv *, jobject) {
    struct lws_client_connect_info info_ws;
    memset(&info_ws, 0, sizeof(info_ws));

    info_ws.port = port;
    info_ws.address = address;
//    info_ws.path = "/";
    info_ws.path = cgi_path;
    info_ws.context = context;
    info_ws.ssl_connection = use_ssl;
    info_ws.host = address;
    info_ws.origin = address;
    info_ws.ietf_version_or_minus_one = -1;
    info_ws.client_exts = exts;
    info_ws.protocol = protocols[PROTOCOL_DUMB_INCREMENT].name;

    // connect
    wsi = lws_client_connect_via_info(&info_ws);

//    LOGV("%d", wsi);
    if (wsi == NULL) {
    }
};

extern "C"
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    jint result = -1;
    gJvm = vm;
    int num_methods = sizeof(methods) / sizeof(methods[0]);
    LOGV("jni on load");
    if (vm->GetEnv((void **) &gEnv, JNI_VERSION_1_6) != JNI_OK) {
        return result;
    };
    if (vm->AttachCurrentThread(&gEnv, NULL) < 0) {
        return result;
    };
    if (registerNativeMethods(gEnv, JNIREG_CLASS, methods, num_methods) != JNI_TRUE) {
        return result;
    }

    result = JNI_VERSION_1_6;
    return result;
}

extern "C"
JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved) {
    gJvm = NULL;
}

