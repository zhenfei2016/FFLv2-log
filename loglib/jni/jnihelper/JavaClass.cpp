/*
*  This file is part of FFL project.
*
*  The MIT License (MIT)
*  Copyright (C) 2017-2018 zhufeifei All rights reserved.
*
*  JavaClass.cpp   
*  Created by zhufeifei(34008081@qq.com) on 2018/06/28 
*  https://github.com/zhenfei2016/FFL-v2.git
*  android jni帮助函数，通过java包名获取java层的类的一些信息
*
*/
#include "JavaClass.hpp"
#include <FFL.h>
#include "JniHelper.hpp"

namespace android {
	JavaClass::JavaClass(JNIEnv& env,const char* sign) :mClass(NULL){
		mClassSign = FFL_strdup(sign);
	}
	JavaClass::~JavaClass() {
		FFL_ASSERT_LOG("JavaClass %s not Free.", mClassSign);
		FFL_free((void*)mClassSign);
		mClassSign = NULL;
	}
	//
	// 初始化，反初始化，用这个类的其他函数前需要执行的
	//
	bool JavaClass::init(JNIEnv& env) {
		if (mClass) {
			return true;
		}

		if (mClassSign == NULL || mClassSign[0] == 0) {
			return false;
		}

		jclass clssz = JNIfindClass(env, mClassSign);
		if (clssz) {
			mClass = (jclass)JNInewGlobalRef(env, clssz);
		}
		JNIdeleteLocalRef(env, clssz);

		if (mClass) {
			if (!onInit(env)) {
				JNIdeleteGlobalRef(env,mClass);
				mClass = NULL;
			}
		}
		return mClass!=NULL;
	}
	void JavaClass::unInit(JNIEnv& env) {
		if (mClass) {
			onUninit(env);
			JNIdeleteGlobalRef(env, mClass);
		}
	}
	//
	//  丢出一个异常
	//
	void JavaClass::throwException(JNIEnv& env, const char* msg) {
		if (env.ThrowNew(mClass, msg) != JNI_OK){
			FFL_LOG_ERROR("%s: Failed: msg:%s", __func__, msg);
		}
	}
	//
	//查找类中函数
	//
	jmethodID JavaClass::getMethodId(JNIEnv& env, const char *name, const char *sign) {
		jmethodID methodID = env.GetMethodID(mClass, name, sign);
		if (!methodID) {
			FFL_LOG_WARNING("Failed to getMethodId: %s ,%s",name,sign);
		}
		return methodID;
	}
	//
	//  查找静态函数
	//
	jmethodID JavaClass::getStaticMethodId(JNIEnv& env, const char *name, const char *sign) {
		jmethodID methodID = env.GetStaticMethodID(mClass, name, sign);
		if (!methodID) {
			FFL_LOG_WARNING("Failed to getStaticMethodId: %s ,%s",name, sign);
		}
		return methodID;
	}
	//
	//  查找成员变量
	//
	jfieldID JavaClass::getFieldId(JNIEnv& env, const char *name, const char *sign) {
		jfieldID fieldID = env.GetFieldID(mClass, name, sign);
		if (!fieldID) {
			FFL_LOG_WARNING("Failed to getFieldId: %s ,%s",name, sign);
		}
		return fieldID;
	}
	//
	//  查找静态成员变量
	//
	jfieldID JavaClass::getStaticFieldId(JNIEnv& env, const char *name, const char *sign) {
		jfieldID fieldID = env.GetStaticFieldID(mClass, name, sign);
		if (!fieldID) {
			FFL_LOG_WARNING("Failed to getStaticFieldId: %s ,%s",name, sign);
		}
		return fieldID;
	}
	//
	//  导出一系列native层函数
	//
	bool JavaClass::exportNativeMethod(JNIEnv& env,JNINativeMethod* methodList, int count) {
		env.RegisterNatives(mClass, methodList, count);
		return true;
	}
	//
	//  查找对应签名的类
	//
	jclass JNIfindClass(JNIEnv& env, const char* sign) {
		jclass clazz = env.FindClass(sign);
		JNIclearException(env);
		return clazz;
	}
	//
	//  清空当前的异常
	//
	bool JNIclearException(JNIEnv& env) {
		if (env.ExceptionCheck()) {
			env.ExceptionDescribe();
			env.ExceptionClear();
			return true;
		}
		return false;
	}
	//
	//  创建全局引用
	//
	jobject JNInewGlobalRef(JNIEnv& env, jobject obj) {
		if (obj) {
			jobject globalObj = env.NewGlobalRef(obj);
			JNIclearException(env);
			return globalObj;
		}

		return NULL;
	}
	void JNIdeleteGlobalRef(JNIEnv& env, jobject obj) {
		if (obj) {
			env.DeleteGlobalRef( obj);
		}
	}
	//
	//  减少局部引用
	//
	void JNIdeleteLocalRef(JNIEnv& env, jobject obj) {
		if (obj) {
			env.DeleteLocalRef( obj);
		}
	}
	//
	// 获取java层数组数据指针
	//
	jbyte* JNIgetPtrFromByteArray(JNIEnv& env, jbyteArray bytearray) {
		return (jbyte*) env.GetPrimitiveArrayCritical(bytearray, 0);
	}
	//
	// 释放局部引用
	//
	void JNIreleasePtrFromByteArray(JNIEnv& env, jbyteArray bytearray,void* data) {
		env.ReleasePrimitiveArrayCritical(bytearray, data, 0);
	}
}

