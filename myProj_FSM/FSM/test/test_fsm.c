#include "unity.h"
#include "fsm.h"
#include "test_fsm_data.h"

static const fsm__state_table_t fsm__state_table[ fsm__state_id_number_of ] = {};

static fsm_t fsm;

void setUp(void)
{
}

void tearDown(void)
{
}

void test_fsm_CorrectDataAfterInitialisation(void)
{
    fsm__init( & fsm , fsm__transition_signal_id_number_of , fsm__state_id_number_of , fsm__state_table , fsm__state_id_1 );
    
    TEST_ASSERT_EQUAL_UINT( fsm__transition_signal_id_number_of , fsm.number_of_signals );
    TEST_ASSERT_EQUAL_UINT( fsm__state_id_number_of , fsm.number_of_states );
    TEST_ASSERT_EQUAL_PTR( fsm__state_table , fsm.state_table );
    TEST_ASSERT_EQUAL_UINT( fsm__state_id_1 , fsm.state );
}
