cmake_minimum_required(VERSION 3.24)
project(csimdbyte C)

set(CMAKE_C_STANDARD 17)

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-msse4.2")

add_executable(csimdbyte main.c index_sse2.c index_sse4.c)
