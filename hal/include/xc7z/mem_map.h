#ifndef MEM_MAP_H
#define MEM_MAP_H

#define OCM_SEC_LENG   ( 0x00010000 )

#define OCM0_LOW_BASE  ( 0x00000000 )
#define OCM0_LOW_LENG  ( OCM_SEC_LENG )
#define OCM0_LOW_END   ( OCM0_LOW_BASE + OCM0_LOW_LENG )

#define OCM1_LOW_BASE  ( OCM0_LOW_END )
#define OCM1_LOW_LENG  ( OCM_SEC_LENG )
#define OCM1_LOW_END   ( OCM1_LOW_BASE + OCM1_LOW_LENG )

#define OCM2_LOW_BASE  ( OCM1_LOW_END )
#define OCM2_LOW_LENG  ( OCM_SEC_LENG )
#define OCM2_LOW_END   ( OCM2_LOW_BASE + OCM2_LOW_LENG )

#define OCM_LOW_BASE   ( OCM0_LOW_BASE )
#define OCM_LOW_END    ( OCM2_LOW_END )
#define OCM_LOW_LENG   ( OCM_LOW_END - OCM_LOW_BASE )

#define DDR_BASE       ( 0x00000000 )
#define DDR_END        ( 0x40000000 )
#define DDR_LENG       ( DDR_END - DDR_BASE )

#define PL0_BASE       ( 0x40000000 )
#define PL0_END        ( 0x80000000 )
#define PL0_LENG       ( PL0_END - PL0_BASE )

#define PL1_BASE       ( 0x80000000 )
#define PL1_END        ( 0xC0000000 )
#define PL1_LENG       ( PL1_END - PL1_BASE )

#define IOP_BASE       ( 0xE0000000 )
#define IOP_END        ( 0xE0300000 )
#define IOP_LENG       ( IOP_END - IOP_BASE )

#define SMC_BASE       ( 0xE1000000 )
#define SMC_END        ( 0xE6000000 )
#define SMC_LENG       ( SMC_END - SMC_BASE )

#define SLCR_BASE      ( 0xF8000000 )
#define SLCR_END       ( 0xF800C000 )
#define SLCR_LENG      ( SLCR_END - SLCR_BASE )

#define PS_BASE        ( 0xF8001000 )
#define PS_END         ( 0xF8810000 )
#define PS_LENG        ( PS_END - PS_BASE )

#define CPU_BASE       ( 0xF8900000 )
#define CPU_END        ( 0xF8F03000 )
#define CPU_LENG       ( CPU_END - CPU_BASE )

#define QSPI_BASE      ( 0xFC000000 )
#define QSPI_END       ( 0xFE000000 )
#define QSPI_LENG      ( QSPI_END - QSPI_BASE )

#define OCM0_HIGH_BASE ( 0xFFFC0000 )
#define OCM0_HIGH_LENG ( OCM_SEC_LENG )
#define OCM0_HIGH_END  ( OCM0_HIGH_BASE + OCM0_HIGH_LENG )

#define OCM1_HIGH_BASE ( OCM0_HIGH_END )
#define OCM1_HIGH_LENG ( OCM_SEC_LENG )
#define OCM1_HIGH_END  ( OCM1_HIGH_BASE + OCM1_HIGH_LENG )

#define OCM2_HIGH_BASE ( OCM1_HIGH_END )
#define OCM2_HIGH_LENG ( OCM_SEC_LENG )
#define OCM2_HIGH_END  ( OCM2_HIGH_BASE + OCM2_HIGH_LENG )

#define OCM3_HIGH_BASE ( OCM2_HIGH_END )
#define OCM3_HIGH_LENG ( OCM_SEC_LENG )
#define OCM3_HIGH_END  ( OCM3_HIGH_BASE + OCM3_HIGH_LENG )

#define OCM_HIGH_BASE  ( OCM0_HIGH_BASE )
#define OCM_HIGH_END   ( OCM3_HIGH_END )
#define OCM_HIGH_LENG  ( OCM_HIGH_END - OCM_HIGH_BASE )

#endif // #ifndef MEM_MAP_H
