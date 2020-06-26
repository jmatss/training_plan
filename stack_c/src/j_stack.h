#ifndef STACK_H_
#define STACK_H_

typedef struct Stack Stack;

Stack* stack_create(int capacity);
void stack_free(Stack *stack);
int stack_push(Stack *stack, void *item);
void* stack_pop(Stack *stack);
int stack_getPosition(Stack *stack);
int stack_getCapacity(Stack *stack);

#endif /* STACK_H_ */
