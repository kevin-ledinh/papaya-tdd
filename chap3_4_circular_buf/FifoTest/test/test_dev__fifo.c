#include "unity.h"
#include "dev__fifo.h"

static int * fifo_addr;

void setUp(void)
{
}

void tearDown(void)
{
}

void test_InitializeAllElementsToZeros(void)
{
    fifo_addr = dev__fifo_init();
    TEST_ASSERT_EACH_EQUAL_INT( 0 , fifo_addr , MAX_FIFO_LEN );
}
