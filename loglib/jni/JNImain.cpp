
#include <jni.h>
#include <string>
#include "JavaFFLog.hpp"
#include "jnihelper/JniHelper.hpp"

extern "C" {
#include <android/log.h>
}

extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv* env = NULL;
    android::setJavaVM(vm);
    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        return -1;
    }


    android::importJavaFFLogClass(*env);

    return JNI_VERSION_1_4;
}

extern "C" JNIEXPORT void JNICALL JNI_OnUnload(JavaVM* vm, void* reserved) {

}
