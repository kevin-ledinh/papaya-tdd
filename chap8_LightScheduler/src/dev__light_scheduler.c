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
#include <stdbool.h>

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
static bool dev__light_scheduler_does_light_respond_today( Time * time, int reaction_day );

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
    
    time_service_set_periodic_alarm_in_seconds( 60, dev__light_scheduler_wakeup );
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
    if (lightEvent->id == UNUSED)
    {
        return;
    }
    if ( ! dev__light_scheduler_does_light_respond_today( time , lightEvent->day ) )
    {
        return;
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

/*============================================================================
@brief
------------------------------------------------------------------------------
@note
============================================================================*/
static bool dev__light_scheduler_does_light_respond_today( Time * time, int reaction_day )
{
    int today = time->day;
    if (reaction_day == EVERYDAY)
    {
        return true;
    }
    if (reaction_day == today)
    {
        return true;
    }
    if (reaction_day == WEEKEND && (SATURDAY == today || SUNDAY == today))
    {
        return true;
    }
    if (reaction_day == WEEKDAY && today >= MONDAY && today <= FRIDAY)
    {
        return true;
    }   
    return false;
}
/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/
