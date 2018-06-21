#pragma once
#include"RTLinkedList.h"

// 모든 경로 탐색 및 선택

typedef struct _ROUTENODE *Rnode_ptr;
typedef struct _ROUTENODE { // 탐색된 경로를 가지는 노드들, head point에 줄줄이 달아준다.
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

// 찾은 경로를 줄줄이 달아주는 함수
void RNodeInsert(Rnode_ptr *head, Rnode_ptr new);


