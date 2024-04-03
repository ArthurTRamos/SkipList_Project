#include "skiplist.h"

typedef struct no_ NO;

struct no_ {
    ITEM* item;
    int nivel;
    NO* proximo;
    NO* baixo;
};

struct skiplist_ {
    NO* upleft;
};

SKIPLIST* skip_criar() {
    //Aloca o cabeçalho da skiplist;
    SKIPLIST *sl = (SKIPLIST*) malloc(sizeof(SKIPLIST));
    if(sl == NULL)
        return NULL;
    
    //Cria o topo do nó cabeça;
    NO* x = (NO*) malloc(sizeof(NO));
    sl->upleft = x;
    //Cria um item de conteúdo menor do alfabeto para se colocar no nó cabeça;
    ITEM* item = item_criar("0", "0");
    
    //Configura a cabeça de acordo com o nível máximo;
    for(int i = LEVEL_MAX; i >= 0; --i) {
        x->item = item;
        x->nivel = i;
        x->proximo = NULL;
        if(i == 0) {
            //Faz a base apontar para NULL;
            x->baixo = NULL;
        } else {
            //Cria o nó de baixo, faz o atual apontar para ele e desce;
            NO* y = (NO*) malloc(sizeof(NO));
            x->baixo = y;
            x = y;
        }
    }
    
    //Retorna a lista criada.
    return(sl);
}

int skip_inserir(ITEM* item, SKIPLIST* skiplist) {

    //Verifica se é possível inserir na lista;
    if((skiplist == NULL) || (skip_cheia(skiplist) == 1))
        return 0;

    //Cria o nó que percorrerá a skiplist e um array de nós para suporte;
    NO* atual = skiplist->upleft;
    NO** aux = (NO**) malloc((LEVEL_MAX + 1) * sizeof(NO*));

    //Inicializa o auxiliar;
    for(int i = LEVEL_MAX; i >= 0; --i)
        aux[i] = NULL;

    for(int i = LEVEL_MAX; i >= 0; --i) {
        //Percorre a skiplist, de cima para baixo, da esquerda para a direita;
        if(atual->proximo != NULL) {
            while(strcmp(item_get_verbete(atual->proximo->item), item_get_verbete(item)) < 0) {
                //Para de percorrer a lista ao encontrar um item maior ou igual ao que se deseja ser inserido;
                atual = atual->proximo;
                if(atual->proximo == NULL) {
                    break;
                }
            }
        }
        aux[i] = atual;
        //Armazena o anterior ao maior (ou anterior ao seu igual) no array auxiliar;
        if(atual->baixo != NULL) {
            //E então, se já não estiver na base, desce um nível e repete o processo;
            atual = atual->baixo; 
        }
    }

    //Avança para o ponteiro maior/igual/NULL;
    if(atual != NULL)
        atual = atual->proximo;

    int verify = 0;

    //Se não for NULL ou for igual ao desejado, cancela a função;
    if(atual == NULL) {
        verify = 1;
    } else {
        if(strcmp(item_get_verbete(atual->item), item_get_verbete(item)) != 0) {
            verify = 1;
        }
    }

    if(verify == 1) {
        //Caso contrário, inicia a inserção;

        //Gera o nível maxímo da palavra;
        int n = gerar_nivel();

        //Gera o novo nó;
        NO* new = (NO*) malloc(sizeof(NO));
        NO* reserva = new;

        //Configura os nós da palavra de acordo com seu nível;
        for(int i = n; i >= 0; --i) {
            new->item = item;
            new->nivel = i;
            new->proximo = NULL;
            if(i == 0) {
                //Faz a base apontar para NULL;
                new->baixo = NULL;
            } else {
                //Cria o nó de baixo, faz o atual apontar para ele e desce;
                NO* y = (NO*) malloc(sizeof(NO));
                new->baixo = y;
                new = y;
            }
        }

        //Retorna ao topo da palavra;
        new = reserva;

        for(int i = n; i >= 0; i--) {
            //De acordo com o nível da palavra
            //Faz os nós da palavra apontarem para os próximos dos auxiliares
            new->proximo = (aux[i])->proximo;
            //E os auxiliares apontarem para os nós da palavra;
            (aux[i])->proximo = new;
            new = new->baixo;
        }

        //Libera o auxiliar e confirma a inserção;
        free(aux);
        return 1;
    }

    //Libera o auxiliar e reporta o erro da inserção.
    free(aux);
    return 0;

}

int skip_alterar(ITEM* item, SKIPLIST* skiplist) {
    if (skiplist != NULL && skip_vazia(skiplist) == 0) {
        NO* sentinela = skiplist->upleft;

        while (sentinela != NULL) {
            if (sentinela->proximo != NULL) {
                //Compara os tamanhos e ordens dos verbetes de sentinela->proximo e do item;
                int cmp = strcmp(item_get_verbete(sentinela->proximo->item), item_get_verbete(item));
                //Se o verbete do item de sentinela->proximo é maior do que o verbete procurado
                //e está no nível base, o programa retorna erro;
                if((cmp > 0) && (sentinela->nivel == 0))
                    return 0;
                //Se achar o item, altera a definição para alterar todos os nós até o nível 0 da skiplist;
                if (cmp == 0) {
                    item_set_definicao(sentinela->proximo->item, item_get_definicao(item));
                    sentinela = sentinela->proximo->baixo;
                    //Percorre os níveis alterando as definições e retorna que a alteração deu certo;
                    while(sentinela != NULL) {
                        item_set_definicao(sentinela->item, item_get_definicao(item));
                        sentinela = sentinela->baixo;
                    }
                    return 1;
                } else if (cmp < 0) { //Se o verbete é menor, vai para o próximo nó;
                    sentinela = sentinela->proximo;
                } else { //Se o verbete é maior e não está no nível 0, desce um nível;
                    sentinela = sentinela->baixo;
                }
            } else { //Se chegou no fim do nível, desce para o próximo;
                sentinela = sentinela->baixo;
            }
        }
    }
    return 0;
}

int skip_remover(char* verbete, SKIPLIST* skiplist) {

    //Verifica se é possível remover itens;
    if(skip_vazia(skiplist))
        return 0;

    //Cria o nó que percorrerá a skiplist e um array de nós para suporte;
    NO* atual = skiplist->upleft;
    NO** aux = (NO**) malloc((LEVEL_MAX + 1) * sizeof(NO*));

    //Inicializa o auxiliar;
    for(int i = LEVEL_MAX; i >= 0; --i)
        aux[i] = NULL;

    for(int i = LEVEL_MAX; i >= 0; --i) {
        //Percorre a skiplist de cima pra baixo, da esquerda pra direita;
        if(atual->proximo != NULL) {
            while(strcmp(item_get_verbete(atual->proximo->item), verbete) < 0) {
                //Para de percorrer a lista ao encontrar um item maior ou igual ao que se deseja ser removido;
                atual = atual->proximo;
                if(atual->proximo == NULL)
                    break;
            }
        }
        //Armazena o anterior ao que se deseja removido (ou anterior ao seu maior) no array auxiliar;
        aux[i] = atual;
        if(atual->baixo != NULL) {
            //E então, se já não estiver na base, desce um nível e repete o processo;
            atual = atual->baixo; 
        }
    }

    //Avança para o ponteiro maior/NULL/desejado;
    if(atual != NULL)
        atual = atual->proximo;

    int verify = 0;

    //Se for NULL ou diferente do desejado, cancela a função;
    if(atual == NULL) {
        verify = 0;
    } else {
        if(strcmp(item_get_verbete(atual->item), verbete) == 0) {
            verify = 1;
        }
    }

    if(verify == 1) {
        //Caso contrário, inicia a remoção;
        NO* new;
        ITEM* item = (aux[0])->proximo->item;

        for(int i = LEVEL_MAX; i >= 0; i--) {
            //Percorre o auxiliar a partir do topo;
            if(aux[i]->proximo != NULL) {
                if(strcmp(item_get_verbete(aux[i]->proximo->item), verbete) == 0) {
                    //Se o nó corresponder ao que se deseja apagar
                    //Apaga o nó e conecta seu anterior ao seu próximo;
                    new = aux[i]->proximo;
                    aux[i]->proximo = aux[i]->proximo->proximo;
                    free(new);
                    new = NULL;
                }
            } 
        }

        item_apagar(&item);

        //Libera o auxiliar e confirma a remoção;
        free(aux);
        return 1;
    }

    //Libera o auxiliar e reporta o erro da remoção.
    free(aux);
    return 0;
}

ITEM* skip_busca(char* verbete, SKIPLIST* skiplist) {
    if (skiplist == NULL || skip_vazia(skiplist) == 1)
        return NULL;

    NO* sentinela = skiplist->upleft;

    //Realiza um processo análogo ao feito na função de alteração
    //Mas, ao achar o primeiro item com o verbete desejado, retorna o item;
    while (sentinela != NULL) {
        if (sentinela->proximo != NULL) {
            int cmp = strcmp(item_get_verbete(sentinela->proximo->item), verbete);
            if (cmp == 0) {
                return sentinela->proximo->item;
            } else if (cmp < 0) {
                sentinela = sentinela->proximo;
            } else {
                sentinela = sentinela->baixo;
            }
        } else {
            sentinela = sentinela->baixo;
        }
    }

    return NULL;
}

int skip_imprimir(char ch, SKIPLIST* skiplist) {
    if((skiplist != NULL) && (skip_vazia(skiplist) == 0)) {
        char aux; //armazenará a letra inicial do item em questão para facilitar os processos;
        NO* sentinela = skiplist->upleft;

        //Enquanto não chegar no nível 0 da skiplist, segue a busca para
        //chegar o mais próximo possível da primeira palavra que começa com o
        //char passado como parâmetro;
        while(sentinela->nivel != 0) {
            if(sentinela->proximo != NULL) {
                aux = item_get_verbete(sentinela->proximo->item)[0];
                if(aux >= ch)
                    sentinela = sentinela->baixo;
                //Enquanto aux < ch, continua percorrendo os níveis mais altos,
                //aproveitando as possíveis otimizações de busca que elas proporcionam;
                else
                    sentinela = sentinela->proximo;
            }
            else
                sentinela = sentinela->baixo;
        }

        //No nível 0, verifica se o próximo é diferente de NULL;
        if(sentinela->proximo != NULL)
            aux = item_get_verbete(sentinela->proximo->item)[0];
        //Se for NULL, não há palavras iniciadas por ch;
        else
            return 0;

        //Percorre o nível base até encontrar o char procurado ou alguma letra maior;
        while(aux < ch) {
            if(sentinela->proximo != NULL) {
                sentinela = sentinela->proximo;
                if(sentinela->proximo != NULL)
                    aux = item_get_verbete(sentinela->proximo->item)[0];
            }
            //Se não achou a letra e o próximo é NULL, não há palavras com o char procurado;
            else {
                return 0;
            }
        }

        int counter = 0; //Verifica se pelo menos um item foi impresso;

        while(aux == ch) {
            item_imprimir_completo(sentinela->proximo->item);
            counter++;
            sentinela = sentinela->proximo;
            if(sentinela->proximo != NULL)
                aux = item_get_verbete(sentinela->proximo->item)[0];
            else {
                //Retorna 1 porque pelo menos um item foi impresso com o caractere pedido;
                return 1;
            }
        }

        if(counter != 0)
            return 1;
        return 0;
    }

    return 0;
}

int skip_vazia(SKIPLIST* sl) {
    if(sl == NULL) {
        //Se a skiplist é NULL, consideramos ela vazia;
        return 1;
    }

    NO* aux = sl->upleft;
    while(aux->baixo != NULL) {
        //Desce até o fundo do nó cabeça;
        aux = aux->baixo;
    }

    if(aux->proximo == NULL) {
        //Se não existir algo diferente de NULL depois da base da cabeça, a skiplist é vazia.
        return 1;
    }
    
    //Se existir algo diferente de NULL depois da base da cabeça, a skiplist não é vazia.
    return 0;
}

int skip_cheia(SKIPLIST* skiplist) {
    NO* no;

    no = (NO*) malloc(sizeof(NO));

    //Se o nó conseguir ser alocado sendo diferente de NULL, há espaço livre e ele é desalocado
    //Caso contrário, é retornado 1, indicando que a skiplist está cheia;
    if(no == NULL)
        return 1;
    free(no);
    no = NULL;
    return 0;
}

void skip_apagar(SKIPLIST** skiplist) {
    //Apaga a skiplist, caso ela exista;
    if (*skiplist != NULL) {
        NO* sentinela = (*skiplist)->upleft;
        NO* aux;
        NO* reserva;

        while (sentinela->baixo != NULL) {
            //Percorre a skiplist, dando free em todos os nós, exceto o último;
            //Não é necessário apagar os items, pois todos os niveis de uma palavra compartilham o mesmo ponteiro item;
            //Logo, só é necessário apagar o item da base;
            reserva = sentinela;
            while(reserva != NULL) {
                aux = reserva->proximo;
                free(reserva);
                reserva = aux;
            }
            sentinela = sentinela->baixo;
        }

        while(sentinela != NULL) {
            //Percorre o "fundo" da skiplist, apagando seus items e nós;
            aux = sentinela->proximo;
            item_apagar(&(sentinela->item));
            free(sentinela);
            sentinela = aux;
        }

        //Dá free e apaga o ponteiro do cabeçalho da skiplist.
        free(*skiplist);
        *skiplist = NULL;
    }
}

int gerar_nivel() {
    //Função que gera um valor aleatório para determinar o nivel maximo de uma palavra a ser inserida;
    int lvl = 0;
    
    while(lvl < LEVEL_MAX) {
        //Limitada pelo LEVEL_MAX definido no .h;
        if(rand()%2) {
            //Utiliza a função rand para gerar números aleatórios;
            //Utiliza o modulo 2 de rand (sempre 1 ou 0) para determinar se o nivel é aumentado ou não (50% de chance);
            //Dessa forma, quanto mais alto o nível, menor a chance dele ser escolhido;
            ++lvl;
        } else {
            break;
        }
    }
    //Retorna o nível gerado.
    return(lvl);
}