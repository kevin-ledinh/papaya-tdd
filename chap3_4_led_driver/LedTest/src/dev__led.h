#ifndef _DEV__LED_H
#define _DEV__LED_H

#include <stdint.h>
#include <stdbool.h>

void dev__led_init      ( uint16_t * address );
void dev__led_deinit    ( void );
void dev__led_set       ( int led_number );
void dev__led_clear     ( int led_number );
void dev__led_set_all   ( void );
void dev__led_clear_all ( void );
bool dev__led_is_on     ( int led_number );
bool dev__led_is_off    ( int led_number );

#endif // _DEV__LED_H
