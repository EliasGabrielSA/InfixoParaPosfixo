#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100

typedef struct _pilha {
    char elementos[MAX];
    int topo;
} Pilha;

typedef struct _pilhafloat {
    double elementos[MAX];
    int topo;
} PilhaFloat;

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

short int pilhaFloatEstaVazia(PilhaFloat p) {
    if (p.topo == -1)
        return 1;
    else 
        return 0;
}

void empilharFloat(PilhaFloat *p, double elem) {
    if (p->topo < MAX - 1) {
        p->elementos[++p->topo] = elem;
    } else {
        printf("stack overflow\n");
    }
}

double desempilharFloat(PilhaFloat *p) {
    double ret;
    if (!pilhaFloatEstaVazia(*p)) {
        ret = p->elementos[p->topo--];
    } else {
        printf("stack underflow\n");
        ret = p->topo;
    }
    return ret;
}

PilhaFloat *criaPilhaFloat() {
    PilhaFloat *novaPilha = (PilhaFloat*) malloc(sizeof(PilhaFloat));
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

float converteCaracter(char caracter) {
    switch (caracter) {
        case '0':
            return 0.0;
        case '1':
            return 1.0;
        case '2':
            return 2.0;
        case '3':
            return 3.0;
        case '4':
            return 4.0;
        case '5':
            return 5.0;
        case '6':
            return 6.0;
        case '7':
            return 7.0;
        case '8':
            return 8.0;
        case '9':
            return 9.0;
        default:
            return -1.0;
    }
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

    posfix[j] = '\0';
}

float analisaExpressao(char posfix[]) {
    PilhaFloat *p1 = criaPilhaFloat();
    double aux;

    for (int i = 0; i < strlen(posfix); i++) {
        if (posfix[i] >= '0' && posfix[i] <= '9') {
            aux = converteCaracter(posfix[i]);
            empilharFloat(p1, aux);
        } else {
            float n2 = desempilharFloat(p1);
            float n1 = desempilharFloat(p1);

            switch (posfix[i]) {
                case '/':
                    empilharFloat(p1, n1 / n2);
                    break;
                case '*':
                    empilharFloat(p1, n1 * n2);
                    break;
                case '+':
                    empilharFloat(p1, n1 + n2);
                    break;
                case '-':
                    empilharFloat(p1, n1 - n2);
                    break;
                default:
                    break;
            }
        }
    }
    return desempilharFloat(p1);
}

int main() {
    char infix_ex[MAX];
    char posfix_ex[MAX];

    fgets(infix_ex, MAX, stdin);
    infix_ex[strcspn(infix_ex, "\n")] = '\0';

    infixaParaPosfixa(infix_ex, posfix_ex);

    printf("Infixa: %s\n", infix_ex);
    printf("Posfixa: %s\n", posfix_ex);
    
    float resultado = ceil(analisaExpressao(posfix_ex) * 100) / 100;
    printf("Resultado: %.2f\n", resultado);

    return 0;
}
