#include "FFLogClass.hpp"
#include <FFL.h>
#include "../logLib.h"

JavaFFLogClass::JavaFFLogClass(JNIEnv &env):FFLandroid::JavaClass(env,"ffl/log/FFLog"){
}
//
//  进行初始化，反初始化具体逻辑
//
bool JavaFFLogClass::onInit(JNIEnv& env){
    int methodNum=0;
    JNINativeMethod* methodList=getExportMethods(&methodNum);
    exportNativeMethod(env,methodList,methodNum);
    return  true;
}
void JavaFFLogClass::onUninit(JNIEnv& env){
}
//
//  获取导出的native层函数表
//
JNINativeMethod* JavaFFLogClass::getExportMethods(int32_t* count){
    static JNINativeMethod nativeMethodTables[] = {
            { "native_setTargetUrl","(ILjava/lang/String;)V",(void *)JavaFFLogClass::setTargetUrl },
            { "native_setLevel","(I)V",(void *)JavaFFLogClass::setLevel },
            { "native_startup","()V",(void *)JavaFFLogClass::startup },
            { "native_shutdown","()V",(void *)JavaFFLogClass::shutdown },
            { "native_print","(ILjava/lang/String;)V",(void *)JavaFFLogClass::print },
    };

    if(count){
        *count=FFL_ARRAY_ELEMS(nativeMethodTables);
    }
    return nativeMethodTables;
}
//
//  native的函数
//
void JavaFFLogClass::setTargetUrl(JNIEnv* env, jclass thiz,jint type,jstring url){
    const char* nativeStr=env->GetStringUTFChars(url,NULL);
    if(nativeStr) {
        FFLogSetUrl(type, nativeStr);
    }
    env->ReleaseStringUTFChars(url,nativeStr);
}
void JavaFFLogClass::setLevel(JNIEnv* env, jclass thiz,jint level){
    FFLogSetLevel(level);
}
void JavaFFLogClass::startup(JNIEnv* env, jclass thiz){
    FFLogCreateInstance();
}
void JavaFFLogClass::shutdown(JNIEnv* env, jclass thiz){
    FFLogDestroyInstance(0);
}
void JavaFFLogClass::print(JNIEnv* env, jclass thiz,jint level,jstring info){
    const char* nativeStr=env->GetStringUTFChars(info,NULL);
    if(nativeStr) {
        FFLogPrint(level,"[java] %s", nativeStr);
    }
    env->ReleaseStringUTFChars(info,nativeStr);
}
