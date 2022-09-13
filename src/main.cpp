#include "simbolTable.hpp"
#include "huffmanTree.hpp"
#include "manipulation.hpp"

using namespace std;

int main()
{
    TlistaHuff list;

    inicializa_lista_Huff(list);
    readText_insertList(list); //Trata as palavras e as joga na lista da árvore

    // imprimir_lista_Huff(list);
    ordernar_freq_Huff(list);
    // imprimir_lista_Huff(list);

    // cout << endl << "______________________________________________________________" << endl;
    // cout << "\tINICIA A CONSTRUÇÃO DA ÁRVORE" << endl;
    arvore_Huff(list);

    // cout << endl << "______________________________________________________________" << endl;
    // cout << "\t\tIMPRESSÃO DA ÁRVORE" << endl << endl;
    // imprimir_prefixo(list.inicio, 0);

    tabelaSimbolos table;
    inicializa_tabelaSimbolos(table);
    preenche_tabela(table, list.inicio,"");
    // imprime_tabela(table);

    cout << "\n\t\t\tCodificação do texto em código de Huffman" << endl << endl;
    saveCodeHuffman(table);
    
    return 0;
}
