/*
 * ============================================================================
 * Programa: AgendaDeContatos.c - Gerenciador de Contatos
 * Objetivo: Gestao de contatos com cadastro, edicao, exclusao, busca exata,
 *           busca parcial (substring), ordenacao alfabetica (qsort) e exportacao
 *           para arquivo texto.
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
  #include <windows.h>
  #define LIMPAR_TELA() system("cls")
#else
  #define LIMPAR_TELA() printf("\033[H\033[2J")
#endif

#define MAX_CONTATOS 100

// Estrutura otimizada para armazenar os dados de um contato
typedef struct {
    char nome[100];
    char email[100];
    char telefone[20];
    char aniversario[15];
} Contato;

typedef struct {
    Contato itens[MAX_CONTATOS];
    int quantidade;
} Agenda;

// Limpa o buffer de entrada do stdin
static void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Remove o caractere de nova linha '\n' deixado pelo fgets
static void remover_quebra_linha(char *str) {
    if (str) {
        str[strcspn(str, "\r\n")] = '\0';
    }
}

// Funcao de comparacao para qsort (ordem alfabetica por nome)
static int compararContatos(const void *a, const void *b) {
    const Contato *contatoA = (const Contato *)a;
    const Contato *contatoB = (const Contato *)b;
    return strcmp(contatoA->nome, contatoB->nome);
}

// Ordena os contatos em ordem alfabetica
void ordenarAgenda(Agenda *agenda) {
    if (!agenda || agenda->quantidade <= 1) return;
    qsort(agenda->itens, agenda->quantidade, sizeof(Contato), compararContatos);
}

// Exibe os detalhes de um contato (passagem por ponteiro constante para economia de stack)
void exibirContato(const Contato *contato) {
    if (!contato) return;
    printf("NOME               : %s\n", contato->nome);
    printf("EMAIL              : %s\n", contato->email);
    printf("TELEFONE           : %s\n", contato->telefone);
    printf("DATA DE ANIVERSARIO: %s\n", contato->aniversario);
    puts("----------------------------------------");
}

// Cadastra um novo contato na agenda
void cadastrarContato(Agenda *agenda) {
    if (!agenda) return;
    puts("\n\t====== ADICIONAR NOVO CONTATO ======");
    if (agenda->quantidade >= MAX_CONTATOS) {
        puts("A agenda esta cheia! Exclua um contato antes de adicionar novo.\n");
    } else {
        Contato *novo = &agenda->itens[agenda->quantidade];

        printf("Nome (ex.: Silvio Santos): ");
        if (fgets(novo->nome, sizeof(novo->nome), stdin)) {
            remover_quebra_linha(novo->nome);
        }

        printf("Email (ex.: silvio@email.com): ");
        if (fgets(novo->email, sizeof(novo->email), stdin)) {
            remover_quebra_linha(novo->email);
        }

        printf("Telefone (ex.: 11 91234-5678): ");
        if (fgets(novo->telefone, sizeof(novo->telefone), stdin)) {
            remover_quebra_linha(novo->telefone);
        }

        printf("Data de aniversario (ex.: DD/MM/AAAA): ");
        if (fgets(novo->aniversario, sizeof(novo->aniversario), stdin)) {
            remover_quebra_linha(novo->aniversario);
        }

        agenda->quantidade++;
        puts("\nContato cadastrado com sucesso!");
    }
    puts("Pressione ENTER para continuar...");
    getchar();
}

// Busca exata por nome
void buscarContato(const Agenda *agenda) {
    if (!agenda) return;
    puts("\n\t====== BUSCAR CONTATO ======");
    if (agenda->quantidade == 0) {
        puts("Lista vazia, adicione um contato!\n");
    } else {
        char busca[100];
        printf("Digite o nome exato do contato: ");
        if (fgets(busca, sizeof(busca), stdin)) {
            remover_quebra_linha(busca);

            int encontrado = 0;
            for (int i = 0; i < agenda->quantidade; i++) {
                if (strcmp(busca, agenda->itens[i].nome) == 0) {
                    puts("\nContato encontrado:");
                    exibirContato(&agenda->itens[i]);
                    encontrado = 1;
                    break;
                }
            }
            if (!encontrado) {
                puts("Contato nao encontrado!\n");
            }
        }
    }
    puts("Pressione ENTER para continuar...");
    getchar();
}

// Busca por substring no nome
void buscarContatoParcial(const Agenda *agenda) {
    if (!agenda) return;
    puts("\n\t====== BUSCAR CONTATO PARCIAL ======");
    if (agenda->quantidade == 0) {
        puts("Lista vazia, adicione um contato!\n");
    } else {
        char busca[100];
        printf("Digite parte do nome do contato: ");
        if (fgets(busca, sizeof(busca), stdin)) {
            remover_quebra_linha(busca);

            int encontrado = 0;
            for (int i = 0; i < agenda->quantidade; i++) {
                if (strstr(agenda->itens[i].nome, busca) != NULL) {
                    puts("\nResultado encontrado:");
                    exibirContato(&agenda->itens[i]);
                    encontrado = 1;
                }
            }
            if (!encontrado) {
                puts("Nenhum contato encontrado com esse termo!\n");
            }
        }
    }
    puts("Pressione ENTER para continuar...");
    getchar();
}

// Edita os dados de um contato
void alterarContato(Agenda *agenda) {
    if (!agenda) return;
    puts("\n\t====== ALTERAR CONTATO ======");
    if (agenda->quantidade == 0) {
        puts("Lista vazia, adicione um contato!\n");
    } else {
        char alterar[100];
        printf("Digite o nome do contato que gostaria de alterar: ");
        if (fgets(alterar, sizeof(alterar), stdin)) {
            remover_quebra_linha(alterar);

            int encontrado = 0;
            for (int i = 0; i < agenda->quantidade; i++) {
                if (strcmp(alterar, agenda->itens[i].nome) == 0) {
                    encontrado = 1;
                    puts("\nCONTATO ATUAL:");
                    exibirContato(&agenda->itens[i]);

                    puts("Atualize as novas informacoes do contato:");
                    printf("Novo Nome: ");
                    if (fgets(agenda->itens[i].nome, sizeof(agenda->itens[i].nome), stdin)) {
                        remover_quebra_linha(agenda->itens[i].nome);
                    }

                    printf("Novo Email: ");
                    if (fgets(agenda->itens[i].email, sizeof(agenda->itens[i].email), stdin)) {
                        remover_quebra_linha(agenda->itens[i].email);
                    }

                    printf("Novo Telefone: ");
                    if (fgets(agenda->itens[i].telefone, sizeof(agenda->itens[i].telefone), stdin)) {
                        remover_quebra_linha(agenda->itens[i].telefone);
                    }

                    printf("Nova Data de Aniversario: ");
                    if (fgets(agenda->itens[i].aniversario, sizeof(agenda->itens[i].aniversario), stdin)) {
                        remover_quebra_linha(agenda->itens[i].aniversario);
                    }

                    puts("\nContato atualizado com sucesso!");
                    break;
                }
            }
            if (!encontrado) {
                puts("Contato nao encontrado!\n");
            }
        }
    }
    puts("Pressione ENTER para continuar...");
    getchar();
}

// Exclui um contato da agenda
void apagarContato(Agenda *agenda) {
    if (!agenda) return;
    puts("\n\t====== APAGAR CONTATO ======");
    if (agenda->quantidade == 0) {
        puts("Lista vazia, adicione um contato!\n");
    } else {
        char apagar[100];
        printf("Digite o nome do contato que gostaria de apagar: ");
        if (fgets(apagar, sizeof(apagar), stdin)) {
            remover_quebra_linha(apagar);

            int encontrado = 0;
            for (int i = 0; i < agenda->quantidade; i++) {
                if (strcmp(apagar, agenda->itens[i].nome) == 0) {
                    encontrado = 1;
                    puts("\nCONTATO SELECIONADO:");
                    exibirContato(&agenda->itens[i]);

                    for (int j = i; j < agenda->quantidade - 1; j++) {
                        agenda->itens[j] = agenda->itens[j + 1];
                    }
                    agenda->quantidade--;
                    puts("Contato apagado com sucesso!\n");
                    break;
                }
            }
            if (!encontrado) {
                puts("Contato nao encontrado!\n");
            }
        }
    }
    puts("Pressione ENTER para continuar...");
    getchar();
}

// Exibe a lista ordenada de contatos
void exibirContatos(Agenda *agenda) {
    if (!agenda) return;
    puts("\n\t====== LISTA DE CONTATOS (A - Z) ======");
    if (agenda->quantidade == 0) {
        puts("Lista vazia, cadastre um contato!\n");
    } else {
        ordenarAgenda(agenda);
        for (int i = 0; i < agenda->quantidade; i++) {
            exibirContato(&agenda->itens[i]);
        }
    }
    puts("Pressione ENTER para continuar...");
    getchar();
}

// Exporta contatos para um arquivo de texto
void criarTXT(const Agenda *agenda) {
    if (!agenda) return;
    puts("\n\t====== EXPORTANDO CONTATOS ======");

    FILE *arquivo = fopen("ListaDeContatos.txt", "w");
    if (arquivo == NULL) {
        puts("Erro ao abrir o arquivo para escrita!");
        return;
    }

    if (agenda->quantidade == 0) {
        fprintf(arquivo, "Nenhum contato cadastrado.\n");
    } else {
        for (int i = 0; i < agenda->quantidade; i++) {
            fprintf(arquivo, "NOME: %s\n", agenda->itens[i].nome);
            fprintf(arquivo, "EMAIL: %s\n", agenda->itens[i].email);
            fprintf(arquivo, "TELEFONE: %s\n", agenda->itens[i].telefone);
            fprintf(arquivo, "ANIVERSARIO: %s\n", agenda->itens[i].aniversario);
            fprintf(arquivo, "------------------------\n");
        }
        puts("Contatos salvos em 'ListaDeContatos.txt' com sucesso!");
    }
    fclose(arquivo);
}

// Menu principal da agenda
void menuAgenda(Agenda *agenda) {
    int menu = 0;
    do {
        LIMPAR_TELA();
        puts("\t================= MENU AGENDA =================");
        puts("\t1 - Adicionar novo contato");
        puts("\t2 - Editar dados de um contato");
        puts("\t3 - Excluir um contato");
        puts("\t4 - Buscar um contato (nome exato)");
        puts("\t5 - Buscar contato (termo parcial)");
        puts("\t6 - Mostrar todos os contatos (A-Z)");
        puts("\t7 - Salvar em TXT e Sair");
        printf("\nDigite uma opcao: ");

        if (scanf("%d", &menu) != 1) {
            menu = 0;
        }
        limpar_buffer();

        switch (menu) {
            case 1: cadastrarContato(agenda); break;
            case 2: alterarContato(agenda); break;
            case 3: apagarContato(agenda); break;
            case 4: buscarContato(agenda); break;
            case 5: buscarContatoParcial(agenda); break;
            case 6: exibirContatos(agenda); break;
            case 7: criarTXT(agenda); puts("Saindo do programa..."); break;
            default: puts("Opcao invalida! Pressione ENTER."); getchar(); break;
        }
    } while (menu != 7);
}

int main(void) {
    Agenda agenda;
    agenda.quantidade = 0;

    menuAgenda(&agenda);
    return 0;
}
