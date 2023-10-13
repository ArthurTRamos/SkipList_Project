#include "skiplist.h"

int main() {
    srand(time(0));
    SKIPLIST* sl = skip_criar();
    skip_inserir(item_criar("z", "z"),sl);
    skip_inserir(item_criar("mau", "maligno"),sl);
    skip_inserir(item_criar("mitico", "magico"),sl);
    skip_inserir(item_criar("bom", "bondoso"),sl);
    skip_imprimir('m', sl);
    skip_imprimir('b', sl);
}