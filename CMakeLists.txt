cmake_minimum_required(VERSION 2.6)
project(libchili)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
include_directories(src)
add_definitions(-nostdlib)

file(GLOB_RECURSE LIB43_SOURCE src/*.c)

set(CMAKE_C_FLAGS "-std=c99 -Os -ffreestanding -fno-stack-protector -nostdlib")
add_executable(test example/test.c)

if (APPLE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static")
    set(CMAKE_SKIP_RPATH TRUE)
    set(PLATFORM_ASM_DIR "osx")
else()
    set(PLATFORM_ASM_DIR "linux")  
endif(APPLE)

enable_language(ASM-ATT)
if (CMAKE_SYSTEM_PROCESSOR MATCHES "^i[36]86$")
    file(GLOB_RECURSE ARCH_SOURCE arch/${PLATFORM_ASM_DIR}/i386/*.s)
elseif (CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|amd64)$")
    file(GLOB_RECURSE ARCH_SOURCE arch/${PLATFORM_ASM_DIR}/x86_64/*.s)
else()
    message(FATAL_ERROR "Unsupported processor: " CMAKE_SYSTEM_PROCESSOR)
endif()

add_library(43 STATIC ${LIB43_SOURCE} ${ARCH_SOURCE})
target_link_libraries(test 43)
