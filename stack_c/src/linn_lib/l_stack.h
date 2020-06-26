#ifndef STACK_H_
#define STACK_H_

#define SIZE 5


typedef struct {
    int stack[SIZE];
    int top;
} l_Stack;

l_Stack* createStack();

void deleteStack(l_Stack *st);

int push(int newElem, l_Stack *st);

int pop(l_Stack *st);

int isFull(const l_Stack *st);

int isEmpty(const l_Stack *st);

int getSize(const l_Stack *st);

int peek(const l_Stack *st);


#endif /* STACK_H_ */
