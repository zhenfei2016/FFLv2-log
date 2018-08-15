
#include "NativeFFLog.hpp"
#include "../logLib.h"

namespace android{

	NativeFFLog::NativeFFLog(){
       // mRealPlayer=new player::FFLPlayer();
	}
    NativeFFLog::~NativeFFLog(){
        //FFL_SafeFree(mRealPlayer);
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
//		NativeFFLog* player=new NativeFFLog();
//		JavaFFLPlayerClass::saveNativePlayer(*env,thiz,player);
//
//        jobject globalObj=JNInewGlobalRef(*env,weakthis);
//		player->mJavaFFLPlayer=new JavaFFLPlayer(globalObj,true);
//        player->mRealPlayer->setListener(new TestListener(player->mRealPlayer));

	}
	void NativeFFLog::release(JNIEnv* env, jobject thiz){

	}
	void NativeFFLog::finalize(JNIEnv* env, jobject thiz){

	}

    void NativeFFLog::setTargetUrl(JNIEnv* env, jobject thiz,jint type,jstring url){
//        const char* nativeStr=env->GetStringUTFChars(url,NULL);
//        player->setUrl(nativeStr);
//        env->ReleaseStringUTFChars(url,nativeStr);
    }
    void NativeFFLog::setLevel(JNIEnv* env, jobject thiz,jint level){

    }
    status_t NativeFFLog::startup(JNIEnv* env, jobject thiz){

		return FFL_OK;

    }
    status_t NativeFFLog::shutdown(JNIEnv* env, jobject thiz){
		return FFL_OK;
    }
    void NativeFFLog::print(JNIEnv* env, jobject thiz,jint level,jstring info){

    }

}