#include "arvoreHuffman.hpp"

void inicializa_lista_Huff(TlistaHuff &l){
    l.inicio = nullptr;
}

void insere_inicio_huff(TlistaHuff &l, noHuffman *novo){
    novo->prox = l.inicio;
    l.inicio = novo;
}

void insere_dado_inicio_huff(TlistaHuff &l, string dado, float normalize){
    noHuffman *novo = new noHuffman;
    novo->dado = dado;
    novo->dir = nullptr;
    novo->esq = nullptr;
    novo->freq = normalize;
    novo->prox = nullptr;
    insere_inicio_huff(l, novo);
}

noHuffman *remove_no_lista(TlistaHuff &l){
    noHuffman *retirar;
    retirar = l.inicio;
    l.inicio = l.inicio->prox;
    return retirar;
}

void imprimir_prefixo(noHuffman *no,int altura){
    if(no != nullptr){
        int i = 0;

        while(i < altura){
            cout << "####|";
            i++;
        }

        if(altura == 0){
            cout << "Raiz: ";
        }

        cout << no->dado << " > " << no->freq << endl;
        altura++;

        imprimir_prefixo(no->esq,altura);
        imprimir_prefixo(no->dir,altura);
    }
}

void imprimir_lista_Huff( TlistaHuff l){
    cout << endl << "\t\tImprimindo a lista" << endl << endl;
    
    if(l.inicio == nullptr){
        cout << "Lista vazia" << endl;
    }
    else{
        int i = 0;
        for (noHuffman*nav = l.inicio; nav != NULL; nav = nav->prox){
            cout << "Word[" << i++ << "]: " << nav->dado <<"\t\tNormalize:"<< nav->freq << endl;
        }
    }
}

void ordernar_freq_Huff(TlistaHuff &l){
    bool ordenado = false;
    noHuffman *aux = new noHuffman;

    cout << endl << "______________________________________________________________" << endl;
    cout << "\tORDENANDO LISTA PELA FREQUÊNCIA" << endl;
   
    while(ordenado!=true){
        ordenado = true;
        for(noHuffman*nav = l.inicio; nav != NULL; nav = nav->prox){
            for(noHuffman*nav2 = nav->prox; nav2 != NULL; nav2 = nav2->prox){
                if(nav2->freq < nav->freq){
                        aux->dado = nav2->dado;
                        aux->freq = nav2->freq;

                        nav2->dado = nav->dado;
                        nav2->freq = nav->freq;

                        nav->dado = aux->dado;
                        nav->freq = aux->freq;
                        ordenado = false;
                }
            }
        }
    }
}

void arvore_Huff(TlistaHuff &l){
    noHuffman *no1 = new noHuffman;
    noHuffman *no2 = new noHuffman;

    noHuffman *nav;

    while(l.inicio->prox != nullptr){ // Permanece no laço equanto a lista tiver mais de um elemento

        // Retira os dois primeiros nós da lista
        no1 = remove_no_lista(l);
        no2 = remove_no_lista(l);

        // Cria o pai das duas folhas retiradas
        noHuffman *novo = new noHuffman;

        novo->dado = '-';
        novo->freq = no1->freq + no2->freq;
        novo->esq = no1;
        novo->dir = no2;

        // Inicia navegador para inserir o pai
        nav = l.inicio;
        while(true){
            // Insere ele de acordo com a frequência

            // Último elemento da lista
            if(nav == nullptr){
                l.inicio = novo;
                novo->prox = nullptr;
                break;
            }
            // Inserção do elemento com maior valor
            else if (nav->prox == nullptr){
                novo->prox = nav->prox;
                nav->prox = novo;
                imprimir_lista_Huff(l);
                break;
            }
            // Inserção na posição anterior ao valor maior
            else if(nav->prox->freq >= novo->freq){
                novo->prox = nav->prox;
                nav->prox = novo;
                imprimir_lista_Huff(l);
                break;
            }
            nav = nav->prox;
        }
    }
    
    imprimir_lista_Huff(l);
}