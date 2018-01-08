#include "dev__fifo.h"
#include <string.h>

static int fifo_buf[ MAX_FIFO_LEN ];

void dev__fifo_init( void )
{
    memset( fifo_buf , 0 , MAX_FIFO_LEN * sizeof( int ) );
}

/* This function should only be used for testing purpose only */
int * dev__fifo_get_fifo_address( void )
{
    return fifo_buf;
}