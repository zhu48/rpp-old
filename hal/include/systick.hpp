#ifndef SYSTICK_HPP
#define SYSTICK_HPP

#include <chrono>

#include "portable_types.hpp"

namespace portable::systick {

    /**
     * Supported base system tick intervals.
     */
    enum class period_base {
        us_1, //!< 1 microsecond base.
        us_2, //!< 2 microsecond base.
        us_3, //!< 3 microsecond base.
        us_5  //!< 5 microsecond base.
    };

    /**
     * Initialize the system tick timer with a period and timeout hander function.
     * 
     * The system tick period is the product of the tick base and tick multiplier. Depending on the
     * hardware counter backing the system tick, smaller period bases may be less precise.
     * 
     * \param base       The base system tick period.
     * \param multiplier The system tick period multiplier.
     * \param timeout_fn The interrupt service routine to handle tick timeouts.
     * 
     * \return Returns the actual tick period the timer is configured with.
     */
    std::chrono::microseconds init(
        period_base   base,
        std::uint32_t multiplier,
        handler_fn_t  timeout_fn
    );

    /**
     * Obtain the current system uptime.
     * 
     * \return Returns the amount of time since the last system reset.
     */
    std::chrono::microseconds uptime();

}

#endif // #ifndef SYSTICK_HPP
