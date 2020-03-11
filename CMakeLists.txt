cmake_minimum_required(VERSION 3.15)
project(consumer_producer)

set(CMAKE_CXX_STANDARD 98)

#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
find_package(Threads)

add_executable(consumer_producer main.cpp mutex_store.h mutex_store.cpp producer.h producer.cpp
        consumer.h consumer.cpp store_user.h store_user_container.h store_user_container.cpp store.h store.cpp
        message_queue_store.cpp message_queue_store.h PlatformIndependentConcurrency/external_sources.cpp)
#target_link_libraries(consumer_producer gtest gtest_main pthread)
target_link_libraries(consumer_producer ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(consumer_producer rt)
