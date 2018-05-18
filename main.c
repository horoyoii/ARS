#include<stdio.h>
#include"Grahp.h"

// Linked list ��� �׷��� ����
// ������ �׷��� ����
int main(void) {
	Graph graph; // �׷��� ����
	GraphInit(&graph, 5); // �׷����� �ʱ�ȭ

	// ���� ����
	AddEdge(&graph, A, B);
	AddEdge(&graph, A, D);
	AddEdge(&graph, B, C);
	AddEdge(&graph, C, D);
	AddEdge(&graph, D, E);
	AddEdge(&graph, E, A);

	// ���� ���� ���
	ShowGraphStatus(&graph);

	puts(" ");

	//DepthFirstSearch(&graph, A);
	BreadthFirstSearch(&graph, B);
	return 0;
}