/*============================================================================
@brief A C source for lighting controller spy
------------------------------------------------------------------------------
<!-- Written by Andy Ackland -->
<!-- Copyright (C) 2013 All rights reserved -->
============================================================================*/

/*----------------------------------------------------------------------------
  @brief
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  include files
----------------------------------------------------------------------------*/
#include "dev__light_scheduler_spy.h"

/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  macros
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  global variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  static variables
----------------------------------------------------------------------------*/
static int dev__light_scheduler_spy_last_id;
static int dev__light_scheduler_spy_last_state;

/*----------------------------------------------------------------------------
  public functions
----------------------------------------------------------------------------*/

/*============================================================================
@brief The double initialization
------------------------------------------------------------------------------
@note
============================================================================*/
void dev__light_ctrl_init( void )
{
    dev__light_scheduler_spy_last_id = LIGHT_ID_UNKNOWN;
    dev__light_scheduler_spy_last_state = LIGHT_STATE_UNKNOWN;
}

/*============================================================================
@brief Switch a dummy LED on
------------------------------------------------------------------------------
@note
============================================================================*/
void dev__light_ctrl_on( int id )
{
    dev__light_scheduler_spy_last_id = id;
    dev__light_scheduler_spy_last_state = LIGHT_ON;
}

/*============================================================================
@brief Switch a dummy LED off
------------------------------------------------------------------------------
@note
============================================================================*/
void dev__light_ctrl_off( int id )
{
    dev__light_scheduler_spy_last_id = id;
    dev__light_scheduler_spy_last_state = LIGHT_OFF;
}

/*============================================================================
@brief Return the LED ID
------------------------------------------------------------------------------
@note
============================================================================*/
int dev__light_ctrl_spy_get_last_id( void )
{
    return dev__light_scheduler_spy_last_id;
}

/*============================================================================
@brief Return the LED state
------------------------------------------------------------------------------
@note
============================================================================*/
int dev__light_ctrl_spy_get_last_state( void )
{
    return dev__light_scheduler_spy_last_state;
}

/*============================================================================
@brief Return the LED state
------------------------------------------------------------------------------
@note
============================================================================*/
void dev__light_ctrl_deinit( void )
{}
/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/