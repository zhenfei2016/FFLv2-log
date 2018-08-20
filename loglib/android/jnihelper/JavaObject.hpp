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
#ifndef _JNIJAVA_OBJECT_HPP_
#define _JNIJAVA_OBJECT_HPP_

#include <jni.h>


namespace FFLandroid {
	//
//  获取当前线程的env
//
	extern void getJNIEnv(JNIEnv **env);
	class JavaClass;


	template<typename T>
	class JavaObject {
	public:
		//
		//  javaObj:java层对象，golbal对象
		//   autoDel: 是否当这个javaObj对象删除的时候，需要自动删除java层对象
		//
		JavaObject(T& javaClass,jobject javaObj,bool autoDel):
				mJavaClass(javaClass),
				mJavaObj(javaObj),
		        mAutoDel(autoDel) {
		}
		~JavaObject(){
			if(mAutoDel&&mJavaObj!=NULL){
				JNIEnv* env=0;
				getJNIEnv(&env);
				if(env) {
					JNIdeleteGlobalRef(*env,mJavaObj);
				}
			}
		}

		//
		//  java层对象的对应的class
		//
		T& getClass() const {
			return mJavaClass;
		}
        //
		//  java层的对象
		//
		jobject getJavaObject() const{
			return  mJavaObj;
		}

	protected:
		T& mJavaClass;
		jobject mJavaObj;
		bool mAutoDel;
	};
}
#endif
