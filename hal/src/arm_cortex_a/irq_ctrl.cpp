#include <cstddef>

#include <array>
#include <algorithm>

#include "cpu.hpp"

#include "portable_types.hpp"

namespace {

    constexpr std::size_t num_spi_lines = 224;
    constexpr std::size_t spi_id_base   = 32;

    std::array<portable::handler_fn_t,num_spi_lines> irq_handlers;

    [[gnu::interrupt]]
    void default_handler() {
        while(true);
    }

    bool irqn_valid( IRQn_ID_t irqn ) {
        return irqn >= spi_id_base && irqn < num_spi_lines;
    }

    std::size_t to_index( IRQn_ID_t irqn ) {
        return irqn - spi_id_base;
    }

}

extern "C" {

    int32_t IRQ_Initialize() {
        std::fill( irq_handlers.begin(), irq_handlers.end(), default_handler );
        GIC_Enable();
        return 0;
    }

    int32_t IRQ_SetHandler( IRQn_ID_t irqn, IRQHandler_t handler ) {
        if ( !irqn_valid( irqn ) )
            return -1;

        irq_handlers[to_index(irqn)] = handler;

        return 0;
    }

    IRQHandler_t IRQ_GetHandler( IRQn_ID_t irqn ) {
        return irqn_valid( irqn ) ? irq_handlers[to_index(irqn)] : nullptr;
    }

    int32_t IRQ_Enable( IRQn_ID_t irqn ) {
        if ( !irqn_valid( irqn ) )
            return -1;

        GIC_EnableIRQ( IRQn_Type{ irqn } );

        return 0;
    }

    int32_t IRQ_Disable( IRQn_ID_t irqn ) {
        if ( !irqn_valid( irqn ) )
            return -1;

        GIC_DisableIRQ( IRQn_Type{ irqn } );

        return 0;
    }

    uint32_t IRQ_GetEnableState( IRQn_ID_t irqn ) {
        return irqn_valid( irqn ) ? GIC_GetEnableIRQ( IRQn_Type{ irqn } ) : 0;
    }

    int32_t IRQ_SetMode( IRQn_ID_t irqn, uint32_t mode ) {
        if ( ( mode & IRQ_MODE_TYPE_Msk ) != IRQ_MODE_TYPE_IRQ )
            return -1;

        switch ( mode & IRQ_MODE_TRIG_Msk ) {
            case IRQ_MODE_TRIG_LEVEL :
                GIC_SetConfiguration( IRQn_Type{ irqn }, 0 );
                break;

            case IRQ_MODE_TRIG_EDGE :
                GIC_SetConfiguration( IRQn_Type{ irqn }, 2 );
                break;

            default :
                return -1;
        }

        switch ( mode & IRQ_MODE_CPU_Msk ) {
            case IRQ_MODE_CPU_ALL :
                GIC_SetTarget( IRQn_Type{ irqn }, 0xFFU );
                break;

            default :
                GIC_SetTarget( IRQn_Type{ irqn }, ( mode & IRQ_MODE_CPU_Msk ) >> IRQ_MODE_CPU_Pos );
                break;
        }

        GIC_SetGroup( IRQn_Type{ irqn }, 1 );

        return 0;
    }

    uint32_t IRQ_GetMode( IRQn_ID_t irqn ) {
        if ( !irqn_valid( irqn ) )
            return IRQ_MODE_ERROR;

        std::uint32_t mode = IRQ_MODE_TYPE_IRQ;

        if ( GIC_GetConfiguration( IRQn_Type{ irqn } ) & 2U ) {
            mode |= IRQ_MODE_TRIG_EDGE;
        } else {
            mode |= IRQ_MODE_TRIG_LEVEL;
        }

        return mode | GIC_GetTarget( IRQn_Type{ irqn << IRQ_MODE_CPU_Pos } );
    }

    IRQn_ID_t IRQ_GetActiveIRQ() {
        return GIC_AcknowledgePending();
    }

    IRQn_ID_t IRQ_GetActiveFIQ() {
        return -1;
    }

    int32_t IRQ_EndOfInterrupt( IRQn_ID_t irqn ) {
        if ( !irqn_valid( irqn ) )
            return -1;

        GIC_EndInterrupt( IRQn_Type{ irqn } );

        return 0;
    }

    int32_t IRQ_SetPending( IRQn_ID_t irqn ) {
        if ( !irqn_valid( irqn ) )
            return -1;

        GIC_SetPendingIRQ( IRQn_Type{ irqn } );

        return 0;
    }

    uint32_t IRQ_GetPending( IRQn_ID_t irqn ) {
        return irqn_valid( irqn ) ? GIC_GetPendingIRQ( IRQn_Type{ irqn } ) : 0;
    }

    int32_t IRQ_ClearPending( IRQn_ID_t irqn ) {
        if ( !irqn_valid( irqn ) )
            return -1;

        GIC_ClearPendingIRQ( IRQn_Type{ irqn } );

        return 0;
    }

    int32_t IRQ_SetPriority( IRQn_ID_t irqn, uint32_t priority ) {
        if ( !irqn_valid( irqn ) )
            return -1;

        GIC_SetPriority( IRQn_Type{ irqn }, priority );

        return 0;
    }

    uint32_t IRQ_GetPriority( IRQn_ID_t irqn ) {
        return irqn_valid( irqn ) ? GIC_GetPriority( IRQn_Type{ irqn } ) : IRQ_PRIORITY_ERROR;
    }

    int32_t IRQ_SetPriorityMask( uint32_t priority ) {
        GIC_SetInterfacePriorityMask( priority );
        return 0;
    }

    uint32_t IRQ_GetPriorityMask() {
        return GIC_GetInterfacePriorityMask();
    }

    int32_t IRQ_SetPriorityGroupBits( uint32_t bits ) {
        if ( bits == IRQ_PRIORITY_Msk )
            bits = 7;

        if ( bits < 8 ) {
            GIC_SetBinaryPoint( 7 - bits );
            return 0;
        }

        return -1;
    }

    uint32_t IRQ_GetPriorityGroupBits() {
        return 7 - ( GIC_GetBinaryPoint() & 0x07U );
    }

} // extern "C"
