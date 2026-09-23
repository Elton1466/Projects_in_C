/*
 * ============================================================================
 * Programa: EDD_SortAlgorithms.c - Algoritmos de Ordenacao (Sorting Algorithms)
 * Objetivo: Demonstracao didatica dos principais algoritmos de ordenacao:
 *           BubbleSort, SelectionSort, InsertionSort, RadixSort, MergeSort,
 *           QuickSort e HeapSort.
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
  #include <windows.h>
  #define LIMPAR_TELA() system("cls")
  #define SLEEP_SEC(s) Sleep((s) * 1000)
#else
  #include <unistd.h>
  #define LIMPAR_TELA() printf("\033[H\033[2J")
  #define SLEEP_SEC(s) sleep(s)
#endif

#define TAM 7

// Limpa o buffer de entrada do stdin de forma portavel
static void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Exibe o estado atual de um vetor
static void exibir(const int vetor[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("| %d ", vetor[i]);
    }
    printf("|\n");
}

// Criar vetor com valores inseridos pelo usuario
static void criarVetor(int vetor[], int tamanho) {
    puts("\nDigite 7 valores para inserir no vetor:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Item %d - ", i + 1);
        if (scanf("%d", &vetor[i]) != 1) {
            vetor[i] = 0;
        }
    }
    limpar_buffer();
}

// ----------------------------------------------------------------------------
// 1. BubbleSort - O(n^2)
// ----------------------------------------------------------------------------
void bubbleSort(const int vetorOriginal[], int tamanho) {
    int aux;
    int *vetorCopia = (int *)malloc(tamanho * sizeof(int));
    if (!vetorCopia) return;

    memcpy(vetorCopia, vetorOriginal, tamanho * sizeof(int));
    puts("\nPasso a passo ordenacao com metodo BubbleSort\n");

    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (vetorCopia[j] > vetorCopia[j + 1]) {
                aux = vetorCopia[j];
                vetorCopia[j] = vetorCopia[j + 1];
                vetorCopia[j + 1] = aux;
            }
            exibir(vetorCopia, tamanho);
            SLEEP_SEC(1);
        }
    }
    puts("\nPressione ENTER para continuar...");
    getchar();
    free(vetorCopia);
}

// ----------------------------------------------------------------------------
// 2. SelectionSort - O(n^2)
// ----------------------------------------------------------------------------
void selectSort(const int vetorOriginal[], int tamanho) {
    int indiceMinimo, temp;
    int *vetorCopia = (int *)malloc(tamanho * sizeof(int));
    if (!vetorCopia) return;

    memcpy(vetorCopia, vetorOriginal, tamanho * sizeof(int));
    puts("\nPasso a passo ordenacao com metodo SelectSort\n");

    for (int i = 0; i < tamanho - 1; i++) {
        indiceMinimo = i;
        for (int j = i + 1; j < tamanho; j++) {
            if (vetorCopia[j] < vetorCopia[indiceMinimo]) {
                indiceMinimo = j;
            }
        }
        temp = vetorCopia[indiceMinimo];
        vetorCopia[indiceMinimo] = vetorCopia[i];
        vetorCopia[i] = temp;
        exibir(vetorCopia, tamanho);
        SLEEP_SEC(1);
    }
    puts("\nPressione ENTER para continuar...");
    getchar();
    free(vetorCopia);
}

// ----------------------------------------------------------------------------
// 3. InsertionSort - O(n^2)
// ----------------------------------------------------------------------------
void insertSort(const int vetorOriginal[], int tamanho) {
    int chave, j;
    int *vetorCopia = (int *)malloc(tamanho * sizeof(int));
    if (!vetorCopia) return;

    memcpy(vetorCopia, vetorOriginal, tamanho * sizeof(int));
    puts("\nPasso a passo ordenacao com metodo InsertSort\n");

    for (int i = 1; i < tamanho; i++) {
        chave = vetorCopia[i];
        j = i - 1;
        while (j >= 0 && vetorCopia[j] > chave) {
            vetorCopia[j + 1] = vetorCopia[j];
            j--;
        }
        vetorCopia[j + 1] = chave;
        exibir(vetorCopia, tamanho);
        SLEEP_SEC(1);
    }
    puts("\nPressione ENTER para continuar...");
    getchar();
    free(vetorCopia);
}

// ----------------------------------------------------------------------------
// 4. RadixSort - O(nk)
// ----------------------------------------------------------------------------
static int obterMaior(const int vetor[], int tamanho) {
    int maior = vetor[0];
    for (int i = 1; i < tamanho; i++) {
        if (vetor[i] > maior) {
            maior = vetor[i];
        }
    }
    return maior;
}

static void countingSortRadix(int vetor[], int tamanho, int exp) {
    int *saida = (int *)malloc(tamanho * sizeof(int));
    if (!saida) return;

    int contagem[10] = {0};

    for (int i = 0; i < tamanho; i++) {
        int digito = abs(vetor[i] / exp) % 10;
        contagem[digito]++;
    }

    for (int i = 1; i < 10; i++) {
        contagem[i] += contagem[i - 1];
    }

    for (int i = tamanho - 1; i >= 0; i--) {
        int digito = abs(vetor[i] / exp) % 10;
        saida[contagem[digito] - 1] = vetor[i];
        contagem[digito]--;
    }

    for (int i = 0; i < tamanho; i++) {
        vetor[i] = saida[i];
    }

    free(saida);
}

void radixSort(const int vetorOriginal[], int tamanho) {
    int *vetorCopia = (int *)malloc(tamanho * sizeof(int));
    if (!vetorCopia) return;

    memcpy(vetorCopia, vetorOriginal, tamanho * sizeof(int));
    puts("\nPasso a passo ordenacao com metodo RadixSort\n");

    int maior = obterMaior(vetorCopia, tamanho);

    for (int exp = 1; maior / exp > 0; exp *= 10) {
        countingSortRadix(vetorCopia, tamanho, exp);
        exibir(vetorCopia, tamanho);
        SLEEP_SEC(1);
    }

    puts("\nPressione ENTER para continuar...");
    getchar();
    free(vetorCopia);
}

// ----------------------------------------------------------------------------
// 5. MergeSort - O(n log n)
// ----------------------------------------------------------------------------
static void merge(int vetor[], int esquerda, int meio, int direita) {
    int n1 = meio - esquerda + 1;
    int n2 = direita - meio;

    int *esq = (int *)malloc(n1 * sizeof(int));
    int *dir = (int *)malloc(n2 * sizeof(int));
    if (!esq || !dir) {
        free(esq);
        free(dir);
        return;
    }

    for (int i = 0; i < n1; i++) esq[i] = vetor[esquerda + i];
    for (int j = 0; j < n2; j++) dir[j] = vetor[meio + 1 + j];

    int i = 0, j = 0, k = esquerda;
    while (i < n1 && j < n2) {
        if (esq[i] <= dir[j]) {
            vetor[k++] = esq[i++];
        } else {
            vetor[k++] = dir[j++];
        }
    }

    while (i < n1) vetor[k++] = esq[i++];
    while (j < n2) vetor[k++] = dir[j++];

    free(esq);
    free(dir);
}

static void mergeSortRecursive(int vetor[], int esquerda, int direita) {
    if (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        mergeSortRecursive(vetor, esquerda, meio);
        mergeSortRecursive(vetor, meio + 1, direita);
        merge(vetor, esquerda, meio, direita);
    }
}

void mergeSort(const int vetorOriginal[], int tamanho) {
    int *vetorCopia = (int *)malloc(tamanho * sizeof(int));
    if (!vetorCopia) return;

    memcpy(vetorCopia, vetorOriginal, tamanho * sizeof(int));
    puts("\nPasso a passo ordenacao com metodo MergeSort\n");
    mergeSortRecursive(vetorCopia, 0, tamanho - 1);
    exibir(vetorCopia, tamanho);
    puts("\nPressione ENTER para continuar...");
    getchar();
    free(vetorCopia);
}

// ----------------------------------------------------------------------------
// 6. QuickSort - O(n log n)
// ----------------------------------------------------------------------------
static int partition(int vetor[], int baixo, int alto) {
    int pivo = vetor[alto];
    int i = baixo - 1;

    for (int j = baixo; j < alto; j++) {
        if (vetor[j] < pivo) {
            i++;
            int temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;
        }
    }
    int temp = vetor[i + 1];
    vetor[i + 1] = vetor[alto];
    vetor[alto] = temp;
    return i + 1;
}

static void quickSortRecursive(int vetor[], int baixo, int alto) {
    if (baixo < alto) {
        int pi = partition(vetor, baixo, alto);
        quickSortRecursive(vetor, baixo, pi - 1);
        quickSortRecursive(vetor, pi + 1, alto);
    }
}

void quickSort(const int vetorOriginal[], int tamanho) {
    int *vetorCopia = (int *)malloc(tamanho * sizeof(int));
    if (!vetorCopia) return;

    memcpy(vetorCopia, vetorOriginal, tamanho * sizeof(int));
    puts("\nPasso a passo ordenacao com metodo QuickSort\n");
    quickSortRecursive(vetorCopia, 0, tamanho - 1);
    exibir(vetorCopia, tamanho);
    puts("\nPressione ENTER para continuar...");
    getchar();
    free(vetorCopia);
}

// ----------------------------------------------------------------------------
// 7. HeapSort - O(n log n)
// ----------------------------------------------------------------------------
static void heapify(int vetor[], int tamanho, int i) {
    int maior = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < tamanho && vetor[esquerda] > vetor[maior]) maior = esquerda;
    if (direita < tamanho && vetor[direita] > vetor[maior]) maior = direita;

    if (maior != i) {
        int temp = vetor[i];
        vetor[i] = vetor[maior];
        vetor[maior] = temp;
        heapify(vetor, tamanho, maior);
    }
}

void heapSort(const int vetorOriginal[], int tamanho) {
    int *vetorCopia = (int *)malloc(tamanho * sizeof(int));
    if (!vetorCopia) return;

    memcpy(vetorCopia, vetorOriginal, tamanho * sizeof(int));
    puts("\nPasso a passo ordenacao com metodo HeapSort\n");

    for (int i = tamanho / 2 - 1; i >= 0; i--) {
        heapify(vetorCopia, tamanho, i);
    }
    for (int i = tamanho - 1; i > 0; i--) {
        int temp = vetorCopia[0];
        vetorCopia[0] = vetorCopia[i];
        vetorCopia[i] = temp;
        heapify(vetorCopia, i, 0);
    }

    exibir(vetorCopia, tamanho);
    puts("\nPressione ENTER para continuar...");
    getchar();
    free(vetorCopia);
}

// ----------------------------------------------------------------------------
// Menu principal
// ----------------------------------------------------------------------------
void menuOrdenacao(void) {
    int vetor[TAM] = {34, 7, 23, 32, 5, 62, 12};
    int menu = 0;

    do {
        LIMPAR_TELA();
        puts("\n\t---------- MENU ORDENACAO ----------\n");
        printf("Vetor atual: ");
        exibir(vetor, TAM);
        puts("");
        puts("1 - Criar/Alterar vetor de entrada");
        puts("2 - Ordenar com BubbleSort");
        puts("3 - Ordenar com SelectSort");
        puts("4 - Ordenar com InsertSort");
        puts("5 - Ordenar com RadixSort");
        puts("6 - Ordenar com MergeSort");
        puts("7 - Ordenar com QuickSort");
        puts("8 - Ordenar com HeapSort");
        puts("9 - Sair");
        printf("\nEscolha uma opcao: ");

        if (scanf("%d", &menu) != 1) {
            menu = 0;
        }
        limpar_buffer();

        switch (menu) {
            case 1: criarVetor(vetor, TAM); break;
            case 2: bubbleSort(vetor, TAM); break;
            case 3: selectSort(vetor, TAM); break;
            case 4: insertSort(vetor, TAM); break;
            case 5: radixSort(vetor, TAM); break;
            case 6: mergeSort(vetor, TAM); break;
            case 7: quickSort(vetor, TAM); break;
            case 8: heapSort(vetor, TAM); break;
            case 9: puts("\nSaindo do programa de ordenacao..."); break;
            default:
                puts("Opcao invalida! Pressione ENTER para continuar.");
                getchar();
                break;
        }
    } while (menu != 9);
}

int main(void) {
    menuOrdenacao();
    return 0;
}
