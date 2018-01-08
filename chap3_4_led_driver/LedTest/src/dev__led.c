#include "dev__led.h"

static uint16_t * led_addr;

void dev__led_init( uint16_t * address )
{
    led_addr = address;
    * led_addr = 0;
}

void dev__led_deinit( void )
{
}

void dev__led_set( int led_number )
{
    * led_addr = 1;
}

void dev__led_clear( int led_number )
{
    * led_addr = 0;
}