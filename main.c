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

Pilha *criaPilha() {
    Pilha *novaPilha = (Pilha*) malloc(sizeof(Pilha));
    if (novaPilha != NULL) {
        novaPilha->topo = -1;
    }
    return novaPilha;
}

int precedencia(char op) {
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    return 0;
}

void infixaParaPosfixa(char infix[], char posfix[]) {
    Pilha *ops = criaPilha();
    int j = 0;

    for (int i = 0; i < strlen(infix); i++) {
        if (infix[i] >= '0' && infix[i] <= '9') {
            int k = i;
            while (infix[k] >= '0' && infix[k] <= '9') {
                posfix[j++] = infix[k++];
            }
            i = k - 1;
        } else if (infix[i] == '(') {
            empilhar(ops, infix[i]);
        } else if (infix[i] == ')') {
            while (!pilhaEstaVazia(*ops) && ops->elementos[ops->topo] != '(') {
                posfix[j++] = desempilhar(ops);
            }
            desempilhar(ops);
        } else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/') {
            while (!pilhaEstaVazia(*ops) && precedencia(ops->elementos[ops->topo]) >= precedencia(infix[i])) {
                posfix[j++] = desempilhar(ops);
            }
            empilhar(ops, infix[i]);
        }
    }

    while (!pilhaEstaVazia(*ops)) {
        posfix[j++] = desempilhar(ops);
    }

    posfix[j] = '\0'; // Adicionar o caractere nulo para terminar a string.
}

float analisaExpressao(char posfix[]) {
    Pilha *p1 = criaPilha();
    float resultado = 0;
    float aux;

    for (int i = 0; posfix[i] != '\0'; i++) {
        if (posfix[i] >= '0' && posfix[i] <= '9') {
            aux = posfix[i] - '0'; // Converte char para float
            empilhar(p1, aux);
        } else {
            float n2 = desempilhar(p1);
            float n1 = desempilhar(p1);

            switch (posfix[i]) {
                case '/':
                    empilhar(p1, (float) n1 / n2);
                    break;
                case '*':
                    empilhar(p1, (float) n1 * n2);
                    break;
                case '+':
                    empilhar(p1, (float) n1 + n2);
                    break;
                case '-':
                    empilhar(p1, (float) n1 - n2);
                    break;
                default:
                    break;
            }
        }
    }

    resultado = (float) desempilhar(p1);
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
