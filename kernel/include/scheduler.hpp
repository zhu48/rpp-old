#include <array>
#include <optional>

#include "thread.hpp"

namespace rpp {

    /**
     * \brief Basic kernel scheduler object type.
     * 
     * \details Generic scheduler for running threads.
     * 
     * \tparam MaxThreads The maximum number of threads a single scheduler instance can handle.
     */
    template<std::size_t MaxThreads> class scheduler {
        public:
            /**
             * \brief Thread ID type.
             */
            using tid_t = std::size_t;

            /**
             * \brief Reserved thread ID value that no thread can have.
             */
            static constexpr tid_t invalid_tid = MaxThreads;

        private:
            /**
             * \brief The threads managed by this scheduler.
             */
            std::array<std::optional<thread>,MaxThreads> threads;

        public:
            /**
             * \brief Add a new thread for this scheduler to schedule.
             * 
             * \param[in] new_thread The thread to add to this scheduler.
             * 
             * \return Returns the thread ID assigned to the added thread.
             * \retval invalid_tid Could not schedule the new thread.
             */
            tid_t add_thread( const thread& new_thread ) noexcept;

            /**
             * \brief Run the scheduler, handingcontrol of the CPU to the scheduler.
             */
            [[noreturn]] void run( void ) noexcept;
    };

}

#include "scheduler.ipp"
