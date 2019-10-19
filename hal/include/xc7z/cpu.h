#ifndef CPU_H
#define CPU_H

#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus

#ifdef __cplusplus
typedef enum IRQn : std::int32_t {
#else
typedef enum IRQn {
#endif // #ifdef __cplusplus
    SGI0_IRQn            =  0, //!< Software Generated Interrupt 0
    SGI1_IRQn            =  1, //!< Software Generated Interrupt 1
    SGI2_IRQn            =  2, //!< Software Generated Interrupt 2
    SGI3_IRQn            =  3, //!< Software Generated Interrupt 3
    SGI4_IRQn            =  4, //!< Software Generated Interrupt 4
    SGI5_IRQn            =  5, //!< Software Generated Interrupt 5
    SGI6_IRQn            =  6, //!< Software Generated Interrupt 6
    SGI7_IRQn            =  7, //!< Software Generated Interrupt 7
    SGI8_IRQn            =  8, //!< Software Generated Interrupt 8
    SGI9_IRQn            =  9, //!< Software Generated Interrupt 9
    SGI10_IRQn           = 10, //!< Software Generated Interrupt 10
    SGI11_IRQn           = 11, //!< Software Generated Interrupt 11
    SGI12_IRQn           = 12, //!< Software Generated Interrupt 12
    SGI13_IRQn           = 13, //!< Software Generated Interrupt 13
    SGI14_IRQn           = 14, //!< Software Generated Interrupt 14
    SGI15_IRQn           = 15, //!< Software Generated Interrupt 15
    GlobalTimer_IRQn     = 27, //!< Global Timer Interrupt
    Legacy_FIQ_IRQn      = 28, //!< Legacy FIQ Interrupt
    PrivTimer_IRQn       = 29, //!< Private Timer Interrupt
    PrivWatchdog_IRQn    = 30, //!< Private Watchdog Interrupt
    Legacy_IRQ_IRQn      = 31, //!< Legacy IRQ Interrupt
} IRQn_Type;

#define PRIVATE_PERIPH_BASE (0xF8F00000UL)

#define GIC_INTERFACE_BASE   (PRIVATE_PERIPH_BASE+0x00000100UL)
#define TIMER_BASE           (PRIVATE_PERIPH_BASE+0x00000600UL)
#define GIC_DISTRIBUTOR_BASE (PRIVATE_PERIPH_BASE+0x00001000UL)
#define L2C_310_BASE         (PRIVATE_PERIPH_BASE+0x00002000UL)

#define __CA_REV      0x0300U //!< Core revision r3p0
#define __CORTEX_A         9U //!< Cortex-A9 Core
#define __FPU_PRESENT      1U //!< FPU present
#define __GIC_PRESENT      1U //!< GIC present
#define __TIM_PRESENT      1U //!< TIM present
#define __L2C_PRESENT      1U //!< L2C present

#include "core_ca.h"
#include "irq_ctrl.h"

#ifdef __cplusplus
} // extern "C"
#endif // #ifdef __cplusplus

#endif // #ifndef CPU_H
