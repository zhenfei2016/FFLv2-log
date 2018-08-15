
#ifndef _JNI_HELPER_HPP_
#define _JNI_HELPER_HPP_

#include <jni.h>
#include "JavaClass.hpp"
#include "JavaObject.hpp"


namespace android {
//
//  获取，设置虚拟机
//
	extern JavaVM *getJavaVM();

	extern void setJavaVM(JavaVM *jvm);

//
//  获取当前线程的env
//
	extern void getJNIEnv(JNIEnv **env);
}

#endif
