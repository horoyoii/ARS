#include"Graph.h"
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include"gStack.h"
#include"gLinkedList.h"
#include"SelectRoutes.h"

// �׷��� �ʱ�ȭ
void GraphInit(graph_ptr pg, int nv) {
	pg->adjList = (glist_ptr)malloc(sizeof(struct _gLINKEDLIST)*nv); // ������ ����ŭ ��ũ�帮��Ʈ�� �����Ѵ�. �̴� �迭�̴�.
	pg->numV = nv;
	pg->numE = 0;
	for (int i = 0; i < nv; i++) {
		gListInit(&(pg->adjList[i])); // ��������ŭ ������ ����Ʈ�� �ʱ�ȭ _ ���̻���
	}
}

// �׷����� ���ҽ� ����
void GraphDestroy(graph_ptr pg) {

}

// ���� �߰�
// gLinkedList[fromV] �� toV �� ���� ��������ִ� ���� ��....
void AddEdge(graph_ptr pg, int fromV, int toV) {
	pg->numE += 1;
	gLinsert(&(pg->adjList[fromV]), toV);
	gLinsert(&(pg->adjList[toV]), fromV);
}

// ������ ���� ���
void ShowGraphStatus(graph_ptr pg) {
	int vx;
	for (int i = 0; i < pg->numV; i++) {
		printf("%c�� ����� ���� : ", i + 97);

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

// startV���� GoalV���� ���� ��� ��� ã��
// �����
void DFS(graph_ptr pg, int visitV, int GoalV, gstack_ptr stack, int *CheckArr, Rnode_ptr *Rt) {
	int nextV;				// �湮�� �� �ִ� ���� (����� ����)

							//VisitVertex(pg, visitV); // ���� ������ �湮 - �Դ� ���̸� 0, ó�� �� ���̸� 1�� ��ȯ - �迭�� ��ŷ
							//gStackPush(stack, visitV); // ���� ������ Ǫ��
	CheckArr[visitV] = 1;

	if (visitV == GoalV) { // ������ ã����...
						   //������ ��Ҹ� �����Ͽ� ��ũ�� ����Ʈ�� ��� ����
		RouteSave(stack, Rt, GoalV);
		CheckArr[visitV] = 0;
		gStackPop(stack); // pop 
		return;
	}

	gLFirst(&(pg->adjList[visitV]), &nextV); // ������ �ּ� �ϳ��� ��Ҹ� ������ �ִ��� Ȯ��, �׷����� �̸� ���� ����
	do { // LNext�Լ��� ������ linked list�� cur�� before�� ������ ������.

		if (CheckArr[nextV] == 0) {// �湮������ nextV�� ã����
			gStackPush(stack, visitV); // ��θ� �����
			DFS(pg, nextV, GoalV, stack, CheckArr, Rt);
		}

	} while (gLNext(&(pg->adjList[visitV]), &nextV) == TRUE);

	CheckArr[visitV] = 0;
	gStackPop(stack);
}
