#ifndef J_STACKTEST_H_
#define J_STACKTEST_H_

void testPushAndPopString(void);
void testPushAndPopMultipleIntegers(void);
void testPushAndPopDifferentTypes(void);
void testPushAndPopNull(void);
void testResusesSameSlotAfterPop(void);
void testReturnsNullWhenPopingEmptyStack(void);
void testReturnsNullIfGivenNonPositiveCapacity(void);
void testPushingIntoFullStackIncreasesSize(void);
void testPushToNullStackReturnsError(void);
void testPopFromNullStackReturnsNull(void);

#endif /* J_STACKTEST_H_ */
