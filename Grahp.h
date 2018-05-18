#pragma once
#include"LinkedList.h"
enum {A, B, C, D, E, F, G, H, I, J};

// ������ �̸��� ���ȭ....
// ������ ���� ����Ʈ�� ������ ���踦 ���� ����Ʈ �� ���� �ʿ��ϴ�.

typedef struct _GRAPH *graph_ptr;
typedef struct _GRAPH {
	int numV; // ������ ��
	int numE; // ������ ��
	list_ptr adjList;
	int *visitInfo; // DFS �� �湮�� ������ ������ ��� �迭
}Graph;

// �׷��� �ʱ�ȭ
void GraphInit(graph_ptr pg, int nv);

// �׷����� ���ҽ� ����
void GraphDestroy(graph_ptr pg);

// ���� �߰�
void AddEdge(graph_ptr pg, int fromV, int toV);

// ������ ���� ���
void ShowGraphStatus(graph_ptr pg);

void DepthFirstSearch(graph_ptr pg, int startV);
