#ifndef PORTABLE_TYPES_H
#define PORTABLE_TYPES_H

#ifdef __cplusplus
namespace portable {
extern "C" {
#endif // #ifdef __cplusplus

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
