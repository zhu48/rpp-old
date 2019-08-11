# from 3.3 onwards, detecting whether a string exists in a list has a new syntax using if()
cmake_minimum_required(VERSION 3.3)

####################################
# Set Project-Level Configurations #
####################################

project(RPP CXX)

# set the policy to enable inter-procedural optimization if available
if(POLICY CMP0069)
	cmake_policy(SET CMP0069 NEW)
endif()
if(NOT DEFINED IPO_SUPPORTED)
	# check for inter-procedural optimization support
	include(CheckIPOSupported OPTIONAL RESULT_VARIABLE HAS_CHECK_IPO)
	if(HAS_CHECK_IPO)
		message(STATUS "Determining inter-procedural optimization support.")
		
		check_ipo_supported(RESULT IPO)
		
		if(IPO)
			message(STATUS "Inter-procedural optimization enabled.")
		else()
			message(STATUS "Inter-procedural optimization disabled.")
		endif()
	else()
		message(STATUS "Cannot determine inter-procedural optimization support.")
		message(STATUS "Inter-procedural optimization is disabled.")
		
		set(IPO FALSE)
	endif()
	
	set(IPO_SUPPORTED ${IPO} CACHE STRING "Inter-procedural optimzation support.")
endif()

######################
# Derive Directories #
######################

# get RPP repository root directory
get_filename_component(RPP_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

# get top level directories containing code
set(RPP_KERNEL_DIR ${RPP_ROOT_DIR}/kernel)

# get directories containing internal code
set(KERNEL_INC_DIR ${RPP_KERNEL_DIR}/include)
set(KERNEL_IPP_DIR ${KERNEL_INC_DIR}/ipp)
set(KERNEL_SRC_DIR ${RPP_KERNEL_DIR}/src)

#########################
# Gather Target Sources #
#########################

# all kernel internal files
set(
	K_INC_FILES
		${KERNEL_INC_DIR}/rpp.hpp
		${KERNEL_INC_DIR}/thread.hpp
		${KERNEL_INC_DIR}/scheduler.hpp
)
set(
	K_IPP_FILES
		${KERNEL_IPP_DIR}/scheduler.ipp
)
set(
	K_SRC_FILES
		${KERNEL_SRC_DIR}/rpp.cpp
		${KERNEL_SRC_DIR}/thread.cpp
		${KERNEL_SRC_DIR}/scheduler.cpp
)

###################################
# Configure Kernel Library Target #
###################################

# compile kernel as static library
add_library(
	rpp
	STATIC
		${K_INC_FILES}
		${K_IPP_FILES}
		${K_SRC_FILES}
)
# set include directories
target_include_directories(
	rpp
	PRIVATE
		${KERNEL_INC_DIR}
		${KERNEL_IPP_DIR}
)
# set lin-time optimization if available, and use C++17
set_target_properties(
	rpp
	PROPERTIES
		INTERPROCEDURAL_OPTIMIZATION ${IPO_SUPPORTED}
		C_STANDARD                   17
		CXX_STANDARD                 17
		C_STANDARD_REQUIRED          TRUE
		CXX_STANDARD_REQUIRED        TRUE
)
