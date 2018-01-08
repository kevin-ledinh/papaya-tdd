#include "unity.h"
#include "dev__fifo.h"

static int * fifo_addr;

extern int * dev__fifo_get_fifo_address( void );

void setUp(void)
{
    dev__fifo_init();
}

void tearDown(void)
{
}

void test_InitializeAllElementsToZeros(void)
{
    fifo_addr = dev__fifo_get_fifo_address();
    TEST_ASSERT_EACH_EQUAL_INT( 0 , fifo_addr , MAX_FIFO_LEN );
}

void test_AddOneElementToFifo(void)
{
    dev__fifo_put(1);
    TEST_ASSERT_EQUAL_INT( 1 , fifo_addr[ 0 ] );
}

void test_GetOneElementFromFifo(void)
{
    dev__fifo_put(123);
    int result = dev__fifo_get();
    TEST_ASSERT_EQUAL_INT( 123 , result );
}