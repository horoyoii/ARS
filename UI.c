#include"UI.h"

void gotoxy(int x, int y) {
	COORD CursorPosition = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

void textcolor(int color_number) //�ܼ�â ��»����� ��Ÿ���� �Լ�
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}


void ScreenClearFunc() {
	for (int i = 1; i < 40; i++) {
		gotoxy(2, i); printf("                                                                                                  ");
	}
}