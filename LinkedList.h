#pragma once
// Dummy Node Linked List(�ܹ���)

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
	node_ptr cur; // ���� � ��带 ����Ű�� �ִ�.
	node_ptr before; // ���� ����Ű�� �ִ� � ����� �� ��带 ����Ű�� �ִ�.
	int numOfData;
}LinkedList;

void ListInit(list_ptr plist);


// ��� �߰��ϱ�
void Linsert(list_ptr plist, Data data); // 

// ��� ��ȸ�ϱ�
int LFirst(list_ptr plist, Data *data); // cur�� position�� ù ���� �ű��.
										// true of false�� ��ȯ�Ѵ�.  / *data���� ������ �����͸� �����Ѵ�. 
int LNext(list_ptr plist, Data *data); // cur�� position�� �մ���.

									   // ��� �����ϱ�
Data LRemove(list_ptr plist);