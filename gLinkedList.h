#pragma once
// Dummy Node Linked List(단방향)

#define TRUE 1
#define FALSE 0

typedef int Data;

typedef struct _gNODE *gnode_ptr;
typedef struct _gNODE {
	Data data;
	gnode_ptr next;
}gNode;

typedef struct _gLINKEDLIST *glist_ptr;
typedef struct _gLINKEDLIST {
	gnode_ptr head;
	gnode_ptr cur; // 현재 어떤 노드를 가르키고 있다.
	gnode_ptr before; // 현재 가르키고 있는 어떤 노드의 전 노드를 가르키고 있다.
	int numOfData;
}gLinkedList;

void gListInit(glist_ptr plist);


// 노드 추가하기
void gLinsert(glist_ptr plist, Data data); // 

// 노드 순회하기
int gLFirst(glist_ptr plist, Data *data); 
// cur의 position을 첫 노드로 옮긴다.
// true of false를 반환한다.  
// *data에는 참조한 데이터를 저장한다. 

int gLNext(glist_ptr plist, Data *data);
// cur의 position을 앞당긴다.
// gLFirst로 cur을 세팅 후 사용한다.

// 노드 삭제하기
Data gLRemove(glist_ptr plist);