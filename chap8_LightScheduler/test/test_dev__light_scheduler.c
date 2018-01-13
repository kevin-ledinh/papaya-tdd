/*============================================================================
@brief A C source template
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
#include "unity.h"
#include "dev__light_scheduler.h"
#include "dev__light_scheduler_spy.h"
#include "fake_timer_service.h"


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
static void setTimeTo(int day, int minuteOfDay);
static void checkLightState(int id, int level);
/*----------------------------------------------------------------------------
  global variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  static variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  public functions
----------------------------------------------------------------------------*/

/*============================================================================
@brief Initialisation function which is called before every tests
------------------------------------------------------------------------------
@note
============================================================================*/
void setUp(void)
{
    dev__light_ctrl_init();
    dev__light_scheduler_init();
}

/*============================================================================
@brief This function is called after every tests
------------------------------------------------------------------------------
@note
============================================================================*/
void tearDown(void)
{
    dev__light_scheduler_deinit();
    dev__light_ctrl_deinit();
}

/*============================================================================
@brief The start of test codes
------------------------------------------------------------------------------
@note
============================================================================*/
void test_dev__light_scheduler_NoChangeToLightsDuringInitialization(void)
{
    checkLightState( LIGHT_ID_UNKNOWN , LIGHT_STATE_UNKNOWN );
}

void test_dev__light_scheduler_NoScheduleNothingHappens(void)
{
    setTimeTo( MONDAY , 100 );
    
    dev__light_scheduler_wakeup();
    
    checkLightState( LIGHT_ID_UNKNOWN , LIGHT_STATE_UNKNOWN );
}

void test_dev__light_scheduler_ScheduleOnEverydayNotTimeYet(void)
{
    dev__light_scheduler_schedule_turn_on(3, EVERYDAY, 1200);
    setTimeTo( MONDAY , 1199 );
    
    dev__light_scheduler_wakeup();
    
    checkLightState( LIGHT_ID_UNKNOWN , LIGHT_STATE_UNKNOWN );
}

void test_dev__light_scheduler_ScheduleOnEverydayItsTime(void)
{
    dev__light_scheduler_schedule_turn_on(3, EVERYDAY, 1200);
    setTimeTo( MONDAY , 1200 );
    
    dev__light_scheduler_wakeup();
    
    checkLightState( 3 , LIGHT_ON );
}

void test_dev__light_scheduler_ScheduleOffEverydayItsTime(void)
{
    dev__light_scheduler_schedule_turn_off(3, EVERYDAY, 1200);
    setTimeTo( MONDAY , 1200 );
    
    dev__light_scheduler_wakeup();
    checkLightState( 3 , LIGHT_OFF );
}

void test_dev__light_scheduler_ScheduleTuesdayButItsMonday(void)
{
    dev__light_scheduler_schedule_turn_on(3, TUESDAY, 1200);
    setTimeTo(MONDAY, 1200);
    dev__light_scheduler_wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

void test_dev__light_scheduler_ScheduleTuesdayAndItsTuesday(void)
{
    dev__light_scheduler_schedule_turn_on(3, TUESDAY, 1200);
    setTimeTo(TUESDAY, 1200);
    dev__light_scheduler_wakeup();
    checkLightState(3, LIGHT_ON);
}

void test_dev__light_scheduler_ScheduleWeekendItsFriday(void)
{
    dev__light_scheduler_schedule_turn_on(3, WEEKEND, 1200);
    setTimeTo(FRIDAY, 1200);
    dev__light_scheduler_wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

void test_dev__light_scheduler_ScheduleWeekendItsSat(void)
{
    dev__light_scheduler_schedule_turn_on(3, WEEKEND, 1200);
    setTimeTo(SATURDAY, 1200);
    dev__light_scheduler_wakeup();
    checkLightState(3, LIGHT_ON);
}

void test_dev__light_scheduler_ScheduleWeekendItsSun(void)
{
    dev__light_scheduler_schedule_turn_on(3, WEEKEND, 1200);
    setTimeTo(SUNDAY, 1200);
    dev__light_scheduler_wakeup();
    checkLightState(3, LIGHT_ON);
}

void test_dev__light_scheduler_ScheduleWeekendItsMonday(void)
{
    dev__light_scheduler_schedule_turn_on(3, WEEKEND, 1200);
    setTimeTo(MONDAY, 1200);
    dev__light_scheduler_wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

void test_dev__light_scheduler_CreateStartsOneMinuteAlarm(void)
{
    TEST_ASSERT_EQUAL_PTR( dev__light_scheduler_wakeup , fake_timer_service_get_alarm_callback());
    TEST_ASSERT_EQUAL_INT(60, fake_timer_service_get_alarm_period());
}
/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/
static void setTimeTo(int day, int minuteOfDay)
{
    fake_timer_service_set_day(day);
    fake_timer_service_set_minutes(minuteOfDay);
}

static void checkLightState(int id, int level)
{
    TEST_ASSERT_EQUAL_INT(id, dev__light_ctrl_spy_get_last_id());
    TEST_ASSERT_EQUAL_INT(level, dev__light_ctrl_spy_get_last_state());
}
/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/
