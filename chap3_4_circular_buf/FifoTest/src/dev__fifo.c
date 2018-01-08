#include "dev__fifo.h"
#include <string.h>

void dev__fifo_init( int * buf , int size )
{
    memset( buf , 0 , size * sizeof( int ) );
}