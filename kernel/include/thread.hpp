
namespace rpp {

    /**
     * \brief Kernel thread object type.
     * 
     * \details Consolidated handle object for a thread context.
     */
    class thread {
        public:
            /**
             * \brief Function type used as entry point to thread execution.
             */
            using entry_fn_t = void (*)( void* const );

            /**
             * \brief Thread context type.
             */
            using context_t = struct {
                const void* const stack_base; //!< Pointer to thread's allocated stack's base.
                const void* const frame_base; //!< Pointer to thread's current stack frame.
            };

        private:
            /**
             * \brief Thread entry point function.
             */
            entry_fn_t* const entry;

        public:
            /**
             * \brief Construct a thread object from an entry point function and base stack pointer.
             * 
             * \param[in] entry The entry point function.
             * \param[in] stack The base of the stack to allocate to the thread.
             */
            constexpr thread( entry_fn_t* const entry, void* const stack ) noexcept;

            /**
             * \brief Find the thread object corresponding to the calling context.
             * 
             * \return Returns the thread context corresponding to the calling context.
             */
            static constexpr thread& current( void ) noexcept;

            /**
             * \brief Start or continue running the thread on the current processor.
             */
            void execute( void ) const;
    };

}
