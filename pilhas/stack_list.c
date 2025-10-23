#include <stdio.h>
#include <stdlib.h> // Para malloc(), free(), exit()
#include <stdbool.h> // Para bool, true, false

// Estrutura do Nó da lista
typedef struct Node {
    int valor;
    struct Node *prox;
} Node;

// Estrutura da Pilha (apenas um ponteiro para o topo)
typedef struct {
    Node *topo;
} Stack;

// Função auxiliar para reportar erros
void error(const char *msg) {
    fprintf(stderr, "Erro de Pilha: %s\n", msg);
    // exit(1); // Descomente se quiser que o programa pare em um erro
}

// 1. Inicializa a pilha
void initStack(Stack *s) {
    s->topo = NULL; // Pilha vazia tem topo nulo
}

// 2. Verifica se a pilha está vazia (isEmpty)
bool isEmpty(Stack *s) {
    return s->topo == NULL;
}

// 3. Empilha um elemento (push)
void push(Stack *s, int x) {
    // Aloca memória para o novo nó
    Node *novo = (Node*)malloc(sizeof(Node));
    if (!novo) {
        error("Sem memória (malloc falhou)");
        return;
    }
    
    // Configura o novo nó
    novo->valor = x;
    novo->prox = s->topo; // O novo nó aponta para o antigo topo
    
    // Atualiza o topo da pilha
    s->topo = novo;
}

// 4. Desempilha um elemento (pop)
int pop(Stack *s) {
    if (isEmpty(s)) {
        error("Underflow (pilha vazia)");
        return -1; // Valor de erro
    }
    
    // Salva o nó do topo temporariamente
    Node *temp = s->topo;
    int valor = temp->valor;
    
    // Avança o topo para o próximo elemento
    s->topo = s->topo->prox;
    
    // Libera a memória do nó removido
    free(temp);
    
    return valor;
}

// 5. Consulta o topo (top/peek)
int top(Stack *s) {
    if (isEmpty(s)) {
        error("Pilha vazia (na consulta ao topo)");
        return -1; // Valor de erro
    }
    return s->topo->valor;
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

    return 0;
}