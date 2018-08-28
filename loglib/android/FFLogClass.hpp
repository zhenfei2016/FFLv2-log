#ifndef _JAVA_FFLOG_CLASS_HPP_
#define _JAVA_FFLOG_CLASS_HPP_

#include "jnihelper/JniHelper.hpp"
class JavaFFLogClass : public FFLandroid::JavaClass{
protected:
    JavaFFLogClass(JNIEnv &env);
public:
    static JavaFFLogClass* getInstance(JNIEnv &env){
        static JavaFFLogClass* gInstance=0;
        if(!gInstance){
            gInstance=new JavaFFLogClass(env);
            gInstance->init(env);
        }
        return  gInstance;
    }
protected:
    //
    //  获取导出的native层函数表
    //
    JNINativeMethod* getExportMethods(int32_t* count);
    //
    //  native的函数
    //
    static void setTargetUrl(JNIEnv* env, jclass thiz,jint type,jstring url);
    static void setLevel(JNIEnv* env, jclass thiz,jint level);
    static void startup(JNIEnv* env, jclass thiz);
    static void shutdown(JNIEnv* env, jclass thiz);
    static void print(JNIEnv* env, jclass thiz,jint level,jstring info);
};

#endif
