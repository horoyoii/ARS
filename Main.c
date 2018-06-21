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


// ReserveTable�� ����Ʈ�� ������ Head ������
RTnode_ptr ReserveTable_Head = NULL;
// Graph�� ����Ʈ�� ������ Head ������
Graph Graph_Head;
// Ž���� ��� ��θ� ������ �ִ� Head ������ - �� ���� ���� �ʱ�ȭ����� ��
Rnode_ptr Route_head = NULL;

// �������̽� �ܰ� ����
typedef enum _STAGE {
	MAIN, RESERVATION, CHECKandCANCEL, CHANGE, INFO, CHECKALL
// ����ȭ��, 1)�����ϱ�, 2) Ȯ�ι����        3) ����     4) ����  5) ��� ������Ȳ
}STAGE;
STAGE Stage;


int MoveBar;
void SelectBAR(int Move) {
	ScreenPrint(2, Move, "��");
}

// �Է¹޴� ���鿡 ���� ��������
int GlobalStartPos;
int GlobalDestPos;
char Globalid[100];
SeatLevel GlobalLevel;


// 1) �����ϱ� ��� ========================================================
void ReservationUI() {
	char StartPosC[2];
	char DestPosC[2];
	char id[100];

	SeatLevel level;
	RTnode_ptr newNode; // ������, ������, ���õ� ���, id, ���, �Ÿ�, ���� �� ��� �ִ� ���
	ScreenClearFunc();
	gotoxy(3, 1); printf("[�����ϱ�] - "); textcolor(10); printf("[�����Է�]"); textcolor(15); printf(" - [��μ���] - [Ȯ��] ");
	gotoxy(3, 3); printf("=================================================");
	gotoxy(3, 5); printf("����� : ");
	gotoxy(3, 7); printf("������ : ");
	gotoxy(3, 9); printf("ID     : ");
	gotoxy(3, 11); printf("Seat Level : ");
	gotoxy(3, 13); printf("Seat Level List");
	gotoxy(3, 15); printf("[ 0. FirstClass ] [ 1. Business ] [ 2. Economy ]");
	gotoxy(3, 17); printf("=================================================");

	ReservInput(StartPosC, DestPosC, id, &level); // �Է¹ޱ�
	// ����ȯ
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

	// ��� ��� Ž�� �� Route_head�� ����
	DFS(&Graph_Head, StartPos, DestPos, &stack, CheckArr, &Route_head);

	// ��� ��ο� ���� cost, distance, travel time �߰�
	Route_head->level = level;
	AddCostDisTime(&Graph_Head, &Route_head, DestPos);

	// ���� ������ ���� �ʱ�ȭ
	StartPosC[0] = 0;
	StartPosC[1] = 0;
	DestPosC[0] = 0;
	DestPosC[1] = 0;

	
}

void SelectUI() {
	// ��� ��� display - Route_head �� ������ ����.
	ScreenClearFunc();
	char *cSeatLevel[3] = { "FirstClass", "Business", "Economy" };
	//gotoxy(3, 1); printf("[�����ϱ�] - [�����Է�] - [��μ���] - [Ȯ��] ");
	gotoxy(3, 1); printf("[�����ϱ�] - "); printf("[�����Է�] - "); textcolor(10); printf("[��μ���]"); textcolor(15); printf(" - [Ȯ��]");
	gotoxy(3, 3); printf("=================================================");
	gotoxy(2, 5); printf(" ��� : [ %c ]  ���� : [ %c ] ", GlobalStartPos+97, GlobalDestPos+97);
	gotoxy(2, 6); printf(" id : %s     ��� : %s ", Globalid, cSeatLevel[GlobalLevel]);
	gotoxy(2, 12); printf(" ���"); gotoxy(40, 12); printf("����           �Ÿ�              TravelTime");
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
	gotoxy(2, 9); printf(" ��μ��� : "); scanf("%d", &SelectOne);
	for (int j = 0; j < SelectOne-1; j++) { // ���õ� ��θ� ã�´�.
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
	
	// ��� �߰��ϱ�
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
	
	gotoxy(3, 1); printf("[�����ϱ�] - "); printf("[�����Է�] - ");printf("[��μ���] - "); textcolor(10); printf("[Ȯ��]"); textcolor(15);
	
	gotoxy(3, 3); printf("=================================================");
	gotoxy(2, 5); printf(" ��� : [ %c ]  ���� : [ %c ] ", GlobalStartPos + 97, GlobalDestPos + 97);
	gotoxy(2, 6); printf(" id : %s     ��� : %s ", Globalid, cSeatLevel[GlobalLevel]);
	RTnode_ptr newOne;
	int i = 0;
	gotoxy(3, 8); printf("=================================================");
	gotoxy(3, 9); printf("��� : ");
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
	gotoxy(3, 13); printf("�����Ͻðڽ��ϱ�? (y/n)"); scanf("%s", Check);
	while (getchar() != '\n'); // �����ʱ�ȭ
	switch (Check[0]) {
	case 'y':
	case'Y':
		// RT table �� �߰��ϱ�
		newOne = MakeRnodeToRTnode(Route_head);
		RTInsert(&ReserveTable_Head, newOne);
		//Route_head free�ϱ�
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



// 2) Ȯ�� �� ��� UI ============================================================
int CheckAndCancelUI() {
	char inputId[100], Check[2] = { 0, };
	char *cSeatLevel[3] = { "FirstClass", "Business", "Economy" };	//�¼���� ������ �� ����� �迭
	ScreenClearFunc();
	gotoxy(2, 1); printf("[����Ȯ��] - [���]");
	gotoxy(2, 3); printf("=================================================");
	gotoxy(2, 4); printf("ID �Է� : ");
	gotoxy(2, 5); printf("=================================================");
	gotoxy(12, 4); scanf("%[^\n]", inputId);			while (getchar() != '\n');
	//Ȯ�� �� ��ҿ��� ����. �ش� id�� ���� node�� ������ ����� ���� �ֳ���?
	gotoxy(2, 6);
	RTnode_ptr frontNode = ReserveTable_Head;

	//ReserveTable�� ������� �� return 0
	if (!frontNode) {
		printf("���� ������ �������� �ʽ��ϴ�.");

		Sleep(3000);
		return 0;
	}
	else
		//id ��ȿ ���� üũ
		while (strcmp(inputId, frontNode->id)) {
			if (frontNode->next == ReserveTable_Head) {
				printf("�������� �ʴ� id�Դϴ�.");
				Sleep(3000);
				return 0;
			}
			frontNode = frontNode->next;
		}
	gotoxy(2, 7); printf("��� : [ %c ]", frontNode->StartPos + 97);
	gotoxy(17, 7); printf("���� : [ %c ]", frontNode->DestPos + 97);
	gotoxy(2, 9); //����� ��� ����ϱ�
	printf("���: ");

	int i = 0;
	while (1) {
		printf("%c ", frontNode->ReservedRoute[i] + 97);
		if (frontNode->ReservedRoute[i++] == frontNode->DestPos)
			break;
	}
	gotoxy(2, 10); printf("Seat Level : %s", cSeatLevel[frontNode->seatLev]);
	gotoxy(2, 11); printf("���� : %0.1f", frontNode->Cost);
	gotoxy(2, 13); printf("=================================================");
	gotoxy(2, 15); printf("=================================================");
	gotoxy(2, 14); printf("������ ����Ͻðڽ��ϱ�? (y/n)"); scanf("%s", Check);
	while (getchar() != '\n');
	switch (Check[0]) {
	case 'y':
	case 'Y':
		// ��������ϱ�
		RTDelete(&ReserveTable_Head, inputId);
		gotoxy(2, 16); printf("������ ��ҵǾ����ϴ�.");
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
	char *cSeatLevel[3] = { "FirstClass", "Business", "Economy" };   //�¼���� ������ �� ����� �迭
	SeatLevel newSeatLev;
	ScreenClearFunc();
	gotoxy(2, 1); printf("[���ຯ��]");
	gotoxy(2, 3); printf("========================");
	gotoxy(2, 4); printf("ID �Է� : ");
	gotoxy(2, 5); printf("========================");
	gotoxy(12, 4); scanf("%[^\n]", inputId);         while (getchar() != '\n');
	gotoxy(2, 6);
	RTnode_ptr frontNode = ReserveTable_Head;

	//ReserveTable�� ������� �� return 0
	if (!frontNode) {
		printf("���� ������ �������� �ʽ��ϴ�.");
		Sleep(3000);
		return 0;
	}
	else
		//id ��ȿ ���� üũ
		while (strcmp(inputId, frontNode->id)) {
			if (frontNode->next == ReserveTable_Head) {
				printf("�������� �ʴ� id�Դϴ�.");
				Sleep(3000);
				return 0;
			}
			frontNode = frontNode->next;
		}
	printf("��� : %c", frontNode->StartPos + 97);
	gotoxy(2, 7); printf("���� : %c", frontNode->DestPos + 97);
	gotoxy(2, 8); printf("Seat Level : %s", cSeatLevel[frontNode->seatLev]);
	gotoxy(2, 10); printf("========================");
	gotoxy(2, 11); printf("������ �¼��� �������ּ���.");
	gotoxy(2, 12); printf("[ 0. FirstClass 1. Business 2. Economy ] ");
	gotoxy(2, 14); printf("���� : ");
	gotoxy(9, 14); scanf("%d", &newSeatLev);
	seatChange(frontNode, inputId, newSeatLev);
	gotoxy(2, 16); printf("����Ǿ����ϴ�.");
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

	// ��� ��� Ž�� �� Route_head�� ����
	DFS(&Graph_Head, StartPos, DestPos, &stack, CheckArr, &Route_head);

	// ��� ��ο� ���� cost, distance, travel time �߰�
	Route_head->level = level;
	AddCostDisTime(&Graph_Head, &Route_head, DestPos);

	int SelectOne = 2;
	for (int j = 0; j < SelectOne - 1; j++) { // ���õ� ��θ� ã�´�.
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

void init() { // �ý��� �ʱ�ȭ �ܰ�
	Stage = MAIN;
	MoveBar = 12;

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
	// 20�� �ֱ�
	RandomInsert(3, 5, "eirc8260", 2); RandomInsert(4, 1, "Jane", 1); RandomInsert(12, 11, "ELLE", 0); RandomInsert(4, 12, "Sam", 1);
	RandomInsert(5, 1, "Demonic3540", 0); RandomInsert(7, 3, "Swallow", 1); RandomInsert(4,1 , "Louis", 0); RandomInsert(0, 7, "Ellen page", 1);
	RandomInsert(11, 2, "Horoyoii", 1); RandomInsert(5,  6, "Kyale", 2); RandomInsert(6, 7, "Moondo", 1); RandomInsert(7,8 , "Ashe", 1);
	RandomInsert(10, 3, "Master Lee", 1); RandomInsert(10, 4, "Ahri", 2); RandomInsert(8, 4, "Darius", 0); RandomInsert(12, 3, "Kazhix", 1);
	RandomInsert(9, 0, "Garen", 1); RandomInsert(5, 3, "Piora", 2); RandomInsert(14, 5, "Leblank", 0); RandomInsert(0, 2, "Khogmo", 1);

	// 5��  ����
	RandomDelete("HOHO");	RandomDelete("Swallow");
	RandomDelete("Jane");	RandomDelete("Sam");
	RandomDelete("YOYO");

}

void Update() {
	// ���� Update�κ�
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
	init(); // �ʱ�ȭ
	int nKey;
	while (1) {
		switch (Stage) {
		case RESERVATION:
			ScreenRelease(); // �Է��� �ޱ� ���� screen release
			ReservationUI(); // �������� �Է¹ޱ�
			SelectUI();		// �����ϱ�
			ConfirmUI();     // ����Ȯ���ϱ�
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
		case INFO:
			if (_kbhit()) {
				nKey = _getch();
				if (nKey == 13) {
					Stage = MAIN;
				}
			}
			break;
		case CHECKALL:
			ScreenRelease(); // �Է��� �ޱ� ���� screen release
			CheckAllUI(ReserveTable_Head);
			Stage = MAIN;
			ScreenInit(); // Screen restart
			while (getchar() != '\n');
			break;
		default: // MAIN ȭ��
			if (_kbhit()) {
				nKey = _getch();
				if (nKey == 13) { // Mainȭ�鿡�� enter �Է½� MoveBar�� ����Ű�� �ִ� Stage�� ����
					Stage = MoveBar - 11;
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


