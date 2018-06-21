#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<string.h>
#include"RTLinkedList.h"


void Change(int *num) {
	(*num)++;
	return;
}

// ���� head�� ���������ͷ�
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
	// ���� ���
	if (*head == NULL) {
		return 0 ;
	}
	// �ϳ��ִ� ���
	if ((*head)->next == *head) {
		*head = NULL;
		return 0;
	}
	// �� �̻� (case1 ��尡 �����Ǵ� ��� , case 2 ��尡 �ƴѰ� �����Ǵ� ���)
	RTnode_ptr frontNode = *head;
	RTnode_ptr delNode;
	while (strcmp(id, frontNode->next->id)) { // �ش� ��� Ž��
		frontNode = frontNode->next;
	}
	delNode = frontNode->next;
	// ��尡 �����Ǵ� ���
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
	if (frontNode->seatLev == 0)   //������ 1��� ����
		Royalty = 2;
	else if (frontNode->seatLev == 1)
		Royalty = 1.5;
	else
		Royalty = 1;
	frontNode->Cost /= Royalty;
	frontNode->seatLev = NewSeatLev;   //�� �¼���� �Է�

	if (frontNode->seatLev == 0)
		Royalty = 2;
	else if (frontNode->seatLev == 1)
		Royalty = 1.5;
	else
		Royalty = 1;
	frontNode->Cost *= Royalty;

}

