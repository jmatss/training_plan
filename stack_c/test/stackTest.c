#include "CU_main.h"
#include "j_stackTest.h"
#include "l_stackTest.h"

TEST_TABLE_START
    TEST_TABLE_ENTRY(testPushAndPopString)
    TEST_TABLE_ENTRY(testPushAndPopMultipleIntegers)
    TEST_TABLE_ENTRY(testPushAndPopDifferentTypes)
    TEST_TABLE_ENTRY(testPushAndPopNull)
    TEST_TABLE_ENTRY(testResusesSameSlotAfterPop)
    TEST_TABLE_ENTRY(testReturnsNullWhenPopingEmptyStack)
    TEST_TABLE_ENTRY(testReturnsNullIfGivenNonPositiveCapacity)
    TEST_TABLE_ENTRY(testPushingIntoFullStackIncreasesSize)
    TEST_TABLE_ENTRY(testPushToNullStackReturnsError)
    TEST_TABLE_ENTRY(testPopFromNullStackReturnsNull)

    TEST_TABLE_ENTRY(linn_testPushAndPopOneInteger)
    TEST_TABLE_ENTRY(linn_testPushAndPopMultipleIntegers)
    TEST_TABLE_ENTRY(linn_testResusesSameSlotAfterPop)
    TEST_TABLE_ENTRY(linn_testReturnsIntMinWhenPopingEmptyStack)
    TEST_TABLE_ENTRY(linn_testPushingIntoFullStackReturnsZero)
    //TEST_TABLE_ENTRY(linn_testPushToNullStackReturnsError)
    //TEST_TABLE_ENTRY(linn_testPopFromNullStackReturnsError)
TEST_TABLE_END

INIT_TEST_SUITE("Stack test",   /* Test suite name (GROUP_MODULE) */
                NULL,           /* Test suite init function       */
                NULL)           /* Test suite clean-up function   */