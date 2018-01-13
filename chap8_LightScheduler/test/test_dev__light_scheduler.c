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
    TEST_ASSERT_EQUAL_INT(LIGHT_ID_UNKNOWN, dev__light_ctrl_spy_get_last_id());
    TEST_ASSERT_EQUAL_INT(LIGHT_STATE_UNKNOWN, dev__light_ctrl_spy_get_last_state());
}

void test_dev__light_scheduler_NoScheduleNothingHappens(void)
{
    fake_timer_service_set_day(MONDAY);
    fake_timer_service_set_minutes(100);
    
    dev__light_scheduler_wakeup();
    
    TEST_ASSERT_EQUAL_INT(LIGHT_ID_UNKNOWN, dev__light_ctrl_spy_get_last_id());
    TEST_ASSERT_EQUAL_INT(LIGHT_STATE_UNKNOWN, dev__light_ctrl_spy_get_last_state());
}

void test_dev__light_scheduler_ScheduleOnEverydayNotTimeYet(void)
{
    dev__light_scheduler_schedule_turn_on(3, EVERYDAY, 1200);
    fake_timer_service_set_day(MONDAY);
    fake_timer_service_set_minutes(1199);
    
    dev__light_scheduler_wakeup();
    
    TEST_ASSERT_EQUAL_INT(LIGHT_ID_UNKNOWN, dev__light_ctrl_spy_get_last_id());
    TEST_ASSERT_EQUAL_INT(LIGHT_STATE_UNKNOWN, dev__light_ctrl_spy_get_last_state());
}

void test_dev__light_scheduler_ScheduleOnEverydayItsTime(void)
{
    dev__light_scheduler_schedule_turn_on(3, EVERYDAY, 1200);
    fake_timer_service_set_day(MONDAY);
    fake_timer_service_set_minutes(1200);
    
    dev__light_scheduler_wakeup();
    
    TEST_ASSERT_EQUAL_INT(3, dev__light_ctrl_spy_get_last_id());
    TEST_ASSERT_EQUAL_INT(LIGHT_ON, dev__light_ctrl_spy_get_last_state());
}

void test_dev__light_scheduler_ScheduleOffEverydayItsTime(void)
{
    dev__light_scheduler_schedule_turn_off(3, EVERYDAY, 1200);
    fake_timer_service_set_day(MONDAY);
    fake_timer_service_set_minutes(1200);
    
    dev__light_scheduler_wakeup();
    
    TEST_ASSERT_EQUAL_INT(3, dev__light_ctrl_spy_get_last_id());
    TEST_ASSERT_EQUAL_INT(LIGHT_OFF, dev__light_ctrl_spy_get_last_state());
}
/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/
