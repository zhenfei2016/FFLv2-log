cmake_minimum_required(VERSION 3.4.1)

PROJECT(FFLv2-log)

#  加载公用库 FFLv2
SET(CMAKE_MODULE_PATH  ${CMAKE_SOURCE_DIR}/../FFLv2-cmakemodule/ )
INCLUDE(${CMAKE_MODULE_PATH}FFLv2lib.cmake)

INCLUDE_DIRECTORIES(${FFLV2_LIB_INCLUDE_PATH})
LINK_DIRECTORIES(${FFLV2_LIB_LIB_PATH})

SET(LOCAL_SRC_FILES
   service/main.cpp;service/logServer.cpp
)

IF(WIN32)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 ")
SET(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
ELSE()
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

#  输出的bin路径
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)
#  输出的lib路径
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)

ADD_SUBDIRECTORY(loglib)
ADD_SUBDIRECTORY(example)

IF (ANDROID )

ELSE()

ADD_EXECUTABLE(FFLogServer  ${LOCAL_SRC_FILES})
TARGET_LINK_LIBRARIES(FFLogServer FFL)

add_custom_command(TARGET FFLogServer POST_BUILD
COMMAND  ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/web/ ${PROJECT_BINARY_DIR}/../bin/${CMAKE_CFG_INTDIR}/
)

ENDIF()




