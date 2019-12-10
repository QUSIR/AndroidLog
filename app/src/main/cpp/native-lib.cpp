#include <jni.h>
#include <string>
#include "Logger.h"
extern "C"
JNIEXPORT void JNICALL
Java_com_demo_androidlog_SaveLog_savelog(JNIEnv *env, jclass clazz, jbyteArray data, jint len) {
    // TODO: implement savelog()
    char *savedata = (char*)env->GetByteArrayElements(data, NULL);
    char tmp_data[1024]={'\0'};
    memcpy(tmp_data,savedata,len);
    log_debug("%s",tmp_data);
    env->ReleaseByteArrayElements(data,(jbyte*)savedata,0);
    log_debug("jni Save Log");
}