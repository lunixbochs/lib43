cmake_minimum_required(VERSION 2.6)
project(libchili)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
include_directories(src)
add_definitions(-nostdlib)

enable_language(ASM-ATT)

file(GLOB_RECURSE CHILI_SOURCE src/*.c src/*.s)
add_library(43 STATIC ${CHILI_SOURCE})

set(CMAKE_C_FLAGS "-std=c99 -Os -ffreestanding -nostdlib")
add_executable(test example/test.c)
target_link_libraries(test 43)
