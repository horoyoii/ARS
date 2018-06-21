#include"UI.h"

// Ŀ���� �����̴� �Լ�
void gotoxy(int x, int y) {
	COORD CursorPosition = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

// CLI â�� ���� �����Լ�
void textcolor(int color_number) //�ܼ�â ��»����� ��Ÿ���� �Լ�
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}

// CLI â�� ȭ���� ����� �Լ�
void ScreenClearFunc() {
	for (int i = 0; i < 40; i++) {
		gotoxy(0, i); printf("                                                                                                  ");
	}
}

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
	ScreenPrint(4, 2,"----------------------------------");
	ScreenPrint(7, 4, "Airline Reservation System");
	ScreenPrint(8, 6, "- Exellence in Flight -");
	ScreenPrint(4, 8, "----------------------------------");
	ScreenPrint(4, 10, "[ M E N U ]");
	ScreenPrint(4, 12, "1. �����ϱ�");
	ScreenPrint(4, 13, "2. ����Ȯ�� �� ���");
	ScreenPrint(4, 14, "3. ���� ����");
	ScreenPrint(4, 15, "4. �⺻����");
	ScreenPrint(4, 16, "5. ��� ������Ȳ Ȯ��");
	ScreenPrint(0, 22, "Copyright(c) 2018 Team2. all rights reserved. ");

}

void ReservationSuccessUI() {
	ScreenClearFunc();
	gotoxy(0, 0); printf(" ");
	gotoxy(3, 4); printf("==================");
	gotoxy(4, 5); printf("���ŵǾ����ϴ�.");
	gotoxy(3, 6); printf("==================");

}
void ReservationFailUI() {
	ScreenClearFunc();
	gotoxy(0, 0); printf(" ");
	gotoxy(5, 5); printf("��ҵǾ����ϴ�.");

}

void InfoUI() {
	// ����ǥ ����� ������ִ� �Լ�
	ScreenPrint(4, 2, "--------------Price--------------");
	ScreenPrint(4, 3, "Economy��, �⺻ ���");
	ScreenPrint(4, 4, "Business���� Economy�� ������ 1.5��");
	ScreenPrint(4, 5, "First Class���� Economy�� ������ 2��");

	ScreenPrint(4, 7, "-------------�⳻��-------------");
	ScreenPrint(4, 8, "��� : $5");
	ScreenPrint(4, 9, "����� : $13");
	ScreenPrint(4, 10, "������ũ : $20");
	ScreenPrint(4, 11, "���� : $10");
	ScreenPrint(4, 12, "ź������ : $3");
	ScreenPrint(15, 18, "Press Enter to go Back");
}

// 5) ��� ������Ȳ Ȯ�� UI
void CheckAllUI(RTnode_ptr ReserveTable_Head) {
	ScreenClearFunc();
	char *cSeatLevel[3] = { "FirstClass", "Business", "Economy" };
	gotoxy(0, 0); printf(" ");
	// ����� ��� ������Ȳ ���
	gotoxy(2, 0); printf("[��� ������Ȳ Ȯ��]");
	gotoxy(0, 2); printf("===================================================================================================");
	gotoxy(0, 4); printf("===================================================================================================");
	gotoxy(0, 3); printf("ID"); gotoxy(16, 3); printf("���"); gotoxy(22, 3); printf("����"); gotoxy(30, 3); printf("���"); gotoxy(70, 3); printf("SeatLevel"); gotoxy(90, 3); printf("����"); 
	// 1) ����� ���������� ���� ���
	if (ReserveTable_Head == NULL) {
		gotoxy(4, 6); printf("����� ���������� �����ϴ�.");
		gotoxy(40, 0); printf("Press Enter to go Back");
		while (1) {
			if (_kbhit())
				break;
		}
		return;
	}
	RTnode_ptr temp = ReserveTable_Head;
	int cnt = 0;
	// 2) �ϳ� �ִ� ���
	if (temp->next == temp) {
		gotoxy(0, 5); printf("1."); gotoxy(2, 5); printf("%s", temp->id); gotoxy(14, 5); printf("  [%c]    [%c]", temp->StartPos + 97, temp->DestPos + 97);
		gotoxy(70, 5); printf(" %s", cSeatLevel[temp->seatLev]); gotoxy(90, 5); printf("$ %0.1f", temp->Cost); gotoxy(100, 5); printf("%0.1f", temp->TravelTime);
		// ������
		gotoxy(26, 5);
		int i = 0;
		while (1) {
			printf("%c ", temp->ReservedRoute[i] + 97);
			if (temp->ReservedRoute[i++] == temp->DestPos)
				break;
		}
	}// 3) �� �̻� �ִ� ���
	else {
		do {
			gotoxy(0, 5 + cnt); printf("%d.", cnt + 1); gotoxy(3, 5 + cnt); printf("%s", temp->id); gotoxy(14, 5 + cnt); printf("   [%c]  [%c]", temp->StartPos + 97, temp->DestPos + 97);
			gotoxy(70, 5 + cnt); printf(" %s", cSeatLevel[temp->seatLev]); gotoxy(90, 5 + cnt); printf("$ %0.1f", temp->Cost); //gotoxy(130, 5+cnt); printf("%0.1f", temp->TravelTime);
			// ������
			gotoxy(30, 5 + cnt);
			int i = 0;
			while (1) {
				printf("%c ", temp->ReservedRoute[i] + 97);
				if (temp->ReservedRoute[i++] == temp->DestPos)
					break;
			}
			cnt++;
			temp = temp->next;
		} while (temp != ReserveTable_Head);

	}

	gotoxy(40, 0); printf("����ȭ�� ���ư����� enter �Է�");
	while (1) {
		if (_kbhit())
			break;
	}
}
