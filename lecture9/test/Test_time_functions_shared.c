/**
* Test .c file for shared time functions
*/
#include "unity.h"
#include "time_functions_shared.h"

void test_timespec_add(void)
{
    struct timespec time1;
    struct timespec time2;
    struct timespec result;
    seconds_to_timespec(&time1,1.0);
    seconds_to_timespec(&time2,1.1);
    timespec_add(&result,&time1,&time2);
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(2.1,timespec_to_seconds(&result),"Expect timespec_add of 1.0 + 1.1 to equal 2.1 seconds");
    seconds_to_timespec(&time1,1.9);
    seconds_to_timespec(&time2,0.2);
    timespec_add(&result,&time1,&time2);
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(2.1,timespec_to_seconds(&result),"Expect timespec_add of 1.9 + 0.2 to equal 2.1 seconds");
}

void test_timespec_diff(void)
{
    struct timespec time1;
    struct timespec time2;
    struct timespec result;
    seconds_to_timespec(&time1,1.0);
    seconds_to_timespec(&time2,1.1);
    timespec_diff(&result,&time1,&time2);
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(0.1,timespec_to_seconds(&result),"Expect timespec_diff of 1.1 - 1.0 to equal 0.1 seconds");
    seconds_to_timespec(&time1,0.9);
    seconds_to_timespec(&time2,1.1);
    timespec_diff(&result,&time1,&time2);
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(0.2,timespec_to_seconds(&result),"Expect timespec_diff of 1.1 - 0.9 to equal 0.2 seconds");
    timespec_diff(&result,&time2,&time1);
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(0.2,timespec_to_seconds(&result),"Expect timespec_diff of 0.9 - 1.1 to equal 0.2 seconds");
}

void test_somefailure(void)
{
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(0.2,0.1,"this will fail");
}
