#ifndef THREAD_HPP
#define THREAD_HPP

#include "portable_types.h"

namespace rpp {

    /**
     * \brief Kernel thread object type.
     * 
     * \details Consolidated handle object for a thread context.
     */
    class thread {
        public:
            /**
             * \brief Status codes to indicate the thread's status.
             */
            enum class status_t {
                ready,  //!< Thread is ready to run.
                waiting //!< Thread is waiting for an event.
            };

            status_t status;

            /**
             * \brief Construct a thread object from an entry point function and base stack pointer.
             * 
             * \param[in] entry The entry point function.
             * \param[in] arg   The argument to pass to the entry point function.
             * \param[in] stack The base of the stack to allocate to the thread.
             */
            thread(
                portable::entry_fn_t     entry,
                portable::entry_fn_arg_t arg,
                void* const              stack
            ) noexcept;

            /**
             * \brief Disallow default construction.
             * 
             * Default construction does not make sense, as a thread without an entry point or stack
             * might as well not exist.
             */
            thread( void ) = delete;

            /**
             * \brief Disallow copy construction.
             * 
             * Each thread object has express and exclusive ownership of its own context, and must
             * not be copied.
             */
            thread( const thread& ) = delete;

            /**
             * \brief Construct by taking the contents of another thread object.
             * 
             * \param[in] rhs The object to take the contents of. The moved-from object forfeits
             *                ownership of its context to this thread object.
             */
            thread( thread&& rhs ) noexcept = default;

            /**
             * \brief Kill this thread and free its resources.
             */
            ~thread( void ) noexcept = default;

            /**
             * \brief Disallow copying.
             * 
             * Each thread object has express and exclusive ownership of its own context, and must
             * not be copied.
             * 
             * \return Returns self-reference.
             */
            thread& operator=( const thread& ) = delete;

            /**
             * \brief Move the contents of another thread object to this thread object.
             * 
             * \param[in] rhs The object to take the contents of. The moved-from object forfeits
             *                ownership of its context to this thread object.
             * 
             * \return Returns self-reference.
             */
            thread& operator=( thread&& rhs ) noexcept = default;

            /**
             * \brief Find the thread object corresponding to the calling context.
             * 
             * \return Returns the thread context corresponding to the calling context.
             */
            static constexpr thread& current( void ) noexcept;

            /**
             * \brief Start or continue running the thread on the current processor.
             */
            void execute( void );

        private:
            /**
             * \brief The thread's context information.
             */
            portable::context_t context;
    };

}

#include "thread.ipp"

#endif // #ifndef THREAD_HPP
