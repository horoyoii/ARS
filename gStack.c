#include"gStack.h"

void gStackInit(gstack_ptr sp) {
	sp->top = -1;
}
void gStackPush(gstack_ptr sp, int data) {
	(sp->top)++;
	sp->stackArr[sp->top] = data;
}
int gStackPop(gstack_ptr sp) {
	return sp->stackArr[(sp->top)--];
}
int gStackIsEmpty(gstack_ptr sp) {
	if (sp->top == -1)
		return 1;
	else
		return 0;
}