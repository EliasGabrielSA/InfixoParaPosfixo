#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

short int pilhaEstaVazia(Pilha p) {
    if (p.topo == -1)
        return 1;
    else 
        return 0;
}

void esvaziarPilha(Pilha *p) {
    p->topo = -1;
}


void empilhar(Pilha *p, char elem) {
    if (p->topo < MAX - 1) {
        p->elementos[++p->topo] = elem;
    } else {
        printf("stack overflow\n");
    }
}

char desempilhar(Pilha *p) {
    char ret;
    if (!pilhaEstaVazia(*p)) {
        ret = p->elementos[p->topo--];
    } else {
        printf("stack underflow\n");
        ret = p->topo;
    }
    return ret;
}

void imprimirPilha(Pilha p) {
    if (!pilhaEstaVazia(p)) {
        for (int i = p.topo; i >= 0; i--) {
            printf("%c", p.elementos[i]);
        }
    } else {
        printf("Pilha vazia\n");
    }
}

Pilha *criaPilha() {
    Pilha *novaPilha = (Pilha*) malloc(sizeof(Pilha));
    if (novaPilha != NULL) {
        novaPilha->topo = -1;
    }
    return novaPilha;
}
