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
#include"SelectRoutes.h"
#include"gStack.h"
#include"string.h"

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
// 탐색된 모든 경로를 가지고 있는 Head 포인터 - 다 쓰고 나면 초기화해줘야 함
Rnode_ptr Route_head = NULL;

// 인터페이스 단계 구성
typedef enum _STAGE {
	MAIN, RESERVATION, SELECT, CHECKandCANCEL, CHANGE, INFO, CHECKALL
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


//========================================================================
// 그래프초기화



// 입력 fucntion
void ReservInput(char *StartPos, char *DestPos, char *id, SeatLevel *level) {
	gotoxy(11, 5); fgets(StartPos, 2, stdin);
	while (getchar() != '\n');
	gotoxy(11, 7); fgets(DestPos, 2, stdin);
	while (getchar() != '\n');
	gotoxy(11, 9); scanf("%[^\n]", id);
	while (getchar() != '\n');
	gotoxy(16, 13); scanf("%d", level);
	while (getchar() != '\n');
}

// 예약하기 UI
int GlobalStartPos;
int GlobalDestPos;
char Globalid[100];
SeatLevel GlobalLevel;


void ReservationUI() {
	char StartPosC[2];
	char DestPosC[2];
	char id[100];

	SeatLevel level;
	RTnode_ptr newNode; // 시작지, 도착지, 선택된 경로, id, 비용, 거리, 가격 을 담고 있는 노드
	ScreenClearFunc();
	gotoxy(3, 1); printf("[예약하기] - "); textcolor(10); printf("[정보입력]"); textcolor(15); printf(" - [경로선택] - 확인 ");
	gotoxy(3, 5); printf("출발지 : ");
	gotoxy(3, 7); printf("도착지 : ");
	gotoxy(3, 9); printf("ID : ");
	gotoxy(3, 13); printf("Seat Level : ");
	gotoxy(3, 11); printf(" 0. FirstClass 1. Business 2. Economy");

	ReservInput(StartPosC, DestPosC, id, &level); // 입력받기
	// 형변환
	int StartPos = StartPosC[0] - 97;
	int DestPos = DestPosC[0] - 97;
	GlobalStartPos = StartPos;
	GlobalDestPos = DestPos;
	GlobalLevel = level;
	strcpy(Globalid, id);
	gStack stack;
	gStackInit(&stack);
	int CheckArr[15] = { 0, };

	//Rnode_ptr Route_head = NULL;
	Route_head = NULL;

	// 모든 경로 탐색 후 Route_head에 연결
	DFS(&Graph_Head, StartPos, DestPos, &stack, CheckArr, &Route_head);

	// 모든 경로에 대한 cost, distance, travel time 추가
	AddCostDisTime(&Graph_Head, &Route_head, DestPos);
	
	// 다음 시행을 위한 초기화
	StartPosC[0] = 0;
	StartPosC[1] = 0;
	DestPosC[0] = 0;
	DestPosC[1] = 0;

	
}

void SelectUI() {
	// 모든 경로 display - Route_head 가 가지고 있음.
	ScreenClearFunc();
	char *cSeatLevel[3] = { "FirstClass", "Business", "Economy" };
	//gotoxy(3, 1); printf("[예약하기] - [정보입력] - [경로선택] - [확인] ");
	gotoxy(3, 1); printf("[예약하기] - "); printf("[정보입력] - "); textcolor(10); printf("[경로선택]"); textcolor(15); printf(" - [확인]");
	gotoxy(2, 3); printf("출발 : [ %c ]  도착 : [ %c ] ", GlobalStartPos+97, GlobalDestPos+97);
	gotoxy(2, 4); printf("id : %s    등급 : %s ", Globalid, cSeatLevel[GlobalLevel]);
	gotoxy(2, 9); printf("경로"); gotoxy(40, 9); printf("가격           거리              TravelTime");

	gotoxy(0, 11);
	int i = 0;
	int y = 0;
	int RouteNum = 1;
	Rnode_ptr temp = Route_head;
	while (temp != NULL) {
		i = 0;
		printf("   %d. ", RouteNum++);
		while (1) {
			printf("%c ", temp->Route[i] + 97);
			if (temp->Route[i++] == GlobalDestPos)
				break;
		}
		//gotoxy(40, 11+y++); printf("%0.1f $        %0.1f km         %0.1f", temp->cost, temp->distance, temp->traveltime);
		gotoxy(40, 11 + y); printf("$ %0.1f", temp->cost);
		gotoxy(58, 11 + y); printf("%0.1f km", temp->distance);
		gotoxy(74, 11 + y++); printf("%0.1f h", temp->traveltime);
		puts("  ");
		temp = temp->next;
	}
	int SelectOne;
	gotoxy(2, 7); printf("경로선택 : "); scanf("%d", &SelectOne);
	for (int j = 0; j < SelectOne-1; j++) { // 선택된 경로를 찾는다.
		Route_head = Route_head->next;
	}


}

void ReservationSuccessUI() {
	ScreenClearFunc();
	gotoxy(0, 0); printf(" ");
	gotoxy(5, 5); printf("예매되었습니다.");

}
void ReservationFailUI() {
	ScreenClearFunc();
	gotoxy(0, 0); printf(" ");
	gotoxy(5, 5); printf("취소되었습니다.");

}

void ConfirmUI() {
	ScreenClearFunc();
	gotoxy(0, 0); printf(" ");
	gotoxy(3, 1); printf("[예약하기] - "); printf("[정보입력] - ");printf("[경로선택] - "); textcolor(10); printf("[확인]"); textcolor(15);
	gotoxy(3, 3); printf("출발 : %c", GlobalStartPos+97);
	gotoxy(3, 4); printf("도착 : %c", GlobalDestPos+97);
	gotoxy(3, 5); printf("id : %s", Globalid);
	gotoxy(3, 6); printf("가격 : ");
	gotoxy(3, 8); printf("경로 : ");
	int i = 0;
	while (1) {
		printf("%c ", Route_head->Route[i] + 97);
		if (Route_head->Route[i++] == GlobalDestPos)
			break;
	}
	char Check[2] = { 0, };
	gotoxy(3, 10); printf("예매하시겠습니까? (y/n)"); scanf("%s", Check);
	while (getchar() != '\n'); // 버퍼초기화
	switch (Check[0]) {
	case 'y':
	case'Y':
		// RT table 에 추가하기
		//Route_head free하기
		ReservationSuccessUI();
		break;
	case 'n':
	case 'N':
		ReservationFailUI();
		break;
	}
	Sleep(3000);
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
	Sleep(15000);
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
	case SELECT:
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
			ReservationUI(); // 예약정보 입력받기
			SelectUI();		// 선택하기
			ConfirmUI();     // 예약확인하기
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





