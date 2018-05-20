#pragma once
#include"RTLinkedList.h"

// 모든 경로 탐색 및 선택

//newNode = SelectRoute(StartPos, DestPos, id, &level);
typedef struct _ROUTENODE *Rnode_ptr;
typedef struct _ROUTENODE { // 탐색된 경로를 가지는 노드들, head point에 줄줄이 달아준다.
	int *Route;
	Rnode_ptr next;
}Rnode;

void RNodeInsert(Rnode_ptr *head, Rnode_ptr new);


void ShowAllRoutes(int StartPos, int DestPos, char *id, int *level, Rnode_ptr Route_head);

RTnode_ptr SelectRoute(int StartPos, int DestPos, char *id, int *level);