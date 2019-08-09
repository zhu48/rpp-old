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
             * \brief Thread ID type.
             */
            using tid_t = unsigned int;

            /**
             * \brief Reserved thread ID value that no thread can have.
             */
            static constexpr tid_t invalid_tid = 0;

            /**
             * \brief Add a new thread for this scheduler to schedule.
             * 
             * \param[in] new_thread The thread to add to this scheduler.
             * 
             * \return Returns the thread ID assigned to the added thread.
             * \retval invalid_tid Could not schedule the new thread.
             */
            tid_t add_thread( thread&& new_thread ) noexcept;

            /**
             * \brief Run the scheduler, handingcontrol of the CPU to the scheduler.
             */
            [[noreturn]] void run( void ) noexcept;
    };

}
