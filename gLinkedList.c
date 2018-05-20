#include"gLinkedList.h"
#include<stdio.h>
#include<stdlib.h>

void gListInit(glist_ptr plist) {
	plist->head = (gnode_ptr)malloc(sizeof(gNode)); // ���̳�����
	plist->head->next = NULL; // ���̳�� �ʱ�ȭ
	plist->numOfData = 0;
}

// ��� �߰��ϱ�
// ����� ������ġ�� ���̳�� �ٷ� �����̴�.
void gLinsert(glist_ptr plist, Data data) {
	gnode_ptr newNode = (gnode_ptr)malloc(sizeof(gNode));
	newNode->data = data;
	newNode->next = plist->head->next;
	plist->head->next = newNode;
	(plist->numOfData)++;
}

// ��� ��ȸ�ϱ�
int gLFirst(glist_ptr plist, Data *data) {
	if (plist->head->next == NULL)
		return FALSE;
	plist->before = plist->head;
	plist->cur = plist->head->next;
	*data = plist->cur->data;
	return TRUE;
}
int gLNext(glist_ptr plist, Data *data) {
	if (plist->cur->next == NULL)
		return FALSE;
	plist->before = plist->cur;
	plist->cur = plist->cur->next;

	*data = plist->cur->data;
	return TRUE;
}

// ��� �����ϱ�
//Data LRemove(list_ptr plist);