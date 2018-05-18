#pragma once
#define STACK_SIZE 15

typedef struct _STACK *stack_ptr;
typedef struct _STACK {
	int stackArr[STACK_SIZE];
	int top;
}Stack;

void StackInit(stack_ptr sp);
void StackPush(stack_ptr sp, int Data);
int StackPop(stack_ptr sp);
int StackIsEmpty(stack_ptr sp);