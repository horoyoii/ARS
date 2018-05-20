#pragma once
#define STACK_SIZE 20

typedef struct _gSTACK *gstack_ptr;
typedef struct _gSTACK {
	int stackArr[STACK_SIZE];
	int top;
}gStack;

void gStackInit(gstack_ptr sp);
void gStackPush(gstack_ptr sp, int Data);
int gStackPop(gstack_ptr sp);
int gStackIsEmpty(gstack_ptr sp);
