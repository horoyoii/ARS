#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<string.h>
#include"RTLinkedList.h"


void Change(int *num) {
	(*num)++;
	return;
}

// 수정 head를 더블포인터로
void  RTInsert(RTnode_ptr *head, RTnode_ptr newNode) {
	if (*head == NULL) {
		*head = newNode;
		(*head)->next = *head;
		return;
	}
	RTnode_ptr frontNode = *head;
	while (frontNode->next != *head) {
		frontNode = frontNode->next;
	}

	frontNode->next = newNode;
	newNode->next = *head;

}


int RTDelete(RTnode_ptr *head, char *id) {
	// 없는 경우
	if (*head == NULL) {
		return 0 ;
	}
	// 하나있는 경우
	if ((*head)->next == *head) {
		*head = NULL;
		return 0;
	}
	// 둘 이상 (case1 헤드가 삭제되는 경우 , case 2 헤드가 아닌게 삭제되는 경우)
	RTnode_ptr frontNode = *head;
	RTnode_ptr delNode;
	while (strcmp(id, frontNode->next->id)) { // 해당 노드 탐색
		frontNode = frontNode->next;
	}
	delNode = frontNode->next;
	// 헤드가 삭제되는 경우
	if (delNode == *head) {
		frontNode->next = delNode->next;
		*head = delNode->next;
	}
	else {
		frontNode->next = delNode->next;
	}

	free(delNode);
	return 1;
}

void seatChange(RTnode_ptr frontNode, char *id, SeatLevel NewSeatLev) {
	double Royalty;
	if (frontNode->seatLev == 0)   //가격을 1배로 세팅
		Royalty = 2;
	else if (frontNode->seatLev == 1)
		Royalty = 1.5;
	else
		Royalty = 1;
	frontNode->Cost /= Royalty;
	frontNode->seatLev = NewSeatLev;   //새 좌석등급 입력

	if (frontNode->seatLev == 0)
		Royalty = 2;
	else if (frontNode->seatLev == 1)
		Royalty = 1.5;
	else
		Royalty = 1;
	frontNode->Cost *= Royalty;

}

