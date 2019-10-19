#include <atomic>

#include "cpu.hpp"

#include "ps7_init_gpl.h"

#include "systick.hpp"

using namespace std::chrono_literals;

using namespace portable::systick;

namespace {

    using us_rep_t = std::chrono::microseconds::rep;

    constexpr std::uint32_t ptim_enable      = 1 << 0;
    constexpr std::uint32_t ptim_auto_reload = 1 << 1;
    constexpr std::uint32_t ptim_irq_enable  = 1 << 2;

    std::atomic<us_rep_t> system_uptime = 0; //!< Global system uptime.
    us_rep_t              tick_period   = 0; //!< Global system tick period.

    portable::handler_fn_t user_handler = nullptr; //!< User-supplied tick handler.

    void update_tick() {
        system_uptime += tick_period;
        if (user_handler) {
            user_handler();
        }
    }

    template<
        std::uint32_t counter_freq,
        std::uint32_t duration,
        typename      dur_type
    > constexpr std::uint32_t to_ticks() noexcept {
        return ( duration * counter_freq * dur_type::period::num ) / dur_type::period::den - 1;
    }

    template<
        std::uint32_t counter_freq,
        typename      dur_type
    > constexpr std::uint32_t to_ticks( dur_type duration ) noexcept {
        return
            (
                ( duration.count() * counter_freq * dur_type::period::num ) /
                dur_type::period::den
            ) - 1;
    }

    template<
        std::uint32_t counter_freq,
        std::uint32_t ticks,
        typename      dur_type
    > constexpr dur_type to_duration() noexcept {
        return dur_type{
            ( ( ticks + 1 ) * dur_type::period::den ) /
            ( counter_freq * dur_type::period::num )
        };
    }

    template<
        std::uint32_t counter_freq,
        typename      dur_type
    > constexpr dur_type to_duration( std::uint32_t ticks ) noexcept {
        return dur_type{
            ( ( ticks + 1 ) * dur_type::period::den ) /
            ( counter_freq * dur_type::period::num )
        };
    }

}

std::chrono::microseconds portable::systick::init(
    period_base   base,
    std::uint32_t multiplier,
    handler_fn_t  timeout_fn
) {
    IRQ_Disable( IRQn::PrivTimer_IRQn );

    switch ( base ) {
        case period_base::us_1 :
            PTIM_SetLoadValue( multiplier * to_ticks<APU_FREQ/2,1,std::chrono::microseconds>() );
            tick_period = multiplier * 1;
            break;

        case period_base::us_2 :
            PTIM_SetLoadValue( multiplier * to_ticks<APU_FREQ/2,2,std::chrono::microseconds>() );
            tick_period = multiplier * 2;
            break;

        case period_base::us_3 :
            PTIM_SetLoadValue( multiplier * to_ticks<APU_FREQ/2,3,std::chrono::microseconds>() );
            tick_period = multiplier * 3;
            break;

        case period_base::us_5 :
            PTIM_SetLoadValue( multiplier * to_ticks<APU_FREQ/2,5,std::chrono::microseconds>() );
            tick_period = multiplier * 5;
            break;

        default :
            return std::chrono::microseconds{ 0 };
    }

    IRQ_SetHandler( IRQn::PrivTimer_IRQn, update_tick );
    IRQ_Enable( IRQn::PrivTimer_IRQn );

    PTIM_SetControl( ptim_enable | ptim_auto_reload | ptim_irq_enable );

    switch ( base ) {
        case period_base::us_1 : return std::chrono::microseconds{ multiplier * 1 };
        case period_base::us_2 : return std::chrono::microseconds{ multiplier * 2 };
        case period_base::us_3 : return std::chrono::microseconds{ multiplier * 3 };
        case period_base::us_5 : return std::chrono::microseconds{ multiplier * 5 };
        default                : return std::chrono::microseconds{ 0 };
    }
}

std::chrono::microseconds portable::systick::uptime() {
    return std::chrono::microseconds{ system_uptime };
}
