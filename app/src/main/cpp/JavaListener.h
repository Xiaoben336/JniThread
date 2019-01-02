//
// Created by zjf on 2019/1/2.
//
#include "jni.h"
#ifndef JNITHREAD_JAVALISTENER_H
#define JNITHREAD_JAVALISTENER_H


class JavaListener {

public:
    JavaVM *jvm;
    jobject jobj;//类的对象
    _JNIEnv *jenv;
    jmethodID jmid;
public:
    JavaListener(JavaVM *vm,_JNIEnv *env,jobject obj);
    ~JavaListener();

    /**
     * threadType:
     *      1-主线程
     *      0-子线程
     */
    void onError(int threadType,int code, const char *msg);
};


#endif //JNITHREAD_JAVALISTENER_H
