#ifndef MEM_LOAD_H
#define MEM_LOAD_H

#include "mem_map.h"

#define EXROM_BASE ( OCM_LOW_BASE )
#define EXROM_END  ( EXROM_BASE + 0x00004000 )
#define EXROM_LENG ( EXROM_END - EXROM_BASE )

#define DAROM_BASE ( EXROM_END )
#define DAROM_END  ( DAROM_BASE + 0x00004000 )
#define DAROM_LENG ( DAROM_END - DAROM_BASE )

#define DARAM_BASE ( DAROM_END )
#define DARAM_END  ( DARAM_BASE + 0x00004000 )
#define DARAM_LENG ( DARAM_END - DARAM_BASE )

#define PGRAM_BASE ( DARAM_END )
#define PGRAM_END  ( PGRAM_BASE )
#define PGRAM_LENG ( PGRAM_END - PGRAM_BASE )

#endif // #ifndef MEM_LOAD_H
