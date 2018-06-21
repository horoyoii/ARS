#define _CRT_SECURE_NO_WARNINGS
#include"InputFunc.h"


// ют╥б fucntion
void ReservInput(char *StartPos, char *DestPos, char *id, SeatLevel *level) {
	gotoxy(12, 5); fgets(StartPos, 2, stdin);
	while (getchar() != '\n');
	gotoxy(12, 7); fgets(DestPos, 2, stdin);
	while (getchar() != '\n');
	gotoxy(12, 9); scanf("%[^\n]", id);
	while (getchar() != '\n');
	gotoxy(16, 11); scanf("%d", level);
	while (getchar() != '\n');
}