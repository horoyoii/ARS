#include"Graph.h"
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include"gStack.h"
#include"gLinkedList.h"
// �׷��� �ʱ�ȭ
void GraphInit(graph_ptr pg, int nv) {
	pg->adjList = (glist_ptr)malloc(sizeof(struct _gLINKEDLIST)*nv); // ������ ����ŭ ��ũ�帮��Ʈ�� �����Ѵ�. �̴� �迭�̴�.
	pg->visitInfo = (int*)malloc(sizeof(int)*nv); // �湮�� ������ ���� �迭 �ʱ�ȭ
	pg->numV = nv;
	pg->numE = 0;
	for (int i = 0; i < nv; i++) {
		gListInit(&(pg->adjList[i])); // ��������ŭ ������ ����Ʈ�� �ʱ�ȭ _ ���̻���
		memset(pg->visitInfo, 0, sizeof(int)*nv);
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
		printf("%c�� ����� ���� : ", i + 65);

		if (gLFirst(&(pg->adjList[i]), &vx)) {
			printf("%c ", vx + 65);

			while (gLNext(&(pg->adjList[i]), &vx))
				printf("%c ", vx + 65);
		}
		printf("\n");
	}
}

int VisitVertex(graph_ptr pg, int visitV) {
	if (pg->visitInfo[visitV] == 0) { // visitV vertex �� �湮�� ó���̸�...
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
	VisitVertex(pg, visitV); // ���� ������ �湮
	gStackPush(&stack, visitV); // ���� ������ Ǫ��

	while (gLFirst(&(pg->adjList[visitV]), &nextV) == TRUE) { // ������ �ּ� �ϳ��� ��Ҹ� ������ �ִ��� Ȯ��, �׷����� �̸� ���� ����
		int visitFlag = FALSE;

		if (VisitVertex(pg, nextV) == TRUE) { // nextV ������ �湮�Ͽ��ٸ�, (���ʹ湮)
			gStackPush(&stack, visitV);
			visitV = nextV;
			visitFlag = TRUE;
		}
		else { // �湮���н� (�̹� �湮��), visitiV�� ����� �ٸ� ������ Ž���Ѵ�.
			while (gLNext(&(pg->adjList[visitV]), &nextV) == TRUE) { // LNext�Լ��� ������ linked list�� cur�� before�� ������ ������.
				if (VisitVertex(pg, nextV) == TRUE) {// �湮������ nextV�� ã����
					gStackPush(&stack, visitV); // ��θ� �����
					visitV = nextV;
					visitFlag = TRUE;
					break;
				}

			}
		}

		if (visitFlag == FALSE) { // VisitV �������� �� �̻� �湮�� �� �ִ� ������ ���ٸ� ��Ʈ��ŷ �ǽ�
			if (gStackIsEmpty(&stack) == TRUE)
				break;
			else
				visitV = gStackPop(&stack);
		}

	}

}
