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

SET(LOCAL_SRC_FILES 
  ./lib/FFLog.cpp;include/FFLog.h  
  ./lib/LogPacket.hpp;./lib/LogPacket.cpp
  ./lib/LogUrl.hpp;./lib/LogUrl.cpp
  
  ./lib/LogSender.hpp;./lib/LogSender.cpp
  ./lib/LogTrasport.hpp;./lib/LogTrasport.cpp 
 
 ./lib/LogTrasportFile.hpp;./lib/LogTrasportFile.cpp   
 ./lib/LogTrasportTcpClient.hpp;./lib/LogTrasportTcpClient.cpp  
 ./lib/LogTrasportHttpClient.hpp;./lib/LogTrasportHttpClient.cpp   
  )




FIND_PATH(FFLIB_INSTALL_DIR  include/FFL_lib.h e:/FFL_install/vs2015)
INCLUDE_DIRECTORIES(${FFLIB_INSTALL_DIR}/include ./include)
LINK_DIRECTORIES(${FFLIB_INSTALL_DIR}/lib)

#编译动态库
add_library( FFLogLib SHARED ${LOCAL_SRC_FILES})
TARGET_LINK_LIBRARIES(FFLogLib FFL)



ADD_EXECUTABLE(example1 examples/example1_main.cpp )
TARGET_LINK_LIBRARIES(example1 FFL FFLogLib)

ADD_EXECUTABLE(example_httpserver examples/example_httpserver.cpp )
TARGET_LINK_LIBRARIES(example_httpserver FFL FFLogLib)



