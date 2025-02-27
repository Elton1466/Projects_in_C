#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define TAM 7 

/*
Descrição:
Este código é um programa em C que permite ao usuário criar um vetor de números inteiros e escolher entre diferentes métodos de ordenação para organizar os elementos do vetor. 
Os métodos de ordenação implementados incluem BubbleSort, SelectionSort, InsertionSort, MergeSort, QuickSort e HeapSort. O programa exibe o passo a passo da ordenação, 
facilitando a compreensão do funcionamento de cada algoritmo.

O código foi desenvolvido para fins educacionais e pode ser utilizado como referência para estudos sobre algoritmos de ordenação. 
Sinta-se à vontade para contribuir, sugerir melhorias ou reportar problemas no repositório.
*/

int vetorA[TAM], vetorB[TAM];

// Função para criar um vetor com valores inseridos pelo usuário
void criarVetor() {
    puts("\nDigite 7 valores para inserir no vetor:\n"); 
    for(int i = 0; i < TAM; i++) {
        printf("Item %i - ", i + 1);
        scanf("%i", &vetorA[i]); 
    }
}

// Função para exibir o vetor atual
void exibir(int vetor[], int tamanho) {
    for(int i = 0; i < tamanho; i++) { 
        printf("| %i ", vetor[i]);
    }  
    printf("\n");
} 

// BubbleSort
void bubbleSort(int vetorOriginal[], int tamanho) {
    int aux, vetorCopia[tamanho];
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
            sleep(1);
        }
    }
    puts("\nPressione ENTER para continuar..."); getchar();
} 

// SelectionSort
void selectSort(int vetorOriginal[], int tamanho) {
    int vetorCopia[tamanho], indiceMinimo, temp;
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
        sleep(1);
    }
    puts("\nPressione ENTER para continuar..."); getchar();
}

// InsertionSort
void insertSort(int vetorOriginal[], int tamanho) {
    int vetorCopia[tamanho], chave, j;
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
        sleep(1);
    }
    puts("\nPressione ENTER para continuar..."); getchar();
}

// Funções auxiliares para MergeSort
void merge(int vetor[], int esquerda, int meio, int direita) {
    int tamanhoEsquerda = meio - esquerda + 1;
    int tamanhoDireita = direita - meio;

    int vetorEsquerdo[tamanhoEsquerda], vetorDireito[tamanhoDireita];

    for (int i = 0; i < tamanhoEsquerda; i++) vetorEsquerdo[i] = vetor[esquerda + i];
    for (int i = 0; i < tamanhoDireita; i++) vetorDireito[i] = vetor[meio + 1 + i];

    int i = 0, j = 0, k = esquerda;

    while (i < tamanhoEsquerda && j < tamanhoDireita) {
        if (vetorEsquerdo[i] <= vetorDireito[j]) vetor[k++] = vetorEsquerdo[i++];
        else vetor[k++] = vetorDireito[j++];
    }

    while (i < tamanhoEsquerda) vetor[k++] = vetorEsquerdo[i++];
    while (j < tamanhoDireita) vetor[k++] = vetorDireito[j++];
}

void mergeSortRecursive(int vetor[], int esquerda, int direita) {
    if (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        mergeSortRecursive(vetor, esquerda, meio);
        mergeSortRecursive(vetor, meio + 1, direita);
        merge(vetor, esquerda, meio, direita);
    }
}

void mergeSort(int vetorOriginal[], int tamanho) {
    int vetorCopia[tamanho];
    memcpy(vetorCopia, vetorOriginal, tamanho * sizeof(int));
    puts("\nPasso a passo ordenacao com metodo MergeSort\n");
    mergeSortRecursive(vetorCopia, 0, tamanho - 1);
    exibir(vetorCopia, tamanho);
    puts("\nPressione ENTER para continuar..."); getchar();
}

// Funções auxiliares para QuickSort
int partition(int vetor[], int baixo, int alto) {
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

void quickSortRecursive(int vetor[], int baixo, int alto) {
    if (baixo < alto) {
        int pi = partition(vetor, baixo, alto);
        quickSortRecursive(vetor, baixo, pi - 1);
        quickSortRecursive(vetor, pi + 1, alto);
    }
}

void quickSort(int vetorOriginal[], int tamanho) {
    int vetorCopia[tamanho];
    memcpy(vetorCopia, vetorOriginal, tamanho * sizeof(int));
    puts("\nPasso a passo ordenacao com metodo QuickSort\n");
    quickSortRecursive(vetorCopia, 0, tamanho - 1);
    exibir(vetorCopia, tamanho);
    puts("\nPressione ENTER para continuar..."); getchar();
}

// Funções auxiliares para HeapSort
void heapify(int vetor[], int tamanho, int i) {
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

void heapSort(int vetorOriginal[], int tamanho) {
    int vetorCopia[tamanho];
    memcpy(vetorCopia, vetorOriginal, tamanho * sizeof(int));
    puts("\nPasso a passo ordenacao com metodo HeapSort\n");
    for (int i = tamanho / 2 - 1; i >= 0; i--) heapify(vetorCopia, tamanho, i);
    for (int i = tamanho - 1; i > 0; i--) {
        int temp = vetorCopia[0];
        vetorCopia[0] = vetorCopia[i];
        vetorCopia[i] = temp;
        heapify(vetorCopia, i, 0);
    }
    exibir(vetorCopia, tamanho);
    puts("\nPressione ENTER para continuar..."); getchar();
}

// Menu para selecionar o método de ordenação
void menuOrdenacao() {
    int menu;
    do {
        system("CLS");
        puts("\n\n\t---------- MENU ----------\n");
        puts("1 - Criar um vetor");
        puts("2 - Ordenar com BubbleSort");
        puts("3 - Ordenar com SelectSort");
        puts("4 - Ordenar com InsertSort");
        puts("5 - Ordenar com RadixSort");
        puts("6 - Ordenar com MergeSort");
        puts("7 - Ordenar com QuickSort");
        puts("8 - Ordenar com HeapSort");
        puts("9 - Sair");
        printf("\nEscolha uma opcao: ");
        scanf("%i", &menu);
        switch (menu) {
            case 1: criarVetor(); break;
            case 2: bubbleSort(vetorA, TAM); break;
            case 3: selectSort(vetorA, TAM); break;
            case 4: insertSort(vetorA, TAM); break;
            case 5: radixSort(vetorA, TAM); break;
            case 6: mergeSort(vetorA, TAM); break;
            case 7: quickSort(vetorA, TAM); break;
            case 8: heapSort(vetorA, TAM); break;
            case 9: puts("\n....Program finished with exit code 0\nPress ENTER to exit console."); break;
            default: puts("Digite uma opcao valida!"); getchar(); break;
        }
    } while (menu != 9);
}

int main() {
    menuOrdenacao();
    return 0;
}
