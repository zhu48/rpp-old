#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <cstdint>

#include <optional>
#include <queue>

#include "queue_array.hpp"

#include "thread.hpp"

namespace rpp {

    /**
     * \brief Basic kernel scheduler object type.
     * 
     * \details Generic scheduler for running threads.
     */
    class scheduler {
        public:
            using priority_t = std::uint_fast16_t;

            struct decision_data {
                thread*    thrd = nullptr;
                priority_t prio = 0;

                bool operator==( const decision_data& rhs ) const;
                bool operator!=( const decision_data& rhs ) const;
                bool operator<( const decision_data& rhs ) const;
                bool operator>( const decision_data& rhs ) const;
                bool operator>=( const decision_data& rhs ) const;
                bool operator<=( const decision_data& rhs ) const;
            };

        private:
            std::priority_queue<
                decision_data,
                queue_array<decision_data,16>
            > data;

        public:
            /**
             * \brief Add a new thread for this scheduler to schedule.
             * 
             * \param[in] new_thread The thread to add to this scheduler.
             */
            void add_thread( thread& new_thread );

            /**
             * \brief Run the scheduler, handing control of the CPU to the scheduler.
             */
            [[noreturn]] void run( void ) noexcept;
    };

}

#include "scheduler.ipp"

#endif // #ifndef SCHEDULER_HPP
