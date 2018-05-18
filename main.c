#include<stdio.h>
#include"Grahp.h"

// Linked list 기반 그래프 구현
// 무방향 그래프 구현
int main(void) {
	Graph graph; // 그래프 생성
	GraphInit(&graph, 5); // 그래프의 초기화

	// 간선 연결
	AddEdge(&graph, A, B);
	AddEdge(&graph, A, D);
	AddEdge(&graph, B, C);
	AddEdge(&graph, C, D);
	AddEdge(&graph, D, E);
	AddEdge(&graph, E, A);

	// 간선 정보 출력
	ShowGraphStatus(&graph);

	puts(" ");

	//DepthFirstSearch(&graph, A);
	BreadthFirstSearch(&graph, B);
	return 0;
}