#include "unity.h"
#include "dev__led.h"
#include "RuntimeErrorStub.h"

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

void test_TurnOffMultipleLeds(void)
{
    dev__led_set_all();
    dev__led_clear(9);
    dev__led_clear(8);
    TEST_ASSERT_EQUAL_HEX16((~0x180)&0xffff, virtualLeds);
}

void test_TurnOnAllLeds(void)
{
    dev__led_set_all();
    TEST_ASSERT_EQUAL_HEX16( 0xFFFF , virtualLeds );
}

void test_TurnOffAllLeds(void)
{
    dev__led_set_all();
    dev__led_clear_all();
    TEST_ASSERT_EQUAL_HEX16( 0 , virtualLeds );
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

void test_UpperAndLowerBound(void)
{
    dev__led_set(1);
    dev__led_set(16);
    TEST_ASSERT_EQUAL_HEX16( 0x8001 , virtualLeds );
}

void test_OutOfBoundTurnOnDoesNoHarm(void)
{
    dev__led_set(-1);
    dev__led_set(0);
    dev__led_set(17);
    dev__led_set(3141);
    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

void test_OutOfBoundTurnOffDoesNoHarm(void)
{
    dev__led_set_all();
    
    dev__led_clear(-1);
    dev__led_clear(0);
    dev__led_clear(17);
    dev__led_clear(3141);
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, virtualLeds);
}

void test_OutOfBoundProducesRuntimeError(void)
{
    dev__led_set(-1);
    TEST_ASSERT_EQUAL_STRING("LED Driver: out-of-bounds LED", RuntimeErrorStub_GetLastError());
    TEST_ASSERT_EQUAL(-1, RuntimeErrorStub_GetLastParameter());
}

void test_OutOfBOundTodo(void)
{
    TEST_IGNORE();
}

void test_IsLedOn(void)
{
    TEST_ASSERT_FALSE(dev__led_is_on(11));
    dev__led_set(11);
    TEST_ASSERT_TRUE(dev__led_is_on(11));
}

void test_OutOfBoundLedsAreAlwaysOff(void)
{
    TEST_ASSERT_TRUE(dev__led_is_off(0));
    TEST_ASSERT_TRUE(dev__led_is_off(17));
    TEST_ASSERT_FALSE(dev__led_is_on(0));
    TEST_ASSERT_FALSE(dev__led_is_on(17));

}

void test_IsLedOff(void)
{
    dev__led_set_all();
    TEST_ASSERT_FALSE(dev__led_is_off(11));
    dev__led_clear(11);
    TEST_ASSERT_TRUE(dev__led_is_off(11));
}