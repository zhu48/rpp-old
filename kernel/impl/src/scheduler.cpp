#include "scheduler.hpp"

using namespace rpp;

[[noreturn]] void rpp::run( gsl::span<decision_data> threads ) {
    while(true) {
        for ( auto& tcb : threads ) {
            if ( tcb.thrd && tcb.thrd->status == thread::status_t::ready ) {
                tcb.thrd->execute();
            }
        }
    }
}
