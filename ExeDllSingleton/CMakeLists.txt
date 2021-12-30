cmake_minimum_required(VERSION 3.0.2)
project(ExeSingleton)

if(WIN32)
set(CMAKE_CXX_STANDARD 11)
else()
add_compile_options(-std=c++11)
endif()

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../build/debug)
else()
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../build/bin)
endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

link_libraries(
    ${LIBRARY_OUTPUT_PATH}
)


add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)
if(UNIX)
target_link_libraries(${PROJECT_NAME}
	dl
)
endif()