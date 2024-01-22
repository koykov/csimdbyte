cmake_minimum_required(VERSION 3.24)
project(csimdbyte C)

set(CMAKE_C_STANDARD 17)

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-O3 -Wextra -pedantic -msse4.2 -mavx2")

add_executable(csimdbyte main.c index_sse2.c index_sse4.c index_avx2.c cmp.c)
