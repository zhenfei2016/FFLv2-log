

#ifndef _NATIVE_FFLOG_HPP_
#define _NATIVE_FFLOG_HPP_
#include <FFL.h>
#include <jni.h>
#include "JavaFFLog.hpp"

namespace android {
	class NativeFFLog {
	public:
		NativeFFLog();
		~NativeFFLog();
		//
		//  获取导出的native层函数表
		//
		static JNINativeMethod* getExportMethods(int32_t* count);
	public:
		//
		//  native的函数
		//
		static void setup(JNIEnv* env, jobject thiz,jobject weakthis);
		static void release(JNIEnv* env, jobject thiz);
		static void finalize(JNIEnv* env, jobject thiz);

		static void setTargetUrl(JNIEnv* env, jclass thiz,jint type,jstring url);
		static void setLevel(JNIEnv* env, jclass thiz,jint level);
		static status_t startup(JNIEnv* env, jobject thiz);
		static status_t shutdown(JNIEnv* env, jobject thiz);
		static void print(JNIEnv* env, jclass thiz,jint level,jstring info);
	};
}
#endif