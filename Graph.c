#include"Graph.h"
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include"gStack.h"
#include"gLinkedList.h"
// 그래프 초기화
void GraphInit(graph_ptr pg, int nv) {
	pg->adjList = (glist_ptr)malloc(sizeof(struct _gLINKEDLIST)*nv); // 정점의 수만큼 링크드리스트를 생성한다. 이는 배열이다.
	pg->visitInfo = (int*)malloc(sizeof(int)*nv); // 방문할 정점을 담을 배열 초기화
	pg->numV = nv;
	pg->numE = 0;
	for (int i = 0; i < nv; i++) {
		gListInit(&(pg->adjList[i])); // 정점수만큼 생성된 리스트를 초기화 _ 더미생성
		memset(pg->visitInfo, 0, sizeof(int)*nv);
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
		printf("%c와 연결된 정점 : ", i + 65);

		if (gLFirst(&(pg->adjList[i]), &vx)) {
			printf("%c ", vx + 65);

			while (gLNext(&(pg->adjList[i]), &vx))
				printf("%c ", vx + 65);
		}
		printf("\n");
	}
}

int VisitVertex(graph_ptr pg, int visitV) {
	if (pg->visitInfo[visitV] == 0) { // visitV vertex 의 방문이 처음이면...
		pg->visitInfo[visitV] = 1;
		printf("%c ", visitV + 65);
		return TRUE;
	}
	return FALSE;
}

void DepthFirstSearch(graph_ptr pg, int startV) {
	gStack stack;
	int visitV = startV;
	int nextV;

	gStackInit(&stack);
	VisitVertex(pg, visitV); // 시작 정점을 방문
	gStackPush(&stack, visitV); // 시작 정점을 푸쉬

	while (gLFirst(&(pg->adjList[visitV]), &nextV) == TRUE) { // 정점은 최소 하나의 요소를 가지고 있는지 확인, 그래프는 이를 전부 만족
		int visitFlag = FALSE;

		if (VisitVertex(pg, nextV) == TRUE) { // nextV 정점에 방문하였다면, (최초방문)
			gStackPush(&stack, visitV);
			visitV = nextV;
			visitFlag = TRUE;
		}
		else { // 방문실패시 (이미 방문시), visitiV와 연결되 다른 정점을 탐색한다.
			while (gLNext(&(pg->adjList[visitV]), &nextV) == TRUE) { // LNext함수가 정점의 linked list의 cur과 before을 움직여 나간다.
				if (VisitVertex(pg, nextV) == TRUE) {// 방문가능한 nextV를 찾으면
					gStackPush(&stack, visitV); // 경로를 남기고
					visitV = nextV;
					visitFlag = TRUE;
					break;
				}

			}
		}

		if (visitFlag == FALSE) { // VisitV 정점에서 더 이상 방문할 수 있는 정점이 없다면 백트래킹 실시
			if (gStackIsEmpty(&stack) == TRUE)
				break;
			else
				visitV = gStackPop(&stack);
		}

	}

}
