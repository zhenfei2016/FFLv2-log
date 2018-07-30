cmake_minimum_required(VERSION 3.4.1)

PROJECT(FFLv2-log)

INCLUDE_DIRECTORIES(../install/FFLv2-lib/include)
LINK_DIRECTORIES(../install/FFLv2-lib/libs)

SET(LOCAL_SRC_FILES
   service/main.cpp;service/logServer.cpp
)

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


#  Êä³öÂ·¾¶ bin
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
ADD_EXECUTABLE(FFLv2-log  ${LOCAL_SRC_FILES})
TARGET_LINK_LIBRARIES(FFLv2-log FFL)

add_custom_command(TARGET FFLv2-log POST_BUILD  
  COMMAND  ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/web/ ${PROJECT_BINARY_DIR}/bin/Debug/
   )

