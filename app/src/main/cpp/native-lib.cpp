#include <jni.h>
#include "pthread.h"
#include "android/log.h"
#define LOGD(FORMAT,...) __android_log_print(ANDROID_LOG_DEBUG, "ZJF", FORMAT, ##__VA_ARGS__);

pthread_t thread;

void *normalThreadCallBack(void *data){
    LOGD("Create Normal Thread from C++");
    pthread_exit(&thread);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_zjf_jnithread_ThreadDemo_normalThread(JNIEnv *env, jobject instance) {

    // 创建线程
    pthread_create(&thread,NULL,normalThreadCallBack,NULL);

}


#include "queue"
#include "unistd.h"
pthread_t pThread;      //生产者线程
pthread_t cThread;      //消费者线程

pthread_mutex_t mutex;      //线程锁
pthread_cond_t cond;        //线程条件

std::queue<int> queue;      //一个队列

void *pThreadCallBack(void *data)
{
    while (1) {
        //解锁
        pthread_mutex_lock(&mutex);
        queue.push(1);
        LOGD("生产者生产一个产品，通知消费者消费，产品数量 === %d",queue.size());
        pthread_cond_signal(&cond);//解锁之前通知消费者我已经生产完毕
        //解锁
        pthread_mutex_unlock(&mutex);
        sleep(5);
    }

    pthread_exit(&pThread);
}


void *cThreadCallBack(void *data)
{
    while (1) {
        pthread_mutex_lock(&mutex);
        if (queue.size() > 0) {
            queue.pop();
            LOGD("消费者消费一个产品，产品数量剩余 === %d",queue.size());
        } else {
            LOGD("没有产品可以消费，一直等待...这里会解锁");
            pthread_cond_wait(&cond,&mutex);
        }
        pthread_mutex_unlock(&mutex);
        usleep(500);
    }
    pthread_exit(&cThread);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_zjf_jnithread_ThreadDemo_mutexThread(JNIEnv *env, jobject instance) {

    // TODO
    for (int i = 0; i < 10; i++) {
        queue.push(i);
    }

    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&cond,NULL);

    pthread_create(&pThread,NULL,pThreadCallBack,NULL);
    pthread_create(&cThread,NULL,cThreadCallBack,NULL);
}

#include "JavaListener.h"
JavaListener *javaListener;
JavaVM *jvm;
pthread_t childThread;

void *childCallback(void *data) {
    JavaListener *javaListener = (JavaListener *)(data);
    javaListener->onError(0,101,"C++ Call Java Jmid From Child Thread");
    pthread_exit(&childThread);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_zjf_jnithread_ThreadDemo_callbackFromC(JNIEnv *env, jobject instance) {

    // TODO
    javaListener = new JavaListener(jvm,env,env->NewGlobalRef(instance));//主线程中要用全局的
    //javaListener->onError(1,100,"C++ Call Java Jmid From Main Thread");

    pthread_create(&childThread,NULL,childCallback,javaListener);
}


/**
 * 重写JNI_OnLoad方法
 */
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void*reserved){
    JNIEnv *env;
    jvm = vm;

    if (vm->GetEnv((void **) (&env), JNI_VERSION_1_6) != JNI_OK){
        return -1;
    }
    return JNI_VERSION_1_6;
}