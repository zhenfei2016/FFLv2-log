
#include "NativeFFLog.hpp"
#include "../logLib.h"

namespace android{
	NativeFFLog::NativeFFLog(){
	}
    NativeFFLog::~NativeFFLog(){
    }
	//
	//  获取导出的native层函数表
	//
	JNINativeMethod* NativeFFLog::getExportMethods(int32_t* count){
		//
		//  native层的函数导出到java层
		//
		static JNINativeMethod nativeMethodTables[] = {
				{ "native_setup","(Ljava/lang/Object;)V",(void *)NativeFFLog::setup },
				//{ "native_release","()V",(void *)NativeFFLog::release },
				//{ "native_finalize","()V",(void *)NativeFFLog::finalize },
                { "native_setTargetUrl","(ILjava/lang/String;)V",(void *)NativeFFLog::setTargetUrl },
                { "native_setLevel","(I)V",(void *)NativeFFLog::setLevel },
                { "native_startup","()I",(void *)NativeFFLog::startup },
                { "native_shutdown","()I",(void *)NativeFFLog::shutdown },
                { "native_print","(ILjava/lang/String;)V",(void *)NativeFFLog::print },
		};

		if(count){
			*count=FFL_ARRAY_ELEMS(nativeMethodTables);
		}
		return nativeMethodTables;
	}
	//
	//  native的函数
	//
	void NativeFFLog::setup(JNIEnv* env, jobject thiz,jobject weakthis){
	}
	void NativeFFLog::release(JNIEnv* env, jobject thiz){

	}
	void NativeFFLog::finalize(JNIEnv* env, jobject thiz){

	}

    void NativeFFLog::setTargetUrl(JNIEnv* env, jclass thiz,jint type,jstring url){
		const char* nativeStr=env->GetStringUTFChars(url,NULL);
		if(nativeStr) {
			FFLogSetUrl(type, nativeStr);
		}
		env->ReleaseStringUTFChars(url,nativeStr);
    }
    void NativeFFLog::setLevel(JNIEnv* env, jclass thiz,jint level){
		FFLogSetLevel(level);
    }
    status_t NativeFFLog::startup(JNIEnv* env, jobject thiz){
		FFLogCreateInstance();
		return FFL_OK;

    }
    status_t NativeFFLog::shutdown(JNIEnv* env, jobject thiz){
		FFLogDestroyInstance(0);
		return FFL_OK;
    }
    void NativeFFLog::print(JNIEnv* env, jclass thiz,jint level,jstring info){
		const char* nativeStr=env->GetStringUTFChars(info,NULL);
		if(nativeStr) {
			FFLogPrint(level,"[java] %s", nativeStr);
		}
		env->ReleaseStringUTFChars(info,nativeStr);
    }
}