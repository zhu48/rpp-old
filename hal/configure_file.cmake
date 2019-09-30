
# set required platform-dependent constants
if(HAL_TARGET_ARCH STREQUAL "arm_cortex_a")
    set(HAL_CONTEXT_SIZE "4" CACHE STRING "Size of thread context block")
else()
    set(HAL_CONTEXT_SIZE "8" CACHE STRING "Size of thread context block")
endif()

# generate header from template
configure_file(
	"${HAL_TEMPLATE_DIR}/portable_defs.in"
	"${HAL_INC_DIR}/portable_defs.hpp"
)
