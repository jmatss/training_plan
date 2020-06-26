#include <stdio.h>
#include <stdlib.h>
#include "j_stack.h"

#define PONTER_SIZE sizeof(void*)

typedef struct Stack
{
    void **items;
    int position;
    int capacity;
} Stack;

/**
 *	Creates and allocates heap space for the "stack".
 */
Stack *stack_create(int capacity)
{
    if (capacity <= 0)
    {
        return NULL;
    }

    Stack *stack = malloc(sizeof(Stack));
    if (stack == NULL)
    {
        return NULL;
    }

    void *items = malloc(PONTER_SIZE * capacity);
    if (items == NULL)
    {
        free(stack);
        return NULL;
    }

    stack->capacity = capacity;
    stack->position = 0;
    stack->items = items;

    return stack;
}

/**
 *	Frees the allocated heap memory.
 */
void stack_free(Stack *stack)
{
    if (stack != NULL)
    {
        free(stack->items);
        free(stack);
    }
}

static int increaseCapacity(Stack *stack)
{
    int newCapacity = stack->capacity * 2;
    void* newItems = realloc(stack->items, PONTER_SIZE * newCapacity);
    if (newItems == NULL)
    {
        return -1;
    }

    stack->items = newItems;
    stack->capacity = newCapacity;

    return 0;
}

/**
 *	Pushes item to the "stack". If it is full, double the size.
 *  Returns 0 to indicate success, -1 to indicate error.
 */
int stack_push(Stack *stack, void *item)
{
    if (stack == NULL)
    {
        return -1;
    }

    // Double the size of Stack if it reaches full capacity.
    if (stack->position >= stack->capacity)
    {
        // If unable to increase capacity, returns -1 to indicate error.
        int result = increaseCapacity(stack);
        if (result < 0)
        {
            return -1;
        }
    }

    stack->items[stack->position++] = item;

    return 0;
}

/**
 *	Returns NULL if the "stack" is empty.
 */
void *stack_pop(Stack *stack)
{
    if (stack == NULL)
    {
        return NULL;
    }

    if (stack->position <= 0)
    {
        return NULL;
    }

    return stack->items[--stack->position];
}

int stack_getPosition(Stack *stack)
{
    if (stack == NULL)
    {
        return -1;
    }

    return stack->position;
}

int stack_getCapacity(Stack *stack)
{
    if (stack == NULL)
    {
        return -1;
    }

    return stack->capacity;
}
