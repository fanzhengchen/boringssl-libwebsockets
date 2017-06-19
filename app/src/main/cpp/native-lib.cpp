#include <jni.h>
#include <string>
#include <android/log.h>
#include <openssl/ssl.h>
#include "libwebsockets.h"
#include "openssl/ssl.h"
#include "openssl/ecdh.h"

#define BUFFER_SIZE 4096

static lws_client_connect_info connect_info;
static lws_context_creation_info creation_info;
static lws_context *context;

struct per_session_data { ;// no data
};

static int
callback(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len) {
    __android_log_print(ANDROID_LOG_DEBUG, "www", "%s", "call back");
    return 0;
}

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

extern "C"
JNIEXPORT jstring JNICALL
Java_com_fzc_jni_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    connect_info.host = "127.0.0.1";
    connect_info.address = "127.0.0.1";
    connect_info.ssl_connection = 0;

    creation_info.port = CONTEXT_PORT_NO_LISTEN;
    creation_info.protocols = protocols;

    creation_info.gid = -1;
    creation_info.uid = -1;

    context = lws_create_context(&creation_info);
    //context = lws_client_connect_via_info()

//    X509_VERIFY_PARAM_set1_host()
//

    lws_client_connect_via_info(&connect_info);

    __android_log_print(ANDROID_LOG_ERROR, "jni on unload", "%s", "exit");

    return env->NewStringUTF(hello.c_str());
}


