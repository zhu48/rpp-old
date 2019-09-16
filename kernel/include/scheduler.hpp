#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <cstdint>

#include <queue>

#include "queue_array.hpp"
#include "dynamic_span.hpp"

#include "thread.hpp"

namespace rpp {

    using priority_t = std::uint_fast16_t;

    struct decision_data {
        thread* const thrd = nullptr;
        priority_t    prio = 0;
    };

    [[noreturn]] void run( dynamic_span<decision_data> threads );

}

#include "scheduler.ipp"

#endif // #ifndef SCHEDULER_HPP
