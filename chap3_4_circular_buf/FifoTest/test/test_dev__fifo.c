#include "unity.h"
#include "dev__fifo.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_InitializeAllElementsToZeros(void)
{
    int fifo_buf[ MAX_FIFO_LEN ];
    dev__fifo_init( fifo_buf , MAX_FIFO_LEN );
    TEST_ASSERT_EACH_EQUAL_INT( 0 , fifo_buf , MAX_FIFO_LEN );
}
