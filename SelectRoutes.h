#pragma once
#include"RTLinkedList.h"

// ��� ��� Ž�� �� ����

typedef struct _ROUTENODE *Rnode_ptr;
typedef struct _ROUTENODE { // Ž���� ��θ� ������ ����, head point�� ������ �޾��ش�.
	int *Route;
	int StartPos;
	int DestPos;
	int level;
	char id[100];
	double cost;
	double distance;
	double traveltime;
	Rnode_ptr next;
}Rnode;

// ã�� ��θ� ������ �޾��ִ� �Լ�
void RNodeInsert(Rnode_ptr *head, Rnode_ptr new);


