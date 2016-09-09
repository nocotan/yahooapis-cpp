cmake_minimum_required(VERSION 2.8)
project(Yahooapis-cpp)
set(Yahooapis-cpp_VERSION_MAJOR 1)
set(Yahooapis-cpp_VERSION_MINOR 0)

set(CMAKE_VERBOSE_MAKEFILE 1)
set(CMAKE_CXX_FLAGS "-std=c++14")

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(Main
    main.cpp
    src/yapis_cpp.cpp
    src/yapis_core.cpp
    src/tinyxml2.cpp)

target_link_libraries(Main PRIVATE "-lcurl")
