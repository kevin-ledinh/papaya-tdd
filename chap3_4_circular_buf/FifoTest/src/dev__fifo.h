/*============================================================================
@brief A C source header for a circular buffer
------------------------------------------------------------------------------
<!-- Written by Kevin (Phuc) Le Dinh -->
<!-- Copyright (C) 2018 All rights reserved -->
============================================================================*/

#ifndef _DEV__FIFO_H
#define _DEV__FIFO_H

/*----------------------------------------------------------------------------
  @brief
	This circular buffer takes care of writing and reading the binary log data
	from/to the SPI flash memory
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  nested include files
----------------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>

/*----------------------------------------------------------------------------
  macros
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  extern variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
void dev__fifo_init( void );
void dev__fifo_deinit( void );
void dev__fifo_put( uint8_t * value , uint8_t size);
uint8_t dev__fifo_get( void );
int dev__fifo_get_current_size();
bool dev__fifo_is_full( void );
bool dev__fifo_is_empty( void );

/*----------------------------------------------------------------------------
  compile time checks
----------------------------------------------------------------------------*/

#endif // _DEV__FIFO_H

/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/
