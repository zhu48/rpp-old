# from 3.3 onwards, detecting whether a string exists in a list has a new syntax using if()
cmake_minimum_required(VERSION 3.3)

####################################
# Set Project-Level Configurations #
####################################

project(HAL CXX C ASM)

# set language standards
set(CMAKE_C_STANDARD                    11)
set(CMAKE_CXX_STANDARD                  17)
set(CMAKE_C_STANDARD_REQUIRED           TRUE)
set(CMAKE_CXX_STANDARD_REQUIRED         TRUE)
set(CMAKE_C_IMPLICIT_LINK_LIBRARIES     "")
set(CMAKE_CXX_IMPLICIT_LINK_LIBRARIES   "")
set(CMAKE_C_IMPLICIT_LINK_DIRECTORIES   "")
set(CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES "")

# use CMSIS processor abstraction headers for ARM processors
set(
    HAL_TARGET_ARCH_ARM_OPTS
        "arm_cortex_a"
)
if(HAL_TARGET_ARCH IN_LIST HAL_TARGET_ARCH_ARM_OPTS)
    message(STATUS "Using CMSIS CPU abstraction headers")

    if(EXISTS ${CMSIS_PATH})
        set(HAL_USE_CMSIS TRUE)
    else()
        message(FATAL_ERROR "Could not find CMSIS repository at ${CMSIS_PATH}")
    endif()
else()
    message(STATUS "Using CMSIS CPU abstraction headers")
    set(HAL_USE_CMSIS FALSE)
endif()

# find threading library if required
if(RPP_PTHREADS)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
endif()

######################
# Derive Directories #
######################

set(HAL_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(HAL_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/${HAL_TARGET_ARCH})

set(HAL_ARCH_INC_DIR     ${HAL_INC_DIR}/${HAL_TARGET_ARCH})
set(HAL_PLATFORM_INC_DIR ${HAL_INC_DIR}/${HAL_TARGET_PLATFORM})

set(HAL_TEMPLATE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/templates)

if(HAL_TARGET_ARCH IN_LIST HAL_TARGET_ARCH_ARM_OPTS)
    set(CMSIS_CMSIS_DIR ${CMSIS_PATH}/CMSIS)

    set(CMSIS_ARCH_DIR ${CMSIS_PATH}/Device/ARM/ARMCA9)

    set(CMSIS_CORE_INC_DIR   ${CMSIS_CMSIS_DIR}/Core_A/Include)
    set(CMSIS_CONFIG_INC_DIR ${CMSIS_ARCH_DIR}/Config)
    set(CMSIS_DEVICE_INC_DIR ${CMSIS_ARCH_DIR}/Include)
endif()

###############################
# Detect Custom Linker Script #
###############################

# use SoC-specific linker script path
set(HAL_LD_TEMPLATE ${HAL_TEMPLATE_DIR}/${HAL_TARGET_ARCH}/link_template.ld)
if(EXISTS ${HAL_LD_TEMPLATE})
    set(HAL_CUSTOM_LD TRUE)
else()
    set(HAL_CUSTOM_LD FALSE)
endif()
set(HAL_CUSTOM_LD ${HAL_CUSTOM_LD} PARENT_SCOPE)

#################################
# Generate Files from Templates #
#################################

# generate port-specific definitions
add_custom_command(
    OUTPUT
        ${HAL_INC_DIR}/portable_defs.hpp
    COMMAND
        ${CMAKE_COMMAND}
            -DHAL_TARGET_ARCH=${HAL_TARGET_ARCH}
            -DHAL_INC_DIR=${HAL_INC_DIR}
            -DHAL_TEMPLATE_DIR=${HAL_TEMPLATE_DIR}
            -P ${CMAKE_CURRENT_SOURCE_DIR}/configure_file.cmake
    DEPENDS
        ${HAL_TEMPLATE_DIR}/portable_defs.in
        ${CMAKE_CURRENT_SOURCE_DIR}/configure_file.cmake
)

# pre-process linker script if it exists
if(HAL_CUSTOM_LD)
    message(STATUS "Using custom linker script")

    set(HAL_LD ${HAL_SRC_DIR}/link.ld)
    add_custom_command(
        OUTPUT
            ${HAL_LD}
        COMMAND
            ${CMAKE_C_PREPROCESSOR}
                ${HAL_LD_TEMPLATE} -P
                -o ${HAL_LD}
                -I ${HAL_PLATFORM_INC_DIR}
                -I ${HAL_ARCH_INC_DIR}
        DEPENDS
            ${HAL_LD_TEMPLATE}
    )
else()
    message(STATUS "Using default linker script")
endif()

#########################
# Gather Target Sources #
#########################

set(
    HAL_INC_FILES
        ${HAL_INC_DIR}/portable_defs.hpp
        ${HAL_INC_DIR}/portable_types.hpp
        ${HAL_INC_DIR}/portable.hpp
)
set(
    HAL_PLATFORM_INC_FILES
        ${HAL_PLATFORM_INC_DIR}/mem_map.h
)
set(
    HAL_ARCH_INC_FILES
        ${HAL_ARCH_INC_DIR}/mem_load.h
)
set(
    HAL_SRC_FILES
        ${HAL_SRC_DIR}/mem.c
        ${HAL_SRC_DIR}/portable.cpp
        ${HAL_SRC_DIR}/startup.cpp
)

if(HAL_TARGET_ARCH IN_LIST HAL_TARGET_ARCH_ARM_OPTS)
    set(
        CMSIS_CORE_INC_FILES
            ${CMSIS_CORE_INC_DIR}/cmsis_compiler.h
            ${CMSIS_CORE_INC_DIR}/cmsis_gcc.h
            ${CMSIS_CORE_INC_DIR}/core_ca.h
    )
    set(
        CMSIS_CONFIG_INC_FILES
            ${CMSIS_CONFIG_INC_DIR}/system_ARMCA9.h
    )
    set(
        CMSIS_DEVICE_INC_FILES
            ${CMSIS_DEVICE_INC_DIR}/ARMCA9.h
    )
endif()

################################
# Configure HAL Library Target #
################################

# compile HAL as static library
add_library(
    hal
    STATIC
        ${HAL_INC_FILES}
        ${HAL_ARCH_INC_FILES}
        ${HAL_PLATFORM_INC_FILES}
        ${HAL_SRC_FILES}
        ${CMSIS_CORE_INC_FILES}
        ${CMSIS_CONFIG_INC_FILES}
        ${CMSIS_DEVICE_INC_FILES}
)
# set include directories
target_include_directories(
    hal
    PUBLIC
        ${HAL_INC_DIR}
    PRIVATE
        ${HAL_PLATFORM_INC_DIR}
        ${HAL_ARCH_INC_DIR}
        ${CMSIS_CORE_INC_DIR}
        ${CMSIS_CONFIG_INC_DIR}
        ${CMSIS_DEVICE_INC_DIR}
)
# disable IPO to prevent functions in mem.c from being optimized out
set_target_properties(
    hal
    PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION FALSE
)
# link to pthreads if targeting Unix host
if(RPP_PTHREADS)
	target_link_libraries(hal Threads::Threads)
endif()

# add custom linker script if necessary
if(HAL_CUSTOM_LD)
    add_custom_target(linker DEPENDS ${HAL_LD})
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${HAL_LD}" PARENT_SCOPE)
endif()
