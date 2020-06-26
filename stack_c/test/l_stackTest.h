#ifndef L_STACKTEST_H_
#define L_STACKTEST_H_

void linn_testPushAndPopOneInteger(void);
void linn_testPushAndPopMultipleIntegers(void);
void linn_testResusesSameSlotAfterPop(void);
void linn_testReturnsIntMinWhenPopingEmptyStack(void);
void linn_testPushingIntoFullStackReturnsZero(void);
void linn_testPushToNullStackReturnsError(void);
void linn_testPopFromNullStackReturnsError(void);

#endif /* L_STACKTEST_H_ */
