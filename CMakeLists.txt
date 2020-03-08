cmake_minimum_required(VERSION 3.15)
project(consumer_producer)

set(CMAKE_CXX_STANDARD 98)

#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
find_package(Threads)

add_executable(consumer_producer main.cpp store.h store.cpp producer.h producer.cpp
        consumer.h consumer.cpp store_user.h store_user_container.h store_user_container.cpp)
#target_link_libraries(consumer_producer gtest gtest_main pthread)
target_link_libraries(consumer_producer ${CMAKE_THREAD_LIBS_INIT})