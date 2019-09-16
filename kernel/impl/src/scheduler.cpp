#include "scheduler.hpp"

using namespace rpp;

[[noreturn]] void rpp::run( dynamic_span<decision_data> threads ) {
    while(true) {
        for ( auto& thrd : threads ) {
            // do something
        }
    }
}
