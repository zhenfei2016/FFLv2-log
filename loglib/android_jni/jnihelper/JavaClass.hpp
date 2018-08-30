/*
*  This file is part of FFL project.
*
*  The MIT License (MIT)
*  Copyright (C) 2017-2018 zhufeifei All rights reserved.
*
*  JavaClass.hpp
*  Created by zhufeifei(34008081@qq.com) on 2018/06/28
*  https://github.com/zhenfei2016/FFL-v2.git
*  android jni帮助函数，通过java包名获取java层的类的一些信息
*
*/
#ifndef _JNIJAVA_CLASS_HPP_
#define _JNIJAVA_CLASS_HPP_
#include <jni.h>

namespace FFLandroid {

	enum JNIJavaMethodFlag{
		//
		//  实例的函数
		//
		JNI_INSTANCE_METHDO=0,
		//
		//  静态函数
		//
		JNI_STATIC_METHDO=1,

	};
	//
	//  java层导入函数的定义
	//
	class JNIJavaMethod{
	public:
		JNIJavaMethod(){
			mMethodName=0;
			mMethosSign=0;
			mFlag=JNI_INSTANCE_METHDO;
		}

		const char* mMethodName;
		const char* mMethosSign;
		JNIJavaMethodFlag mFlag;

		jmethodID mMethodId;
	} ;

	class JavaClass {
	public:
		JavaClass(JNIEnv& env,const char* sign);
		virtual ~JavaClass();
	public:
		//
		// 初始化，反初始化，用这个类的其他函数前需要执行的
		//
		bool init(JNIEnv& env);
		void unInit(JNIEnv& env);
	protected:
		//
		//  进行初始化，反初始化具体逻辑
		//
		virtual bool onInit(JNIEnv& env);
		virtual void onUninit(JNIEnv& env);

		//
		//  class导出的native函数列表
		//
		virtual JNINativeMethod* getExportMethods(int32_t* count)=0;
		//
		//  导入的java层函数
		//
		virtual JNIJavaMethod* getImportMethods(int32_t* count);
	public:
		jclass getJClass() const {
			return  mClass;
		}
		//
		//  调用java层函数
		//
        #define callJavaStaticMethod(env,...) env.CallStaticVoidMethod(env,mClass,__VA_ARGS__)
        #define callJavaMethod(env,obj,...) env.CallVoidMethod(env,mClass,obj, __VA_ARGS__)	
		//
		//  导出一系列native层函数
		//
		bool exportNativeMethod(JNIEnv& env,JNINativeMethod* methodList, int count);
		//
		//  导入java层函数
		//
		bool importJavaMethod(JNIEnv& env);
	public:
		//
		//  丢出一个异常
		//
		void throwException(JNIEnv& env, const char* msg);
		//
		//查找类中函数
		//
		jmethodID getMethodId(JNIEnv& env,const char *name, const char *sign);
		//
		//  查找静态函数
		//
		jmethodID getStaticMethodId(JNIEnv& env, const char *name, const char *sign);
		//
		//  查找成员变量
		//
		jfieldID getFieldId(JNIEnv& env, const char *name, const char *sign);
		//
		//  查找静态成员变量
		//
		jfieldID getStaticFieldId(JNIEnv& env, const char *name, const char *sign);
	private:		
		jclass mClass;
		const char* mClassSign;
	};
	//
	//  查找对应签名的类
	//
	jclass JNIfindClass(JNIEnv& env, const char* sign);
	//
	//  清空当前的异常,返回是否存在异常的
	//
	bool JNIclearException(JNIEnv& env);
	//
	//  创建全局引用
	//
	jobject JNInewGlobalRef(JNIEnv& env, jobject obj);
	void JNIdeleteGlobalRef(JNIEnv& env, jobject obj);
	//
	//  减少局部引用
	//
	void JNIdeleteLocalRef(JNIEnv& env, jobject obj);
	//
	// 获取java层数组数据指针
	//
	jbyte* JNIgetPtrFromByteArray(JNIEnv& env, jbyteArray bytearray);
	//
	// 释放局部引用
	//
	void JNIreleasePtrFromByteArray(JNIEnv& env, jbyteArray bytearray,void* data);
}
#endif
