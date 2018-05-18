#pragma once

typedef struct _NODE *music_ptr;
typedef struct _NODE { // ÇÑ °î´ç ÇÏ ³ëµå
	int id;
	int cnt; // Àç»ýÈ½¼ö
	char title[100]; // °î¸í
	char artist[100]; // °¡¼ö¸í
	music_ptr left;
	music_ptr right;
}Node;


void LLInsert(char *title, char *artist);