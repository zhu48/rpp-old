# from 3.3 onwards, detecting whether a string exists in a list has a new syntax using if()
cmake_minimum_required(VERSION 3.3)

#########################
# Configuration Options #
#########################

set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)

set(RPP_TARGET_PLATFORM "NONE"    CACHE STRING "Target platform." FORCE)
set(RPP_COMPILER        "DEFAULT" CACHE STRING "Target compiler" FORCE)

##############################
# Valid Configuration Values #
##############################

set(
    RPP_TARGET_PLATFORM_OPTS
        "xc7z" # Zynq-7000 SoC
)

set(RPP_COMPILER_OPTS
        "gcc"
)

################################
# Toolchain Path Configuration #
################################

if(RPP_TARGET_PLATFORM IN_LIST RPP_TARGET_PLATFORM_OPTS)
    if(RPP_COMPILER STREQUAL "DEFAULT")
        message(STATUS "Compiling for testing on host platform")
    elseif(RPP_COMPILER IN_LIST RPP_COMPILER_OPTS)
        # set toolchain file based on target architecture.
        set(CMAKE_TOOLCHAIN_FILE "${RPP_TARGET_PLATFORM}_${RPP_COMPILER}.cmake" CACHE PATH "" FORCE)
    else()
        message(STATUS "Configured target device family: ${RPP_TARGET_PLATFORM}")
        message(STATUS "Configured target compiler     : ${RPP_COMPILER}")
        message(STATUS "When cross-compiling, set RPP_COMPILER to one of the folowing:")
        message(STATUS "    ${RPP_COMPILER_OPTS}")
        message(FATAL_ERROR "Unsupported cross-compilation toolchain: ${RPP_COMPILER}")
    endif()
else()
    message(STATUS "Configured target device family: ${RPP_TARGET_PLATFORM}")
    message(STATUS "Set RPP_TARGET_PLATFORM to one of the following:")
    message(STATUS "    ${RPP_TARGET_PLATFORM_OPTS}")
    message(FATAL_ERROR "Unsupported target device family: ${RPP_TARGET_PLATFORM}.")
endif()
