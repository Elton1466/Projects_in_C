#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#define MAX_CONTATOS 100

/*
 * Programa: Agenda de Contatos
 * Objetivo: Este programa é uma aplicação em C que permite gerenciar uma agenda de contatos.
 * Ele possibilita adicionar, editar, buscar, listar e excluir contatos. Além disso, permite 
 * salvar os dados cadastrados em um arquivo de texto para consulta posterior. A lista de 
 * contatos é organizada em ordem alfabética para facilitar a navegação.
 */

// Estrutura para armazenar os dados de um contato
struct Agenda {
    char nome[1000];
    char email[1000];
    char telefone[20];
    char aniversario[20];
};

struct Agenda contatos[MAX_CONTATOS]; // Vetor para armazenar os contatos
int quantidadeContatos = 0; // Contador de contatos cadastrados

// Função de comparação para ordenar os contatos por nome (ordem alfabética)
int compararContatos(const void *a, const void *b) {
    struct Agenda *contatoA = (struct Agenda *)a;
    struct Agenda *contatoB = (struct Agenda *)b;
    return strcmp(contatoA->nome, contatoB->nome);
}

// Função para ordenar a lista de contatos em ordem alfabética
void ordenarAgenda() {
    qsort(contatos, quantidadeContatos, sizeof(struct Agenda), compararContatos);
}

// Função para limpar o buffer de entrada após fgets
void limparBuffer() {
    while(getchar() != '\n');
}

// Função para buscar um contato pelo nome exato
void buscarContato() {
    char busca[1000];
    puts("\n\t====== BUSCAR CONTATO ======");
    if (quantidadeContatos == 0) {
        puts("Lista vazia, adicione um contato!\n");
        return;
    }
    puts("Digite o nome do contato que está procurando:");
    fgets(busca, sizeof(busca), stdin);
    // Remover o newline inserido pelo fgets
    busca[strcspn(busca, "\n")] = '\0'; 
    
    for (int i = 0; i < quantidadeContatos; ++i) {
        if (strcmp(busca, contatos[i].nome) == 0) {
            printf("NOME: %s", contatos[i].nome);
            printf("EMAIL: %s", contatos[i].email);
            printf("TELEFONE: %s", contatos[i].telefone);
            printf("DATA DE ANIVERSÁRIO: %s\n", contatos[i].aniversario);    
            return;
        }
    }
    puts("Contato não encontrado!\n");
}

// Função para buscar um contato por parte do nome
void buscarContatoParcial() {
    char busca[1000];
    puts("\n\t====== BUSCAR CONTATO ======");
    if (quantidadeContatos == 0) {
        puts("Lista vazia, adicione um contato!\n");
        return;
    }
    puts("Digite parte do nome do contato que está procurando:");
    fgets(busca, sizeof(busca), stdin);
    busca[strcspn(busca, "\n")] = '\0'; // Remover o newline

    int encontrado = 0;
    for (int i = 0; i < quantidadeContatos; ++i) {
        if (strstr(contatos[i].nome, busca) != NULL) { // strstr encontra substring
            printf("NOME: %s", contatos[i].nome);
            printf("EMAIL: %s", contatos[i].email);
            printf("TELEFONE: %s", contatos[i].telefone);
            printf("DATA DE ANIVERSÁRIO: %s\n", contatos[i].aniversario);
            encontrado = 1;
        }
    }
    if (!encontrado) {
        puts("Nenhum contato encontrado com esse nome!\n");
    }
}

// Função para exibir os detalhes de um contato
void exibirContato(struct Agenda contato) {
    printf("NOME: %s", contato.nome);
    printf("EMAIL: %s", contato.email);
    printf("TELEFONE: %s", contato.telefone);
    printf("DATA DE ANIVERSÁRIO: %s\n", contato.aniversario);
}

// Função para cadastrar um novo contato
void cadastrarContato() {
    puts("\n\t====== ADICIONAR NOVO CONTATO ======");
    if (quantidadeContatos == MAX_CONTATOS) {
        puts("Lista cheia, exclua um contato!\n");
        return;
    }
    puts("Insira os dados do contato");

    printf("Nome (ex.: Silvio Santos): ");
    fgets(contatos[quantidadeContatos].nome, sizeof(contatos[quantidadeContatos].nome), stdin);
    contatos[quantidadeContatos].nome[strcspn(contatos[quantidadeContatos].nome, "\n")] = '\0'; // Remover o newline
    
    printf("Email (ex.: Silviosantos@email.com): ");
    fgets(contatos[quantidadeContatos].email, sizeof(contatos[quantidadeContatos].email), stdin);
    contatos[quantidadeContatos].email[strcspn(contatos[quantidadeContatos].email, "\n")] = '\0';
    
    printf("Telefone (ex.: 11 91234-5678): ");
    fgets(contatos[quantidadeContatos].telefone, sizeof(contatos[quantidadeContatos].telefone), stdin);
    contatos[quantidadeContatos].telefone[strcspn(contatos[quantidadeContatos].telefone, "\n")] = '\0';
    
    printf("Data de aniversário (ex.: DD/MM/AAAA): ");
    fgets(contatos[quantidadeContatos].aniversario, sizeof(contatos[quantidadeContatos].aniversario), stdin);
    contatos[quantidadeContatos].aniversario[strcspn(contatos[quantidadeContatos].aniversario, "\n")] = '\0';

    quantidadeContatos++;
}

// Função para alterar os dados de um contato
void alterarContato() {
    char alterar[1000];
    puts("\n\t====== ALTERAR CONTATO ======");
    if (quantidadeContatos == 0) {
        puts("Lista vazia, adicione um contato!\n");
        return;
    }
    printf("Digite o nome do contato que gostaria de alterar: ");
    fgets(alterar, sizeof(alterar), stdin);
    alterar[strcspn(alterar, "\n")] = '\0'; // Remover o newline
    
    for (int i = 0; i < quantidadeContatos; ++i) {
        if (strcmp(alterar, contatos[i].nome) == 0) {
            puts("\nCONTATO ATUAL");
            exibirContato(contatos[i]);
            
            puts("Atualize as novas informações do contato");
            printf("Nome: ");
            fgets(contatos[i].nome, sizeof(contatos[i].nome), stdin);
            contatos[i].nome[strcspn(contatos[i].nome, "\n")] = '\0'; // Remover o newline

            printf("Email: ");
            fgets(contatos[i].email, sizeof(contatos[i].email), stdin);
            contatos[i].email[strcspn(contatos[i].email, "\n")] = '\0';
            
            printf("Telefone: ");
            fgets(contatos[i].telefone, sizeof(contatos[i].telefone), stdin);
            contatos[i].telefone[strcspn(contatos[i].telefone, "\n")] = '\0';
            
            printf("Data de aniversário: ");
            fgets(contatos[i].aniversario, sizeof(contatos[i].aniversario), stdin);
            contatos[i].aniversario[strcspn(contatos[i].aniversario, "\n")] = '\0';
            break;
        }
    }
}

// Função para excluir um contato
void apagarContato() {
    char apagar[1000];
    puts("\n\t====== APAGAR CONTATO ======");
    if (quantidadeContatos == 0) {
        puts("Lista vazia, adicione um contato!\n");
        return;
    }
    printf("Digite o nome do contato que gostaria de apagar: ");
    fgets(apagar, sizeof(apagar), stdin);
    apagar[strcspn(apagar, "\n")] = '\0'; // Remover o newline
    
    for (int i = 0; i < quantidadeContatos; ++i) {
        if (strcmp(apagar, contatos[i].nome) == 0) {
            puts("\nCONTATO SELECIONADO PARA EXCLUIR");
            exibirContato(contatos[i]);
            // Exclui o contato deslocando os outros para a esquerda
            for (int j = i; j < quantidadeContatos - 1; j++) {
                contatos[j] = contatos[j + 1];
            }
            quantidadeContatos--;
            puts("Contato apagado!\n");
            break;
        }
    }
}

// Função para exibir todos os contatos em ordem alfabética
void exibirContatos() {
    puts("\n\t====== LISTA DE CONTATOS (A - Z) ======");
    if (quantidadeContatos == 0) {
        puts("Lista vazia, cadastre um contato!\n");
        return;
    }
    ordenarAgenda();
    for (int i = 0; i < quantidadeContatos; ++i) {
        exibirContato(contatos[i]);
    }
}

// Função para salvar os contatos em um arquivo .txt
void criarTXT() {
    puts("\n\t====== SAIR DO PROGRAMA ======");

    FILE *TXT = fopen("ListaDeContatos.txt", "w");
    if (TXT == NULL) {
        puts("Erro ao abrir o arquivo para escrita!");
        return;
    }
    if (quantidadeContatos == 0) {
        fprintf(TXT, "Nenhum contato cadastrado.\n");
    } else {
        for (int i = 0; i < quantidadeContatos; ++i) {
            fprintf(TXT, "NOME: %s", contatos[i].nome);
            fprintf(TXT, "EMAIL: %s", contatos[i].email);
            fprintf(TXT, "TELEFONE: %s", contatos[i].telefone);
            fprintf(TXT, "DATA DE ANIVERSÁRIO: %s\n", contatos[i].aniversario);
            fprintf(TXT, "------------------------\n");
        }
        puts("Contatos salvos em 'ListaDeContatos.txt' com sucesso!");
    }
    fclose(TXT);
}

// Função do menu principal da agenda
void menuAgenda() {
    int menu;
    do {
        system("CLS"); // Limpa a tela (no Windows)
        puts("\t================= MENU AGENDA =================");
        puts("\t1 - Adicionar novo contato");
        puts("\t2 - Editar dados de um contato");
        puts("\t3 - Excluir um contato");
        puts("\t4 - Buscar um contato");
        puts("\t5 - Buscar por parte do nome do contato");
        puts("\t6 - Mostrar todos contatos");
        puts("\t7 - Sair do programa");
        printf("\nDigite uma opção: ");
        scanf("%i", &menu); getchar(); // Captura a opção do usuário
        switch(menu) {
            case 1: cadastrarContato(); break;
            case 2: alterarContato(); break;
            case 3: apagarContato(); break;
            case 4: buscarContato(); break;
            case 5: buscarContatoParcial(); break; 
            case 6: exibirContatos(); break; 
            case 7: criarTXT(); break; 
            default: puts("Opção inválida! Tente novamente."); break;
        }
    } while(menu != 7);
}

// Função principal do programa
int main () {
    setlocale(LC_ALL, "Portuguese");
    menuAgenda(); // Chama o menu da agenda
    return 0;
}
