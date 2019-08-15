#include <algorithm>
#include <iterator>

namespace rpp {

    template<std::size_t MaxThreads>
    typename scheduler<MaxThreads>::tid_t
    scheduler<MaxThreads>::add_thread(
        const thread& new_thread
    ) noexcept {
        auto empty_pos = std::find_if_not(
            threads.begin(),
            threads.end(),
            []( const auto& curr_pos ) {
                return curr_pos.has_value();
            }
        );

        if ( empty_pos == threads.end() ) {
            return invalid_tid;
        } else {
            *empty_pos = new_thread;
            return std::distance( threads.begin(), empty_pos );
        }
    }

    template<std::size_t MaxThreads>
    [[noreturn]] void
    scheduler<MaxThreads>::run( void ) noexcept {
        while( true ) {
            for ( const auto& opt_thrd : threads ) {
                if ( opt_thrd.has_value() ) {
                    const auto& thrd = opt_thrd.value();
                    if ( thrd.status == thread::status_t::ready ) {
                        thrd.execute();
                    }
                }
            }
        }
    }

}
