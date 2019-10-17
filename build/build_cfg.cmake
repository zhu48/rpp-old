# from 3.3 onwards, detecting whether a string exists in a list has a new syntax using if()
cmake_minimum_required(VERSION 3.3)

#########################
# Configuration Options #
#########################

set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)

set(RPP_TARGET_PLATFORM "NONE"    CACHE STRING "Target platform"              FORCE)
set(RPP_COMPILER        "DEFAULT" CACHE STRING "Target compiler"              FORCE)
set(RPP_TEST_TARGET     "FALSE"   CACHE BOOL   "Flag to create a test target" FORCE)

set(CMSIS_PATH "NONE" CACHE PATH "ARM CMSIS-5 repository root" FORCE)

set(XSDK_VERSION      "NONE" CACHE STRING "Xilinx SDK version"            FORCE)
set(XSDK_INSTALL_PATH "NONE" CACHE PATH   "Xilinx SDK installation path"  FORCE)
set(XSDK_HW_PLATFORM  "NONE" CACHE PATH   "Xilinx hardware platform path" FORCE)

##############################
# Valid Configuration Values #
##############################

set(
    RPP_TARGET_PLATFORM_OPTS
        "hosted" # run on a non-baremetal host
        "xc7z"   # Zynq-7000 SoC
)

set(
    RPP_COMPILER_OPTS
        "gcc"
)

set(
    XSDK_VERSION_OPTS
        "2019.1"
        "2018.2"
        "2017.1"
)

##########################
# Platform Configuration #
##########################

if(WIN32)
    set(CMAKE_EXECUTABLE_SUFFIX ".exe" CACHE STRING "Host platform executable file extension.")
endif()

# targeting Unix hosts requires pthreads linkage to support threading
if(RPP_TARGET_PLATFORM STREQUAL "hosted" AND UNIX)
    set(RPP_PTHREADS TRUE  CACHE BOOL "Requirement to link to pthreads library")
else()
    set(RPP_PTHREADS FALSE CACHE BOOL "Requirement to link to pthreads library")
endif()

########################
# Vivado Configuration #
########################

if(XSDK_VERSION STREQUAL "NONE")
    message(STATUS "Using non-IDE environment")
else()
    message(STATUS "Configured Xilinx SDK version     : ${XSDK_VERSION}")
    message(STATUS "Configured Xilinx SDK install path: ${XSDK_INSTALL_PATH}")

    # set paths to Xilinx-distributed compilers and build tools
    set(XSDK_ROOT_DIR "${XSDK_INSTALL_PATH}/${XSDK_VERSION}" CACHE PATH "" FORCE)
    set(TC_PATH "${XSDK_ROOT_DIR}/gnu/aarch32/nt/gcc-arm-none-eabi/bin/" CACHE STRING "" FORCE)

    if(EXISTS ${TC_PATH})
        # for Xilinx SDK force gcc as the compiler
        set(RPP_COMPILER "gcc" CACHE STRING "Target compiler" FORCE)

        # generate Makefile and Xilinx SDK projects
        set(CMAKE_GENERATOR       "Unix Makefiles" CACHE INTERNAL "" FORCE)
        set(CMAKE_EXTRA_GENERATOR "Eclipse CDT4"   CACHE INTERNAL "" FORCE)

        # use Make from Xilinx
        set(
            CMAKE_MAKE_PROGRAM
                "${XSDK_ROOT_DIR}/gnuwin/bin/make${CMAKE_EXECUTABLE_SUFFIX}"
            CACHE PATH "" FORCE
        )

        # set expected Eclipse version based on the Xilinx SDK version
        if(XSDK_VERSION STREQUAL "2019.1")
            set(CMAKE_ECLIPSE_VERSION 4.6.1 CACHE PATH "" FORCE)
        elseif(XSDK_VERSION STREQUAL "2018.2")
            set(CMAKE_ECLIPSE_VERSION 4.6.1 CACHE PATH "" FORCE)
        elseif(XSDK_VERSION STREQUAL "2017.1")
            set(CMAKE_ECLIPSE_VERSION 4.6.1 CACHE PATH "" FORCE)
        else()
            message(STATUS "Set XSDK_VERSION to one of the following:")
            message(STATUS "    ${XSDK_VERSION_OPTS}")
            message(FATAL_ERROR "Unsupported XSDK version: ${XSDK_VERSION}")
        endif()
    else()
        message(FATAL_ERROR "Could not find Xilinx-distributed compilers at install path")
    endif()
endif()

################################
# Toolchain Path Configuration #
################################

message(STATUS "Configured target device family: ${RPP_TARGET_PLATFORM}")
message(STATUS "Configured target compiler     : ${RPP_COMPILER}")

if(RPP_TARGET_PLATFORM IN_LIST RPP_TARGET_PLATFORM_OPTS)
    if(RPP_COMPILER STREQUAL "DEFAULT")
        message(STATUS "Using default compiler for build environment")
    elseif(RPP_COMPILER IN_LIST RPP_COMPILER_OPTS)
        # set toolchain file based on target architecture.
        set(
            CMAKE_TOOLCHAIN_FILE
                "${CMAKE_CURRENT_LIST_DIR}/${RPP_TARGET_PLATFORM}_${RPP_COMPILER}.cmake"
            CACHE PATH "" FORCE
        )
    else()
        message(STATUS "When cross-compiling, set RPP_COMPILER to one of the folowing:")
        message(STATUS "    ${RPP_COMPILER_OPTS}")
        message(FATAL_ERROR "Unsupported cross-compilation toolchain: ${RPP_COMPILER}")
    endif()
else()
    message(STATUS "Set RPP_TARGET_PLATFORM to one of the following:")
    message(STATUS "    ${RPP_TARGET_PLATFORM_OPTS}")
    message(FATAL_ERROR "Unsupported target device family: ${RPP_TARGET_PLATFORM}.")
endif()
