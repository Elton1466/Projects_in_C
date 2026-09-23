/*
 * ============================================================================
 * Programa: EDD_queue_stack.c - Gerenciador de Fila e Pilha (TAD)
 * Objetivo: Demonstracao de Tipos Abstratos de Dados (TAD) em C:
 *           - Fila (FIFO - First In, First Out)
 *           - Pilha (LIFO - Last In, First Out)
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
  #include <windows.h>
  #define LIMPAR_TELA() system("cls")
#else
  #define LIMPAR_TELA() printf("\033[H\033[2J")
#endif

#define N 10

// ----------------------------------------------------------------------------
// Definicao dos Tipos Abstratos de Dados (TADs)
// ----------------------------------------------------------------------------
typedef struct {
    int itens[N];
    int inicio;
    int fim;
} Fila;

typedef struct {
    int itens[N];
    int topo;
} Pilha;

// Limpa o buffer de entrada do stdin
static void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ----------------------------------------------------------------------------
// Funcoes do TAD Fila (FIFO)
// ----------------------------------------------------------------------------
static void inicializarFila(Fila *f) {
    if (!f) return;
    f->inicio = 0;
    f->fim = 0;
}

static int filaCheia(const Fila *f) {
    return f ? (f->fim == N) : 1;
}

static int filaVazia(const Fila *f) {
    return f ? (f->inicio == f->fim) : 1;
}

void inserirFila(Fila *f) {
    if (!f) return;
    if (filaCheia(f)) {
        puts("\nA fila esta cheia! Remova um elemento antes de inserir.");
    } else {
        int novo;
        printf("\nDigite o valor que gostaria de inserir na fila: ");
        if (scanf("%d", &novo) == 1) {
            f->itens[f->fim++] = novo;
            printf("Valor %d inserido com sucesso!\n", novo);
        }
    }
    limpar_buffer();
    puts("Pressione ENTER para continuar...");
    getchar();
}

void removerFila(Fila *f) {
    if (!f) return;
    if (filaVazia(f)) {
        puts("\nA fila esta vazia, nao ha elementos para remover!");
    } else {
        int valorRemovido = f->itens[f->inicio];
        printf("\nValor removido da fila: %d\n", valorRemovido);
        for (int i = f->inicio; i < f->fim - 1; i++) {
            f->itens[i] = f->itens[i + 1];
        }
        f->fim--;
    }
    limpar_buffer();
    puts("Pressione ENTER para continuar...");
    getchar();
}

void exibirFila(const Fila *f) {
    puts("\n\t======== FILA ========");
    if (!f || filaVazia(f)) {
        puts("\tA fila esta vazia!");
    } else {
        for (int i = f->inicio; i < f->fim; i++) {
            printf("%d (Pos: %d) | ", f->itens[i], i + 1);
        }
        printf("\n");
    }
    puts("Pressione ENTER para continuar...");
    getchar();
}

void verificarEstadoFila(const Fila *f) {
    if (!f) return;
    float ocupacao = (f->fim / (float)N) * 100.0f;
    if (filaCheia(f)) {
        printf("\nA fila esta cheia (%.2f%% ocupada)\n", ocupacao);
    } else if (filaVazia(f)) {
        printf("\nA fila esta vazia (%.2f%% ocupada)\n", ocupacao);
    } else {
        printf("\nA fila possui elementos (%.2f%% ocupada)\n", ocupacao);
    }
    puts("Pressione ENTER para continuar...");
    getchar();
}

void localizarFila(const Fila *f) {
    if (!f) return;
    if (filaVazia(f)) {
        puts("\nA fila esta vazia, nao ha elementos para localizar!");
    } else {
        int valorLocalizar, encontrado = 0;
        printf("\nDigite o valor que deseja localizar: ");
        if (scanf("%d", &valorLocalizar) == 1) {
            for (int i = f->inicio; i < f->fim; i++) {
                if (f->itens[i] == valorLocalizar) {
                    encontrado = 1;
                    printf("Valor %d encontrado na posicao %d da fila.\n", valorLocalizar, i + 1);
                    break;
                }
            }
            if (!encontrado) {
                printf("Valor %d nao encontrado na fila.\n", valorLocalizar);
            }
        }
    }
    limpar_buffer();
    puts("Pressione ENTER para continuar...");
    getchar();
}

// ----------------------------------------------------------------------------
// Funcoes do TAD Pilha (LIFO)
// ----------------------------------------------------------------------------
static void inicializarPilha(Pilha *p) {
    if (!p) return;
    p->topo = 0;
}

static int pilhaCheia(const Pilha *p) {
    return p ? (p->topo == N) : 1;
}

static int pilhaVazia(const Pilha *p) {
    return p ? (p->topo == 0) : 1;
}

void inserirPilha(Pilha *p) {
    if (!p) return;
    if (pilhaCheia(p)) {
        puts("\nA pilha esta cheia! Remova um elemento antes de inserir.");
    } else {
        int novo;
        printf("\nDigite o valor que gostaria de inserir na pilha: ");
        if (scanf("%d", &novo) == 1) {
            p->itens[p->topo++] = novo;
            printf("Valor %d empilhado com sucesso!\n", novo);
        }
    }
    limpar_buffer();
    puts("Pressione ENTER para continuar...");
    getchar();
}

void removerPilha(Pilha *p) {
    if (!p) return;
    if (pilhaVazia(p)) {
        puts("\nA pilha esta vazia, nao ha elementos para remover!");
    } else {
        int valorRemovido = p->itens[--p->topo];
        printf("\nValor desempilhado: %d\n", valorRemovido);
    }
    limpar_buffer();
    puts("Pressione ENTER para continuar...");
    getchar();
}

void exibirPilha(const Pilha *p) {
    puts("\n\t======== PILHA ========");
    if (!p || pilhaVazia(p)) {
        puts("\tA pilha esta vazia!");
    } else {
        for (int i = p->topo - 1; i >= 0; i--) {
            if (i == p->topo - 1) {
                printf("| %d | (topo)\n", p->itens[i]);
            } else {
                printf("| %d |\n", p->itens[i]);
            }
        }
    }
    puts("Pressione ENTER para continuar...");
    getchar();
}

void verificarEstadoPilha(const Pilha *p) {
    if (!p) return;
    float ocupacao = (p->topo / (float)N) * 100.0f;
    if (pilhaVazia(p)) {
        printf("\nA pilha esta vazia (%.2f%% ocupada)\n", ocupacao);
    } else if (pilhaCheia(p)) {
        printf("\nA pilha esta cheia (%.2f%% ocupada)\n", ocupacao);
    } else {
        printf("\nA pilha possui elementos (%.2f%% ocupada)\n", ocupacao);
    }
    puts("Pressione ENTER para continuar...");
    getchar();
}

// ----------------------------------------------------------------------------
// Menus interativos
// ----------------------------------------------------------------------------
void menuFila(Fila *f) {
    int menu = 0;
    do {
        LIMPAR_TELA();
        puts("\n\t---------- MENU FILA (FIFO) ----------");
        puts("1 - Inserir elemento (Enqueue)");
        puts("2 - Remover elemento (Dequeue)");
        puts("3 - Exibir elementos");
        puts("4 - Verificar estado da fila");
        puts("5 - Localizar elemento");
        puts("6 - Voltar ao menu principal");
        printf("\nEscolha uma opcao: ");

        if (scanf("%d", &menu) != 1) {
            menu = 0;
        }
        limpar_buffer();

        switch (menu) {
            case 1: inserirFila(f); break;
            case 2: removerFila(f); break;
            case 3: exibirFila(f); break;
            case 4: verificarEstadoFila(f); break;
            case 5: localizarFila(f); break;
            case 6: puts("Voltando ao menu principal..."); break;
            default: puts("Opcao invalida! Pressione ENTER."); getchar(); break;
        }
    } while (menu != 6);
}

void menuPilha(Pilha *p) {
    int menu = 0;
    do {
        LIMPAR_TELA();
        puts("\n\t---------- MENU PILHA (LIFO) ----------");
        puts("1 - Inserir elemento (Push)");
        puts("2 - Remover elemento (Pop)");
        puts("3 - Exibir pilha");
        puts("4 - Verificar estado da pilha");
        puts("5 - Voltar ao menu principal");
        printf("\nEscolha uma opcao: ");

        if (scanf("%d", &menu) != 1) {
            menu = 0;
        }
        limpar_buffer();

        switch (menu) {
            case 1: inserirPilha(p); break;
            case 2: removerPilha(p); break;
            case 3: exibirPilha(p); break;
            case 4: verificarEstadoPilha(p); break;
            case 5: puts("Voltando ao menu principal..."); break;
            default: puts("Opcao invalida! Pressione ENTER."); getchar(); break;
        }
    } while (menu != 5);
}

int main(void) {
    Fila fila;
    Pilha pilha;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    int op = 0;
    do {
        LIMPAR_TELA();
        puts("//////////////////////////////////////");
        puts("\tESTRUTURA DE DADOS (TAD)");
        puts("//////////////////////////////////////");
        puts("\nQual estrutura gostaria de acessar?");
        puts("1 - FILA (FIFO)");
        puts("2 - PILHA (LIFO)");
        puts("3 - Sair do programa");
        printf("\nDigite uma opcao: ");

        if (scanf("%d", &op) != 1) {
            op = 0;
        }
        limpar_buffer();

        switch (op) {
            case 1: menuFila(&fila); break;
            case 2: menuPilha(&pilha); break;
            case 3: printf("Saindo do programa...\n"); break;
            default: puts("Opcao invalida! Pressione ENTER."); getchar(); break;
        }
    } while (op != 3);

    return 0;
}
