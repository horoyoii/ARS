#pragma once
#include"RTLinkedList.h"

// ��� ��� Ž�� �� ����

//newNode = SelectRoute(StartPos, DestPos, id, &level);
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

void RNodeInsert(Rnode_ptr *head, Rnode_ptr new);


void ShowAllRoutes(Rnode_ptr Route_head);

RTnode_ptr SelectRoute(int StartPos, int DestPos, char *id, int *level);