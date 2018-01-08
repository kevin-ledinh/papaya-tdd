#include "dev__fifo.h"
#include <string.h>

static int fifo_buf[ MAX_FIFO_LEN ];

void dev__fifo_init( void )
{
    memset( fifo_buf , 0 , MAX_FIFO_LEN * sizeof( int ) );
}

void dev__fifo_put( int value )
{
    fifo_buf[ 0 ] = value;
}

int dev__fifo_get( void )
{
    return fifo_buf[ 0 ];
}

/* This function should only be used for testing purpose only */
int * dev__fifo_get_fifo_address( void )
{
    return fifo_buf;
}