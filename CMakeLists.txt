cmake_minimum_required(VERSION 2.6)
project(lib43)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
include_directories(src)

enable_language(ASM-ATT)
add_definitions(-nostdlib)
set(CMAKE_C_FLAGS "-std=c99 -Os -ffreestanding -fno-stack-protector -nostdlib")

# OS test
if (APPLE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static")
    set(CMAKE_SKIP_RPATH TRUE)
    set(OS_DIR "osx")
elseif (CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(OS_DIR "linux")
else()
    message(FATAL_ERROR "Unsupported OS: ${CMAKE_SYSTEM_NAME}")
endif()

# CPU test
if (CMAKE_SYSTEM_PROCESSOR MATCHES "^i[36]86$")
    set(ARCH_DIR "i386")
elseif (CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|amd64)$")
    set(ARCH_DIR "x86_64")
else()
    message(FATAL_ERROR "Unsupported processor: ${CMAKE_SYSTEM_PROCESSOR}")
endif()

file(GLOB_RECURSE LIB43_SOURCE src/*.c)
file(GLOB_RECURSE LIB43_PLATFORM_SOURCE arch/${ARCH_DIR}/${OS_DIR}/*.s arch/${ARCH_DIR}/${OS_DIR}/*.c)
file(GLOB LIB43_ARCH_SOURCE arch/${ARCH_DIR}/*.s arch/${ARCH_DIR}/*.c)
add_library(43 STATIC ${LIB43_SOURCE} ${LIB43_PLATFORM_SOURCE} ${LIB43_ARCH_SOURCE})

add_executable(test example/test.c)
target_link_libraries(test 43)
