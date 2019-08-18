# from 3.3 onwards, detecting whether a string exists in a list has a new syntax using if()
cmake_minimum_required(VERSION 3.3)

# compile for bare metal ARM
set(CMAKE_SYSTEM_NAME      Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# specify core and FPU architectures
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcpu=cortex-a9")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mfloat-abi=hard")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mfpu=vfpv3")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=armv7-a")

set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "")
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -nostartfiles" CACHE STRING "CFLAGS")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mcpu=cortex-a9")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfloat-abi=hard")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfpu=vfpv3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=armv7-a")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nostartfiles")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" CACHE STRING "CXXFLAGS")

# toolchain executable prefix
set(CROSS_COMPILE arm-none-eabi-)

# set compilers, linker, and archiver
set(CMAKE_ASM_COMPILER   "${TC_PATH}${CROSS_COMPILE}as${EXTENSION}"         CACHE PATH "" FORCE)
set(CMAKE_C_COMPILER     "${TC_PATH}${CROSS_COMPILE}gcc${EXTENSION}"        CACHE PATH "" FORCE)
set(CMAKE_C_PREPROCESSOR "${TC_PATH}${CROSS_COMPILE}cpp${EXTENSION}"        CACHE PATH "" FORCE)
set(CMAKE_CXX_COMPILER   "${TC_PATH}${CROSS_COMPILE}g++${EXTENSION}"        CACHE PATH "" FORCE)
set(CMAKE_LINKER         "${TC_PATH}${CROSS_COMPILE}ld${EXTENSION}"         CACHE PATH "" FORCE)
set(CMAKE_AR             "${TC_PATH}${CROSS_COMPILE}gcc-ar${EXTENSION}"     CACHE FILEPATH "" FORCE)
set(CMAKE_RANLIB         "${TC_PATH}${CROSS_COMPILE}gcc-ranlib${EXTENSION}" CACHE FILEPATH "" FORCE)
set(CMAKE_NM             "${TC_PATH}${CROSS_COMPILE}gcc-nm${EXTENSION}"     CACHE FILEPATH "" FORCE)
set(CMAKE_OBJCOPY        "${TC_PATH}${CROSS_COMPILE}objcopy${EXTENSION}"    CACHE FILEPATH "" FORCE)

# force compile test library instead of a test executable to avoid testing for startup code, etc.
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# disable various system calls
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostartfiles")

# do not search for binaries on compile host
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# do not use system includes and libraries
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
