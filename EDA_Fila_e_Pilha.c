/*
=================================================================================
                        GERENCIADOR DE FILA E PILHA
=================================================================================

Este programa implementa um sistema para gerenciar duas estruturas de dados:
uma **fila** e uma **pilha**, ambas com capacidade fixa definida pela constante `N`.

A estrutura geral do programa é organizada em funções para facilitar a manutenção
e a reutilização do código, oferecendo funcionalidades completas para manipulação
dessas estruturas. O programa também possui menus interativos para o usuário
navegar e realizar operações nas duas estruturas.

**Principais funcionalidades:**
1. **Fila:**
   - Inserir elementos na fila (enfileiramento).
   - Remover elementos da fila (desenfileiramento).
   - Exibir todos os elementos presentes na fila.
   - Verificar se a fila está cheia ou vazia.
   - Localizar um elemento específico na fila.

2. **Pilha:**
   - Inserir elementos na pilha (push).
   - Remover elementos da pilha (pop).
   - Exibir todos os elementos da pilha, indicando o topo.
   - Verificar se a pilha está cheia ou vazia.

3. **Menus interativos:**
   - Menu principal para escolha entre as estruturas de fila e pilha.
   - Menus específicos para as operações de cada estrutura.

**Regras das estruturas de dados:**
- **Fila (FIFO - First In, First Out):**
  A fila segue a política de "primeiro a entrar, primeiro a sair". Os elementos
  são inseridos no final e removidos do início.

- **Pilha (LIFO - Last In, First Out):**
  A pilha segue a política de "último a entrar, primeiro a sair". Os elementos
  são inseridos no topo e também removidos do topo.

**Detalhes técnicos:**
- O programa utiliza arrays para armazenar os elementos da fila e da pilha.
- As operações de inserção e remoção verificam previamente se as estruturas
  estão cheias ou vazias, evitando erros de acesso à memória.
- A interface foi projetada para ser intuitiva e fornecer mensagens claras ao
  usuário sobre o estado das estruturas (cheias, vazias, ocupação percentual).

**Finalidade:**
Este programa é um exemplo prático de manipulação de estruturas de dados
básicas em C, sendo útil tanto para fins educacionais quanto para aplicações
simples que exijam gerenciamento de filas e pilhas.

=================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define N 10

int FILA[N], PILHA[N];
int ini = 0, fim = 0, topo = 0, novo;

// Função auxiliar para verificar se a fila está cheia
int filaCheia() {
    return fim == N;
}

// Função auxiliar para verificar se a fila está vazia
int filaVazia() {
    return ini == fim;
}

// Função auxiliar para verificar se a pilha está cheia
int pilhaCheia() {
    return topo == N;
}

// Função auxiliar para verificar se a pilha está vazia
int pilhaVazia() {
    return topo == 0;
}

// Função para inserir na fila
void inserirFila() {
    if (filaCheia()) {
        puts("A fila está cheia, remova um elemento!");
        getchar();
    } else {
        printf("\nDigite o valor que gostaria de inserir: ");
        scanf("%i", &novo);
        FILA[fim++] = novo;
    }
}

// Função para remover da fila
void removerFila() {
    if (filaVazia()) {
        puts("A fila está vazia, não há elementos para remover!");
    } else {
        int valorRemovido = FILA[ini];
        printf("Valor removido: %d\n", valorRemovido);
        for (int i = ini; i < fim - 1; i++) {
            FILA[i] = FILA[i + 1];
        }
        fim--;
    }
    getchar();
}

// Função para exibir os elementos da fila
void exibirFila() {
    puts("\n\t======== FILA ========");
    if (filaVazia()) {
        puts("\tA fila está vazia!");
    } else {
        for (int i = ini; i < fim; ++i) {
            printf("%i (Pos: %d) | ", FILA[i], i + 1);
        }
        printf("\n");
    }
    getchar();
}

// Função para verificar o estado da fila
void verificarEstadoFila() {
    if (filaCheia()) {
        printf("A fila está cheia (%.2f%% ocupada)\n", (fim / (float)N) * 100);
    } else if (filaVazia()) {
        printf("A fila está vazia (%.2f%% ocupada)\n", (fim / (float)N) * 100);
    } else {
        printf("A fila não está cheia (%.2f%% ocupada)\n", (fim / (float)N) * 100);
    }
    getchar();
}

// Função para localizar um valor na fila
void localizarFila() {
    if (filaVazia()) {
        puts("A fila está vazia, não há elementos para localizar!");
    } else {
        int valorLocalizar, encontrado = 0;
        printf("Digite o valor que deseja localizar: ");
        scanf("%i", &valorLocalizar);
        for (int i = ini; i < fim; i++) {
            if (FILA[i] == valorLocalizar) {
                encontrado = 1;
                printf("Valor %d encontrado na posição %d da fila.\n", valorLocalizar, i+1);
                break;
            }
        }
        if (!encontrado) {
            printf("Valor %d não encontrado na fila.\n", valorLocalizar);
        }
    }
    getchar();
}

// Função para inserir na pilha
void inserirPilha() {
    if (pilhaCheia()) {
        puts("A pilha está cheia, remova um elemento!");
        getchar();
    } else {
        printf("\nDigite o valor que gostaria de inserir: ");
        scanf("%i", &novo);
        PILHA[topo++] = novo;
    }
}

// Função para remover da pilha
void removerPilha() {
    if (pilhaVazia()) {
        puts("A pilha está vazia, não há elementos para remover!");
    } else {
        int valorRemovido = PILHA[--topo];
        printf("Valor removido: %d\n", valorRemovido);
    }
    getchar();
}

// Função para exibir os elementos da pilha
void exibirPilha() {
    puts("\n\t======== PILHA ========");
    if (pilhaVazia()) {
        puts("\tA pilha está vazia!");
    } else {
        for (int i = topo - 1; i >= 0; i--) {
            if (i == topo - 1) {
                printf("| %i | (topo)\n", PILHA[i]);
            } else {
                printf("| %i |\n", PILHA[i]);
            }
        }
    }
    getchar();
}

// Função para verificar o estado da pilha
void verificarEstadoPilha() {
    if (pilhaVazia()) {
        printf("A pilha está vazia (%.2f%% ocupada)\n", (topo / (float)N) * 100);
    } else if (pilhaCheia()) {
        printf("A pilha está cheia (%.2f%% ocupada)\n", (topo / (float)N) * 100);
    } else {
        printf("A pilha não está cheia (%.2f%% ocupada)\n", (topo / (float)N) * 100);
    }
    getchar();
}

// Menu para a fila
void menuFila() {
    int menu;
    do {
        system("CLS");
        puts("\n\t---------- FILA ----------");
        puts("1 - Inserir elemento");
        puts("2 - Remover elemento");
        puts("3 - Exibir todos elementos");
        puts("4 - Verificar o estado da fila (cheia / vazia)");
        puts("5 - Localizar elemento");
        puts("6 - Sair do menu da fila");
        printf("\nEscolha uma opção: ");
        scanf("%i", &menu);

        switch (menu) {
            case 1: inserirFila(); break;
            case 2: removerFila(); break;
            case 3: exibirFila(); break;
            case 4: verificarEstadoFila(); break;
            case 5: localizarFila(); break;
            case 6: puts("Saindo do menu da fila..."); break;
            default: puts("Digite uma opção válida!"); getchar(); break;
        }
    } while (menu != 6);
}

// Menu para a pilha
void menuPilha() {
    int menu;
    do {
        system("CLS");
        puts("\n\t---------- PILHA ----------");
        puts("1 - Inserir elemento");
        puts("2 - Remover elemento");
        puts("3 - Exibir topo");
        puts("4 - Verificar o estado da pilha (cheia / vazia)");
        puts("5 - Sair do menu da pilha");
        printf("\nEscolha uma opção: ");
        scanf("%i", &menu);

        switch (menu) {
            case 1: inserirPilha(); break;
            case 2: removerPilha(); break;
            case 3: exibirPilha(); break;
            case 4: verificarEstadoPilha(); break;
            case 5: puts("Saindo do menu Pilha..."); break;
            default: puts("Digite uma opção válida!"); getchar(); break;
        }
    } while (menu != 5);
}

// Menu principal
int menuPrincipal() {
    int op;
    do {
        system("CLS");
        puts("//////////////////////////////////////");
        puts("\tESTRUTURA DE DADOS");
        puts("//////////////////////////////////////");
        puts("\nQual estrutura gostaria de acessar ?");
        puts("1 - FILA");
        puts("2 - PILHA");
        puts("3 - Sair do programa");
        printf("\nDigite uma opção: ");
        scanf("%i", &op);

        switch (op) {
            case 1: menuFila(); break;
            case 2: menuPilha(); break;
            case 3: printf("Saindo do programa...\n"); break;
            default: puts("Digite uma opção válida!");
        }
		
    } while (op != 3);
    	return 0;
}

int main() {
    
	setlocale(LC_ALL, "Portuguese");
	
	menuPrincipal();
		
}
