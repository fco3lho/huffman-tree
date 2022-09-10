#include "tabelaSimbolos.hpp"

void inicializa_tabelaSimbolos(tabelaSimbolos &t){
    t.inicio = nullptr;
}

void insere_inicio_tabela(tabelaSimbolos &t, dadoTabela *novo){
    novo->prox = t.inicio;
    t.inicio = novo;
}

void preenche_tabela(tabelaSimbolos &t, noHuffman *no, string codigo){
    string test = "-";

    //Nó possui conteúdo
    if(no->dado != test){
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
    cout << endl << "______________________________________________________________" << endl;
    cout  << "\t\tImprimindo a tabela" << endl << endl;
    if(t.inicio == nullptr){
        cout << "Tabela vazia" << endl;
    }else{
        for (dadoTabela*nav = t.inicio; nav != NULL; nav = nav->prox){
            cout << "Dado [" << nav->dado << "]\t\tNormalize [" << nav->freq << "]\t\tCode [" << nav->cod << "]" << endl;
        }
    }
}

string codificacao_huff(tabelaSimbolos t, string letra){
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