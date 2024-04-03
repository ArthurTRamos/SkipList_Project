#ifndef ITEM_H
	#define ITEM_H
	
	#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <time.h>

	typedef struct item_ ITEM;

	ITEM *item_criar(char* verbete, char* definicao);
	int item_apagar(ITEM **item);
	void item_imprimir_completo(ITEM *item);
	void item_imprimir_definicao(ITEM *item);
	char* item_get_verbete(ITEM *item);
    char* item_get_definicao(ITEM *item);
	int item_set_definicao(ITEM *item, char* definicao);

#endif