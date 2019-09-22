#include <cstdint>

#include "portable.h"

using namespace portable;

namespace {

    struct context_t_impl {
        std::uint32_t sp;
    };

    void assert_invariants( void ) {
        static_assert( sizeof( context_t_impl ) == context_size, "context size mismatch" );
    }

}

void portable::initialize_stack(
    void* const      stack,
    entry_fn_t       entry,
    entry_fn_arg_t   arg,
    context_t* const context
) {
    
}

void portable::switch_context( context_t* const context ) {
    
}
