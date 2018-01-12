/*******************************************************************************
 * A C source file written by Kevin Le Dinh
 *    Copyright 2018
 ******************************************************************************/

/*******************************************************************************
 *    INCLUDED FILES
 ******************************************************************************/
 #include "fsm.h"
 
/*******************************************************************************
 *    DEFINITIONS
 ******************************************************************************/
 
/*******************************************************************************
 *    PRIVATE TYPES
 ******************************************************************************/
 
/*******************************************************************************
 *    PRIVATE DATA
 ******************************************************************************/

/*******************************************************************************
 *    PROTOTYPES
 ******************************************************************************/
static fsm__signal_sets_t fsm__pend( fsm_t * self );
static void fsm__despatch( fsm_t * self , fsm__signal_sets_t signals );

 /*******************************************************************************
 *    PUBLIC FUNCTIONS
 ******************************************************************************/
 
 /*****************************************************************************
  *  Function:
  *  Purpose:
 *******************************************************************************/
void fsm__init( fsm_t * self , uint8_t total_signals , uint8_t total_states , const fsm__state_table_t * state_table , fsm__state_t initial_state )
{
    self -> number_of_signals = total_signals;
    self -> number_of_states = total_states;
    self -> state_table = state_table;
    self -> state = initial_state;
    self -> signal_sets = 0;
}
 
 /*****************************************************************************
  *  Function:
  *  Purpose: Dummy function without any operation.
 *******************************************************************************/
void fsm__none( void )
{
}
 
 /*****************************************************************************
  *  Function:
  *  Purpose: Insert a signal into the current signal set
 *******************************************************************************/
void fsm__post( fsm_t * self , uint8_t signal_idx )
{
    if( signal_idx < ( self -> number_of_signals ) )
    {
        self -> signal_sets |= ( 1 << signal_idx );
    }
}

/*****************************************************************************
  *  Function:
  *  Purpose: Change the FSM to a new state
 *******************************************************************************/
void fsm__change_state( fsm_t * self , fsm__state_t state_id )
{
    if( state_id < ( self -> number_of_states ) )
    {
        self -> state_table[ self -> state ].on_exit();
        self -> state = state_id;
        self -> state_table[ self -> state ].on_entry();
    }
}

/*****************************************************************************
  *  Function:
  *  Purpose: The main loop of the FSM is here
 *******************************************************************************/
void fsm__main( fsm_t * self )
{
    while(1)
    {
        fsm__signal_sets_t signals = fsm__pend( self );        
        fsm__despatch( self , signals );
    }
}
/*******************************************************************************
 *    PRIVATE FUNCTIONS
 ******************************************************************************/
 
/*****************************************************************************
  *  Function:
  *  Purpose: Look into the signal set
 *******************************************************************************/
static fsm__signal_sets_t fsm__pend( fsm_t * self )
{
    // Disable Interrupt here, ready to sleep
    while( self -> signal_sets == 0 )
    {
        self -> state_table[ self -> state ].on_yield();
        
        //Enable Interrupt briefly to receive signals
        //Disable Interrupt, ready to sleep again
    }
    
    //Enter critical section to prevent the signal being changed here.
    fsm__signal_sets_t signals = self -> signal_sets;
    self -> signal_sets = 0;
    //exit critical section
    
    //Enable Interrupt
    return signals;
}

/*****************************************************************************
  *  Function:
  *  Purpose: Perform an action when the receive a signal
 *******************************************************************************/
static void fsm__despatch( fsm_t * self , fsm__signal_sets_t signals )
{
   for( int i = 0 ; i < ( self -> number_of_signals ) ; i ++ )
   {
       if( ( ( signals >> i ) & 1 ) == 1 )
       {
           self -> state_table[ self -> state ].transition_table[ i ].action();
       }
   }
}
