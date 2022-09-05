#include "tabelaSimbolos.hpp"

void inicializa_tabelaSimbolos(tabelaSimbolos &t){
    t.inicio = nullptr;
}

void insere_inicio_tabela(tabelaSimbolos &t, dadoTabela *novo){
    novo->prox = t.inicio;
    t.inicio = novo;
}

void preenche_tabela(tabelaSimbolos &t, noHuffman *no, string codigo){

    ///NÓ POSSUI CONTEÚDO
    if(no->dado != '-'){
        dadoTabela *novo = new dadoTabela;
        novo->dado = no->dado;
        novo->freq = no->freq;
        novo->cod = codigo;
        insere_inicio_tabela(t, novo);
    }

    if(no->esq != nullptr){
        preenche_tabela(t, no->esq, codigo + '0');
    }
    if(no->dir != nullptr){
        preenche_tabela(t, no->dir, codigo + '1');
    }

}

void imprime_tabela(tabelaSimbolos t){
    cout << endl << "\t||IMPRIMINDO TABELA||" << endl;
    if(t.inicio == nullptr){
        cout << " ||Tabela vazia|| ";
    }else{
        for (dadoTabela*nav = t.inicio; nav != NULL; nav = nav->prox){
            cout << "Dado[" << nav->dado << "]\tFreq[" << nav->freq << "]\tCodigo[" << nav->cod << "]" << endl;
        }
    }
}

string codificacao_huff(tabelaSimbolos t, char letra){
    if(t.inicio == nullptr){
        cout << " ||Tabela vazia|| ";
    }
    else{
        for(dadoTabela*nav = t.inicio; nav != NULL; nav = nav->prox){
            if(nav->dado == letra){
                return nav->cod;
            }
        }
    }
    return 0;
}