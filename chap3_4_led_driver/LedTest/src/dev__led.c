/*******************************************************************************
 *    INCLUDED FILES
 ******************************************************************************/
 #include "dev__led.h"
 #include "RuntimeError.h"
 
/*******************************************************************************
 *    DEFINITIONS
 ******************************************************************************/
 
/*******************************************************************************
 *    PRIVATE TYPES
 ******************************************************************************/
enum 
{
    ALL_LEDS_ON = ~0, 
    ALL_LEDS_OFF = ~ALL_LEDS_ON
};
 
enum 
{
    FIRST_LED = 1, 
    LAST_LED = 16
};

/*******************************************************************************
 *    PRIVATE DATA
 ******************************************************************************/
static uint16_t * led_addr;
static uint16_t leds_image;

/*******************************************************************************
 *    PROTOTYPES
 ******************************************************************************/
static uint16_t dev__led_convert_led_number_to_bit( int led_number );
static void dev__led_update_hardware(void);
static bool dev__led_is_led_out_of_bounds(int led_number);
static void dev__led_set_led_image_bit(int led_number);
static void dev__led_clear_led_image_bit(int led_number);

/*******************************************************************************
*    PUBLIC FUNCTIONS
******************************************************************************/

/*****************************************************************************
 *  Function:
 *  Purpose:
*******************************************************************************/
void dev__led_init( uint16_t * address )
{
    led_addr = address;
    leds_image = ALL_LEDS_OFF;
    dev__led_update_hardware();
}

/*****************************************************************************
 *  Function:
 *  Purpose:
*******************************************************************************/
void dev__led_deinit( void )
{
}

/*****************************************************************************
 *  Function:
 *  Purpose:
*******************************************************************************/
void dev__led_set( int led_number )
{
    if ( dev__led_is_led_out_of_bounds( led_number ) )
    {    
        return;
    }   
    
    dev__led_set_led_image_bit( led_number );
    dev__led_update_hardware();
}

/*****************************************************************************
 *  Function:
 *  Purpose:
*******************************************************************************/
void dev__led_clear( int led_number )
{
    if ( dev__led_is_led_out_of_bounds( led_number ) )
    {    
        return;
    }   
    
    dev__led_clear_led_image_bit( led_number );
    dev__led_update_hardware();
}

/*****************************************************************************
 *  Function:
 *  Purpose:
*******************************************************************************/
void dev__led_set_all( void )
{
    leds_image = ALL_LEDS_ON;
    dev__led_update_hardware();
}

/*****************************************************************************
 *  Function:
 *  Purpose:
*******************************************************************************/
void dev__led_clear_all ( void )
{
    leds_image = ALL_LEDS_OFF;
    dev__led_update_hardware();
}

/*****************************************************************************
 *  Function:
 *  Purpose:
*******************************************************************************/
bool dev__led_is_on ( int led_number )
{
    if ( dev__led_is_led_out_of_bounds( led_number ) )
    {    
        return false;
    } 
    
    return ( 0 != ( leds_image & (dev__led_convert_led_number_to_bit( led_number ) ) ) );
}

/*****************************************************************************
 *  Function:
 *  Purpose:
*******************************************************************************/
bool dev__led_is_off ( int led_number )
{
    return !dev__led_is_on( led_number );
}

/*******************************************************************************
 *    PRIVATE FUNCTIONS
 ******************************************************************************/

 /*****************************************************************************
 *  Function:
 *  Purpose:
*******************************************************************************/
static uint16_t dev__led_convert_led_number_to_bit( int led_number )
{
    return 1 << (led_number - 1);
}

static void dev__led_update_hardware(void)
{
    * led_addr = leds_image;
}

static bool dev__led_is_led_out_of_bounds(int led_number)
{
    RUNTIME_ERROR("LED Driver: out-of-bounds LED" , led_number);
    return (led_number < FIRST_LED) || (led_number > LAST_LED);
}

static void dev__led_set_led_image_bit(int led_number)
{
    leds_image |= dev__led_convert_led_number_to_bit(led_number);
}

static void dev__led_clear_led_image_bit(int led_number)
{
    leds_image &= ~dev__led_convert_led_number_to_bit( led_number );
}