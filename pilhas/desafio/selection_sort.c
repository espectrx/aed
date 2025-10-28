#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <time.h>    

// Função para trocar dois inteiros (reutilizada)
void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Implementação do Selection Sort instrumentada
// Conta comparações e trocas (swaps)
void selection_sort(int A[], int n, long long *comparisons, long long *swaps) {
    *comparisons = 0;
    *swaps = 0;

    for (int i = 0; i < n - 1; i++) {
        int min_idx = i; // Assume que o mínimo está na posição inicial 'i'

        // Encontra o índice do menor elemento no restante do array (A[i+1...n-1])
        for (int j = i + 1; j < n; j++) {
            (*comparisons)++; // Incrementa a contagem de comparações
            if (A[j] < A[min_idx]) {
                min_idx = j; // Atualiza o índice do mínimo encontrado
            }
        }

        // Se o índice do mínimo encontrado for diferente de 'i',
        // significa que o menor elemento não estava na posição correta. Troca!
        if (min_idx != i) {
            swap(&A[i], &A[min_idx]);
            (*swaps)++; // Incrementa a contagem de trocas
        }
        // Se min_idx == i, o elemento já está na posição correta, nenhuma troca é necessária.
    }
}


// Função para ler dados de um arquivo para um array (reutilizada)
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

    int *ptr = *arr;
    int *end_ptr = *arr + n;

    while (ptr < end_ptr) {
        if (fscanf(file, "%d", ptr) != 1) {
            fprintf(stderr, "Erro ao ler dados do arquivo ou arquivo incompleto (%s)\n", filename);
            free(*arr);
            *arr = NULL;
            fclose(file);
            return -1;
        }
        ptr++;
    }

    fclose(file);
    return 0;
}

// Função principal para testar
int main() {
    const int n = 10000;
    // Assume que os arquivos estão em um subdiretório 'data'
    const char *filenames[] = {
        "ordered_10000.txt",
        "reverse_10000.txt",
        "random_10000.txt"
    };
    const char *descriptions[] = {
        "Ordenado",
        "Reverso",
        "Aleatório"
    };

    printf("--- Selection Sort (n=%d) ---\n\n", n);

    for (int i = 0; i < 3; i++) {
        int *data_array = NULL;
        long long comparisons = 0;
        long long swaps = 0;
        clock_t start, end;
        double cpu_time_used;

        printf("--- Dataset: %s ---\n", descriptions[i]);

        // Ler dados
        if (read_data(filenames[i], &data_array, n) != 0) {
            continue; 
        }

        // Medir tempo e executar o sort
        start = clock();
        selection_sort(data_array, n, &comparisons, &swaps);
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
    
    // Você precisará executar os códigos anteriores (Bubble e Insertion)
    // para preencher a tabela comparativa completa.

    return 0;
}