#include <stdlib.h>
#include <limits.h>

#include "l_stack.h"


/*
  Function to dynamically allocate the stack
*/
l_Stack* createStack()
{
    l_Stack *st = (l_Stack*)malloc(sizeof(l_Stack));
    st->top = -1;
    return st;
}

/*
  Function to delete the stack, also possible by just calling free(stack)
*/
void deleteStack(l_Stack *st)
{
    free(st);
}

/*
  Pushes the element passed as the first argument into the stack which is pointed to by the second argument 
  Returns 1 if the push was successful
  Returns INT_MIN if the push was not successful
*/
int push(int newElem, l_Stack *st)
{
    int full; 
    full = isFull(st);

    if(full == 0 && newElem != INT_MIN)
    {
        st->top++;
        st->stack[st->top] = newElem;
        return 1;
    }

    return 0;
}

/*
  Pushes the element passed as the first argument into the stack which is pointed to by the second argument 
  Returns 1 if the push was successful
  Returns 0 if the push was not successful
*/
int pop(l_Stack *st)
{
    int empty = isEmpty(st);
    int value;

    if(empty != 0)
    {
        //Is there a better way to show that one could not pop?
        return INT_MIN;
    }

    value = st->stack[st->top];
    st->top--;
    return value;
}

/*
  Checks if the stack is full 
  Returns 1 if the stack is full
  Returns 0 if the stack is not full
*/
int isFull(const l_Stack *st)
{
    if(st->top >= SIZE-1)
    { 
        return 1;
    }

    return 0;
}

/*
  Checks if the stack is empty 
  Returns 1 if the stack is empty
  Returns 0 if the stack is not empty
*/
int isEmpty(const l_Stack *st)
{
    if(st->top == -1)
    {
        return 1;
    }

    return 0;
}

/*
  Checks the size of the stack
  Returns the size of the stack
*/
int getSize(const l_Stack *st)
{
    int size = st->top +1;
    return size;
}

/*
  Looking at the top element of the stack 
  Returns the value of the top element
  If stack is full returns INT_MIN
*/
int peek(const l_Stack *st)
{
    if(st->top < 0)
    {
        return INT_MIN;
    }
    
    return st->stack[st->top];
}


