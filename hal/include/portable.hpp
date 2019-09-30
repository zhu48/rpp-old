#ifndef PORTABLE_HPP
#define PORTABLE_HPP

#include "portable_types.hpp"

#ifdef __cplusplus
namespace portable {
extern "C" {
#endif // #ifdef __cplusplus

void initialize_stack(
    void* const    stack,
    entry_fn_t     entry,
    entry_fn_arg_t arg,
    context_t&     context
);

/**
 * \brief Switch the current CPU to the given context.
 * 
 * \param[in,out] context The context to switch to. The new context may modify the stack frame,
 *                        but not the stack base.
 */
void switch_context( context_t& context );

#ifdef __cplusplus
} // extern "C"
} // namespace portable
#endif // #ifdef __cplusplus

#endif // #ifndef PORTABLE_HPP
