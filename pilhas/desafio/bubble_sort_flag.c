#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // Para usar bool, true, false
#include <time.h>    // Para medir o tempo

// Função para trocar dois inteiros
void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Implementação do Bubble Sort com flag de otimização
// e contadores para comparações e trocas
void bubble_sort_flag(int A[], int n, long long *comparisons, long long *swaps) {
    bool swapped = true;
    *comparisons = 0; // Inicializa contadores
    *swaps = 0;

    // O loop externo vai de 0 a n-2. A otimização 'swapped' pode pará-lo antes.
    for (int i = 0; i < n - 1 && swapped; i++) {
        swapped = false; // Supõe que não haverá trocas nesta passagem

        // O loop interno percorre os elementos não ordenados
        // A cada passagem 'i', o i-ésimo maior elemento já está no lugar certo (no fim)
        for (int j = 0; j < n - 1 - i; j++) {
            (*comparisons)++; // Incrementa a contagem de comparações
            if (A[j] > A[j + 1]) {
                swap(&A[j], &A[j + 1]);
                (*swaps)++; // Incrementa a contagem de trocas
                swapped = true; // Marca que houve uma troca nesta passagem
            }
        }
        // Se 'swapped' permaneceu 'false' após o loop interno, o array está ordenado.
    }
}

// Função para ler dados de um arquivo para um array
// Retorna 0 em sucesso, -1 em erro.
int read_data(const char *filename, int **arr, int n) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    *arr = (int*)malloc(n * sizeof(int));
    if (*arr == NULL) {
        fprintf(stderr, "Erro ao alocar memória\n");
        fclose(file);
        return -1;
    }

    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%d", &((*arr)[i])) != 1) {
            fprintf(stderr, "Erro ao ler dados do arquivo ou arquivo incompleto\n");
            free(*arr);
            *arr = NULL;
            fclose(file);
            return -1;
        }
    }

    fclose(file);
    return 0;
}

// Função principal para testar
int main() {
    const int n = 1000;
    const char *filenames[] = {
        "ordered_1000.txt", // 
        "reverse_1000.txt", // 
        "random_1000.txt"   // 
    };
    const char *descriptions[] = {
        "Ordenado",
        "Reverso",
        "Aleatório"
    };

    for (int i = 0; i < 3; i++) {
        int *data_array = NULL;
        long long comparisons = 0;
        long long swaps = 0;
        clock_t start, end;
        double cpu_time_used;

        printf("--- Dataset: %s ---\n", descriptions[i]);

        // Ler dados
        if (read_data(filenames[i], &data_array, n) != 0) {
            continue; // Pula para o próximo arquivo em caso de erro
        }

        // Medir tempo e executar o sort
        start = clock();
        bubble_sort_flag(data_array, n, &comparisons, &swaps);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Imprimir métricas
        printf("Comparacoes: %lld\n", comparisons);
        printf("Trocas:      %lld\n", swaps);
        printf("Tempo (s):   %f\n", cpu_time_used);
        printf("\n");

        // Liberar memória
        free(data_array);
        data_array = NULL;
    }

    return 0;
}