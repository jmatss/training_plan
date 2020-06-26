#include <limits.h>
#include "CUnit/Basic.h"
#include "l_stack.h"
#include "l_stackTest.h"

void linn_testPushAndPopOneInteger()
{
    // ARRANGE
    int expectedValue = 123;
    l_Stack *stack = createStack();

    // ACT
    push(expectedValue, stack);
    int actualValue = peek(stack);

    // ASSERT
    CU_ASSERT_EQUAL(actualValue, expectedValue);

    deleteStack(stack);
}

void linn_testPushAndPopMultipleIntegers()
{
    // ARRANGE
    int expectedValues[] = { 0, -2 };
    int actualValues[2];
    l_Stack *stack = createStack();

    // ACT
    push(expectedValues[0], stack);
    push(expectedValues[1], stack);
    actualValues[1] = pop(stack);
    actualValues[0] = pop(stack);

    // ASSERT
    CU_ASSERT_EQUAL(actualValues[0], expectedValues[0]);
    CU_ASSERT_EQUAL(actualValues[1], expectedValues[1]);

    deleteStack(stack);
}

void linn_testResusesSameSlotAfterPop() {
    // ARRANGE
    l_Stack *stack = createStack();
    int expectedSize = 0;

    // ACT
    push(0, stack);
    pop(stack);
    int actualSize = getSize(stack);

    // ASSERT
    CU_ASSERT_EQUAL(actualSize, expectedSize);

    deleteStack(stack);
}

void linn_testReturnsIntMinWhenPopingEmptyStack()
{
    // ARRANGE
    int expectedValue = INT_MIN;
    l_Stack *stack = createStack();

    // ACT
    int actualValue = pop(stack);

    // ASSERT
    CU_ASSERT_EQUAL(actualValue, expectedValue);

    deleteStack(stack);
}

void linn_testPushingIntoFullStackReturnsZero()
{
    // ARRANGE
    int expectedResult = 0;
    int expectedSize = SIZE;
    l_Stack *stack = createStack();
    for (int i = 0; i < SIZE; i++)
    {
        push(0, stack);
    }

    // ACT
    int actualResult = push(0, stack);
    int actualSize = getSize(stack);

    // ASSERT
    CU_ASSERT_EQUAL(actualResult, expectedResult);
    CU_ASSERT_EQUAL(actualSize, expectedSize);

    deleteStack(stack);
}

void linn_testPushToNullStackReturnsError()
{
    // ARRANGE
    int expectedResult = INT_MIN;
    l_Stack *stack = NULL;

    // ACT
    int actualResult = push(0, stack);

    // ASSERT
    CU_ASSERT_EQUAL(actualResult, expectedResult);
}

void linn_testPopFromNullStackReturnsError()
{
    // ARRANGE
    int expectedResult = INT_MIN;
    l_Stack *stack = NULL;

    // ARRANGE
    int actualResult = pop(stack);

    // ASSERT
    CU_ASSERT_EQUAL(actualResult, expectedResult);
}