#include "portable.h"

#include "thread.hpp"

using namespace rpp;

void thread::execute( void ) {
    portable::switch_context( &context );
}
