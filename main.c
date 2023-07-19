#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

typedef struct _pilha {
    char elementos[MAX];
    int topo;
} Pilha;

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

void infixaParaPosfixa(char infix[], char posfix[]) {
    Pilha *operacoes = criaPilha();
    int aux_count = 0;

    for (int i = 0; i < strlen(infix); i++) {
        if(infix[i] >= '0' && infix[i] <= '9') {
            posfix[aux_count] = infix[i];
            aux_count++;
        } else if (infix[i] == '/' || infix[i] == '*' || infix[i] == '+' || infix[i] == '-') {
            empilhar(operacoes, infix[i]);
        } else if(infix[i] == '(') {
            Pilha *operacoes_aux = criaPilha();
            for(i; infix[i] != ')'; i++) {
                if (infix[i] == '/' || infix[i] == '*' || infix[i] == '+' || infix[i] == '-') {
                    empilhar(operacoes_aux, infix[i]);
                } else if(infix[i] >= '0' && infix[i] <= '9') {
                    posfix[aux_count] = infix[i];
                    aux_count++;
                }
            }
            while(!pilhaEstaVazia(*operacoes_aux)) {
                posfix[aux_count] = desempilhar(operacoes_aux);
                aux_count++;
            }
            
            while(!pilhaEstaVazia(*operacoes)) {
                posfix[aux_count] = desempilhar(operacoes);
                aux_count++;
            }
        }
    }
    
    while (!pilhaEstaVazia(*operacoes)) {
        posfix[aux_count] = desempilhar(operacoes);
        aux_count++;
    }

    posfix[aux_count] = '\0';
}

double analisaExpressao(char posfix[]) {
    Pilha *p1 = criaPilha();
    float resultado = 0;
    float aux;

    for (int i = 0; posfix[i] != '\0'; i++) {
        if (posfix[i] >= '0' && posfix[i] <= '9') {
            aux = posfix[i] - '0'; 
            empilhar(p1, aux);
        } else {
            float n2 = desempilhar(p1);
            float n1 = desempilhar(p1);

            switch (posfix[i]) {
                case '/':
                    empilhar(p1, n1 / n2);
                    break;
                case '*':
                    empilhar(p1, n1 * n2);
                    break;
                case '+':
                    empilhar(p1, n1 + n2);
                    break;
                case '-':
                    empilhar(p1, n1 - n2);
                    break;
                default:
                    break;
            }
        }
    }

    resultado = desempilhar(p1);
    return resultado;
}

int main() {
    char infix_ex[MAX];
    char posfix_ex[MAX];

    fgets(infix_ex, MAX, stdin);
    infix_ex[strcspn(infix_ex, "\n")] = '\0';

    infixaParaPosfixa(infix_ex, posfix_ex);

    printf("Infixa: %s\n", infix_ex);
    printf("Posfixa: %s\n", posfix_ex);
    printf("Resultado: %.2f\n", analisaExpressao(posfix_ex));

    return 0;
}
