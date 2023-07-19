#ifndef PILHA_H
#define PILHA_H

#define MAX 100

//Funcoes de Pilha 
struct _pilha {
    char elementos[MAX];
    int topo;
};

typedef struct _pilha Pilha;

short int pilhaEstaVazia(Pilha p);

void esvaziarPilha(Pilha *p);

void empilhar(Pilha *p, char elem); 

char desempilhar(Pilha *p);

void imprimirPilha(Pilha p);

Pilha *criaPilha();

#endif