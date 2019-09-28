#include <string.h>

int memcmp( const void* s1, const void* s2, size_t n ) {
    const unsigned char* puc1 = (const unsigned char*)s1;
    const unsigned char* puc2 = (const unsigned char*)s2;

    for ( size_t i = 0; i < n; ++i ) {
        if ( puc1[i] > puc2[i] ) {
            return 1;
        } else if ( *puc1 < *puc2 ) {
            return -1;
        }
    }

    return 0;
}

void* memset( void* ptr, int value, size_t num ) {
    unsigned char* puc = (unsigned char*)ptr;

    for ( size_t i = 0; i < num; ++i ) {
        puc[i] = value;
    }

    return ptr;
}

void* memcpy( void* destination, const void* source, size_t num ) {
    unsigned char* pdst = (unsigned char*)destination;
    const unsigned char* psrc = (const unsigned char*)source;

    for ( size_t i = 0; i < num; ++i ) {
        pdst[i] = psrc[i];
    }

    return destination;
}

void* memmove( void* destination, const void* source, size_t num ) {
    if ( destination < source ) {
        return memcpy( destination, source, num );
    } else {
        for ( size_t i = num-1; i >= 0; --i ) {
            unsigned char* pdst = (unsigned char*)destination;
            const unsigned char* psrc = (const unsigned char*)source;

            pdst[i] = psrc[i];
        }
    }

    return destination;
}
