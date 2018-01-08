#include "dev__fifo.h"
#include <string.h>

static int fifo_buf[ MAX_FIFO_LEN ];

int * dev__fifo_init( void )
{
    memset( fifo_buf , 0 , MAX_FIFO_LEN * sizeof( int ) );
}