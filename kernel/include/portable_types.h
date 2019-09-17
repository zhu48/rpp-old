#ifndef PORTABLE_TYPES_H
#define PORTABLE_TYPES_H

#ifdef __cplusplus
namespace portable {
extern "C" {
#endif // #ifdef __cplusplus

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
    const void* const stack_base; //!< Pointer to thread's allocated stack's base.
    const void* const frame_base; //!< Pointer to thread's current stack frame.
} context_t;

#ifdef __cplusplus
} // extern "C"
} // namespace portable
#endif // #ifdef __cplusplus

#endif // #ifndef PORTABLE_TYPES_H
