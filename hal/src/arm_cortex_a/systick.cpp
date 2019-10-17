#include <atomic>

#include "systick.hpp"

using namespace std::chrono_literals;

using namespace portable::systick;

namespace {

    using us_rep_t = std::chrono::microseconds::rep;

    std::atomic<us_rep_t> system_uptime = 0; //!< Global system uptime.
    us_rep_t              tick_period   = 0; //!< Global system tick period.

    portable::handler_fn_t user_handler = nullptr; //!< User-supplied tick handler.

    void update_tick() {
        system_uptime += tick_period;
        if (user_handler) {
            user_handler();
        }
    }

}

std::chrono::microseconds init(
    std::chrono::microseconds period,
    portable::handler_fn_t    timeout_fn
) {
    return 0us;
}

std::chrono::microseconds uptime() {
    return std::chrono::microseconds{ system_uptime };
}
