#include "unity.h"
#include "dev__led.h"

static uint16_t virtualLeds;

void setUp(void)
{
    dev__led_init( & virtualLeds );
}

void tearDown(void)
{
}

void test_dev__led_init_AllLedsAreOffAfterInitialisation(void)
{
    uint16_t virtualLeds = 0xffff;
    dev__led_init( & virtualLeds );
    TEST_ASSERT_EQUAL_HEX16( 0 , virtualLeds );
}

void test_TurnOnLedOne(void)
{
    dev__led_set( 1 );
    TEST_ASSERT_EQUAL_HEX16( 1 , virtualLeds );
}

void test_TurnOffLedOne(void)
{
    dev__led_set( 1 );
    dev__led_clear( 1 );
    TEST_ASSERT_EQUAL_HEX16( 0 , virtualLeds );
}

void test_TurnOnMultipleLeds(void)
{
    dev__led_set(8);
    dev__led_set(9);
    TEST_ASSERT_EQUAL_HEX16( 0x180 , virtualLeds );
}

void test_TurnOnAllLeds(void)
{
    dev__led_set_all();
    TEST_ASSERT_EQUAL_HEX16( 0xFFFF , virtualLeds );
}

void test_TurnOffAnyLeds(void)
{
    dev__led_set_all();
    dev__led_clear(8);
    TEST_ASSERT_EQUAL_HEX16(0xff7f, virtualLeds);
}

void test_LedMemoryIsNotReadable(void)
{
    virtualLeds = 0xFFF;
    dev__led_set(8);
    TEST_ASSERT_EQUAL_HEX16( 0x80 , virtualLeds );
}