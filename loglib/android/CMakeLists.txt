cmake_minimum_required(VERSION 3.4.1)

PROJECT(FFLv2-loglib-jni)

#隐藏所有的默认符号
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -fvisibility=hidden")
SET(CMAKE_CXX_FLAGS "-std=c++11 -fvisibility=hidden ${CMAKE_CXX_FLAGS}")

find_library(log-lib  log )
add_library( FFLogLib_jni SHARED 
			JNImain.cpp
			FFLogClass.hpp;FFLogClass.cpp
			jnihelper/JniHelper.hpp;jnihelper/JniHelper.cpp;
			jnihelper/JavaClass.hpp;jnihelper/JavaClass.cpp;
			jnihelper/JavaObject.hpp;jnihelper/JavaObject.cpp;
			)
TARGET_LINK_LIBRARIES(FFLogLib_jni FFLogLib android ${log-lib})





