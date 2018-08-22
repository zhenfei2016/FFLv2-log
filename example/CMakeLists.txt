cmake_minimum_required(VERSION 3.4.1)

PROJECT(FFLv2-log)

IF (ANDROID)

ELSE()
ADD_EXECUTABLE(FFLogLibTest logLibTest.cpp;main.cpp)
TARGET_LINK_LIBRARIES(FFLogLibTest FFLogLib FFL)

INCLUDE_DIRECTORIES()
LINK_DIRECTORIES()

ADD_EXECUTABLE(FFLogLibSimpleTest main-simple.cpp)
TARGET_LINK_LIBRARIES(FFLogLibSimpleTest FFLogLib)



ENDIF()




