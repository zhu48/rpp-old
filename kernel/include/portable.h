#ifndef PORTABLE_H
#define PORTABLE_H

#include "portable_types.h"

#ifdef __cplusplus
namespace portable {
extern "C" {
#endif // #ifdef __cplusplus

/**
 * \brief Switch the current CPU to the given context.
 * 
 * \param[in,out] context The context to switch to. The new context may modify the stack frame, but
 *                        not the stack base.
 */
void switch_context( context_t* const context );

#ifdef __cplusplus
} // extern "C"
} // namespace portable
#endif // #ifdef __cplusplus

#endif // #ifndef PORTABLE_H
