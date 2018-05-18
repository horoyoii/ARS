#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include"Screen.h"
#include"NodeADT.h"
#include<windows.h>
#include"UI.h"

void gotoxy(int x, int y) {
	COORD CursorPosition = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

#define LEFT 75 
#define RIGHT 77 
#define UP 72 
#define DOWN 80 


// �������̽� �ܰ� ����
typedef enum _STAGE {
	MAIN, RECENTa, MOSTLY, RECENTp, FAVORITE, PLAYING, INSERTS, DELETES
// ����ȭ��, �ֱ��߰�, �������, �ֱ����, ���ã��, �����,   ���߰�   , �����
}STAGE;
STAGE Stage;


char title[100];
char artist[100];

void BasicUI() {
	ScreenPrint(0, 0, "����������������������");
	for (int i = 1; i < 20; i++) {
		ScreenPrint(0, i, "��\t\t\t\t\t��");
	}
	ScreenPrint(0, 20, "����������������������");
}

void MainUI() {
	ScreenPrint(4, 2, "1. �����ϱ�");
	ScreenPrint(4, 3, "2. ����Ȯ���ϱ�");
	ScreenPrint(4, 4, "3. �ִܰ�� �˻�");
	ScreenPrint(4, 5, "4. ��/�պ�");
	ScreenPrint(4, 6, "5. ���ڳ�� / �����Ͻ� / �Ϲ�");
	ScreenPrint(4, 7, "6. ���� / �Ƶ� / ���");
	ScreenPrint(4, 8, "7. �ܿ���");
}
int MoveBar;
void SelectBAR(int Move) {
	ScreenPrint(2, Move, "��");
}

void RecentlyAddUI() {
	ScreenPrint(2, 2, "�����ϱ�");
	ScreenPrint(2, 3, title);

	ScreenPrint(2, 4, artist);
}

void MostlyPlayUI() {
	ScreenPrint(2, 2, "����Ȯ���ϱ�");
}

void RecentlyPlayUI() {
	ScreenPrint(2, 2, "�ֱٿ� ����� �� ���");
}

void FavoriteUI() {
	ScreenPrint(2, 2, "���ã�� ���");
}

void PlayingUI() {
	ScreenPrint(2, 2, "��� ��");
}

void InsertUI() {
	gotoxy(10, 5); printf("                           ");
	gotoxy(11, 6); printf("                           ");
	gotoxy(2, 4); printf("�� �߰�");
	gotoxy(2, 5); printf("��� : ");
	gotoxy(2, 6); printf("������ : ");
	gotoxy(10, 5); fgets(title,100, stdin);
	gotoxy(11, 6); fgets(artist, 100, stdin);
	fflush(stdin);
	//LLInsert(title, artist); // ��ũ�� ����Ʈ�� �߰��ϴ� �۾� ����
	if (1) {
		gotoxy(5, 8); printf("�� �߰� �Ϸ�!");
	}
	else
		gotoxy(5, 8); printf("�� �߰� ����");
	Sleep(1500);
}
void DeleteUI() {
	gotoxy(10, 5); printf("                         ");
	gotoxy(11, 6); printf("                         ");
	gotoxy(2, 4); printf("�� ����");
	gotoxy(2, 5); printf("��� : ");
	gotoxy(2, 6); printf("������ : ");
	gotoxy(10, 5); fgets(title, 100, stdin);
	gotoxy(11, 6); fgets(artist, 100, stdin);
	fflush(stdin);
	//LLDelete(title, artist); // ��ũ�� ����Ʈ�� �����ϴ� �۾� ����
	if (1) {
		gotoxy(5, 8); printf("�� ���� �Ϸ�!");
	}
	else
		gotoxy(5, 8); printf("�� ���� ����");
	Sleep(1500);
}
void init() {
	Stage = MAIN;
	MoveBar = 2;
}

void Update() {

}

void Render() {

	ScreenClear();
	//����ڵ�
	BasicUI();
	switch (Stage) {
	case MAIN:
		MainUI();
		SelectBAR(MoveBar);
		break;
	case RECENTa:
		RecentlyAddUI();
		break;
	case MOSTLY:
		MostlyPlayUI();
		break;
	case RECENTp:
		RecentlyPlayUI();
		break;
	case FAVORITE:
		FavoriteUI();
		break;
	case PLAYING:
		PlayingUI();
		break;
	case INSERTS:
		break;
	case DELETES:
		break;
	}

	ScreenFlipping();
}

void Release() {

}

int main(void) {
	
	ScreenInit();
	init(); // �ʱ�ȭ
	int nKey;
	while (1) {
		switch (Stage) {
		case INSERTS:
			ScreenRelease(); // �Է��� �ޱ� ���� screen release
			InsertUI();
			Stage = MAIN;
			ScreenInit(); // Screen restart
			break;
		case DELETES:
			ScreenRelease(); // �Է��� �ޱ� ���� screen release
			DeleteUI();
			Stage = MAIN;
			ScreenInit(); // Screen restart
			break;
		case PLAYING:
			// ������ ���, ���� ���, ���ã�� �߰�, �ڷΰ��� ���
			break;
		default: // MAIN ȭ��
			if (_kbhit()) {
				nKey = _getch();
				if (nKey == 13) { // enter �Է½�
					Stage = MoveBar - 1;
				}
				if (nKey == 224) {
					nKey = _getch();
					switch (nKey) {
					case UP:
						MoveBar--;
						break;
					case DOWN:
						MoveBar++;
						break;
					case LEFT: // �ڷΰ���
						Stage = MAIN;
						break;
					case RIGHT:
						break;
					}
				}
			}
			break;
		}
		Update();  // ������ ����
		Render();  // ȭ�����
	}
	Release(); // ����
	ScreenRelease();
	return 0;
}