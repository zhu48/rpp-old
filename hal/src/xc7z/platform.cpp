#include "ps7_init_gpl.h"

#include "platform.hpp"

using namespace platform;

void platform::init( void ) noexcept {
    ps7_init();
    ps7_post_config();
}
