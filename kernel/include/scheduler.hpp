#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <queue>
#include <functional>
#include <array>
#include <optional>

#include "thread.hpp"

namespace rpp {

    /**
     * \brief Basic kernel scheduler object type.
     * 
     * \details Generic scheduler for running threads.
     */
    class scheduler {
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
