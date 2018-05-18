#include"LinkedList.h"
#include<stdio.h>
#include<stdlib.h>

void ListInit(list_ptr plist) {
	plist->head = (node_ptr)malloc(sizeof(Node)); // 더미노드생성
	plist->head->next = NULL; // 더미노드 초기화
	plist->numOfData = 0;
}

// 노드 추가하기
// 노드의 저장위치는 더미노드 바로 다음이다.
void Linsert(list_ptr plist, Data data) {
	node_ptr newNode = (node_ptr)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = plist->head->next;
	plist->head->next = newNode;
	(plist->numOfData)++;
}

// 노드 순회하기
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

// 노드 삭제하기
//Data LRemove(list_ptr plist);