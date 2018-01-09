/*******************************************************************************
 * A C source file written by ....
 *    Copyright 2018
 ******************************************************************************/

/*******************************************************************************
 *    INCLUDED FILES
 ******************************************************************************/
#include "dev__fifo.h"
#include <string.h>

/*******************************************************************************
 *    DEFINITIONS
 ******************************************************************************/
 
/*******************************************************************************
 *    PRIVATE TYPES
 ******************************************************************************/
 
/*******************************************************************************
 *    PRIVATE DATA
 ******************************************************************************/
static int dev__fifo_buf[ MAX_FIFO_LEN ];
static int dev__fifo_wr_idx;
static int dev__fifo_rd_idx;
static int dev__fifo_number_of_entries;

/*******************************************************************************
 *    PROTOTYPES
 ******************************************************************************/

 /*******************************************************************************
 *    PUBLIC FUNCTIONS
 ******************************************************************************/
 
/*****************************************************************************
 *  Function:
 *  Purpose:
*******************************************************************************/
void dev__fifo_init( void )
{
    memset( dev__fifo_buf , 0 , MAX_FIFO_LEN * sizeof( int ) );
    dev__fifo_wr_idx = 0;
    dev__fifo_rd_idx = 0;
    dev__fifo_number_of_entries = 0;
}

/*****************************************************************************
 *  Function:
 *  Purpose: Put an element to the circular buffer
*******************************************************************************/
void dev__fifo_put( int value )
{
    dev__fifo_buf[ dev__fifo_wr_idx ] = value;
    
    if( ++ dev__fifo_number_of_entries >= MAX_FIFO_LEN )
    {
        dev__fifo_number_of_entries = MAX_FIFO_LEN;
    }
    
    if( ++ dev__fifo_wr_idx >= MAX_FIFO_LEN )
    {
        dev__fifo_wr_idx = 0;
    }
}

/*****************************************************************************
 *  Function:
 *  Purpose: Get the current element of the circular buffer
*******************************************************************************/
int dev__fifo_get( void )
{
    int result;
    if( dev__fifo_number_of_entries == MAX_FIFO_LEN )
    {
        dev__fifo_rd_idx = dev__fifo_wr_idx;
    }
    
    result = dev__fifo_buf[ dev__fifo_rd_idx ];
    
    dev__fifo_number_of_entries --;
    
    if( ++ dev__fifo_rd_idx >= MAX_FIFO_LEN )
    {
        dev__fifo_rd_idx = 0;
    }
    
    return result;
}

/*****************************************************************************
 *  Function:
 *  Purpose: Get the number of element of the circular buffer
*******************************************************************************/
int dev__fifo_get_available_entries()
{
    return dev__fifo_number_of_entries;
}

/*****************************************************************************
 *  Function:
 *  Purpose: Return the pointer to the internal buffer.
             This function should only be used for testing purpose only
*******************************************************************************/
/*  */
int * dev__fifo_get_fifo_address( void )
{
    return dev__fifo_buf;
}
/*******************************************************************************
 *    PRIVATE FUNCTIONS
 ******************************************************************************/

