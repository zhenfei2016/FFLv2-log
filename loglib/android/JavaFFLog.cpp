#include "JavaFFLog.hpp"
#include "NativeFFLog.hpp"

namespace android{
    static  JavaFFLogClass* gJavaFFLogClass=NULL;

    JavaFFLogClass* importJavaFFLogClass( JNIEnv& env){
        if(!gJavaFFLogClass) {
            gJavaFFLogClass = new JavaFFLogClass(env);
            gJavaFFLogClass->init(env);
        }
        return gJavaFFLogClass;
    }
    JavaFFLogClass* getJJavaFFLogClass(){
        return  gJavaFFLogClass;
    }

    JavaFFLogClass::JavaFFLogClass(JNIEnv &env):
            JavaClass(env,"ffl/log/FFLog"){
    }
    //
    //  进行初始化，反初始化具体逻辑
    //
    bool JavaFFLogClass::onInit(JNIEnv& env){
        int methodNum=0;
        JNINativeMethod* methodList=NativeFFLog::getExportMethods(&methodNum);
        exportNativeMethod(env,methodList,methodNum);
        return  true;
    }
    void JavaFFLogClass::onUninit(JNIEnv& env){
    }

}