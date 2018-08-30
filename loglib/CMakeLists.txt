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

SET(LOCAL_SRC_FILES ./source/FFLv2Log.cpp;FFLv2Log.h)
AUX_SOURCE_DIRECTORY(./source/logsender/ DIR_SRCS)
SET(LOCAL_SRC_FILES ${DIR_SRCS} ${LOCAL_SRC_FILES})


#编译动态库
add_library( FFLogLib SHARED ${LOCAL_SRC_FILES})
TARGET_LINK_LIBRARIES(FFLogLib FFL)

#编译静态库
#add_library( FFLogLib_static STATIC ${LOCAL_SRC_FILES})
#TARGET_LINK_LIBRARIES(FFLogLib FFL)

#添加android  jni支持
IF(${BUILD_FFLOG_ANDROIDJNI} MATCHES "ON" )
add_subdirectory(android_jni)
ENDIF()





