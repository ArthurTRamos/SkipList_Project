#include "skiplist.h"

typedef struct no_ NO;
int it = 0;

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
        x->item = item_criar("\0", "\0");
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

    skip_inserir(item_criar("{", "{"),sl);
    
    return(sl);
}

int skip_inserir(ITEM* item, SKIPLIST* skiplist) {

    if((skiplist == NULL) || (skip_cheia(skiplist) == 1)) {
        printf("Erro\n");
        return 0;
    }

    NO** prox = (NO**) malloc((LEVEL_MAX + 1) * sizeof(NO*));
    NO** ant = (NO**) malloc((LEVEL_MAX + 1) * sizeof(NO*));

    NO* sentinela = skiplist->upleft;
    for(int i = LEVEL_MAX; i >= 0; --i) {
        ant[i] = sentinela;
        sentinela = sentinela->baixo;
    }

    sentinela = skiplist->upleft;

    while(sentinela->nivel != 0) {
        ant[sentinela->nivel] = sentinela;
        if(sentinela->proximo != NULL) {
            while(strcmp(item_get_verbete(sentinela->proximo->item), item_get_verbete(item)) < 0) {
                ant[sentinela->nivel] = sentinela;
                sentinela = sentinela->proximo;
            }
        }
        prox[sentinela->nivel] = sentinela->proximo;
        sentinela = sentinela->baixo;
    }

    if(sentinela->proximo != NULL) {
        while(strcmp(item_get_verbete(sentinela->proximo->item), item_get_verbete(item)) < 0) {
            ant[sentinela->nivel] = sentinela;
            sentinela = sentinela->proximo;
        }
        ant[sentinela->nivel] = sentinela;
    }

    prox[sentinela->nivel] = sentinela->proximo;
    if(sentinela->proximo != NULL) {
        if(strcmp(item_get_verbete(sentinela->proximo->item), item_get_verbete(item)) == 0) {
            printf("Erro\n");
            return 0;
        }
    }

    NO* new = (NO*) malloc(sizeof(NO));

    for(int i = gerar_nivel(); i >= 0; --i) {

        //printf("%d\n", i);
        new->item = item;
        new->nivel = i;
        new->proximo = prox[i];

        (ant[i])->proximo = new;

        if(i == 0) {
            new->baixo = NULL;
        } else {
            NO* y = (NO*) malloc(sizeof(NO));
            new->baixo = y;
            new = y;
        }
    }

    return 1;
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

int skip_remover(char* verbete, SKIPLIST* skiplist) {

    if((skiplist == NULL) || (skip_cheia(skiplist) == 1)) {
        return 0;
    }

    NO** prox = (NO**) malloc((LEVEL_MAX + 1) * sizeof(NO*));
    NO** ant = (NO**) malloc((LEVEL_MAX + 1) * sizeof(NO*));

    NO* sentinela = skiplist->upleft;
    for(int i = LEVEL_MAX; i >= 0; --i) {
        ant[i] = sentinela;
        sentinela = sentinela->baixo;
    }

    sentinela = skiplist->upleft;

    while(sentinela->nivel != 0) {
        ant[sentinela->nivel] = sentinela;
        if(sentinela->proximo != NULL) {
            while(strcmp(item_get_verbete(sentinela->proximo->item), verbete) < 0) {
                ant[sentinela->nivel] = sentinela;
                sentinela->proximo;
            }
        }
        prox[sentinela->nivel] = sentinela->proximo;
        sentinela = sentinela->baixo;
    }

    if(sentinela->proximo != NULL) {
        while(strcmp(item_get_verbete(sentinela->proximo->item), verbete) < 0) {
            ant[sentinela->nivel] = sentinela;
            sentinela = sentinela->proximo;
        }
        ant[sentinela->nivel] = sentinela;
    }

    prox[sentinela->nivel] = sentinela->proximo;
    if(sentinela->proximo != NULL) {
        if(strcmp(item_get_verbete(sentinela->proximo->item), verbete) != 0) {
            return 0;
        }
    }

    NO* aux = (NO*) malloc(sizeof(NO));

    for(int i = sentinela->nivel; i >= 0; --i) {
        aux = sentinela;
        sentinela = sentinela->baixo;
        free(aux);
        (ant[i])->proximo = prox[i];
    }

    return 1;
}

ITEM* skip_busca(char* verbete, SKIPLIST* skiplist) {
    if((skiplist != NULL) && (skip_vazia(skiplist) == 0)) {
        NO* sentinela = skiplist->upleft;

        while(sentinela->nivel != 0) {
            while(strcmp(item_get_verbete(sentinela->proximo->item), verbete) < 0)
                sentinela = sentinela->proximo;
            if(strcmp(item_get_verbete(sentinela->proximo->item), verbete) == 0)
                return(sentinela->proximo->item);
            else
                sentinela = sentinela->baixo;
        }
        
        while(strcmp(item_get_verbete(sentinela->proximo->item), verbete) < 0)
            sentinela = sentinela->proximo;

        if(strcmp(item_get_verbete(sentinela->item), verbete) == 0)
            return(sentinela->item);
    }
    
    return NULL;
}

int skip_imprimir(char ch, SKIPLIST* skiplist) {

    if((skiplist == NULL) || (skip_cheia(skiplist) == 1)) {
        printf("Erro\n");
        return 0;
    }

    NO* sentinela = skiplist->upleft->baixo->baixo->baixo->baixo;

    while((sentinela->nivel) != 0) {
        printf("%c", item_get_verbete(sentinela->proximo->item)[0]);
        if(sentinela->proximo != NULL) {
            while(item_get_verbete(sentinela->proximo->item)[0] != ch) {}
                sentinela = sentinela->proximo;
        }
        sentinela = sentinela->baixo;
    }

    if(sentinela->proximo != NULL) {
        while(item_get_verbete(sentinela->proximo->item)[0] != ch) {
            sentinela = sentinela->proximo;
        }
    }

    if(sentinela->proximo != NULL) {
        if(item_get_verbete(sentinela->proximo->item)[0] != ch) {
            printf("Erro\n");
            return 0;
        }
    }

    while(sentinela != NULL) {
        if((item_get_verbete(sentinela->item))[0] == ch) {
            item_imprimir_completo(sentinela->item);
        }
        //Ele percorre a lista inteira por algum motivo...
        //item_imprimir_completo(sentinela->item);
        sentinela = sentinela->proximo;
    }

    return 1;
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
