#include "tabelaSimbolos.hpp"
#include "arvoreHuffman.hpp"
#include "huff.hpp"

using namespace std;

int main()
{
    TlistaHuff lista1;

    inicializa_lista_Huff(lista1);
    readText_insertList(lista1);

    // string frase = "VAI TOMAR NO CU CU CARALHO";
    // string fraseConc;
    // string fraseCode;
    // stringstream X(frase);

    // vector<string> tokens;

    // cout << "FRASE: " << frase << endl;

    // while(getline(X, fraseConc, ' ')){
    //     cout << fraseConc << endl;
    //     tokens.push_back(fraseConc);
    //     insere_dado_inicio_huff(lista1, fraseConc);
    // }

    imprimir_lista_Huff(lista1);
    ordernar_freq_Huff(lista1);
    imprimir_lista_Huff(lista1);

    cout << endl << "______________________________________________________________" << endl;
    cout << "\tINICIA A CONSTRUÇÃO DA ÁRVORE" << endl;
    arvore_Huff(lista1);

    cout << endl << "______________________________________________________________" << endl;
    cout << "\t\tIMPRESSÃO DA ÁRVORE" << endl << endl;
    imprimir_prefixo(lista1.inicio,0);

    tabelaSimbolos tabela;
    inicializa_tabelaSimbolos(tabela);

    preenche_tabela(tabela, lista1.inicio,"");

    imprime_tabela(tabela);

    cout << endl << "______________________________________________________________" << endl;
    cout << "\tCODIFICAÇÃO DO TEXTO EM CÓDIGO DE HUFFMAN" << endl << endl;

    // cout << endl << words.size() << endl;

    // for(int i = 0; i < int(words.size()); i++){
    //     test = words[i];
    //     cout << words[i] << endl;
    //     // cout << codificacao_huff(tabela, test) << " ";
    // }

    cout << endl;
    
    return 0;
}
