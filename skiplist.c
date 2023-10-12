#include "skiplist.h"

typedef struct no_ NO;

struct no_ {
    ITEM* item;
    int nivel;
    NO* proximo;
    NO* baixo;
};

struct skiplist_ {
    int levelAtual;
    int levelmax;
    NO* upleft;
};

SKIPLIST* skip_criar(void) {

}

void skip_inserir(ITEM* item, SKIPLIST* skiplist) {

}

int skip_alterar(ITEM* item, SKIPLIST* skiplist) {
    if((skiplist != NULL) && (skip_vazia(skiplist) == 0)) {
        NO* sentinela = skiplist->upleft;

        while(sentinela->nivel != 0) {
            while(strcmp(item_get_verbete(sentinela->proximo->item), item_get_verbete(item)) < 0)
                sentinela = sentinela->proximo;
            sentinela = sentinela->baixo;
        }

        while(strcmp(item_get_verbete(sentinela->proximo->item), item_get_verbete(item)) < 0)
            sentinela = sentinela->proximo;
        
        if(strcmp(item_get_verbete(sentinela->proximo->item), item_get_verbete(item)) == 0) {
            item_set_definicao(sentinela->item, item_get_definicao(item));
            return 1;
        }
    }

    return 0;
}

void skip_remover(char* verbete, SKIPLIST* skiplist) {

}

ITEM* skip_busca(char* verbete, SKIPLIST* skiplist) {
    if((skiplist != NULL) && (skip_vazia(skiplist) == 0)) {
        NO* sentinela = skiplist->upleft;

        while(sentinela->nivel != 0) {
            while(strcmp(item_get_verbete(sentinela->proximo->item), verbete) < 0)
                sentinela = sentinela->proximo;
            sentinela = sentinela->baixo;
        }

        while(strcmp(item_get_verbete(sentinela->proximo->item), verbete) < 0)
            sentinela = sentinela->proximo;

        if(strcmp(item_get_verbete(sentinela->item), verbete) == 0)
            return(sentinela->item);
    }
    
    return NULL;
}

void skip_imprimir(char ch, SKIPLIST* skiplist) {

}

int skip_vazia(SKIPLIST* skiplist) {

}

int skip_cheia(SKIPLIST* skiplist) {
    NO* no;

    no = (NO*) malloc(sizeof(NO));

    if(no == NULL)
        return 1;
    return 0;
}

void skip_apagar(SKIPLIST** skiplist) {
    if(skiplist != NULL) {
        NO* aux;
        NO* atual;

        while((*skiplist)->upleft != NULL) {
            while(atual != NULL) {
                aux = (*skiplist)->upleft->proximo;
                atual = aux->proximo;

                free(aux);
            
                aux = atual;
                atual = atual->proximo;
            }
            free(aux);
            aux = NULL;
        }
        
        free(*skiplist);
        *skiplist = NULL;
    }
}

int gerar_nivel(int level_max) {

}
