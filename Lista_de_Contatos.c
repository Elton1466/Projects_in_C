#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#define MAX_CONTATOS 100

struct Agenda {
    char nome[1000];
    char email[1000];
    char telefone[20];
    char aniversario[20];
};
struct Agenda contatos[MAX_CONTATOS];
int quantidadeContatos = 0;

int compararContatos(const void *a, const void *b) {
    struct Agenda *contatoA = (struct Agenda *)a;
    struct Agenda *contatoB = (struct Agenda *)b;
    return strcmp(contatoA->nome, contatoB->nome);
}

void ordenarAgenda() {
    qsort(contatos, quantidadeContatos, sizeof(struct Agenda), compararContatos);
}

void buscarContatoParcial() {
    char busca[1000];
    puts("\n\t====== BUSCAR CONTATO ======\n");
    if (quantidadeContatos == 0) {
        puts("Lista vazia, adicione um contato!\n");
        return;
    }
    puts("Digite parte do nome do contato que está procurando:");
    fgets(busca, sizeof(busca), stdin);
    int encontrado = 0;
    for (int i = 0; i < quantidadeContatos; ++i) {
        if (strstr(contatos[i].nome, busca) != NULL) {
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
	getchar();
}

void cadastrarContato() {
    puts("\n\t====== ADICIONAR NOVO CONTATO ======\n");
    if(quantidadeContatos == MAX_CONTATOS) {
        puts("Lista cheia, exclua um contato!\n");
    } else {
        puts("Insira os dados do contato");
        puts("Nome (ex.: Silvio Santos)");
        fgets(contatos[quantidadeContatos].nome, sizeof(contatos[quantidadeContatos].nome), stdin);    
        puts("Email (ex.: Silviosantos@email.com)");
        fgets(contatos[quantidadeContatos].email, sizeof(contatos[quantidadeContatos].email), stdin);    
        puts("Telefone (ex.: 11 91234-5678)");
        fgets(contatos[quantidadeContatos].telefone, sizeof(contatos[quantidadeContatos].telefone), stdin);
        puts("Data de aniversário (ex.: DD/MM/AAAA)");
        fgets(contatos[quantidadeContatos].aniversario, sizeof(contatos[quantidadeContatos].aniversario), stdin);
        quantidadeContatos++;
    }
}

void alterarContato() {
    char alterar[1000];
    puts("\n\t====== ALTERAR CONTATO ======\n");
    if(quantidadeContatos == 0) {
        puts("Lista vazia, adicione um contato!\n");
    } else {
        printf("Digite o nome do contato que gostaria de alterar:  ");
        fgets(alterar, sizeof(alterar), stdin);        
        for(int i = 0; i < quantidadeContatos; ++i) {
            if (strcmp(alterar, contatos[i].nome) == 0) {
                puts("\nCONTATO ATUAL");
                printf("NOME: %s", contatos[i].nome);
                printf("EMAIL: %s", contatos[i].email);
                printf("TELEFONE: %s", contatos[i].telefone);
                printf("DATA DE ANIVERSÁRIO: %s\n\n", contatos[i].aniversario);
                puts("Atualize as novas informações do contato");
                printf("Nome (ex.: Silvio Santos):  ");
                fgets(contatos[i].nome, sizeof(contatos[i].nome), stdin);    
                printf("Email (ex.: Silviosantos@email.com):  ");
                fgets(contatos[i].email, sizeof(contatos[i].email), stdin);    
                printf("Telefone (ex.: 11 91234-5678):  ");
                fgets(contatos[i].telefone, sizeof(contatos[i].telefone), stdin);
                printf("Data de aniversário (ex.: DD/MM/AAAA):  ");
                fgets(contatos[i].aniversario, sizeof(contatos[i].aniversario), stdin);
                break;
            }
        }
    }
    getchar();
}

void apagarContato() {
    char apagar[1000];
    puts("\n\t====== APAGAR CONTATO ======\n");
    if(quantidadeContatos == 0) {
        puts("Lista vazia, adicione um contato!\n");
    } else {
        printf("Digite o nome do contato que gostaria de apagar:  ");
        fgets(apagar, sizeof(apagar), stdin);
        for(int i = 0; i < quantidadeContatos; ++i) {
            if (strcmp(apagar, contatos[i].nome) == 0) {
                puts("\nCONTATO SELECIONADO PARA EXCLUIR");
                printf("NOME: %s", contatos[i].nome);
                printf("EMAIL: %s", contatos[i].email);
                printf("TELEFONE: %s", contatos[i].telefone);
                printf("DATA DE ANIVERSÁRIO: %s\n\n", contatos[i].aniversario);
                for(int j = i; j < quantidadeContatos - 1; j++) {
                    contatos[j] = contatos[j + 1];
                }
                quantidadeContatos--;
                puts("Contato apagado!\n");
                break;		
            }
        }
    }
    getchar();
}

void buscarContato() {
    char busca[1000];
    puts("\n\t====== BUSCAR CONTATO ======\n");
    if(quantidadeContatos == 0) {
        puts("Lista vazia, adicione um contato!\n");
    } else { 
        puts("Digite o nome do contato que está procurando:");
        fgets(busca, sizeof(busca), stdin);
        for(int i = 0; i < quantidadeContatos; ++i) {
            if(strcmp(busca, contatos[i].nome) == 0) {
                printf("NOME: %s", contatos[i].nome);
                printf("EMAIL: %s", contatos[i].email);
                printf("TELEFONE: %s", contatos[i].telefone);
                printf("DATA DE ANIVERSÁRIO: %s\n", contatos[i].aniversario);	
                return;
            }
        }
        puts("Contato não encontrado!\n");
    }
    getchar();
}

void exibirContatos() {
    puts("\n\t====== LISTA DE CONTATOS (A - Z) ======\n");
    if(quantidadeContatos == 0) {
        puts("Lista vazia, cadastre um contato!\n");
    } else {
        ordenarAgenda();
        for(int i = 0; i < quantidadeContatos; ++i ) {
            printf("NOME: %s", contatos[i].nome);
            printf("EMAIL: %s", contatos[i].email);
            printf("TELEFONE: %s", contatos[i].telefone);
            printf("DATA DE ANIVERSÁRIO: %s\n", contatos[i].aniversario);	
        }
    }
    getchar();
}

void criarTXT() {
	puts("\n\t====== SAIR DO PROGRAMA ======\n");

    FILE *TXT;
    TXT = fopen("ListaDeContatos.txt", "w");
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

void menuAgenda() {
    int menu;
    do {
        system("CLS");
        puts("\t================= MENU AGENDA =================");
        puts("\t1 - Adicionar novo contato");
        puts("\t2 - Editar dados de um contato");
        puts("\t3 - Excluir um contato");
        puts("\t4 - Buscar um contato");
        puts("\t5 - Buscar por parte do nome do contato");
        puts("\t6 - Mostrar todos contatos");
        puts("\t7 - Sair do programa");
        printf("\nDigite uma opção: ");
        scanf("%i", &menu); getchar(); 
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

int main () {
    setlocale(LC_ALL, "Portuguese");
    menuAgenda();
    return 0;
}
