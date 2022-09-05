#ifndef TABELASIMBOLOS_HPP
#define TABELASIMBOLOS_HPP

#include "arvoreHuffman.hpp"

typedef struct dadoTabela dadoTabela;
typedef struct tabelaSimbolos tabelaSimbolos;

struct dadoTabela{
    char dado;
    int freq;
    string cod;
    dadoTabela *prox;
};

struct tabelaSimbolos{
    dadoTabela * inicio;
};

void inicializa_tabelaSimbolos(tabelaSimbolos &t);
void insere_inicio_tabela(tabelaSimbolos &t, dadoTabela *novo);
void preenche_tabela(tabelaSimbolos &t, noHuffman *no, string codigo);
void imprime_tabela(tabelaSimbolos t);
string codificacao_huff(tabelaSimbolos t, char letra);

#endif
