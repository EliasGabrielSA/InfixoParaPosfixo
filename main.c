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
    Pilha *ops = criaPilha();
    int j = 0;

    for (int i = 0; i < strlen(infix); i++) {
        if (infix[i] >= '0' && infix[i] <= '9') {
            posfix[j] = infix[i];
            j++;
        } else if (infix[i] == '(') {
            empilhar(ops, infix[i]);
        } else if (infix[i] == '/' || infix[i] == '*' || infix[i] == '+' || infix[i] == '-') {
            while (!pilhaEstaVazia(*ops) && ops->elementos[ops->topo] != '(') {
                posfix[j] = desempilhar(ops);
                j++;
            }
            empilhar(ops, infix[i]);
        } else if (infix[i] == ')') {
            while (!pilhaEstaVazia(*ops) && ops->elementos[ops->topo] != '(') {
                posfix[j] = desempilhar(ops);
                j++;
            }
            desempilhar(ops); 
        }
    }

    while (!pilhaEstaVazia(*ops)) {
        posfix[j] = desempilhar(ops);
        j++;
    }

    posfix[j] = '\0';
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
