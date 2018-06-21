#pragma once
#include"SelectRoutes.h"

typedef struct _RT_NODE *RTnode_ptr;


typedef enum _SEATLEVEL {
	FirstClass, Business, Economy
}SeatLevel;


typedef struct _RT_NODE {
	RTnode_ptr next;
	char id[30];
	int StartPos;
	int DestPos;
	int *ReservedRoute;
	SeatLevel seatLev;
	double Cost;
	double Distance;
	double TravelTime;
}RTNode;



void RTInsert(RTnode_ptr *head, RTnode_ptr newNode);

int RTDelete(RTnode_ptr *head, char *id);

void seatChange(RTnode_ptr frontNode, char *id, SeatLevel NewSeatLev);

