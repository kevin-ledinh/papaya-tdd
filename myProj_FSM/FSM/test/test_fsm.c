#include "unity.h"
#include "fsm.h"
#include "test_fsm_data.h"
#include <stdbool.h>

static void dummy_on_entry( void );
static void dummy_on_exit( void );
static void dummy_on_yield( void );
static void fsm__transition_on_signal_1( void );
static void fsm__transition_on_signal_2( void );
static void fsm__transition_on_signal_3( void );
static void fsm__transition_on_signal_4( void );
static void fsm__transition_on_signal_5( void );

static const fsm__transition_table_t fsm__transition_table_state_1[ fsm__transition_signal_id_number_of ] = 
{
    fsm__transition_on_signal_1,
    fsm__transition_on_signal_2,
    fsm__transition_on_signal_3,
    fsm__transition_on_signal_4,
    fsm__transition_on_signal_5
};
static const fsm__transition_table_t fsm__transition_table_state_2[ fsm__transition_signal_id_number_of ] = 
{
    fsm__transition_on_signal_1,
    fsm__transition_on_signal_2,
    fsm__transition_on_signal_3,
    fsm__transition_on_signal_4,
    fsm__transition_on_signal_5
};
static const fsm__transition_table_t fsm__transition_table_state_3[ fsm__transition_signal_id_number_of ] = 
{
    fsm__transition_on_signal_1,
    fsm__transition_on_signal_2,
    fsm__transition_on_signal_3,
    fsm__transition_on_signal_4,
    fsm__transition_on_signal_5
};

static const fsm__state_table_t fsm__state_table[ fsm__state_id_number_of ] = 
{
    /*transition_table                  on_entry                on_exit                 on_yield */
    { fsm__transition_table_state_1 ,   dummy_on_entry ,        dummy_on_exit ,         dummy_on_yield },
    { fsm__transition_table_state_2 ,   dummy_on_entry ,        dummy_on_exit ,         dummy_on_yield },
    { fsm__transition_table_state_3 ,   dummy_on_entry ,        dummy_on_exit ,         dummy_on_yield }
};

static fsm_t fsm;
static bool on_entry_is_called[ fsm__state_id_number_of ];
static bool on_exit_is_called[ fsm__state_id_number_of ];
static bool on_yield_is_called[ fsm__state_id_number_of ];
static bool on_transition_signal_is_called[ fsm__state_id_number_of ][ fsm__transition_signal_id_number_of ];

static void dummy_on_entry( void )
{
    on_entry_is_called[ fsm.state ] = true;
}

static void dummy_on_exit( void )
{
    on_exit_is_called[ fsm.state ] = true;
}

static void dummy_on_yield( void )
{
    on_yield_is_called[ fsm.state ] = true;
    // Post a signal to exit from fsm_pend()
    fsm__post( & fsm , fsm__transition_signal_id_1 );
}

static void fsm__transition_on_signal_1( void )
{
    on_transition_signal_is_called[ fsm.state ][ fsm__transition_signal_id_1 ] = true;
}

static void fsm__transition_on_signal_2( void )
{
    on_transition_signal_is_called[ fsm.state ][ fsm__transition_signal_id_2 ] = true;
}

static void fsm__transition_on_signal_3( void )
{
    on_transition_signal_is_called[ fsm.state ][ fsm__transition_signal_id_3 ] = true;
}

static void fsm__transition_on_signal_4( void )
{
    on_transition_signal_is_called[ fsm.state ][ fsm__transition_signal_id_4 ] = true;
}

static void fsm__transition_on_signal_5( void )
{
    on_transition_signal_is_called[ fsm.state ][ fsm__transition_signal_id_5 ] = true;
}

void setUp(void)
{
    fsm__init( & fsm , fsm__transition_signal_id_number_of , fsm__state_id_number_of , fsm__state_table , fsm__state_id_1 );
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

void test_fsm_PostASingleSignal(void)
{
    fsm__post( & fsm , fsm__transition_signal_id_1 );
    fsm__signal_sets_t test_sets = 0 | ( 1 << fsm__transition_signal_id_1 );    
    TEST_ASSERT_EQUAL_INT( test_sets , fsm.signal_sets );
}

void test_fsm_PostMultipleSignals(void)
{
    fsm__post( & fsm , fsm__transition_signal_id_1 );
    fsm__post( & fsm , fsm__transition_signal_id_5 );
    fsm__signal_sets_t test_sets = 0 | ( 1 << fsm__transition_signal_id_1 ) | ( 1 << fsm__transition_signal_id_5 ); 
    TEST_ASSERT_EQUAL_INT( test_sets , fsm.signal_sets );
}

void test_fsm_PostOutofBoundSignalShouldReturnZero(void)
{
    fsm__post( & fsm , fsm__transition_signal_id_number_of + 5 );
    TEST_ASSERT_EQUAL_INT( 0 , fsm.signal_sets );
}

void test_fsm_ChangeState(void)
{
    fsm__change_state( & fsm , fsm__state_id_2 );
    TEST_ASSERT_EQUAL_INT( fsm__state_id_2 , fsm.state );    
}

void test_fsm_InvalidStateShouldBeZero(void)
{
    fsm__change_state( & fsm , fsm__state_id_number_of );
    TEST_ASSERT_EQUAL_INT( 0 , fsm.state );
}

void test_fsm_CheckPendingSignalIsCorrect(void)
{
    fsm__post( & fsm , fsm__transition_signal_id_1 );
    fsm__post( & fsm , fsm__transition_signal_id_5 );
    
    fsm__signal_sets_t test_sets = 0 | ( 1 << fsm__transition_signal_id_1 ) | ( 1 << fsm__transition_signal_id_5 ); 
    TEST_ASSERT_EQUAL_INT( test_sets , fsm__pend( & fsm ) );
}

void test_fsm_CheckOnYieldIsCalledWhenThereIsNoSignal(void)
{
    on_yield_is_called[ fsm.state ] = false;
    fsm__pend( & fsm );
    TEST_ASSERT_TRUE( on_yield_is_called[ fsm.state ] );
}

void test_fsm_CheckOnExitIsCalledWhenChangeState(void)
{
    fsm__state_t prev_state = fsm.state;
    on_exit_is_called[ prev_state ] = false;
    fsm__change_state( & fsm , fsm__state_id_2 );
    TEST_ASSERT_TRUE( on_exit_is_called[ prev_state ] );
}

void test_fsm_CheckOnEntryIsCalledWhenChangeState(void)
{
    on_entry_is_called[ fsm__state_id_2 ] = false;
    fsm__change_state( & fsm , fsm__state_id_2 );
    TEST_ASSERT_TRUE( on_entry_is_called[ fsm__state_id_2 ] );
}

void test_fsm_SendASingleSignalInTheSameState(void)
{
    on_transition_signal_is_called[ fsm.state ][ fsm__transition_signal_id_1 ] = false;
    fsm__post( & fsm , fsm__transition_signal_id_1 );
    fsm__despatch( & fsm , fsm__pend( & fsm ) );
    TEST_ASSERT_TRUE( on_transition_signal_is_called[ fsm.state ][ fsm__transition_signal_id_1 ] );
}

void test_fsm_SendMultipleSignalsInTheSameState(void)
{
    on_transition_signal_is_called[ fsm.state ][ fsm__transition_signal_id_1 ] = false;
    on_transition_signal_is_called[ fsm.state ][ fsm__transition_signal_id_3 ] = false;
    fsm__post( & fsm , fsm__transition_signal_id_1 );
    fsm__post( & fsm , fsm__transition_signal_id_3 );
    fsm__despatch( & fsm , fsm__pend( & fsm ) );
    TEST_ASSERT_TRUE( on_transition_signal_is_called[ fsm.state ][ fsm__transition_signal_id_1 ] );
    TEST_ASSERT_TRUE( on_transition_signal_is_called[ fsm.state ][ fsm__transition_signal_id_3 ] );
}

void test_fsm_ChangeStateAndSendSignal(void)
{
    fsm__state_t prev_state = fsm.state;
    on_transition_signal_is_called[ prev_state ][ fsm__transition_signal_id_1 ] = false;
    on_transition_signal_is_called[ fsm__state_id_3 ][ fsm__transition_signal_id_1 ] = false;
    fsm__change_state( & fsm , fsm__state_id_3 );
    fsm__post( & fsm , fsm__transition_signal_id_1 );
    fsm__despatch( & fsm , fsm__pend( & fsm ) );
    TEST_ASSERT_FALSE( on_transition_signal_is_called[ prev_state ][ fsm__transition_signal_id_1 ] );
    TEST_ASSERT_TRUE( on_transition_signal_is_called[ fsm.state ][ fsm__transition_signal_id_1 ] );    
}