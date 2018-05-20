#pragma once

typedef struct _RT_NODE *RTnode_ptr;

typedef struct _RT_NODE {
	char id[30];
	char StartPos;
	char DestPos;
	//RouteNode_ptr ReservedRoute;
	int SeatLevel;
	int Cost;
	int  Distance;
	int TravelTime;
}RTNode;


void RTInsert(RTnode_ptr head, RTnode_ptr newNode);