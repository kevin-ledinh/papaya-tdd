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
    TEST_ASSERT_EQUAL_INT( 123 , dev__fifo_get() );
}

void test_AddMultipleElementsToFifo(void)
{
    dev__fifo_put(123);
    dev__fifo_put(456);
    TEST_ASSERT_EQUAL_INT( 123 , fifo_addr[ 0 ] );
    TEST_ASSERT_EQUAL_INT( 456 , fifo_addr[ 1 ] );
}

void test_GetMultipleElementsFromFifo(void)
{
    dev__fifo_put(123);
    dev__fifo_put(456);
    TEST_ASSERT_EQUAL_INT( 123 , dev__fifo_get() );
    TEST_ASSERT_EQUAL_INT( 456 , dev__fifo_get() );
}

void test_GetNumberOfElementsAfterAdd(void)
{
    dev__fifo_put(123);
    dev__fifo_put(456);
    TEST_ASSERT_EQUAL_INT( 2 , dev__fifo_get_available_entries() );
}

void test_GetNumberofEntriesAfterRemoveSomeElements(void)
{
    dev__fifo_put(123);
    dev__fifo_put(456);
    dev__fifo_put(789);
    dev__fifo_get();
    TEST_ASSERT_EQUAL_INT( 2 , dev__fifo_get_available_entries() );    
}

void test_AddMoreElementThanMaxEntries(void)
{
    int expected_values [ MAX_FIFO_LEN ] = { 17 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10 , 11 , 12 , 13 , 14 , 15 , 16 };
    int count;
    for( count  = 1 ; count <= ( MAX_FIFO_LEN + 1 ) ; count ++ )
    {
        dev__fifo_put( count );
    }
    
    TEST_ASSERT_EQUAL_INT_ARRAY( expected_values , fifo_addr , MAX_FIFO_LEN );
}

void test_GetElementAfterOutOfBound(void)
{
    int expected_values [ MAX_FIFO_LEN ] = { 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10 , 11 , 12 , 13 , 14 , 15 , 16 , 17 };
    int count;
    for( count  = 1 ; count <= ( MAX_FIFO_LEN + 1 ) ; count ++ )
    {
        dev__fifo_put( count );
    }
    
    for( count  = 0 ; count < MAX_FIFO_LEN ; count ++ )
    {
        TEST_ASSERT_EQUAL_INT( expected_values[ count ] , dev__fifo_get() );
    }
}

//TODO: test for empty Fifo when do a get()
