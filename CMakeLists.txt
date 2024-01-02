cmake_minimum_required(VERSION 3.24)
project(csimdbyte C)

set(CMAKE_C_STANDARD 17)

add_executable(csimdbyte main.c index_sse2.c)
