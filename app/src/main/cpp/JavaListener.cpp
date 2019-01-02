//
// Created by zjf on 2019/1/2.
//

#include "JavaListener.h"

JavaListener::JavaListener(JavaVM *vm, _JNIEnv *env, jobject obj) {
    jvm = vm;
    jobj = obj;
    jenv = env;
    jclass clazz = env->GetObjectClass(jobj);
    if (!clazz) {
        return ;
    }
    jmid =  env->GetMethodID(clazz,"onError","(ILjava/lang/String;)V");


}

void JavaListener::onError(int threadType, int code, const char *msg) {
    if (threadType == 1){//
        jstring jmsg = jenv->NewStringUTF(msg);
        jenv->CallVoidMethod(jobj,jmid,code,jmsg);
        jenv->DeleteLocalRef(jmsg);
    } else {
        JNIEnv *env;
        jvm->AttachCurrentThread(&env,0);//拿到env

        jstring jmsg = env->NewStringUTF(msg);
        env->CallVoidMethod(jobj,jmid,code,jmsg);
        env->DeleteLocalRef(jmsg);

        jvm->DetachCurrentThread();
    }
}
