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


// 인터페이스 단계 구성
typedef enum _STAGE {
	MAIN, RECENTa, MOSTLY, RECENTp, FAVORITE, PLAYING, INSERTS, DELETES
// 시작화면, 최근추가, 많이재생, 최근재생, 즐겨찾기, 재생중,   곡추가   , 곡삭제
}STAGE;
STAGE Stage;


char title[100];
char artist[100];

void BasicUI() {
	ScreenPrint(0, 0, "□□□□□□□□□□□□□□□□□□□□□");
	for (int i = 1; i < 20; i++) {
		ScreenPrint(0, i, "□\t\t\t\t\t□");
	}
	ScreenPrint(0, 20, "□□□□□□□□□□□□□□□□□□□□□");
}

void MainUI() {
	ScreenPrint(4, 2, "1. 예약하기");
	ScreenPrint(4, 3, "2. 예약확인하기");
	ScreenPrint(4, 4, "3. 최단경로 검색");
	ScreenPrint(4, 5, "4. 편도/왕복");
	ScreenPrint(4, 6, "5. 이코노미 / 비지니스 / 일반");
	ScreenPrint(4, 7, "6. 성인 / 아동 / 명수");
	ScreenPrint(4, 8, "7. 잔여석");
}
int MoveBar;
void SelectBAR(int Move) {
	ScreenPrint(2, Move, "▶");
}

void RecentlyAddUI() {
	ScreenPrint(2, 2, "예약하기");
	ScreenPrint(2, 3, title);

	ScreenPrint(2, 4, artist);
}

void MostlyPlayUI() {
	ScreenPrint(2, 2, "예약확인하기");
}

void RecentlyPlayUI() {
	ScreenPrint(2, 2, "최근에 재생한 곡 목록");
}

void FavoriteUI() {
	ScreenPrint(2, 2, "즐겨찾기 목록");
}

void PlayingUI() {
	ScreenPrint(2, 2, "재생 중");
}

void InsertUI() {
	gotoxy(10, 5); printf("                           ");
	gotoxy(11, 6); printf("                           ");
	gotoxy(2, 4); printf("곡 추가");
	gotoxy(2, 5); printf("곡명 : ");
	gotoxy(2, 6); printf("가수명 : ");
	gotoxy(10, 5); fgets(title,100, stdin);
	gotoxy(11, 6); fgets(artist, 100, stdin);
	fflush(stdin);
	//LLInsert(title, artist); // 링크드 리스트에 추가하는 작업 수행
	if (1) {
		gotoxy(5, 8); printf("곡 추가 완료!");
	}
	else
		gotoxy(5, 8); printf("곡 추가 실패");
	Sleep(1500);
}
void DeleteUI() {
	gotoxy(10, 5); printf("                         ");
	gotoxy(11, 6); printf("                         ");
	gotoxy(2, 4); printf("곡 삭제");
	gotoxy(2, 5); printf("곡명 : ");
	gotoxy(2, 6); printf("가수명 : ");
	gotoxy(10, 5); fgets(title, 100, stdin);
	gotoxy(11, 6); fgets(artist, 100, stdin);
	fflush(stdin);
	//LLDelete(title, artist); // 링크드 리스트에 삭제하는 작업 수행
	if (1) {
		gotoxy(5, 8); printf("곡 삭제 완료!");
	}
	else
		gotoxy(5, 8); printf("곡 삭제 실패");
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
	//출력코드
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
	init(); // 초기화
	int nKey;
	while (1) {
		switch (Stage) {
		case INSERTS:
			ScreenRelease(); // 입력을 받기 위한 screen release
			InsertUI();
			Stage = MAIN;
			ScreenInit(); // Screen restart
			break;
		case DELETES:
			ScreenRelease(); // 입력을 받기 위한 screen release
			DeleteUI();
			Stage = MAIN;
			ScreenInit(); // Screen restart
			break;
		case PLAYING:
			// 다음곡 재생, 전곡 재생, 즐겨찾기 추가, 뒤로가기 등등
			break;
		default: // MAIN 화면
			if (_kbhit()) {
				nKey = _getch();
				if (nKey == 13) { // enter 입력시
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