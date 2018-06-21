#pragma once
#include"gLinkedList.h"
#include"gStack.h"
#include"SelectRoutes.h"
enum { a, b, c, d, e, f, g, h, i, j, k, l, m, n, o };

// ������ �̸��� ���ȭ....
// ������ ���� ����Ʈ�� ������ ���踦 ���� ����Ʈ �� ���� �ʿ��ϴ�.

typedef struct _GRAPH *graph_ptr;
typedef struct _GRAPH {
	int numV; // ������ ��
	int numE; // ������ ��
	glist_ptr adjList; // ���������� �׷����� ������ ����Ǵ� linked list
	double Weight[15][15]; // ���� ���� ����ġ�� ������ 2���� �迭
}Graph;

// �׷��� �ʱ�ȭ
void GraphInit(graph_ptr pg, int nv);

// ���� �߰�
void AddEdge(graph_ptr pg, int fromV, int toV);

// ������ ���� ���
void ShowGraphStatus(graph_ptr pg);

//  DFS �� ���� ��� ��� Ž��
void DFS(graph_ptr pg, int startV, int GoalV, gstack_ptr gStack, int *CheckArr, Rnode_ptr *ptr);

// Ž���� ��� ��ε鿡 ���� ���, �Ÿ�, Travel time�� �߰��ϴ� �Լ�
void AddCostDisTime(graph_ptr pg, Rnode_ptr *Route_head, int DestPos);