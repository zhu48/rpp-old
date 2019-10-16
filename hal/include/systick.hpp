#ifndef SYSTICK_HPP
#define SYSTICK_HPP

#include <chrono>

#include "portable_types.hpp"

namespace portable::systick {

    /**
     * Initialize the system tick timer with a period and timeout hander function.
     * 
     * The requested tick period may not always be supported by the system. If it is not, the tick
     * period will be rounded up to a supported period.
     * 
     * \param period     The requested system tick period.
     * \param timeout_fn The interrupt service routine to handle tick timeouts.
     * 
     * \return Returns the actual tick period the timer is configured with.
     */
    std::chrono::microseconds init( std::chrono::microseconds period, handler_fn_t timeout_fn );

    /**
     * Obtain the current system uptime.
     * 
     * \return Returns the amount of time since the last system reset.
     */
    std::chrono::microseconds uptime();

}

#endif // #ifndef SYSTICK_HPP
