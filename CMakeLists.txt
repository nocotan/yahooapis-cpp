cmake_minimum_required(VERSION 2.8)
set(CMAKE_VERBOSE_MAKEFILE 1)
set(CMAKE_CXX_FLAGS "-std=c++14")
include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(Main
    main.cpp
    src/yapis_cpp.cpp
    src/yapis_core.cpp)
