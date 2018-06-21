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

	// ����ġ 2���� �迭 ����
	for (int i = 0; i < 15; i++) { // 1) 0���� �ʱ�ȭ
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
	// �ݴ� �����ϱ�
	for (int i = 0; i < 15; i++) { 
		for (int j = i; j < 15; j++) {
			if (pg->Weight[i][j])
				pg->Weight[j][i] = pg->Weight[i][j];
		}
	}
	// ����ġ �׷��� �ϼ�
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


// ���� �� ���� 30��(0.5) �߰�
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
			Time += pg->Weight[row][col] + 0.5; // �������� 30�� �߰�
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