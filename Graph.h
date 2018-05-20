#pragma once
#include"gLinkedList.h"
#include"gStack.h"
#include"SelectRoutes.h"
enum { a, b, c, d, e, f, g, h, i, j, k, l, m, n, o };

// 정점의 이름을 상수화....
// 정점을 이을 리스트와 정점의 관계를 이을 리스트 두 개가 필요하다.

typedef struct _GRAPH *graph_ptr;
typedef struct _GRAPH {
	int numV; // 정점의 수
	int numE; // 간선의 수
	glist_ptr adjList; // 실질적으로 그래프의 정보가 저장되는 linked list
}Graph;

// 그래프 초기화
void GraphInit(graph_ptr pg, int nv);

// 그래프의 리소스 해제
void GraphDestroy(graph_ptr pg);

// 간선 추가
void AddEdge(graph_ptr pg, int fromV, int toV);

// 간선의 정보 출력
void ShowGraphStatus(graph_ptr pg);

void DFS(graph_ptr pg, int startV, int GoalV, gstack_ptr gStack, int *CheckArr, Rnode_ptr *ptr);
