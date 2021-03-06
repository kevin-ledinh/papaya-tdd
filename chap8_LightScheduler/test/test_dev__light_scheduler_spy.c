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

/*----------------------------------------------------------------------------
  public functions
----------------------------------------------------------------------------*/

/*============================================================================
@brief Initilisation code before running every tests
------------------------------------------------------------------------------
@note
============================================================================*/
void setUp(void)
{
    dev__light_ctrl_init();
}

/*============================================================================
@brief Runs after every tests
------------------------------------------------------------------------------
@note
============================================================================*/
void tearDown(void)
{
}

void test_dev__light_scheduler_spy_Create(void)
{
    TEST_ASSERT_EQUAL_INT(LIGHT_ID_UNKNOWN, dev__light_ctrl_spy_get_last_id());
    TEST_ASSERT_EQUAL_INT(LIGHT_STATE_UNKNOWN, dev__light_ctrl_spy_get_last_state());
}

void test_dev__light_scheduler_spy_RememberTheLastLightIdControlled(void)
{
    dev__light_ctrl_on(10);
    TEST_ASSERT_EQUAL_INT(10, dev__light_ctrl_spy_get_last_id());
    TEST_ASSERT_EQUAL_INT(LIGHT_ON, dev__light_ctrl_spy_get_last_state());
}
/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/
