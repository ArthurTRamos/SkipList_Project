#include "skiplist.h"

int main(void) {
    //Utilizada para o funcionamento correto das funções de geração de
    //nivel aleatório
    srand(time(0));
    char operacao[10], verbete[51], definicao[151];
    char ch = '!'; //Inicializa o char para evitar problemas com leituras indevidas;
    int flag = 0; //Verifica se ocorre EOF ou não
    SKIPLIST* skiplist;

    skiplist = skip_criar();
    
    if(skiplist != NULL) {
        while(flag != EOF) {
            int i = 0;
            ch = '!';
            //Lê a operação até o EOF ou espaço em branco;
            while (1) {
                flag = scanf("%c", &ch);
                if (flag == EOF || ch == ' ') {
                    i++;
                    break;
                }
                operacao[i] = ch;
                i++;
            }
            if (flag == EOF)
                break;
            operacao[i - 1] = '\0';

            if(strcmp(operacao, "insercao") == 0) {
                i = 0;
                ch = '!';
                //Lê a palavra até o espaço;
                while(ch != ' ') {
                    scanf("%c", &ch);
                    verbete[i] = ch;
                    i++;
                }
                verbete[i-1] = '\0';
                
                i = 0;

                //Lê a definição até o \n, \r ou EOF;
                while(ch != '\n' && ch != 13) {
                    flag = scanf("%c", &ch);
                    if(flag == EOF)
                        break;
                    definicao[i] = ch;
                    i++;
                }

                if(ch == 13)
                    scanf("%c", &ch); //Lê o \n posterior ao \r (13);
                definicao[i-1] = '\0';

                ITEM* item = item_criar(verbete, definicao);
                if(skip_inserir(item, skiplist) == 0)
                    printf("OPERACAO INVALIDA\n");

                if(flag == EOF)
                    break;
            }

            if(strcmp(operacao, "remocao") == 0) {
                i = 0;
                ch = '!';
                //Lê o verbete;
                while(ch != '\n' && ch != 13) {
                    flag = scanf("%c", &ch);
                    if(flag == EOF)
                        break;
                    verbete[i] = ch;
                    i++;
                }

                if(ch == 13)
                    scanf("%c", &ch);
                verbete[i-1] = '\0';

                if(skip_remover(verbete, skiplist) == 0)
                    printf("OPERACAO INVALIDA\n");

                if(flag == EOF)
                    break;
            }

            if(strcmp(operacao, "alteracao") == 0) {
                i = 0;
                ch = '!';
                //Lê a palavra em questão;
                while(ch != ' ') {
                    scanf("%c", &ch);
                    verbete[i] = ch;
                    i++;
                }
                verbete[i-1] = '\0';
                
                i = 0;

                //Lê a nova definição para a palavra;
                while(ch != '\n' && ch != 13) {
                    flag = scanf("%c", &ch);
                    if(flag == EOF)
                        break;
                    definicao[i] = ch;
                    i++;
                }

                if(ch == 13)
                    flag = scanf("%c", &ch);
                definicao[i-1] = '\0';

                ITEM* item = item_criar(verbete, definicao);
                if(skip_alterar(item, skiplist) == 0)
                    printf("OPERACAO INVALIDA\n");

                item_apagar(&item);

                if(flag == EOF)
                    break;
            }

            if(strcmp(operacao, "busca") == 0) {
                i = 0;
                ch = '!';
                //Lê a palavra a ser buscada;
                while(ch != '\n' && ch != 13) {
                    flag = scanf("%c", &ch);
                    if(flag == EOF)
                        break;
                    verbete[i] = ch;
                    i++;
                }
                verbete[i-1] = '\0';

                if(ch == 13)
                    scanf("%c", &ch);
                
                ITEM* item = skip_busca(verbete, skiplist);
                if(item == NULL)
                    printf("OPERACAO INVALIDA\n");
                else
                    item_imprimir_completo(item);

                if(flag == EOF)
                    break;
            }

            if(strcmp(operacao, "impressao") == 0) {
                scanf("%c", &ch);
                if(skip_imprimir(ch, skiplist) == 0)
                    printf("NAO HA PALAVRAS INICIADAS POR %c\n", ch);
                flag = scanf("%c", &ch); //Lê o \r ou EOF na sequência
                if(ch == 13)
                    scanf("%c", &ch);
                if(flag == EOF)
                    break;
            }
        }
    }

    skip_apagar(&skiplist);

    return 0;
}