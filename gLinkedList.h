#pragma once
// Dummy Node Linked List(�ܹ���)

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
	gnode_ptr cur; // ���� � ��带 ����Ű�� �ִ�.
	gnode_ptr before; // ���� ����Ű�� �ִ� � ����� �� ��带 ����Ű�� �ִ�.
	int numOfData;
}gLinkedList;

void gListInit(glist_ptr plist);


// ��� �߰��ϱ�
void gLinsert(glist_ptr plist, Data data); // 

// ��� ��ȸ�ϱ�
int gLFirst(glist_ptr plist, Data *data); 
// cur�� position�� ù ���� �ű��.
// true of false�� ��ȯ�Ѵ�.  
// *data���� ������ �����͸� �����Ѵ�. 

int gLNext(glist_ptr plist, Data *data);
// cur�� position�� �մ���.
// gLFirst�� cur�� ���� �� ����Ѵ�.

// ��� �����ϱ�
Data gLRemove(glist_ptr plist);