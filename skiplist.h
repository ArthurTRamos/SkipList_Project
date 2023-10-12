#ifndef SKIPLIST_H
	#define SKIPLIST_H
	
	#include "item.h"

	typedef struct skiplist_ SKIPLIST;

	SKIPLIST* skip_criar(void);
    void skip_inserir(ITEM* item, SKIPLIST* skiplist);
    void skip_alterar(ITEM* item, SKIPLIST* skiplist);
    void skip_remover(char* verbete, SKIPLIST* skiplist);
    void skip_busca(char* verbete, SKIPLIST* skiplist);
    void skip_imprimir(char ch, SKIPLIST* skiplist);
    int skip_vazia(SKIPLIST* skiplist);
    int skip_cheia(SKIPLIST* skiplist);
    void skip_apagar(SKIPLIST** skiplist);
    int gerar_nivel(int level_max);

#endif