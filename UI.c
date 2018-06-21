#include"UI.h"

// 커서를 욺직이는 함수
void gotoxy(int x, int y) {
	COORD CursorPosition = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

// CLI 창의 색깔 변경함수
void textcolor(int color_number) //콘솔창 출력색상을 나타내는 함수
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}

// CLI 창의 화면을 지우는 함수
void ScreenClearFunc() {
	for (int i = 0; i < 40; i++) {
		gotoxy(0, i); printf("                                                                                                  ");
	}
}

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
	ScreenPrint(4, 2,"----------------------------------");
	ScreenPrint(7, 4, "Airline Reservation System");
	ScreenPrint(8, 6, "- Exellence in Flight -");
	ScreenPrint(4, 8, "----------------------------------");
	ScreenPrint(4, 10, "[ M E N U ]");
	ScreenPrint(4, 12, "1. 예약하기");
	ScreenPrint(4, 13, "2. 예약확인 및 취소");
	ScreenPrint(4, 14, "3. 예약 변경");
	ScreenPrint(4, 15, "4. 기본정보");
	ScreenPrint(4, 16, "5. 모든 예약현황 확인");
	ScreenPrint(0, 22, "Copyright(c) 2018 Team2. all rights reserved. ");

}

void ReservationSuccessUI() {
	ScreenClearFunc();
	gotoxy(0, 0); printf(" ");
	gotoxy(3, 4); printf("==================");
	gotoxy(4, 5); printf("예매되었습니다.");
	gotoxy(3, 6); printf("==================");

}
void ReservationFailUI() {
	ScreenClearFunc();
	gotoxy(0, 0); printf(" ");
	gotoxy(5, 5); printf("취소되었습니다.");

}

void InfoUI() {
	// 가격표 등등을 출력해주는 함수
	ScreenPrint(4, 2, "--------------Price--------------");
	ScreenPrint(4, 3, "Economy석, 기본 요금");
	ScreenPrint(4, 4, "Business석은 Economy석 가격의 1.5배");
	ScreenPrint(4, 5, "First Class석은 Economy석 가격의 2배");

	ScreenPrint(4, 7, "-------------기내식-------------");
	ScreenPrint(4, 8, "라면 : $5");
	ScreenPrint(4, 9, "비빔밥 : $13");
	ScreenPrint(4, 10, "스테이크 : $20");
	ScreenPrint(4, 11, "와인 : $10");
	ScreenPrint(4, 12, "탄산음료 : $3");
	ScreenPrint(15, 18, "Press Enter to go Back");
}

// 5) 모든 예약현황 확인 UI
void CheckAllUI(RTnode_ptr ReserveTable_Head) {
	ScreenClearFunc();
	char *cSeatLevel[3] = { "FirstClass", "Business", "Economy" };
	gotoxy(0, 0); printf(" ");
	// 저장된 모든 예약현황 출력
	gotoxy(2, 0); printf("[모든 예약현황 확인]");
	gotoxy(0, 2); printf("===================================================================================================");
	gotoxy(0, 4); printf("===================================================================================================");
	gotoxy(0, 3); printf("ID"); gotoxy(16, 3); printf("출발"); gotoxy(22, 3); printf("도착"); gotoxy(30, 3); printf("경로"); gotoxy(70, 3); printf("SeatLevel"); gotoxy(90, 3); printf("가격"); 
	// 1) 저장된 예매정보가 없는 경우
	if (ReserveTable_Head == NULL) {
		gotoxy(4, 6); printf("저장된 예매정보가 없습니다.");
		gotoxy(40, 0); printf("Press Enter to go Back");
		while (1) {
			if (_kbhit())
				break;
		}
		return;
	}
	RTnode_ptr temp = ReserveTable_Head;
	int cnt = 0;
	// 2) 하나 있는 경우
	if (temp->next == temp) {
		gotoxy(0, 5); printf("1."); gotoxy(2, 5); printf("%s", temp->id); gotoxy(14, 5); printf("  [%c]    [%c]", temp->StartPos + 97, temp->DestPos + 97);
		gotoxy(70, 5); printf(" %s", cSeatLevel[temp->seatLev]); gotoxy(90, 5); printf("$ %0.1f", temp->Cost); gotoxy(100, 5); printf("%0.1f", temp->TravelTime);
		// 경로출력
		gotoxy(26, 5);
		int i = 0;
		while (1) {
			printf("%c ", temp->ReservedRoute[i] + 97);
			if (temp->ReservedRoute[i++] == temp->DestPos)
				break;
		}
	}// 3) 둘 이상 있는 경우
	else {
		do {
			gotoxy(0, 5 + cnt); printf("%d.", cnt + 1); gotoxy(3, 5 + cnt); printf("%s", temp->id); gotoxy(14, 5 + cnt); printf("   [%c]  [%c]", temp->StartPos + 97, temp->DestPos + 97);
			gotoxy(70, 5 + cnt); printf(" %s", cSeatLevel[temp->seatLev]); gotoxy(90, 5 + cnt); printf("$ %0.1f", temp->Cost); //gotoxy(130, 5+cnt); printf("%0.1f", temp->TravelTime);
			// 경로출력
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

	gotoxy(40, 0); printf("메인화면 돌아가려면 enter 입력");
	while (1) {
		if (_kbhit())
			break;
	}
}
