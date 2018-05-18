#pragma once
// Dummy Node Linked List(단방향)

#define TRUE 1
#define FALSE 0

typedef int Data;

typedef struct _NODE *node_ptr;
typedef struct _NODE {
	Data data;
	node_ptr next;
}Node;

typedef struct _LINKEDLIST *list_ptr;
typedef struct _LINKEDLIST {
	node_ptr head;
	node_ptr cur; // 현재 어떤 노드를 가르키고 있다.
	node_ptr before; // 현재 가르키고 있는 어떤 노드의 전 노드를 가르키고 있다.
	int numOfData;
}LinkedList;

void ListInit(list_ptr plist);


// 노드 추가하기
void Linsert(list_ptr plist, Data data); // 

// 노드 순회하기
int LFirst(list_ptr plist, Data *data); // cur의 position을 첫 노드로 옮긴다.
										// true of false를 반환한다.  / *data에는 참조한 데이터를 저장한다. 
int LNext(list_ptr plist, Data *data); // cur의 position을 앞당긴다.

									   // 노드 삭제하기
Data LRemove(list_ptr plist);