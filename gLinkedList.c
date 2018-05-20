#include"gLinkedList.h"
#include<stdio.h>
#include<stdlib.h>

void gListInit(glist_ptr plist) {
	plist->head = (gnode_ptr)malloc(sizeof(gNode)); // 더미노드생성
	plist->head->next = NULL; // 더미노드 초기화
	plist->numOfData = 0;
}

// 노드 추가하기
// 노드의 저장위치는 더미노드 바로 다음이다.
void gLinsert(glist_ptr plist, Data data) {
	gnode_ptr newNode = (gnode_ptr)malloc(sizeof(gNode));
	newNode->data = data;
	newNode->next = plist->head->next;
	plist->head->next = newNode;
	(plist->numOfData)++;
}

// 노드 순회하기
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

// 노드 삭제하기
//Data LRemove(list_ptr plist);