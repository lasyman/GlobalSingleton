cmake_minimum_required(VERSION 3.0.2)
project(sgtmgr)

if(WIN32)
set(CMAKE_CXX_STANDARD 11)
add_definitions(-D_WINDLL)
else()
add_compile_options(-std=c++11)
endif()

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../build/debug)
else()
    set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../build/bin)
endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(${PROJECT_NAME} SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/SingletonManager.cpp
)