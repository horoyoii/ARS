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
}

// 그래프의 리소스 해제
void GraphDestroy(graph_ptr pg) {

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
