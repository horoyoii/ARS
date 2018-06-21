#include"Graph.h"
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include"gStack.h"
#include"gLinkedList.h"
#include"SelectRoutes.h"

// 그래프 초기화
void GraphInit(graph_ptr pg, int nv) {
	pg->adjList = (glist_ptr)malloc(sizeof(struct _gLINKEDLIST)*nv); // 정점의 수만큼 링크드리스트를 생성한다. 이는 배열이다.
	pg->numV = nv;
	pg->numE = 0;
	for (int i = 0; i < nv; i++) {
		gListInit(&(pg->adjList[i])); // 정점수만큼 생성된 리스트를 초기화 _ 더미생성
	}

	// 가중치 2차원 배열 생성
	for (int i = 0; i < 15; i++) { // 1) 0으로 초기화
		for (int j = 0; j < 15; j++) {
			pg->Weight[i][j] = 0;
		}
	}

	pg->Weight[0][1] = 1;
	pg->Weight[0][2] = 1.2;
	pg->Weight[0][14] = 7;
	pg->Weight[1][6] = 2;
	pg->Weight[1][4] = 1.7;
	pg->Weight[2][3] = 2.4;
	pg->Weight[2][11] = 2.6;
	pg->Weight[3][4] = 2.5;
	pg->Weight[3][10] = 2.7;
	pg->Weight[3][11] = 3.1;
	pg->Weight[4][5] = 2;
	pg->Weight[5][7] = 3.2;
	pg->Weight[5][8] = 3;
	pg->Weight[7][8] = 2.8;
	pg->Weight[8][13] = 4;
	pg->Weight[9][10] = 4.5;
	pg->Weight[9][13] = 5;
	pg->Weight[10][12] = 3;
	pg->Weight[11][14] = 4.1;
	pg->Weight[12][13] = 4.8;
	// 반대 복사하기
	for (int i = 0; i < 15; i++) { 
		for (int j = i; j < 15; j++) {
			if (pg->Weight[i][j])
				pg->Weight[j][i] = pg->Weight[i][j];
		}
	}
	// 가중치 그래프 완성
}

// 간선 추가
// gLinkedList[fromV] 에 toV 의 값을 연결시켜주는 것일 뿐....
void AddEdge(graph_ptr pg, int fromV, int toV) {
	pg->numE += 1;
	gLinsert(&(pg->adjList[fromV]), toV);
	gLinsert(&(pg->adjList[toV]), fromV);
}

// 간선의 정보 출력
void ShowGraphStatus(graph_ptr pg) {
	int vx;
	for (int i = 0; i < pg->numV; i++) {
		printf("%c와 연결된 정점 : ", i + 97);

		if (gLFirst(&(pg->adjList[i]), &vx)) {
			printf("%c ", vx + 97);

			while (gLNext(&(pg->adjList[i]), &vx))
				printf("%c ", vx + 97);
		}
		printf("\n");
	}
}



void RouteSave(gstack_ptr stack, Rnode_ptr *Rt, int GoalV) {
	int *Route = (int*)malloc(sizeof(int)*((stack->top) + 2));
	int tempTop = stack->top;
	Route[(stack->top) + 1] = GoalV;
	for (int i = stack->top; i>-1; i--) {
		Route[i] = gStackPop(stack);
	}
	stack->top = tempTop;

	Rnode_ptr newNode = (Rnode_ptr)malloc(sizeof(Rnode));
	newNode->Route = Route;
	newNode->next = NULL;
	RNodeInsert(Rt, newNode);
}



// startV에서 GoalV까지 가는 모든 경로 찾기
// 재귀적
void DFS(graph_ptr pg, int visitV, int GoalV, gstack_ptr stack, int *CheckArr, Rnode_ptr *Rt) {
	int nextV;				// 방문할 수 있는 정점 (연결된 정점)

							//VisitVertex(pg, visitV); // 시작 정점을 방문 - 왔던 곳이면 0, 처음 온 곳이면 1을 반환 - 배열에 마킹
							//gStackPush(stack, visitV); // 시작 정점을 푸쉬
	CheckArr[visitV] = 1;

	if (visitV == GoalV) { // 도착지 찾으면...
						   //스택의 요소를 복사하여 링크드 리스트에 목록 저장
		RouteSave(stack, Rt, GoalV);
		CheckArr[visitV] = 0;
		gStackPop(stack); // pop 
		return;
	}

	gLFirst(&(pg->adjList[visitV]), &nextV); // 정점은 최소 하나의 요소를 가지고 있는지 확인, 그래프는 이를 전부 만족
	do { // LNext함수가 정점의 linked list의 cur과 before을 움직여 나간다.

		if (CheckArr[nextV] == 0) {// 방문가능한 nextV를 찾으면
			gStackPush(stack, visitV); // 경로를 남기고
			DFS(pg, nextV, GoalV, stack, CheckArr, Rt);
		}

	} while (gLNext(&(pg->adjList[visitV]), &nextV) == TRUE);

	CheckArr[visitV] = 0;
	gStackPop(stack);
}


// 경유 한 곳당 30분(0.5) 추가
void AddCostDisTime(graph_ptr pg, Rnode_ptr *Route_head, int DestPos) {
	Rnode_ptr temp  = *Route_head;
	int i = 0;
	double cost = 0;
	double distance = 0;
	double Time = 0;
	int row;
	int col;
	double Royalty;
	if ((*Route_head)->level == 0)
		Royalty = 2;
	else if ((*Route_head)->level == 1)
		Royalty = 1.5;
	else
		Royalty = 1;
	while (temp != NULL) {
		i = 0; cost = 0; distance = 0; Time = 0;
		while (1) {
			row = temp->Route[i];
			col = temp->Route[i+1];
			Time += pg->Weight[row][col] + 0.5; // 경유마다 30분 추가
			cost += (pg->Weight[row][col])*100;
			distance += (pg->Weight[row][col]) * 100;
			if (temp->Route[i+1] == DestPos)
				break;
			i++;
		}
		temp->cost = cost*Royalty;
		temp->distance = distance;
		temp->traveltime = Time;

		temp = temp->next;
	}



}