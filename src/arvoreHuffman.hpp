#ifndef ARVOREHUFFMAN_HPP
#define ARVOREHUFFMAN_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iomanip>

using namespace std;

typedef struct noHuffman noHuffman;
typedef struct TlistaHuff TlistaHuff;

struct noHuffman{
    string dado;
    float freq;
    noHuffman *prox;
    noHuffman *esq;
    noHuffman *dir;
};

struct TlistaHuff{
    noHuffman *inicio;
};

void inicializa_lista_Huff(TlistaHuff &l);
void insere_inicio_huff(TlistaHuff &l, noHuffman *novo);
void insere_dado_inicio_huff(TlistaHuff &l, string dado, float normalize);

noHuffman *remove_no_lista(TlistaHuff &l);

void imprimir_prefixo(noHuffman *no, int altura);
void imprimir_lista_Huff(TlistaHuff l);
void ordernar_freq_Huff(TlistaHuff &l);
void arvore_Huff(TlistaHuff &l);

#endif