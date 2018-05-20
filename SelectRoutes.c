#include"SelectRoutes.h"
#include"Graph.h" // dfs Å½»ö
#include"UI.h"
#include"SelectRoutes.h"
#include"Graph.h" // dfs Å½»ö
#include"UI.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void RNodeInsert(Rnode_ptr *head, Rnode_ptr new) {
	if ((*head) == NULL) {
		*head = new;
	}
	else {
		new->next = (*head)->next;
		(*head)->next = new;
	}
}

void ShowAllRoutes(int StartPos, int DestPos, char *id, int *level, Rnode_ptr Route_head) {
	//ScreenClearFunc();
	int i = 0;
	while (Route_head != NULL) {
		i = 0;
		while (1) {
			printf("%c ", Route_head->Route[i]+97);
			if (Route_head->Route[i++] == DestPos)
				break;
		}
		puts("  ");
		Route_head = Route_head->next;
	}
}

RTnode_ptr SelectRoute(int StartPos, int DestPos, char *id, int *level) {

}

