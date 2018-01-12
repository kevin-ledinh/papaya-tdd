#include "unity.h"
#include "fsm.h"
#include "test_fsm_data.h"

static const fsm__transition_table_t fsm__transition_table_state_1[ fsm__transition_signal_id_number_of ] = 
{
    fsm__none,
    fsm__none,
    fsm__none,
    fsm__none,
    fsm__none
};
static const fsm__transition_table_t fsm__transition_table_state_2[ fsm__transition_signal_id_number_of ] = 
{
    fsm__none,
    fsm__none,
    fsm__none,
    fsm__none,
    fsm__none
};
static const fsm__transition_table_t fsm__transition_table_state_3[ fsm__transition_signal_id_number_of ] = 
{
    fsm__none,
    fsm__none,
    fsm__none,
    fsm__none,
    fsm__none
};

static const fsm__state_table_t fsm__state_table[ fsm__state_id_number_of ] = 
{
    /*transition_table                  on_entry            on_exit             on_yield */
    { fsm__transition_table_state_1 ,   fsm__none ,         fsm__none ,         fsm__none },
    { fsm__transition_table_state_2 ,   fsm__none ,         fsm__none ,         fsm__none },
    { fsm__transition_table_state_3 ,   fsm__none ,         fsm__none ,         fsm__none }
};

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
    TEST_ASSERT_EQUAL_UINT( 0 , fsm.signal_sets );
    
    for(int i = 0 ; i < fsm__state_id_number_of ; i ++ )
    {
        TEST_ASSERT_NOT_NULL( fsm.state_table[ i ].transition_table );
        TEST_ASSERT_NOT_NULL( fsm.state_table[ i ].on_entry );
        TEST_ASSERT_NOT_NULL( fsm.state_table[ i ].on_exit );
        TEST_ASSERT_NOT_NULL( fsm.state_table[ i ].on_yield );
        for( int y = 0 ; y < fsm__transition_signal_id_number_of ; y ++ )
        {
            TEST_ASSERT_NOT_NULL( fsm.state_table[ i ].transition_table[ y ].action );

        }
    }
}
