
# set required platform-dependent constants
set(HAL_CONTEXT_SIZE "${CMAKE_SIZEOF_VOID_P}" CACHE STRING "Size of thread context block")

# generate header from template
configure_file(
    "${HAL_TEMPLATE_DIR}/portable_defs.in"
    "${HAL_INC_DIR}/portable_defs.hpp"
)
