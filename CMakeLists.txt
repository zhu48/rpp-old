# from 3.9.6 onwards, checking IPO has a cleaner syntax
cmake_minimum_required(VERSION 3.9.6)

####################################
# Set Project-Level Configurations #
####################################

project(rpp LANGUAGES CXX VERSION 0.0.1)



# set the policy to enable inter-procedural optimization if available
if(POLICY CMP0069)
	cmake_policy(SET CMP0069 NEW)
endif()
if(NOT DEFINED CMAKE_INTERPROCEDURAL_OPTIMIZATION)
    include(CheckIPOSupported)
    message(STATUS "Determining inter-procedural optimization support")
    check_ipo_supported(RESULT CMAKE_INTERPROCEDURAL_OPTIMIZATION)

    if(CMAKE_INTERPROCEDURAL_OPTIMIZATION)
        message(STATUS "Inter-procedural optimization enabled")
    else()
        message(STATUS "Inter-procedural optimization disabled")
    endif()
    set(
        CMAKE_INTERPROCEDURAL_OPTIMIZATION
            ${CMAKE_INTERPROCEDURAL_OPTIMIZATION}
        CACHE INTERNAL "" FORCE
    )
endif()

######################
# Derive Directories #
######################

# get header generation template directory
set(RPP_TEMPLATE_DIR ${CMAKE_CURRENT_LIST_DIR}/templates)

# get top level directories containing code
set(RPP_KERNEL_DIR ${CMAKE_CURRENT_LIST_DIR}/kernel)

# get directories containing kernel headers
set(KERNEL_PUB_INC_DIR ${RPP_KERNEL_DIR}/include)
set(KERNEL_PUB_IPP_DIR ${KERNEL_PUB_INC_DIR}/ipp)

# get kernel implementation directories
set(KERNEL_IMP_DIR ${RPP_KERNEL_DIR}/impl)
set(KERNEL_INC_DIR ${KERNEL_IMP_DIR}/include)
set(KERNEL_IPP_DIR ${KERNEL_INC_DIR}/ipp)
set(KERNEL_SRC_DIR ${KERNEL_IMP_DIR}/src)

#########################
# Gather Target Sources #
#########################

# all kernel internal files
set(
    K_API_INC_FILES
        ${KERNEL_PUB_INC_DIR}/rpp.hpp
        ${KERNEL_PUB_INC_DIR}/thread.hpp
        ${KERNEL_PUB_INC_DIR}/scheduler.hpp
        ${KERNEL_PUB_INC_DIR}/queue_array.hpp
)
set(
    K_API_IPP_FILES
        ${KERNEL_PUB_IPP_DIR}/thread.ipp
        ${KERNEL_PUB_IPP_DIR}/scheduler.ipp
        ${KERNEL_PUB_IPP_DIR}/queue_array.ipp
)
set(
    K_INC_FILES
)
set(
    K_IPP_FILES
)
set(
    K_SRC_FILES
        ${KERNEL_SRC_DIR}/rpp.cpp
        ${KERNEL_SRC_DIR}/thread.cpp
        ${KERNEL_SRC_DIR}/scheduler.cpp
)

#######################
# Gather Dependencies #
#######################

get_filename_component(RPP_PARENT_DIR ${CMAKE_CURRENT_LIST_DIR} DIRECTORY)

# C++ Core Guidelines Guideline Support Library
add_subdirectory(${RPP_PARENT_DIR}/gsl ${CMAKE_CURRENT_BINARY_DIR}/gsl)

# hardware abstraction layer
set(HAL_TARGET_PLATFORM ${RPP_TARGET_PLATFORM})
if(RPP_TARGET_PLATFORM STREQUAL "xc7z")
    set(HAL_TARGET_ARCH "arm_cortex_a")
else()
    set(HAL_TARGET_ARCH ${HAL_TARGET_PLATFORM})
endif()
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/hal ${CMAKE_CURRENT_BINARY_DIR}/hal)

###################################
# Configure Kernel Library Target #
###################################

# compile kernel as static library
add_library(
    rpp
    STATIC
        ${K_API_INC_FILES}
        ${K_API_IPP_FILES}
        ${K_INC_FILES}
        ${K_IPP_FILES}
        ${K_SRC_FILES}
)
# set include directories
target_include_directories(
    rpp
    PUBLIC
        ${KERNEL_PUB_INC_DIR}
        ${KERNEL_PUB_IPP_DIR}
    PRIVATE
        ${KERNEL_INC_DIR}
        ${KERNEL_IPP_DIR}
)
# require C++17
target_compile_features(rpp PRIVATE cxx_std_17)
# link to HAL
target_link_libraries(rpp PUBLIC rpp_hal)
# link to GSL
target_link_libraries(rpp PUBLIC gsl)
# use custom linker script if it exists
if(TARGET linker)
    add_dependencies(rpp linker)
endif()
