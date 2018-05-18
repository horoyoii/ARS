#include"Stack.h"

void StackInit(stack_ptr sp) {
	sp->top = -1;
}
void StackPush(stack_ptr sp, int data) {
	(sp->top)++;
	sp->stackArr[sp->top] = data;
}
int StackPop(stack_ptr sp) {
	return sp->stackArr[(sp->top)--];
}
int StackIsEmpty(stack_ptr sp) {
	if (sp->top == -1)
		return 1;
	else
		return 0;
}