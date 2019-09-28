#ifndef PORTABLE_TYPES_H
#define PORTABLE_TYPES_H

#include "portable_defs.hpp"

namespace portable {

    /**
     * \brief Type used as the thread entry point function argument.
     */
    typedef void* const entry_fn_arg_t;

    /**
     * \brief Function type used as entry point to thread execution.
     */
    typedef void (*entry_fn_t)( entry_fn_arg_t );

    /**
     * \brief Thread context type.
     */
    typedef struct {
        std::byte reserved[context_size];
    } context_t;

}

#endif // #ifndef PORTABLE_TYPES_H
