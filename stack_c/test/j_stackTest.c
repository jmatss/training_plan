#include "CUnit/Basic.h"
#include "j_stack.h"
#include "j_stackTest.h"

void testPushAndPopString()
{
    // ARRANGE
    char *expectedValue = "123";
    Stack *stack = stack_create(1);

    // ACT
    stack_push(stack, expectedValue);
    void* actualValue = stack_pop(stack);

    stack_free(stack);

    // ASSERT
    CU_ASSERT_PTR_NOT_NULL_FATAL(actualValue);
    CU_ASSERT_STRING_EQUAL(actualValue, expectedValue);
}

void testPushAndPopMultipleIntegers()
{
    // ARRANGE
    int expectedValues[] = { 0, -2 };
    int* actualValues[2];
    Stack *stack = stack_create(2);

    // ACT
    stack_push(stack, &expectedValues[0]);
    stack_push(stack, &expectedValues[1]);
    actualValues[1] = stack_pop(stack);
    actualValues[0] = stack_pop(stack);

    stack_free(stack);

    // ASSERT
    CU_ASSERT_PTR_NOT_NULL_FATAL(actualValues[0]);
    CU_ASSERT_PTR_NOT_NULL_FATAL(actualValues[1]);
    CU_ASSERT_EQUAL(*actualValues[0], expectedValues[0]);
    CU_ASSERT_EQUAL(*actualValues[1], expectedValues[1]);
}

void testPushAndPopDifferentTypes()
{
    // ARRANGE
    char *expectedFirstValue = "testString";
    float expectedSecondValue = 1.0f;
    Stack *stack = stack_create(2);

    // ACT
    stack_push(stack, expectedFirstValue);
    stack_push(stack, &expectedSecondValue);
    float *actualSecondValue = stack_pop(stack);
    const char *actualFirstValue = stack_pop(stack);

    stack_free(stack);

    // ASSERT
    CU_ASSERT_PTR_NOT_NULL_FATAL(actualFirstValue);
    CU_ASSERT_PTR_NOT_NULL_FATAL(actualSecondValue);
    CU_ASSERT_STRING_EQUAL(actualFirstValue, expectedFirstValue);
    CU_ASSERT_DOUBLE_EQUAL(*actualSecondValue, expectedSecondValue, 0.001);
}

void testPushAndPopNull()
{
    // ARRANGE
    Stack *stack = stack_create(1);

    // ACT
    stack_push(stack, NULL);
    void *actualValue = stack_pop(stack);

    stack_free(stack);

    // ASSERT
    CU_ASSERT_PTR_NULL(actualValue);
}

void testResusesSameSlotAfterPop() {
    // ARRANGE
    Stack *stack = stack_create(1);
    int expectedPosition = 0;

    // ACT
    stack_push(stack, NULL);
    stack_pop(stack);
    int actualPosition = stack_getPosition(stack);

    stack_free(stack);

    // ASSERT
    CU_ASSERT_EQUAL(actualPosition, expectedPosition);
}

void testReturnsNullWhenPopingEmptyStack()
{
    // ARRANGE
    Stack *stack = stack_create(1);

    // ACT
    void *actualValue = stack_pop(stack);

    stack_free(stack);

    // ASSERT
    CU_ASSERT_PTR_NULL(actualValue);
}

void testReturnsNullIfGivenNonPositiveCapacity()
{
    // ARRANGE & ACT
    Stack *stackA = stack_create(0);
    Stack *stackB = stack_create(-1);

    // ASSERT
    CU_ASSERT_PTR_NULL(stackA);
    CU_ASSERT_PTR_NULL(stackB);
}

void testPushingIntoFullStackIncreasesSize()
{
    // ARRANGE
    int startCapacity = 1;
    Stack *stack = stack_create(startCapacity);
    stack_push(stack, NULL);

    // ACT
    stack_push(stack, NULL);
    int currentCapacity = stack_getCapacity(stack);

    stack_free(stack);

    // ASSERT
    CU_ASSERT_TRUE(currentCapacity > startCapacity);
}

void testPushToNullStackReturnsError()
{
    // ARRANGE
    int expectedResult = -1;
    Stack *stack = NULL;

    // ACT
    int actualResult = stack_push(stack, NULL);

    // ASSERT
    CU_ASSERT_EQUAL(actualResult, expectedResult);
}

void testPopFromNullStackReturnsNull()
{
    // ARRANGE
    Stack *stack = NULL;

    // ARRANGE
    void *actualItem = stack_pop(stack);

    // ASSERT
    CU_ASSERT_PTR_NULL(actualItem);
}