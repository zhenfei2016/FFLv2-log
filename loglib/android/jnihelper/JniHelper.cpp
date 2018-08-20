#include "JniHelper.hpp"

namespace FFLandroid {
	static JavaVM* gJVM;
    //
    //  获取，设置虚拟机
    //
	JavaVM *getJavaVM(){
		return  gJVM;
	}

	void setJavaVM(JavaVM *jvm){
		gJVM=jvm;
	}
    //
    //  获取当前线程的env
    //
	void getJNIEnv(JNIEnv **env){
        getJavaVM()->GetEnv((void**)env,JNI_VERSION_1_4);
	}

}