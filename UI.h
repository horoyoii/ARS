#pragma once
#include<stdlib.h>
#include<time.h>
#include<ctype.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include"Screen.h"
#include"UI.h"
#include"RTLinkedList.h"
void gotoxy(int x, int y);

void ScreenClearFunc();

void textcolor(int color_number);

// 메인화면의 기본 UI
void BasicUI();

// 메인화면
void MainUI();

// 예매 성공 시 출력화면
void ReservationSuccessUI();

// 예매 실패 시 출력화면
void ReservationFailUI();

// 기본정보 출력화면
void InfoUI();

// 모든 예약 현황 출력화면
void CheckAllUI(RTnode_ptr ReserveTable_Head);