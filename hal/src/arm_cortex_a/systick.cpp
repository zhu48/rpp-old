#include "systick.hpp"

using namespace std::chrono_literals;

using namespace portable::systick;

std::chrono::microseconds init(
    std::chrono::microseconds period,
    portable::handler_fn_t    timeout_fn
) {
    return 0us;
}

std::chrono::microseconds uptime() {
    return 0us;
}
