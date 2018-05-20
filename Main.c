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
#include"RTLinkedList.h"
#include<windows.h>
#include"UI.h"
#include"Graph.h"

void gotoxy(int x, int y) {
	COORD CursorPosition = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

#define LEFT 75 
#define RIGHT 77 
#define UP 72 
#define DOWN 80 
#define BUFFER_SIZE 100

// SeatLevel ����
typedef enum _SEATLEVEL{
	FirstClass, Business, Economy
}SeatLevel;

// ReserveTable�� ����Ʈ�� ������ Head ������
RTnode_ptr ReserveTable_Head;
// Graph�� ����Ʈ�� ������ Head ������
Graph Graph_Head;

// �������̽� �ܰ� ����
typedef enum _STAGE {
	MAIN, RESERVATION, CHECKandCANCEL, CHANGE, INFO, CHECKALL
// ����ȭ��, 1)�����ϱ�, 2) Ȯ�ι����        3) ����     4) ����  5) ��� ������Ȳ
}STAGE;
STAGE Stage;


// ����ȭ���� �⺻ UI
void BasicUI() {
	ScreenPrint(0, 0, "����������������������");
	for (int i = 1; i < 20; i++) {
		ScreenPrint(0, i, "��\t\t\t\t\t��");
	}
	ScreenPrint(0, 20, "����������������������");
}

// ����ȭ��
void MainUI() {
	ScreenPrint(4, 2, "1. �����ϱ�");
	ScreenPrint(4, 3, "2. ����Ȯ�� �� ���");
	ScreenPrint(4, 4, "3. ���� ����");
	ScreenPrint(4, 5, "4. �⺻����");
	ScreenPrint(4, 6, "5. ��� ������Ȳ Ȯ��");
}
int MoveBar;
void SelectBAR(int Move) {
	ScreenPrint(2, Move, "��");
}

void ScreenClearFunc() {
	for (int i = 1; i < 20; i++) {
		gotoxy(2, i); printf("                                       ");
	}
}

//========================================================================
// �Է� fucntion
void ReservInput(char *StartPos, char *DestPos, char *id, SeatLevel *level) {
	gotoxy(10, 5); fgets(StartPos, 2, stdin);
	while (getchar() != '\n');
	gotoxy(10, 6); fgets(DestPos, 2, stdin);
	while (getchar() != '\n');
	gotoxy(10, 7); scanf("%[^\n]", id);
	while (getchar() != '\n');
	gotoxy(15, 8); scanf("%d", &level);
	while (getchar() != '\n');
}

// �����ϱ� UI
void ReservationUI() {
	char StartPos[2];
	char DestPos[2];
	char id[100];
	SeatLevel level;
	RTnode_ptr newNode;

	ScreenClearFunc();
	gotoxy(2, 4); printf("�����ϱ�");
	gotoxy(2, 5); printf("����� : ");
	gotoxy(2, 6); printf("������ : ");
	gotoxy(2, 7); printf("ID : ");
	gotoxy(2, 8); printf("Seat Level : ");

	ReservInput(StartPos, DestPos, id, &level);

	//newNode = SelectRoute(StartPos, DestPos, id, &level);
	//RTInsert(ReserveTable_Head, newNode);
	//ShowGraphStatus(&Graph_Head);
	/*
	if (1) {
		gotoxy(5, 10); printf("���� �Ϸ�!");
	}
	else
		gotoxy(5, 11); printf("���� ����");
	*/
	Sleep(15000);
}

//========================================================================


// 2) Ȯ�� �� ��� UI
void CheckAndCancelUI() {
	char id[100];
	ScreenClearFunc();
	gotoxy(2, 4); printf("����Ȯ�� �� ���");
	gotoxy(2, 5); printf("id �Է� : ");
	gotoxy(12, 5); scanf("%[^\n]", id);
	while (getchar() != '\n');
	Sleep(1500);
}

// 3) ���� UI
void ChangeUI() {
	char id[100];
	ScreenClearFunc();
	gotoxy(2, 4); printf("���� ����");
	gotoxy(2, 5); printf("id �Է� : ");
	gotoxy(12, 5); scanf("%[^\n]", id);
	while (getchar() != '\n');
	Sleep(1500);
}

// 4) �⺻���� UI
void InfoUI() {
	// ����ǥ ����� ������ִ� �Լ�
	ScreenPrint(4, 4, "����ǥ ���");
}

// 5) ��� ������Ȳ Ȯ�� UI
void CheckAllUI() {
	// ����� ��� ������Ȳ ���
	ScreenPrint(4, 4, "All the Resev Info");
}

void init() { // �ý��� �ʱ�ȭ �ܰ�
	Stage = MAIN;
	MoveBar = 2;
	// �׷��� �ʱ�ȭ =========================================
	GraphInit(&Graph_Head, 15); 
	AddEdge(&Graph_Head, a,b); AddEdge(&Graph_Head, a,c);
	AddEdge(&Graph_Head, a,o); AddEdge(&Graph_Head, b,g);
	AddEdge(&Graph_Head, c,d); AddEdge(&Graph_Head, c,l);
	AddEdge(&Graph_Head, b,e); AddEdge(&Graph_Head, o,l);
	AddEdge(&Graph_Head, l,d); AddEdge(&Graph_Head, d,e);
	AddEdge(&Graph_Head, d,k); AddEdge(&Graph_Head, e,f);
	AddEdge(&Graph_Head, f,h); AddEdge(&Graph_Head, f,i);
	AddEdge(&Graph_Head, i, h); AddEdge(&Graph_Head, i, n);
	AddEdge(&Graph_Head, k, j); AddEdge(&Graph_Head, k ,m);
	AddEdge(&Graph_Head, m, n); AddEdge(&Graph_Head, j, n);
	// ====================================================
}

void Update() {

}

void Render() {

	ScreenClear();
	BasicUI();
	switch (Stage) {
	case MAIN:
		MainUI();
		SelectBAR(MoveBar);
		break;
	case RESERVATION:
		break;
	case CHECKandCANCEL:
		break;
	case CHANGE:
		break;
	case INFO:
		InfoUI();
		break;
	case CHECKALL:
		CheckAllUI();
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
		case RESERVATION:
			ScreenRelease(); // �Է��� �ޱ� ���� screen release
			ReservationUI();
			Stage = MAIN;
			ScreenInit(); // Screen restart
			break;
		case CHECKandCANCEL:
			ScreenRelease(); // �Է��� �ޱ� ���� screen release
			CheckAndCancelUI();
			Stage = MAIN;
			ScreenInit(); // Screen restart
			break;
		case CHANGE:
			ScreenRelease(); // �Է��� �ޱ� ���� screen release
			ChangeUI();
			Stage = MAIN;
			ScreenInit(); // Screen restart
			break;
		default: // MAIN ȭ��
			if (_kbhit()) {
				nKey = _getch();
				if (nKey == 13) { // Mainȭ�鿡�� enter �Է½� MoveBar�� ����Ű�� �ִ� Stage�� ����
					Stage = MoveBar - 1;
				}
				if (nKey == 224) { // Mainȭ�鿡�� ����Ű�� ���� MoveBar�� �����̴� ����
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


// reservation table [ circular singly linked list ]
/*
typedef struct _ROUTE *RouteNode_ptr;
typedef struct _ROUTE {

}Route;

typedef struct _RT_NODE *RTnode_ptr;

enum { FirstClass, Business, Economy };
typedef struct _RT_NODE {
	char id[30];
	char StartPos;
	char DestPos;
	RouteNode_ptr ReservedRoute;
	int SeatLevel;
	int Cost;
	int  Distance;
	int TravelTime;
}RTNode;


RTnode_ptr ReserveTable_Head;
*/
// �����ϱ� 





