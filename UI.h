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

// ����ȭ���� �⺻ UI
void BasicUI();

// ����ȭ��
void MainUI();

// ���� ���� �� ���ȭ��
void ReservationSuccessUI();

// ���� ���� �� ���ȭ��
void ReservationFailUI();

// �⺻���� ���ȭ��
void InfoUI();

// ��� ���� ��Ȳ ���ȭ��
void CheckAllUI(RTnode_ptr ReserveTable_Head);