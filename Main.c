#define _CRT_SECURE_NO_WARNINGS
#include"Screen.h"
#include"RTLinkedList.h"
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


// ReserveTable의 리스트를 가지는 Head 포인터
RTnode_ptr ReserveTable_Head = NULL;
// Graph의 리스트를 가지는 Head 포인터
Graph Graph_Head;
// 탐색된 모든 경로를 가지고 있는 Head 포인터 - 다 쓰고 나면 초기화해줘야 함
Rnode_ptr Route_head = NULL;

// 인터페이스 단계 구성
typedef enum _STAGE {
	MAIN, RESERVATION, CHECKandCANCEL, CHANGE, INFO, CHECKALL
// 메인화면, 1)예약하기, 2) 확인및취소        3) 변경     4) 정보  5) 모든 예약현황
}STAGE;
STAGE Stage;


int MoveBar;
void SelectBAR(int Move) {
	ScreenPrint(2, Move, "▶");
}

// 입력받는 값들에 대한 전역변수
int GlobalStartPos;
int GlobalDestPos;
char Globalid[100];
SeatLevel GlobalLevel;


// 1) 예약하기 기능 ========================================================
void ReservationUI() {
	char StartPosC[2];
	char DestPosC[2];
	char id[100];

	SeatLevel level;
	RTnode_ptr newNode; // 시작지, 도착지, 선택된 경로, id, 비용, 거리, 가격 을 담고 있는 노드
	ScreenClearFunc();
	gotoxy(3, 1); printf("[예약하기] - "); textcolor(10); printf("[정보입력]"); textcolor(15); printf(" - [경로선택] - [확인] ");
	gotoxy(3, 3); printf("=================================================");
	gotoxy(3, 5); printf("출발지 : ");
	gotoxy(3, 7); printf("도착지 : ");
	gotoxy(3, 9); printf("ID     : ");
	gotoxy(3, 11); printf("Seat Level : ");
	gotoxy(3, 13); printf("Seat Level List");
	gotoxy(3, 15); printf("[ 0. FirstClass ] [ 1. Business ] [ 2. Economy ]");
	gotoxy(3, 17); printf("=================================================");

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
	Route_head->level = level;
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
	gotoxy(3, 3); printf("=================================================");
	gotoxy(2, 5); printf(" 출발 : [ %c ]  도착 : [ %c ] ", GlobalStartPos+97, GlobalDestPos+97);
	gotoxy(2, 6); printf(" id : %s     등급 : %s ", Globalid, cSeatLevel[GlobalLevel]);
	gotoxy(2, 12); printf(" 경로"); gotoxy(40, 12); printf("가격           거리              TravelTime");
	gotoxy(3, 8); printf("=================================================");
	gotoxy(3, 10); printf("=================================================");
	gotoxy(3, 11); printf("==================================================================================");
	gotoxy(0, 14);
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
		gotoxy(40, 14 + y); printf("$ %0.1f", temp->cost);
		gotoxy(58, 14 + y); printf("%0.1f km", temp->distance);
		gotoxy(74, 14 + y++); printf("%0.1f h", temp->traveltime);
		puts("  ");
		temp = temp->next;
	}
	int SelectOne;
	gotoxy(2, 9); printf(" 경로선택 : "); scanf("%d", &SelectOne);
	for (int j = 0; j < SelectOne-1; j++) { // 선택된 경로를 찾는다.
		Route_head = Route_head->next;
	}
	Route_head->StartPos = GlobalStartPos;
	Route_head->DestPos = GlobalDestPos;

}



RTnode_ptr MakeRnodeToRTnode(Rnode_ptr Selected) {
	RTnode_ptr newOne = (RTnode_ptr)malloc(sizeof(RTNode));
	newOne->StartPos = Selected->StartPos;
	newOne->DestPos = Selected->DestPos;
	newOne->seatLev = GlobalLevel;
	newOne->Cost = Selected->cost;
	newOne->Distance = Selected->distance;
	newOne->TravelTime = Selected->traveltime;
	
	// 경로 추가하기
	int i = 0;
	while (1) {
		if (Selected->Route[i++] == Selected->DestPos)
			break;
	}
	newOne->ReservedRoute = (int*)malloc(sizeof(int)*i);
	int j = 0;
	while (1) {
		newOne->ReservedRoute[j] = Selected->Route[j];

		if (Selected->Route[j++] == Selected->DestPos)
			break;
	}
	char ch;
	int n = 0;
	while ((ch = Globalid[n]) != NULL) {
		newOne->id[n++] = ch;
	}
	newOne->id[n] = NULL;
	
	return newOne;
}

void ConfirmUI() {
	ScreenClearFunc();
	gotoxy(0, 0); printf(" ");
	char *cSeatLevel[3] = { "FirstClass", "Business", "Economy" };
	
	gotoxy(3, 1); printf("[예약하기] - "); printf("[정보입력] - ");printf("[경로선택] - "); textcolor(10); printf("[확인]"); textcolor(15);
	
	gotoxy(3, 3); printf("=================================================");
	gotoxy(2, 5); printf(" 출발 : [ %c ]  도착 : [ %c ] ", GlobalStartPos + 97, GlobalDestPos + 97);
	gotoxy(2, 6); printf(" id : %s     등급 : %s ", Globalid, cSeatLevel[GlobalLevel]);
	RTnode_ptr newOne;
	int i = 0;
	gotoxy(3, 8); printf("=================================================");
	gotoxy(3, 9); printf("경로 : ");
	gotoxy(3, 10); printf("=================================================");
	gotoxy(12, 9);
	while (1) {
		printf("%c ", Route_head->Route[i] + 97);
		if (Route_head->Route[i++] == GlobalDestPos)
			break;
	}
	char Check[2] = { 0, };
	gotoxy(3, 12); printf("=================================================");
	gotoxy(3, 14); printf("=================================================");
	gotoxy(3, 13); printf("예매하시겠습니까? (y/n)"); scanf("%s", Check);
	while (getchar() != '\n'); // 버퍼초기화
	switch (Check[0]) {
	case 'y':
	case'Y':
		// RT table 에 추가하기
		newOne = MakeRnodeToRTnode(Route_head);
		RTInsert(&ReserveTable_Head, newOne);
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
// ========================================================================



// 2) 확인 및 취소 UI ============================================================
int CheckAndCancelUI() {
	char inputId[100], Check[2] = { 0, };
	char *cSeatLevel[3] = { "FirstClass", "Business", "Economy" };	//좌석등급 보여줄 때 사용할 배열
	ScreenClearFunc();
	gotoxy(2, 1); printf("[예약확인] - [취소]");
	gotoxy(2, 3); printf("=================================================");
	gotoxy(2, 4); printf("ID 입력 : ");
	gotoxy(2, 5); printf("=================================================");
	gotoxy(12, 4); scanf("%[^\n]", inputId);			while (getchar() != '\n');
	//확인 후 취소여부 묻기. 해당 id를 갖는 node에 접근할 방법이 따로 있나요?
	gotoxy(2, 6);
	RTnode_ptr frontNode = ReserveTable_Head;

	//ReserveTable이 비어있을 때 return 0
	if (!frontNode) {
		printf("예약 정보가 존재하지 않습니다.");

		Sleep(3000);
		return 0;
	}
	else
		//id 유효 여부 체크
		while (strcmp(inputId, frontNode->id)) {
			if (frontNode->next == ReserveTable_Head) {
				printf("존재하지 않는 id입니다.");
				Sleep(3000);
				return 0;
			}
			frontNode = frontNode->next;
		}
	gotoxy(2, 7); printf("출발 : [ %c ]", frontNode->StartPos + 97);
	gotoxy(17, 7); printf("도착 : [ %c ]", frontNode->DestPos + 97);
	gotoxy(2, 9); //예약된 경로 출력하기
	printf("경로: ");

	int i = 0;
	while (1) {
		printf("%c ", frontNode->ReservedRoute[i] + 97);
		if (frontNode->ReservedRoute[i++] == frontNode->DestPos)
			break;
	}
	gotoxy(2, 10); printf("Seat Level : %s", cSeatLevel[frontNode->seatLev]);
	gotoxy(2, 11); printf("가격 : %0.1f", frontNode->Cost);
	gotoxy(2, 13); printf("=================================================");
	gotoxy(2, 15); printf("=================================================");
	gotoxy(2, 14); printf("예약을 취소하시겠습니까? (y/n)"); scanf("%s", Check);
	while (getchar() != '\n');
	switch (Check[0]) {
	case 'y':
	case 'Y':
		// 예약취소하기
		RTDelete(&ReserveTable_Head, inputId);
		gotoxy(2, 16); printf("예약이 취소되었습니다.");
		break;
	case 'n':
	case 'N':
		break;
	}
	Sleep(1500);
	return 1;
}



int ChangeUI() {
	char inputId[100], Check[2] = { 0, };
	char *cSeatLevel[3] = { "FirstClass", "Business", "Economy" };   //좌석등급 보여줄 때 사용할 배열
	SeatLevel newSeatLev;
	ScreenClearFunc();
	gotoxy(2, 1); printf("[예약변경]");
	gotoxy(2, 3); printf("========================");
	gotoxy(2, 4); printf("ID 입력 : ");
	gotoxy(2, 5); printf("========================");
	gotoxy(12, 4); scanf("%[^\n]", inputId);         while (getchar() != '\n');
	gotoxy(2, 6);
	RTnode_ptr frontNode = ReserveTable_Head;

	//ReserveTable이 비어있을 때 return 0
	if (!frontNode) {
		printf("예약 정보가 존재하지 않습니다.");
		Sleep(3000);
		return 0;
	}
	else
		//id 유효 여부 체크
		while (strcmp(inputId, frontNode->id)) {
			if (frontNode->next == ReserveTable_Head) {
				printf("존재하지 않는 id입니다.");
				Sleep(3000);
				return 0;
			}
			frontNode = frontNode->next;
		}
	printf("출발 : %c", frontNode->StartPos + 97);
	gotoxy(2, 7); printf("도착 : %c", frontNode->DestPos + 97);
	gotoxy(2, 8); printf("Seat Level : %s", cSeatLevel[frontNode->seatLev]);
	gotoxy(2, 10); printf("========================");
	gotoxy(2, 11); printf("변경할 좌석을 선택해주세요.");
	gotoxy(2, 12); printf("[ 0. FirstClass 1. Business 2. Economy ] ");
	gotoxy(2, 14); printf("선택 : ");
	gotoxy(9, 14); scanf("%d", &newSeatLev);
	seatChange(frontNode, inputId, newSeatLev);
	gotoxy(2, 16); printf("변경되었습니다.");
	while (getchar() != '\n');
	Sleep(1500);
	return 1;

}

void RandomInsert(int Start, int Dest, char *id, int level) {
	int StartPos = Start;
	int DestPos = Dest;
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
	Route_head->level = level;
	AddCostDisTime(&Graph_Head, &Route_head, DestPos);

	int SelectOne = 2;
	for (int j = 0; j < SelectOne - 1; j++) { // 선택된 경로를 찾는다.
		Route_head = Route_head->next;
	}
	Route_head->StartPos = GlobalStartPos;
	Route_head->DestPos = GlobalDestPos;

	RTnode_ptr newOne;
	newOne = MakeRnodeToRTnode(Route_head);
	RTInsert(&ReserveTable_Head, newOne);
}

void RandomDelete(char *inputId) {
	RTnode_ptr frontNode = ReserveTable_Head;
	while (strcmp(inputId, frontNode->id)) {
		if (frontNode->next == ReserveTable_Head) {
			return 0;
		}
		frontNode = frontNode->next;
	}
	RTDelete(&ReserveTable_Head, inputId);

}

void init() { // 시스템 초기화 단계
	Stage = MAIN;
	MoveBar = 12;

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
	// 20개 넣기
	RandomInsert(3, 5, "eirc8260", 2); RandomInsert(4, 1, "Jane", 1); RandomInsert(12, 11, "ELLE", 0); RandomInsert(4, 12, "Sam", 1);
	RandomInsert(5, 1, "Demonic3540", 0); RandomInsert(7, 3, "Swallow", 1); RandomInsert(4,1 , "Louis", 0); RandomInsert(0, 7, "Ellen page", 1);
	RandomInsert(11, 2, "Horoyoii", 1); RandomInsert(5,  6, "Kyale", 2); RandomInsert(6, 7, "Moondo", 1); RandomInsert(7,8 , "Ashe", 1);
	RandomInsert(10, 3, "Master Lee", 1); RandomInsert(10, 4, "Ahri", 2); RandomInsert(8, 4, "Darius", 0); RandomInsert(12, 3, "Kazhix", 1);
	RandomInsert(9, 0, "Garen", 1); RandomInsert(5, 3, "Piora", 2); RandomInsert(14, 5, "Leblank", 0); RandomInsert(0, 2, "Khogmo", 1);

	// 5개  삭제
	RandomDelete("HOHO");	RandomDelete("Swallow");
	RandomDelete("Jane");	RandomDelete("Sam");
	RandomDelete("YOYO");

}

void Update() {
	// 내용 Update부분
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
		case INFO:
			if (_kbhit()) {
				nKey = _getch();
				if (nKey == 13) {
					Stage = MAIN;
				}
			}
			break;
		case CHECKALL:
			ScreenRelease(); // 입력을 받기 위한 screen release
			CheckAllUI(ReserveTable_Head);
			Stage = MAIN;
			ScreenInit(); // Screen restart
			while (getchar() != '\n');
			break;
		default: // MAIN 화면
			if (_kbhit()) {
				nKey = _getch();
				if (nKey == 13) { // Main화면에서 enter 입력시 MoveBar가 가르키고 있는 Stage로 진입
					Stage = MoveBar - 11;
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


