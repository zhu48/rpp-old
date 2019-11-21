# from 3.9.6 onwards, checking IPO has a cleaner syntax
cmake_minimum_required(VERSION 3.9.6)

####################################
# Set Project-Level Configurations #
####################################

project(RPP CXX)

# set language standards
set(CMAKE_CXX_STANDARD                  17)
set(CMAKE_CXX_STANDARD_REQUIRED         TRUE)
set(CMAKE_CXX_IMPLICIT_LINK_LIBRARIES   "")
set(CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES "")

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

# get RPP repository root directory
get_filename_component(RPP_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

# get header generation template directory
set(RPP_TEMPLATE_DIR ${RPP_ROOT_DIR}/templates)

# get top level directories containing code
set(RPP_KERNEL_DIR ${RPP_ROOT_DIR}/kernel)

# get directories containing kernel headers
set(KERNEL_PUB_INC_DIR ${RPP_KERNEL_DIR}/include)
set(KERNEL_PUB_IPP_DIR ${KERNEL_PUB_INC_DIR}/ipp)

# get kernel implementation directories
set(KERNEL_IMP_DIR ${RPP_KERNEL_DIR}/impl)
set(KERNEL_INC_DIR ${KERNEL_IMP_DIR}/include)
set(KERNEL_IPP_DIR ${KERNEL_INC_DIR}/ipp)
set(KERNEL_SRC_DIR ${KERNEL_IMP_DIR}/src)

# get directory containing code specific to the selected platform
set(HAL_DIR ${RPP_ROOT_DIR}/hal)

# get directories containing kernel tests
set(TEST_SRC_DIR ${RPP_ROOT_DIR}/test)

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

# all test files
set(
	TEST_SCHED_SRC_FILES
		${TEST_SRC_DIR}/test_sched.cpp
)
set(
	TEST_SYSTICK_SRC_FILES
		${TEST_SRC_DIR}/test_systick.cpp
)

#######################
# Gather Dependencies #
#######################

get_filename_component(RPP_PARENT_DIR ${RPP_ROOT_DIR} DIRECTORY)

# C++ Core Guidelines Guideline Support Library
add_subdirectory(${RPP_PARENT_DIR}/gsl ${CMAKE_CURRENT_BINARY_DIR}/gsl)

# hardware abstraction layer
set(HAL_TARGET_PLATFORM ${RPP_TARGET_PLATFORM})
if(RPP_TARGET_PLATFORM STREQUAL "xc7z")
	set(HAL_TARGET_ARCH "arm_cortex_a")
else()
	set(HAL_TARGET_ARCH ${HAL_TARGET_PLATFORM})
endif()
add_subdirectory(${HAL_DIR} ${CMAKE_CURRENT_BINARY_DIR}/hal)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}" PARENT_SCOPE)

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
# link to HAL
target_link_libraries(rpp PUBLIC hal)
# link to GSL
target_link_libraries(rpp PUBLIC gsl)
# use custom linker script if it exists
if(TARGET linker)
	add_dependencies(rpp linker)
endif()

####################################
# Configure Test Executable Target #
####################################

if(RPP_TEST_TARGET)
	message(STATUS "Creating test executable targets")

	# compile test executable
	add_executable(
		rpp_test_sched
			${TEST_SCHED_SRC_FILES}
	)
	# link to kernel library
	target_link_libraries(rpp_test_sched PUBLIC rpp)

	# compile test executable
	add_executable(
		rpp_test_systick
			${TEST_SYSTICK_SRC_FILES}
	)
	# link to kernel library
	target_link_libraries(rpp_test_systick PUBLIC rpp)

	if(HAL_PERIPH_LIB)
		add_executable(pwm_test ${TEST_PWM_SRC_FILES})
		target_link_libraries(pwm_test PUBLIC rpp)
		target_link_libraries(pwm_test PUBLIC periph)
		
		add_executable(pwb_test ${TEST_PWB_SRC_FILES})
		target_link_libraries(pwb_test PUBLIC rpp)
		target_link_libraries(pwb_test PUBLIC periph)
	endif()
else()
	message(STATUS "Excluding test executable targets from build")
endif()

############################
# Configure Doxygen Target #
############################

# check if Doxygen is installed
find_program(DOXYGEN doxygen)

# configure documentation target
if(DOXYGEN STREQUAL "DOXYGEN-NOTFOUND")
	message(STATUS "No Doxygen installation found. Documentation target will not be created")
else()
	message(STATUS "Doxygen installation found. A documentation target will be created")
	
	# get documentation directory
	set(DOCS_ROOT_DIR ${RPP_ROOT_DIR}/docs)
	set(DOCS_HTML_DIR ${DOCS_ROOT_DIR}/html)
	
	# set project name in documentation
	set(DOCS_PROJECT_NAME ${CMAKE_PROJECT_NAME})

	# set files to generated documentation from
	set(
		DOCUMENTED_FILES
			${K_API_INC_FILES}
			${K_API_IPP_FILES}
			${K_INC_FILES}
			${K_IPP_FILES}
			${K_SRC_FILES}
	)
	# convert CMake files list to a space-separated list for Doxygen
	string(REPLACE ";" " " DOX_INPUT "${DOCUMENTED_FILES}")
	
	# check if GraphViz dot is installed
	find_program(DOT dot)
	# set dot existence flag and dot installation path
	if(DOT STREQUAL "DOT-NOTFOUND")
		message(STATUS "GraphViz dot tool not found. Configuring Doxygen to use native graphs")
		set(DOX_HAVE_DOT NO)
		set(DOX_DOT_PATH "")
	else()
		message(STATUS "GraphViz dot tool found. Configuring Doxygen to use dot graphs")
		set(DOX_HAVE_DOT YES)
		set(DOX_DOT_PATH DOT)
	endif()
	
	# generate the Doxygen configuration file
	configure_file(
		"${DOCS_ROOT_DIR}/Doxyfile.in"
		"${DOCS_ROOT_DIR}/Doxyfile"
	)
	
	# create custom command to generate documentation dependent on source files
	add_custom_command(
		OUTPUT
			${DOCS_HTML_DIR}/index.html
		COMMAND
			${DOXYGEN}
		WORKING_DIRECTORY
			${DOCS_ROOT_DIR}
		DEPENDS
			${DOCUMENTED_FILES}
			${DOCS_ROOT_DIR}/Doxyfile
	)
	
	# create documentation target
	add_custom_target(docs DEPENDS ${DOCS_HTML_DIR}/index.html)
endif()
