#pragma once

typedef struct _NODE *music_ptr;
typedef struct _NODE { // �� ��� �� ���
	int id;
	int cnt; // ���Ƚ��
	char title[100]; // ���
	char artist[100]; // ������
	music_ptr left;
	music_ptr right;
}Node;


void LLInsert(char *title, char *artist);