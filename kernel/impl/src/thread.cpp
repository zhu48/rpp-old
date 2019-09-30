#include "portable.hpp"

#include "thread.hpp"

using namespace rpp;

thread::thread(
    portable::entry_fn_t     entry,
    portable::entry_fn_arg_t arg,
    void* const              stack
) noexcept :
    status( status_t::ready )
{
    portable::initialize_stack( stack, entry, arg, context );
}

void thread::execute( void ) {
    portable::switch_context( context );
}
