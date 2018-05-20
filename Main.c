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

// SeatLevel 정보
typedef enum _SEATLEVEL{
	FirstClass, Business, Economy
}SeatLevel;

// ReserveTable의 리스트를 가지는 Head 포인터
RTnode_ptr ReserveTable_Head;
// Graph의 리스트를 가지는 Head 포인터
Graph Graph_Head;

// 인터페이스 단계 구성
typedef enum _STAGE {
	MAIN, RESERVATION, CHECKandCANCEL, CHANGE, INFO, CHECKALL
// 메인화면, 1)예약하기, 2) 확인및취소        3) 변경     4) 정보  5) 모든 예약현황
}STAGE;
STAGE Stage;


// 메인화면의 기본 UI
void BasicUI() {
	ScreenPrint(0, 0, "□□□□□□□□□□□□□□□□□□□□□");
	for (int i = 1; i < 20; i++) {
		ScreenPrint(0, i, "□\t\t\t\t\t□");
	}
	ScreenPrint(0, 20, "□□□□□□□□□□□□□□□□□□□□□");
}

// 메인화면
void MainUI() {
	ScreenPrint(4, 2, "1. 예약하기");
	ScreenPrint(4, 3, "2. 예약확인 및 취소");
	ScreenPrint(4, 4, "3. 예약 변경");
	ScreenPrint(4, 5, "4. 기본정보");
	ScreenPrint(4, 6, "5. 모든 예약현황 확인");
}
int MoveBar;
void SelectBAR(int Move) {
	ScreenPrint(2, Move, "▶");
}

void ScreenClearFunc() {
	for (int i = 1; i < 20; i++) {
		gotoxy(2, i); printf("                                       ");
	}
}

//========================================================================
// 입력 fucntion
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

// 예약하기 UI
void ReservationUI() {
	char StartPos[2];
	char DestPos[2];
	char id[100];
	SeatLevel level;
	RTnode_ptr newNode;

	ScreenClearFunc();
	gotoxy(2, 4); printf("예약하기");
	gotoxy(2, 5); printf("출발지 : ");
	gotoxy(2, 6); printf("도착지 : ");
	gotoxy(2, 7); printf("ID : ");
	gotoxy(2, 8); printf("Seat Level : ");

	ReservInput(StartPos, DestPos, id, &level);

	//newNode = SelectRoute(StartPos, DestPos, id, &level);
	//RTInsert(ReserveTable_Head, newNode);
	//ShowGraphStatus(&Graph_Head);
	/*
	if (1) {
		gotoxy(5, 10); printf("예약 완료!");
	}
	else
		gotoxy(5, 11); printf("예약 실패");
	*/
	Sleep(15000);
}

//========================================================================


// 2) 확인 및 취소 UI
void CheckAndCancelUI() {
	char id[100];
	ScreenClearFunc();
	gotoxy(2, 4); printf("예약확인 및 취소");
	gotoxy(2, 5); printf("id 입력 : ");
	gotoxy(12, 5); scanf("%[^\n]", id);
	while (getchar() != '\n');
	Sleep(1500);
}

// 3) 변경 UI
void ChangeUI() {
	char id[100];
	ScreenClearFunc();
	gotoxy(2, 4); printf("예약 변경");
	gotoxy(2, 5); printf("id 입력 : ");
	gotoxy(12, 5); scanf("%[^\n]", id);
	while (getchar() != '\n');
	Sleep(1500);
}

// 4) 기본정보 UI
void InfoUI() {
	// 가격표 등등을 출력해주는 함수
	ScreenPrint(4, 4, "가격표 등등");
}

// 5) 모든 예약현황 확인 UI
void CheckAllUI() {
	// 저장된 모든 예약현황 출력
	ScreenPrint(4, 4, "All the Resev Info");
}

void init() { // 시스템 초기화 단계
	Stage = MAIN;
	MoveBar = 2;
	// 그래프 초기화 =========================================
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
	init(); // 초기화
	int nKey;
	while (1) {
		switch (Stage) {
		case RESERVATION:
			ScreenRelease(); // 입력을 받기 위한 screen release
			ReservationUI();
			Stage = MAIN;
			ScreenInit(); // Screen restart
			break;
		case CHECKandCANCEL:
			ScreenRelease(); // 입력을 받기 위한 screen release
			CheckAndCancelUI();
			Stage = MAIN;
			ScreenInit(); // Screen restart
			break;
		case CHANGE:
			ScreenRelease(); // 입력을 받기 위한 screen release
			ChangeUI();
			Stage = MAIN;
			ScreenInit(); // Screen restart
			break;
		default: // MAIN 화면
			if (_kbhit()) {
				nKey = _getch();
				if (nKey == 13) { // Main화면에서 enter 입력시 MoveBar가 가르키고 있는 Stage로 진입
					Stage = MoveBar - 1;
				}
				if (nKey == 224) { // Main화면에서 방향키를 통해 MoveBar를 움직이는 역할
					nKey = _getch();
					switch (nKey) {
					case UP:
						MoveBar--;
						break;
					case DOWN:
						MoveBar++;
						break;
					case LEFT: // 뒤로가기
						Stage = MAIN;
						break;
					case RIGHT:
						break;
					}
				}
			}
			break;
		}
		Update();  // 데이터 갱신
		Render();  // 화면출력
	}
	Release(); // 해제
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
// 예약하기 





