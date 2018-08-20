
#ifndef _JAVA_FFLOG_HPP_
#define _JAVA_FFLOG_HPP_

#include "jnihelper/JavaClass.hpp"
#include "jnihelper/JavaObject.hpp"

namespace android{
    class JavaFFLogClass;
    class JavaFFLPlayer;
    class JavaFFLogClass;
    //
    //  引用进来java层的FFLPlayer
    //
    JavaFFLogClass* importJavaFFLogClass( JNIEnv& env);
    JavaFFLogClass* getJJavaFFLogClass();

      //
    //  FFLplayer的class
    //
    class JavaFFLogClass : public  JavaClass{
    public:
        JavaFFLogClass(JNIEnv &env);
    protected:
        //
        //  进行初始化，反初始化具体逻辑
        //
        virtual bool onInit(JNIEnv& env);
        virtual void onUninit(JNIEnv& env);

    public:
        friend class JavaFFLPlayer;
        //
        //  java对象中，保存的native层变量
        //
        jfieldID mField_mNativePlayer;
    };
//    //
//    //  一个java层的FFLPlayer
//    //
//    class JavaFFLog : public JavaObject<JavaFFLogClass>{
//    public:
//        //
//        //  javaObj:java层对象，golbal对象
//        //   autoDel: 是否当这个JavaFFLPlayer对象删除的时候，需要自动删除java层对象
//        //
//        JavaFFLog(jobject javaObj,bool autoDel);
//        ~JavaFFLog();
//    public:
//        inline void setJniEnv(JNIEnv* env){
//            mJNIEnv=env;
//        }
//
//        void postMessage();
//    private:
//        JNIEnv* mJNIEnv;
//    };
}
#endif
