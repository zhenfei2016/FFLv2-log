#include <jni.h>
#include <string>
#include "FFLogClass.hpp"
#include "jnihelper/JniHelper.hpp"

extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved){
    JNIEnv* env = NULL;
    FFLandroid::setJavaVM(vm);
    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        return -1;
    }

    JavaFFLogClass::getInstance(*env);
    return JNI_VERSION_1_4;
}

extern "C" JNIEXPORT void JNICALL JNI_OnUnload(JavaVM* vm, void* reserved) {

}
