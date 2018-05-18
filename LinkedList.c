#include"LinkedList.h"
#include<stdio.h>
#include<stdlib.h>

void ListInit(list_ptr plist) {
	plist->head = (node_ptr)malloc(sizeof(Node)); // ���̳�����
	plist->head->next = NULL; // ���̳�� �ʱ�ȭ
	plist->numOfData = 0;
}

// ��� �߰��ϱ�
// ����� ������ġ�� ���̳�� �ٷ� �����̴�.
void Linsert(list_ptr plist, Data data) {
	node_ptr newNode = (node_ptr)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = plist->head->next;
	plist->head->next = newNode;
	(plist->numOfData)++;
}

// ��� ��ȸ�ϱ�
int LFirst(list_ptr plist, Data *data) {
	if (plist->head->next == NULL)
		return FALSE;
	plist->before = plist->head;
	plist->cur = plist->head->next;
	*data = plist->cur->data;
	return TRUE;
}
int LNext(list_ptr plist, Data *data) {
	if (plist->cur->next == NULL)
		return FALSE;
	plist->before = plist->cur;
	plist->cur = plist->cur->next;

	*data = plist->cur->data;
	return TRUE;
}

// ��� �����ϱ�
//Data LRemove(list_ptr plist);