cmake_minimum_required(VERSION 4.3)
project(Lock_Free_SPSC_Ring_Buffer)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(include)
include_directories(src)

add_executable(Lock_Free_SPSC_Ring_Buffer
        include/spsc_queue.hpp
        src/bench.cpp
        src/main.cpp)
