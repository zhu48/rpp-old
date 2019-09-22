
# set required platform-dependent constants
if(RPP_TARGET_PLATFORM STREQUAL "xc7z")
    set(RPP_CONTEXT_SIZE "4" CACHE STRING "Size of thread context block")
else()
    set(RPP_CONTEXT_SIZE "4" CACHE STRING "Size of thread context block")
endif()

# generate header from template
configure_file(
	"${RPP_TEMPLATE_DIR}/portable_defs.in"
	"${KERNEL_PUB_INC_DIR}/portable_defs.hpp"
)
