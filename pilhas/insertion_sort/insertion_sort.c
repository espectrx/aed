#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // Para usar bool, true, false
#include <time.h>    // Para medir o tempo

// Implementação do Insertion Sort instrumentada
// Conta comparações (chave vs. elemento A[j]) e movimentos (atribuições no array)
void insertion_sort(int A[], int n, long long *comparisons, long long *movements) {
    *comparisons = 0;
    *movements = 0;

    for (int i = 1; i < n; i++) {
        int key = A[i]; // Elemento a ser inserido na parte ordenada
        int j = i - 1;

        // Compara 'key' com os elementos na parte ordenada (A[0...i-1])
        // e desloca os elementos maiores que 'key' uma posição para a direita.
        
        // Contamos a comparação A[j] > key. Ela ocorre antes de entrar/continuar o while
        // e uma última vez quando a condição falha (ou j < 0).
        while (j >= 0) {
             (*comparisons)++; // Conta a comparação A[j] vs key
             if (A[j] > key) {
                 A[j + 1] = A[j]; // Movimenta o elemento A[j] para a direita
                 (*movements)++;
                 j--;
             } else {
                 break; // Encontrou a posição correta ou A[j] <= key
             }
        }
        // Se o while parou por j < 0, a comparação extra não foi feita no loop,
        // mas é conceitualmente a comparação com "antes do início" do array.
        // A contagem já reflete o número de vezes que A[j] > key foi avaliado.

        // Insere a chave na posição correta (após o último elemento deslocado)
        A[j + 1] = key;
        // Se o elemento A[i] já estava na posição correta (nenhum shift ocorreu),
        // esta atribuição A[j+1] = key (onde j+1 == i) ainda conta como 1 movimento?
        // Vamos contar sempre, pois é uma escrita no array.
        (*movements)++; 
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
    const int n = 1000;
    // Assume que os arquivos estão em um subdiretório 'data'
    const char *filenames[] = {
        "ordered_1000.txt",
        "reverse_1000.txt",
        "random_1000.txt"
    };
    const char *descriptions[] = {
        "Ordenado",
        "Reverso",
        "Aleatório"
    };

    printf("--- Insertion Sort (n=%d) ---\n\n", n);

    for (int i = 0; i < 3; i++) {
        int *data_array = NULL;
        long long comparisons = 0;
        long long movements = 0;
        clock_t start, end;
        double cpu_time_used;

        printf("--- Dataset: %s ---\n", descriptions[i]);

        // Ler dados
        if (read_data(filenames[i], &data_array, n) != 0) {
            continue; // Pula para o próximo arquivo em caso de erro
        }

        // Medir tempo e executar o sort
        start = clock();
        insertion_sort(data_array, n, &comparisons, &movements);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Imprimir métricas
        printf("Comparacoes: %lld\n", comparisons);
        printf("Movimentos:  %lld\n", movements);
        printf("Tempo (s):   %f\n", cpu_time_used);
        printf("\n");

        // Liberar memória
        free(data_array);
        data_array = NULL;
    }

    // Nota: Para uma comparação completa, você precisaria rodar o Bubble Sort
    // novamente com os mesmos dados e registrar suas métricas aqui ou
    // rodar os dois programas separadamente e anotar os resultados.

    return 0;
}