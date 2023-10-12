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

SKIPLIST* skip_criar() {
    SKIPLIST *sl = (SKIPLIST*) malloc(sizeof(SKIPLIST));
    sl->levelAtual = 0;
    sl->levelmax = LEVEL_MAX;
    
    NO* x = (NO*) malloc(sizeof(NO));
    sl->upleft = x;
    
    for(int i = sl->levelmax; i >= 0; --i) {
        x->item = item_criar("-1", "-1");
        x->nivel = i;
        x->proximo = NULL;
        if(i == 0) {
            x->baixo = NULL;
        } else {
            NO* y = (NO*) malloc(sizeof(NO));
            x->baixo = y;
            x = y;
        }
    }
    
    return(sl);
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
    NO* carry = skiplist->upleft;
    NO* aux;
    int achado = 0;

    while(carry != NULL) {
        while(carry->proximo != NULL) {

            if(item_get_verbete(carry->proximo->item)[0] == ch) {
                if(carry->baixo == NULL) {
                    achado = 1;
                    break;
                }
                carry = carry->baixo;
            }

            if(item_get_verbete(carry->proximo->item)[0] > ch) {
                if(carry->baixo == NULL) {
                    break;
                }
                carry = carry->baixo;
            }

            carry = carry->proximo;
        }

        if(achado == 1) {
            break;
        }

        if(carry->baixo == NULL) {
            printf("erro");
            exit(1);
        }

        aux = skiplist->upleft->baixo;
        while(aux->nivel != carry->nivel - 1) {
            aux = aux->baixo;
        }
        carry = aux;
    }


    while(carry->proximo != NULL) {
        if((item_get_verbete(carry->proximo->item))[0] == ch) {
            item_imprimir_completo(carry->proximo->item);
        } else {
            break;
        }
        carry = carry->proximo;
    }
}

int skip_vazia(SKIPLIST* sl) {
    if(sl == NULL) {
        return 1;
    }

    NO* aux = sl->upleft;
    while(aux->baixo != NULL) {
        aux = aux->baixo;
    }

    if(aux->proximo == NULL) {
        return 1;
    }
    
    return 0;
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

int gerar_nivel() {
    srand(time(0));
    int lvl = 0;
    
    while(lvl < LEVEL_MAX) {
        if(rand()%2) {
            ++lvl;
        } else {
            break;
        }
    }
    return(lvl);
}
