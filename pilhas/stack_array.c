#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>

#define MAX 100 // Define o tamanho máximo da pilha

// Estrutura da Pilha baseada em array
typedef struct {
    int data[MAX];
    int top; // Índice do elemento no topo
} Stack;

// Função auxiliar para reportar erros
void error(const char *msg) {
    fprintf(stderr, "Erro de Pilha: %s\n", msg);
    exit(1); // Descomente se quiser que o programa pare em um erro
}

// 1. Inicializa a pilha
void initStack(Stack *s) {
    s->top = -1; // Pilha vazia é indicada por topo = -1
}

// 2. Verifica se a pilha está vazia (isEmpty)
bool isEmpty(Stack *s) {
    return s->top < 0;
}

// 3. Verifica se a pilha está cheia (isFull)
bool isFull(Stack *s) {
    return s->top >= MAX - 1;
}

// 4. Empilha um elemento (push)
void push(Stack *s, int x) {
    if (isFull(s)) {
        error("Overflow (pilha cheia)");
        return;
    }
    // Pré-incrementa o topo e então insere o dado
    s->data[++s->top] = x;
}

// 5. Desempilha um elemento (pop)
int pop(Stack *s) {
    if (isEmpty(s)) {
        error("Underflow (pilha vazia)");
        return -1; // Valor de erro (idealmente, um tratamento melhor)
    }
    // Retorna o dado e pós-decrementa o topo
    return s->data[s->top--];
}

// 6. Consulta o topo (top/peek)
int top(Stack *s) {
    if (isEmpty(s)) {
        error("Pilha vazia (na consulta ao topo)");
        return -1; // Valor de erro
    }
    return s->data[s->top];
}

// --- Main para Testes ---
// (Os testes de unidade fornecidos usariam estas funções)
int main() {
    Stack minhaPilha;
    initStack(&minhaPilha);

    printf("Pilha está vazia? %s\n", isEmpty(&minhaPilha) ? "Sim" : "Não"); // Sim

    // Teste de Push
    push(&minhaPilha, 10);
    push(&minhaPilha, 20);
    push(&minhaPilha, 30);

    printf("Topo da pilha: %d\n", top(&minhaPilha)); // 30
    printf("Pilha está vazia? %s\n", isEmpty(&minhaPilha) ? "Sim" : "Não"); // Não

    // Teste de Pop
    printf("Pop: %d\n", pop(&minhaPilha)); // 30
    printf("Topo da pilha: %d\n", top(&minhaPilha)); // 20

    // Teste de Underflow
    printf("Pop: %d\n", pop(&minhaPilha)); // 20
    printf("Pop: %d\n", pop(&minhaPilha)); // 10
    printf("Pilha está vazia? %s\n", isEmpty(&minhaPilha) ? "Sim" : "Não"); // Sim
    pop(&minhaPilha); // Erro: Underflow

    // Teste de Overflow (depende do MAX)
    // initStack(&minhaPilha);
    // for (int i = 0; i < MAX + 5; i++) {
    //     push(&minhaPilha, i); // Deve dar erro de Overflow
    // }

    return 0;
}