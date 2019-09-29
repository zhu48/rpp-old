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

# find threading library if required
if(RPP_PTHREADS)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
endif()

######################
# Derive Directories #
######################

set(HAL_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(HAL_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/${RPP_TARGET_PLATFORM})

set(HAL_TEMPLATE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/templates)

###############################
# Detect Custom Linker Script #
###############################

# use SoC-specific linker script path
set(HAL_LD_TEMPLATE ${HAL_TEMPLATE_DIR}/${RPP_TARGET_PLATFORM}/link.ld.in)
if(EXISTS ${HAL_LD_TEMPLATE})
    set(HAL_CUSTOM_LD TRUE)
else()
    set(HAL_CUSTOM_LD FALSE)
endif()
set(HAL_CUSTOM_LD ${HAL_CUSTOM_LD} PARENT_SCOPE)

###################################
# Generate Headers from Templates #
###################################

add_custom_command(
    OUTPUT
        ${HAL_INC_DIR}/portable_defs.hpp
    COMMAND
        ${CMAKE_COMMAND}
            -DHAL_TARGET_PLATFORM=${RPP_TARGET_PLATFORM}
            -DHAL_INC_DIR=${HAL_INC_DIR}
            -DHAL_TEMPLATE_DIR=${HAL_TEMPLATE_DIR}
            -P ${CMAKE_CURRENT_SOURCE_DIR}/configure_file.cmake
    DEPENDS
        ${HAL_TEMPLATE_DIR}/portable_defs.in
        ${CMAKE_CURRENT_SOURCE_DIR}/configure_file.cmake
)

#########################
# Gather Target Sources #
#########################

set(
    HAL_INC_FILES
        ${HAL_INC_DIR}/portable_defs.hpp
        ${HAL_INC_DIR}/portable_types.hpp
        ${HAL_INC_DIR}/portable.h
)
set(
    HAL_SRC_FILES
        ${HAL_SRC_DIR}/mem.c
        ${HAL_SRC_DIR}/portable.cpp
        ${HAL_SRC_DIR}/startup.c
)

################################
# Configure HAL Library Target #
################################

# compile HAL as static library
add_library(
    hal
    STATIC
        ${HAL_INC_FILES}
        ${HAL_SRC_FILES}
)
# set include directories
target_include_directories(
    hal
    PUBLIC
        ${HAL_INC_DIR}
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
# pre-process linker script if it exists
if(HAL_CUSTOM_LD)
    message(STATUS "Using custom linker script")

    set(HAL_LD ${HAL_SRC_DIR}/link.ld)
    add_custom_command(
        TARGET hal PRE_LINK
        COMMAND
            ${CMAKE_C_PREPROCESSOR}
                ${HAL_LD_TEMPLATE} -P
                -o ${HAL_LD}
                -I ${HAL_INC_DIR}/${RPP_TARGET_PLATFORM}
        DEPENDS
            ${HAL_LD_TEMPLATE}
    )
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${HAL_LD}" PARENT_SCOPE)
else()
    message(STATUS "Using default linker script")
endif()
