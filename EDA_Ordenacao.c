#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define TAM 7 

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
void exibir(int a[], int size) {
    for(int i = 0; i < size; i++) { 
        printf("| %i ", a[i]);
    }  
    printf("\n");
} 

// BubbleSort
void bubbleSort(int b[], int size) {
    int aux, a[size];
    memcpy(a, b, size * sizeof(int));
    puts("\nPasso a passo ordenacao com metodo BubbleSort\n");
    for (int i = 0; i < size - 1; i++) { 
        for (int j = 0; j < size - i - 1; j++) { 
            if (a[j] > a[j + 1]) {
                aux = a[j];
                a[j] = a[j + 1];
                a[j + 1] = aux;
            }
            exibir(a, size);
            sleep(1);
        }
    }
    puts("\nPressione ENTER para continuar..."); getchar();
} 

// SelectionSort
void selectSort(int b[], int size) {
    int a[size], minIdx, temp;
    memcpy(a, b, size * sizeof(int));
    puts("\nPasso a passo ordenacao com metodo SelectSort\n");
    for (int i = 0; i < size - 1; i++) {
        minIdx = i;
        for (int j = i + 1; j < size; j++) {
            if (a[j] < a[minIdx]) {
                minIdx = j;
            }
        }
        temp = a[minIdx];
        a[minIdx] = a[i];
        a[i] = temp;
        exibir(a, size);
        sleep(1);
    }
    puts("\nPressione ENTER para continuar..."); getchar();
}

// InsertionSort
void insertSort(int b[], int size) {
    int a[size], key, j;
    memcpy(a, b, size * sizeof(int));
    puts("\nPasso a passo ordenacao com metodo InsertSort\n");
    for (int i = 1; i < size; i++) {
        key = a[i];
        j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
        exibir(a, size);
        sleep(1);
    }
    puts("\nPressione ENTER para continuar..."); getchar();
}

// Funções auxiliares para MergeSort
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSortRecursive(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortRecursive(arr, l, m);
        mergeSortRecursive(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void mergeSort(int b[], int size) {
    int a[size];
    memcpy(a, b, size * sizeof(int));
    puts("\nPasso a passo ordenacao com metodo MergeSort\n");
    mergeSortRecursive(a, 0, size - 1);
    exibir(a, size);
    puts("\nPressione ENTER para continuar..."); getchar();
}

// Funções auxiliares para QuickSort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quickSortRecursive(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortRecursive(arr, low, pi - 1);
        quickSortRecursive(arr, pi + 1, high);
    }
}

void quickSort(int b[], int size) {
    int a[size];
    memcpy(a, b, size * sizeof(int));
    puts("\nPasso a passo ordenacao com metodo QuickSort\n");
    quickSortRecursive(a, 0, size - 1);
    exibir(a, size);
    puts("\nPressione ENTER para continuar..."); getchar();
}

// Funções auxiliares para HeapSort
void heapify(int arr[], int size, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < size && arr[l] > arr[largest]) largest = l;
    if (r < size && arr[r] > arr[largest]) largest = r;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, size, largest);
    }
}

void heapSort(int b[], int size) {
    int a[size];
    memcpy(a, b, size * sizeof(int));
    puts("\nPasso a passo ordenacao com metodo HeapSort\n");
    for (int i = size / 2 - 1; i >= 0; i--) heapify(a, size, i);
    for (int i = size - 1; i > 0; i--) {
        int temp = a[0];
        a[0] = a[i];
        a[i] = temp;
        heapify(a, i, 0);
    }
    exibir(a, size);
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
