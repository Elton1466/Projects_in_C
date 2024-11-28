/***********************************************************************************************************
*                                                                                                          *
*     Estrutura de Dados I                                                                                 *                                                                                            *
*                                                                                                          *
*     Dado o vetor abaixo, faça o passo a passo para ordenação de valores de forma crescente               *
*     utilizando os três algoritmos vistos em sala de aula: Bolha, Seleção e Inserção.                     *
*                                                                                                          *
*     | 7 | 34 | 45 | 23 | 15 | 3 | 5 |                                                                    *
*                                                                                                          *
*     Faça um programa em linguagem C, que permita ao usuário digitar o números. Em seguida,               *
*     mostre um menu com os métodos de ordenação disponiveis e mostre na tela o passo a passo              *
*     da execução.                                                                                         *
*                                                                                                          *            
************************************************************************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define TAM 7 

int vetorA[TAM], vetorB[TAM];

void criarVetor() {
    puts("\nDigite 7 valores para inserir no vetor:\n"); 
    for(int i = 0; i < TAM; i++) {
        printf("Item %i - ", i + 1);
        scanf("%i", &vetorA[i]); 
    }
}
    
void exibir(int a[], int size) {
	
	for(int i = 0; i < size; i++) { 
		printf("| %i ", a[i]);
	}  
    printf("\n");
    
} 

void bubbleSort(int b[], int size) {
	int aux, a[size];
	
	for (int i = 0; i < size; i++) {
        a[i] = b[i];
  }
    
  puts("\nPasso a passo ordenção com método BubbleSort\n");
	
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

void selectSort () { }

void insertSort() { }

void menuOrdenacao() { 
	int menu;
    do {
        system("CLS");
        puts("\n\n\t---------- MENU ----------\n");
        puts("1 - Criar um vetor");
        puts("2 - Ordenar com BubbleSort");
        puts("3 - Ordenar com SelectSort");
        puts("4 - Ordenar com InsertSort");
        puts("5 - Sair");
        printf("\nEscolha uma opção: ");
        scanf("%i", &menu);
        
        switch (menu) {
            case 1: criarVetor(); break;
            case 2: bubbleSort(vetorA, TAM); break;
            case 3: selectSort(); break;
            case 4: insertSort(); break;
            case 5: puts("\n....Program finished with exite code 0\nPress ENTER to exite console."); break;
            default: puts("Digite uma opção válida!"); getchar(); break;
        }
    } while (menu != 5);
}

int main() { 

    menuOrdenacao();
    
    return 0;
	
}
