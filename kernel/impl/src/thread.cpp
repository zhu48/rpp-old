#include "portable.h"

#include "thread.hpp"

using namespace rpp;

thread::thread( entry_fn_t entry, entry_fn_arg_t arg, void* const stack ) noexcept :
    status( status_t::ready ),
    context{ stack, stack }
{
    // nothing
}

void thread::execute( void ) {
    portable::switch_context( &context );
}
