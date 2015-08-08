cmake_minimum_required(VERSION 3.2)
project(recipes)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES
    main.cpp
    utils/BoundedQueue.hpp
    utils/BlockingQueue.hpp
    utils/ThreadPool.hpp)

add_executable(recipes ${SOURCE_FILES})