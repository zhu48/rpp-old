#ifndef PORTABLE_TYPES_HPP
#define PORTABLE_TYPES_HPP

#include "portable_defs.hpp"

namespace portable {

    /**
     * \brief Type used as the thread entry point function argument.
     */
    using entry_fn_arg_t = void* const;

    /**
     * \brief Function type used as entry point to thread execution.
     */
    typedef void (*entry_fn_t)( entry_fn_arg_t );

    /**
     * \brief Thread context type.
     */
    struct context_t {
        std::byte reserved[context_size];
    };

}

#endif // #ifndef PORTABLE_TYPES_HPP
