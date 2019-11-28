# from 3.3 onwards, detecting whether a string exists in a list has a new syntax using if()
cmake_minimum_required(VERSION 3.3)

# compile for bare metal ARM
set(CMAKE_SYSTEM_NAME      Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# specify core and FPU architectures
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --target=armv7a-none-eabi")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=armv7-a")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcpu=cortex-a9")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mfpu=neon-vfpv3")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mfloat-abi=hard")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffunction-sections")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fdata-sections")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fpie")

set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "ASM compile flags")
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}" CACHE STRING "C compile flags")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" CACHE STRING "CXX compile flags")

# toolchain executable prefix
set(CROSS_COMPILE "")

# set compiler
set(CMAKE_C_COMPILER clang CACHE STRING "" FORCE)
set(CMAKE_CXX_COMPILER clang++ CACHE STRING "" FORCE)

# force compile test library instead of a test executable to avoid testing for startup code, etc.
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# disable various system calls
set(
    CMAKE_EXE_LINKER_FLAGS
        "${CMAKE_EXE_LINKER_FLAGS} -nostartfiles"
    CACHE STRING "Linker flags"
)

# do not search for binaries on compile host
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# do not use system includes and libraries
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
