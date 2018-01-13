/*============================================================================
@brief A C source for a Lighting Scheduler
------------------------------------------------------------------------------
<!-- Written by Kevin Le Dinh -->
<!-- Copyright (C) 2018 All rights reserved -->
============================================================================*/

/*----------------------------------------------------------------------------
  @brief
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  include files
----------------------------------------------------------------------------*/
#include "dev__light_scheduler.h"
#include "dev__light_controller.h"
#include "timer_service.h"

/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/
enum dev__light_scheduler_event
{
    UNUSED,
    TURN_ON,
    TURN_OFF
};
/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/
typedef struct dev__light_scheduler_event_s
{
    int id;
    int event;
    int minuteOfDay;
    Day day;
} dev__light_scheduler_event_t;

/*----------------------------------------------------------------------------
  macros
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
static void dev__light_scheduler_schedule_event(int id, Day day, int minutes_of_day, int event);
static void dev__light_scheduler_process_event_due_now( Time * time, dev__light_scheduler_event_t * lightEvent );
static void dev__light_scheduler_operate_light(dev__light_scheduler_event_t * lightEvent);

/*----------------------------------------------------------------------------
  global variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  static variables
----------------------------------------------------------------------------*/
static dev__light_scheduler_event_t dev__light_scheduler_event;
/*----------------------------------------------------------------------------
  public functions
----------------------------------------------------------------------------*/

/*============================================================================
@brief
------------------------------------------------------------------------------
@note
============================================================================*/
void dev__light_scheduler_init( void )
{
    dev__light_scheduler_event.id = UNUSED;
}

/*============================================================================
@brief
------------------------------------------------------------------------------
@note
============================================================================*/
void dev__light_scheduler_deinit( void )
{}

/*============================================================================
@brief
------------------------------------------------------------------------------
@note
============================================================================*/
void dev__light_scheduler_wakeup( void )
{
    Time time;
    time_service_get_time(&time);
    
    dev__light_scheduler_process_event_due_now( & time , & dev__light_scheduler_event );
}

/*============================================================================
@brief
------------------------------------------------------------------------------
@note
============================================================================*/
void dev__light_scheduler_schedule_turn_on( int id , Day day , int minutes_of_day )
{
    dev__light_scheduler_schedule_event( id , day , minutes_of_day , TURN_ON );
}

/*============================================================================
@brief
------------------------------------------------------------------------------
@note
============================================================================*/
void dev__light_scheduler_schedule_turn_off( int id , Day day , int minutes_of_day )
{
    dev__light_scheduler_schedule_event( id , day , minutes_of_day , TURN_OFF );
}
/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/
/*============================================================================
@brief
------------------------------------------------------------------------------
@note
============================================================================*/
static void dev__light_scheduler_schedule_event(int id, Day day, int minutes_of_day, int event)
{
    dev__light_scheduler_event.id = id;
    dev__light_scheduler_event.event = event;
    dev__light_scheduler_event.minuteOfDay = minutes_of_day;
    dev__light_scheduler_event.day = day;
}

/*============================================================================
@brief
------------------------------------------------------------------------------
@note
============================================================================*/
static void dev__light_scheduler_process_event_due_now( Time * time, dev__light_scheduler_event_t * lightEvent )
{
    int reactionDay = lightEvent->day;
    
    if (lightEvent->id == UNUSED)
    {
        return;
    }
    if ( ( lightEvent->day != EVERYDAY ) && ( reactionDay != time->day ) )
    {
        if( ! ( ( lightEvent->day == WEEKEND ) && ( ( time->day == SATURDAY ) || ( time->day == SUNDAY ) ) ) )
        {
            return;
        }
    }
    
    if (lightEvent->minuteOfDay != time->minuteOfDay)
    {
        return;
    }
    
    
    dev__light_scheduler_operate_light( lightEvent );
}

/*============================================================================
@brief
------------------------------------------------------------------------------
@note
============================================================================*/
static void dev__light_scheduler_operate_light(dev__light_scheduler_event_t * lightEvent)
{
    if (lightEvent->event == TURN_ON)
    {
        dev__light_ctrl_on(lightEvent->id);
    }
    else if (lightEvent->event == TURN_OFF)
    {
        dev__light_ctrl_off(lightEvent->id);
    }
}
/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/
