cmake_minimum_required(VERSION 3.4.1)

PROJECT(FFLv2-loglib)

IF(WIN32)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 ")
SET(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
ELSE()
#隐藏所有的默认符号
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -fvisibility=hidden")
SET(CMAKE_CXX_FLAGS "-std=c++11 -fvisibility=hidden ${CMAKE_CXX_FLAGS}")
ENDIF()


if (MSVC)
    add_definitions("/wd4819")
    set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
        )
    foreach(CompilerFlag ${CompilerFlags})
        string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
    endforeach()
endif(MSVC)


#编译动态库
add_library( FFLogLib SHARED logLib.cpp;logLib.h)
TARGET_LINK_LIBRARIES(FFLogLib FFL)

#编译静态库
add_library( FFLogLib_static STATIC logLib.cpp;logLib.h)
TARGET_LINK_LIBRARIES(FFLogLib FFL)

#添加android  jni支持
IF (ANDROID)
find_library(log-lib  log )
add_library( FFLogLib_android SHARED 
			android/JNImain.cpp
			android/FFLogClass.hpp;android/FFLogClass.cpp
			android/jnihelper/JniHelper.hpp;android/jnihelper/JniHelper.cpp;
			android/jnihelper/JavaClass.hpp;android/jnihelper/JavaClass.cpp;
			android/jnihelper/JavaObject.hpp;android/jnihelper/JavaObject.cpp;
			)
TARGET_LINK_LIBRARIES(FFLogLib_android FFLogLib android ${log-lib})
ENDIF()





