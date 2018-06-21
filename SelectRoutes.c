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





