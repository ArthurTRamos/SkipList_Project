#include "item.h"

struct item_ {
    char verbete[51];
    char definicao[141];
};

ITEM *item_criar(char* verbete, char* definicao) {
    ITEM* item;

    item = (ITEM*) malloc(sizeof(item));
    if(item != NULL) {
        strcpy(item->verbete, verbete);
        strcpy(item->definicao, definicao);
    }
    return item;
}

int item_apagar(ITEM** item) {
    if(*item != NULL) {
        free(*item);
        *item = NULL;
        return 1;
    }
    return 0;
}

void item_imprimir_completo(ITEM *item) {
    if(item != NULL) {
        printf("%s %s", item->verbete, item->definicao);
    }
}

void item_imprimir_definicao(ITEM *item) {
    if(item != NULL) {
        printf("%s", item->definicao);
    }
}

char* item_get_verbete(ITEM *item) {
    if(item != NULL) {
        return(item->verbete);
    }
    return NULL;
}


int item_set_definicao(ITEM *item, char* definicao) {
    if(item != NULL) {
        strcpy(item->definicao, definicao);
        return 1;
    }
    return 0;
}
