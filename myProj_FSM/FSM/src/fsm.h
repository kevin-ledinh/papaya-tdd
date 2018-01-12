/*******************************************************************************
 * A C header file written by Kevin Le Dinh
 *    Copyright 2018
 ******************************************************************************/
/**************************************************************************
*   Briefs:
*
*
*****************************************************************************/

#ifndef _FSM_H
#define _FSM_H

/*******************************************************************************
 *    INCLUDED FILES
 ******************************************************************************/
#include <stdint.h>
 
/*******************************************************************************
 *    DEFINITIONS
 ******************************************************************************/
 
/*******************************************************************************
 *    TYPES
 ******************************************************************************/
typedef uint8_t fsm__state_t;
typedef uint32_t fsm__signal_sets_t;
typedef void ( * fsm__action_t )      ( void );
typedef void ( * fsm__on_yield_t )    ( void );

typedef struct fsm__transition_table_s
{
    fsm__action_t action; 
} fsm__transition_table_t;

typedef struct fsm__state_table_s
{
    const fsm__transition_table_t * transition_table;
    fsm__action_t   on_entry;
    fsm__action_t   on_exit;
    fsm__on_yield_t on_yield;
}fsm__state_table_t;
 
 typedef struct fsm_s
{
    uint8_t number_of_signals;
    uint8_t number_of_states;
    const fsm__state_table_t * state_table;
    fsm__state_t state;
    volatile fsm__signal_sets_t signal_sets;
} fsm_t;
/*******************************************************************************
 *    PROTOTYPES
 ******************************************************************************/
void fsm__init( fsm_t * self , uint8_t total_signals , uint8_t total_states , const fsm__state_table_t * state_table , fsm__state_t initial_state );
void fsm__none( void );
void fsm__post( fsm_t * self , uint8_t signal_idx );
void fsm__change_state( fsm_t * self , fsm__state_t state_id );
void fsm__main( fsm_t * self );
 
 
#endif // _FSM_H
