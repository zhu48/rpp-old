#include <thread>

#include "portable.h"

using namespace portable;

namespace {

    void store_handle( context_t* const context, std::thread::native_handle_type handle ) {
        *reinterpret_cast<std::thread::native_handle_type*>( context ) = handle;
    }

}

void portable::initialize_stack(
    void* const      stack,
    entry_fn_t       entry,
    entry_fn_arg_t   arg,
    context_t* const context
) {
    std::thread thrd( entry, arg );
    store_handle( context, thrd.native_handle() );
    thrd.detach();
}

void portable::switch_context( context_t* const context ) {
    
}
