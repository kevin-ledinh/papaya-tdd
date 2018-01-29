/*******************************************************************************
 * A C source file written by ....
 *    Copyright 2018
 ******************************************************************************/

/*******************************************************************************
 *    INCLUDED FILES
 ******************************************************************************/
#include "dev__fifo.h"
#ifdef UNIT_TEST    
    #include "hw__fake_memory.h"
#endif
#include <string.h>

/*******************************************************************************
 *    DEFINITIONS
 ******************************************************************************/
#ifdef UNIT_TEST    
    #define DEV__FIFO_LOG_DATA_SIZE         MAX_FIFO_LEN
#else
    #define DEV__FIFO_LOG_DATA_START_ADDR   0x00000
    #define DEV__FIFO_LOG_DATA_END_ADDR     0x18000
    #define DEV__FIFO_LOG_DATA_SIZE         ( DEV__FIFO_LOG_DATA_END_ADDR - DEV__FIFO_LOG_DATA_START_ADDR )
#endif

#define DEV__FIFO_META_DATA_START_ADDR  DEV__FIFO_LOG_DATA_END_ADDR
#define DEV__FIFO_META_DATA_END_ADDR    0x19000
#define DEV__FIFO_META_DATA_SIZE        ( DEV__FIFO_META_DATA_END_ADDR - DEV__FIFO_META_DATA_START_ADDR )
 
/*******************************************************************************
 *    PRIVATE TYPES
 ******************************************************************************/
typedef struct dev__fifo_s
{
    uint32_t wr_addr;
    uint32_t rd_addr;
    uint16_t size;
#ifdef UNIT_TEST    
    uint8_t * fifo_addr;
#endif    
} dev__fifo_t;

/*******************************************************************************
 *    PRIVATE DATA
 ******************************************************************************/
static dev__fifo_t fifo;

/*******************************************************************************
 *    PROTOTYPES
 ******************************************************************************/
static void dev__fifo_increment_write_ptr( void );
static void dev__fifo_increment_read_ptr( void );
static void dev__fifo_increment_number_of_entries( void );
static void dev__fifo_update_read_ptr_when_buf_full( void );

 /*******************************************************************************
 *    PUBLIC FUNCTIONS
 ******************************************************************************/
 
/*****************************************************************************
 *  Function:
 *  Purpose:
*******************************************************************************/
void dev__fifo_init( void )
{
    fifo.wr_addr = 0;
    fifo.rd_addr = 0;
    fifo.size = 0;
#ifdef UNIT_TEST    
    fifo.fifo_addr = hw__fake_memory_init();
#endif    
}

/*****************************************************************************
 *  Function:
 *  Purpose:
*******************************************************************************/
void dev__fifo_deinit( void )
{
#ifdef UNIT_TEST    
    hw__fake_memory_deinit();
#endif    
}
/*****************************************************************************
 *  Function:
 *  Purpose: Put an element to the circular buffer
*******************************************************************************/
void dev__fifo_put( uint8_t * value , uint8_t size )
{
    if( ( DEV__FIFO_LOG_DATA_SIZE - fifo.size ) >= size )
    {
#ifdef UNIT_TEST    
        memcpy( fifo.fifo_addr + fifo.wr_addr , value , size );
#endif        
        fifo.wr_addr += size;
        fifo.size += size;
        if( fifo.wr_addr >= DEV__FIFO_LOG_DATA_SIZE)
        {
            fifo.wr_addr = 0;
        }
    }
}

/*****************************************************************************
 *  Function:
 *  Purpose: Get the current element of the circular buffer
*******************************************************************************/
uint8_t dev__fifo_get( void )
{
    uint8_t val = 0;
    if( fifo.size > 0 )
    {
#ifdef UNIT_TEST   
        val = fifo.fifo_addr[ fifo.rd_addr ++ ];
#endif
        fifo.size --;
        if( fifo.rd_addr >= DEV__FIFO_LOG_DATA_SIZE)
        {
            fifo.rd_addr = 0;
        }
    }
    return val;
}

/*****************************************************************************
 *  Function:
 *  Purpose: Get the number of element of the circular buffer
*******************************************************************************/
int dev__fifo_get_current_size()
{
    return fifo.size;
}

/*****************************************************************************
 *  Function:
 *  Purpose: Get the number of element of the circular buffer
*******************************************************************************/
bool dev__fifo_is_full( void )
{
    return ( fifo.size == DEV__FIFO_LOG_DATA_SIZE );
}

/*****************************************************************************
 *  Function:
 *  Purpose: Get the number of element of the circular buffer
*******************************************************************************/
bool dev__fifo_is_empty( void )
{
    return ( fifo.size == 0 );
}
/*******************************************************************************
 *    PRIVATE FUNCTIONS
 ******************************************************************************/

/*****************************************************************************
 *  Function:
 *  Purpose: Increment the write pointer and wrap around if needed
*******************************************************************************/
static void dev__fifo_increment_write_ptr( void )
{
    
}

/*****************************************************************************
 *  Function:
 *  Purpose: Increment the read pointer and wrap around if needed
*******************************************************************************/
static void dev__fifo_increment_read_ptr( void )
{
    
}

/*****************************************************************************
 *  Function:
 *  Purpose: Increment the number of entries
*******************************************************************************/
static void dev__fifo_increment_number_of_entries( void )
{
    
}

/*****************************************************************************
 *  Function:
 *  Purpose: Update the read pointer when the buffer is full
*******************************************************************************/
static void dev__fifo_update_read_ptr_when_buf_full( void )
{
    
}
