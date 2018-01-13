/*============================================================================
@brief A C source header for the fake timer service
------------------------------------------------------------------------------
<!-- Written by Kevin Le Dinh -->
<!-- Copyright (C) 2018 All rights reserved -->
============================================================================*/

#ifndef _FAKE_TIMER_SERVICE_H
#define _FAKE_TIMER_SERVICE_H

/*----------------------------------------------------------------------------
  @brief

----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  nested include files
----------------------------------------------------------------------------*/
#include "dev__light_scheduler.h"

/*----------------------------------------------------------------------------
  macros
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/
enum {TIME_UNKNOWN = -1};
/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  extern variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
void fake_timer_service_set_day( Day day );
void fake_timer_service_set_minutes( int minutes );
/*----------------------------------------------------------------------------
  compile time checks
----------------------------------------------------------------------------*/

#endif // _FAKE_TIMER_SERVICE_H

/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/


