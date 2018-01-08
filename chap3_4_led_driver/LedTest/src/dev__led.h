#ifndef _DEV__LED_H
#define _DEV__LED_H

#include <stdint.h>

void dev__led_init      ( uint16_t * address );
void dev__led_deinit    ( void );
void dev__led_set       ( int led_number );
void dev__led_clear     ( int led_number );

#endif // _DEV__LED_H
