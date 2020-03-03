cmake_minimum_required(VERSION 3.15)
project(consumer_producer)

set(CMAKE_CXX_STANDARD 98)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
find_package(Threads)

add_executable(consumer_producer main.cpp)
target_link_libraries(consumer_producer gtest gtest_main pthread ${CMAKE_THREAD_LIBS_INIT})