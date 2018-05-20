#include"UI.h"


void gotoxy(int x, int y) {
	COORD CursorPosition = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

void ScreenClearFunc() {
	for (int i = 1; i < 20; i++) {
		gotoxy(2, i); printf("                                       ");
	}
}