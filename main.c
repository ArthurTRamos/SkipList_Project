#include "skiplist.h"

int main(void) {
    char operacao[10], verbete[51], definicao[141];
    char ch;
    SKIPLIST* skiplist;

    skiplist = skip_criar();
    if(skiplist != NULL) {
        while(1) {
            if(scanf("%s", operacao) == EOF)
                break;
            if(strcmp(operacao, "insercao") == 0) {
                int i = 0;
                scanf("%s", verbete);
                while((ch = getchar()) != '\n') {
                    definicao[i] = ch;
                    i++;
                }
                definicao[i] = '\0';
                ITEM* item = item_criar(verbete, definicao);
                skip_inserir(item, skiplist);
            }
            if(strcmp(operacao, "alteracao") == 0) {
                int i = 0;
                scanf("%s", verbete);
                while((ch = getchar()) != '\n') {
                    definicao[i] = ch;
                    i++;
                }
                definicao[i] = '\0';
                ITEM *item = item_criar(verbete, definicao);
                skip_alterar(item, skiplist);
            }
            if(strcmp(operacao, "remocao") == 0) {
                scanf("%s", verbete);
                skip_remover(verbete, skiplist);
            }
            if(strcmp(operacao, "busca") == 0) {
                scanf("%s", verbete);
                skip_busca(verbete, skiplist);
            }
            if(strcmp(operacao, "impressao") == 0) {
                scanf("%c", &ch);
                skip_imprimir(ch, skiplist);
            }
        }
    }

    skip_apagar(&skiplist);
    skiplist = NULL;
    
   return 0;
}