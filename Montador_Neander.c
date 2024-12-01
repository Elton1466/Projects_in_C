/*
Este programa tem como objetivo transformar um arquivo de texto contendo instruções em Assembly 
(escritas no formato compatível com o simulador Neander) em um arquivo binário no formato .mem. 
Este arquivo gerado pode ser executado diretamente no simulador Neander.

Requisitos para funcionamento:
- O arquivo de texto deve estar salvo no mesmo diretório que o executável deste programa.
- O arquivo de entrada deve ter a extensão .txt e conter apenas instruções em Assembly sem 
  numeração de linhas.
- Os valores de endereço devem estar em formato hexadecimal.
- O arquivo gerado, denominado "prog1.mem", será salvo no mesmo diretório do programa e 
  incluirá um cabeçalho fixo seguido das instruções em binário.

Exemplo de entrada no arquivo .txt:

LDA 80 
NOT 
ADD 81 
STA 83 
HLT

Exemplo de saída no arquivo prog1.mem:
- O binário gerado seguirá o formato adequado para ser executado no simulador Neander.

Instruções de compilação:
- Este código deve ser compilado com o DEV-C++ para evitar problemas de compatibilidade.
*/

#include <stdio.h>
#include <string.h>
#include <conio.h>

// Declaração das instruções com seus valores correspondentes no simulador Neander
const int inst[11] = {0,16,32,48,64,80,96,128,144,160,240}; 

// Declaração de função para converter strings hexadecimais em números decimais
int encontraNum(char hex[2]); 

// Cabeçalho fixo que será adicionado no início do arquivo .mem
unsigned char cabecalho[4] = {3,78,68,82}; 

int main () {
    FILE *arquivo; // Ponteiro para o arquivo de entrada .txt
    FILE *Neander; // Ponteiro para o arquivo de saída .mem
    char nome[80]; // Nome do arquivo de entrada fornecido pelo usuário
    char opcode[3]; // Para armazenar a instrução lida do arquivo
    char endereco[2]; // Para armazenar os endereços em hexadecimal
    int num; // Variável para armazenar o valor decimal do endereço

    // Solicita ao usuário o nome do arquivo de entrada
    printf("Digite o nome do arquivo txt (arquivo deve estar na mesma pasta do programa): ");
    fflush(stdin);
    scanf("%s", &nome); 
    
    // Abre o arquivo de entrada no modo leitura
    arquivo = fopen(nome, "r");

    // Verifica se o arquivo de entrada existe
    if(arquivo == NULL) {
        puts("\nArquivo não encontrado...\n");
        return 1;
    } else {
        // Cria o arquivo de saída no modo binário
        Neander = fopen("prog1.mem", "wb"); 
    }
    
    // Verifica se o arquivo de saída foi criado com sucesso
    if(Neander == NULL) {
        puts("\nNão foi possível criar o arquivo...\n");
        fclose(arquivo);
        return 1;
    }
    
    if(arquivo != NULL && Neander != NULL)
        printf("Gerando prog1.mem ...");
    
    // Escreve o cabeçalho no início do arquivo .mem
    for(int i = 0; i < sizeof(cabecalho); i++)
        fwrite(&cabecalho[i], sizeof(cabecalho[i]), 1, Neander);
    
    // Loop para ler e processar as instruções do arquivo de entrada
    while (fscanf(arquivo, "%s", opcode) != EOF) { 
        strcpy(opcode, strupr(opcode)); // Converte a instrução para maiúscula

        // Processa cada instrução e escreve o código binário correspondente no arquivo .mem
        if (strcmp(opcode, "NOP") == 0) {
            fwrite(&inst[0], 2, 1, Neander);
        }
        if (strcmp(opcode, "STA") == 0) {
            fwrite(&inst[1], 2, 1, Neander);
            fscanf(arquivo, " %s", endereco);
            num = encontraNum(endereco);
            fwrite(&num, 2, 1, Neander);
        }
        if (strcmp(opcode, "LDA") == 0) {
            fwrite(&inst[2], 2, 1, Neander);
            fscanf(arquivo, " %s", endereco);
            num = encontraNum(endereco);
            fwrite(&num, 2, 1, Neander);
        }
        if (strcmp(opcode, "ADD") == 0) {
            fwrite(&inst[3], 2, 1, Neander);
            fscanf(arquivo, " %s", endereco);
            num = encontraNum(endereco);
            fwrite(&num, 2, 1, Neander);
        }
        if (strcmp(opcode, "OR") == 0) {
            fwrite(&inst[4], 2, 1, Neander);
            fscanf(arquivo, " %s", endereco);
            num = encontraNum(endereco);
            fwrite(&num, 2, 1, Neander);
        }
        if (strcmp(opcode, "AND") == 0) {
            fwrite(&inst[5], 2, 1, Neander);
            fscanf(arquivo, " %s", endereco);
            num = encontraNum(endereco);
            fwrite(&num, 2, 1, Neander);
        }
        if (strcmp(opcode, "NOT") == 0) {
            fwrite(&inst[6], 2, 1, Neander);
        }
        if (strcmp(opcode, "JMP") == 0) {
            fwrite(&inst[7], 2, 1, Neander);
            fscanf(arquivo, " %s", endereco);
            num = encontraNum(endereco);
            fwrite(&num, 2, 1, Neander);
        }
        if (strcmp(opcode, "JN") == 0) {
            fwrite(&inst[8], 2, 1, Neander);
            fscanf(arquivo, " %s", endereco);
            num = encontraNum(endereco);
            fwrite(&num, 2, 1, Neander);
        }
        if (strcmp(opcode, "JZ") == 0) {
            fwrite(&inst[9], 2, 1, Neander);
            fscanf(arquivo, " %s", endereco);
            num = encontraNum(endereco);
            fwrite(&num, 2, 1, Neander);
        }
        if (strcmp(opcode, "HLT") == 0) {
            fwrite(&inst[10], 2, 1, Neander);
        }
    }
    
    // Fecha os arquivos após o processamento
    fclose(arquivo);
    fclose(Neander); 
}

// Função para converter uma string hexadecimal em um número decimal
int encontraNum(char hex[2]) {
    int decimal;
    sscanf(hex, "%x", &decimal); // Lê o valor hexadecimal e o converte para decimal
    return decimal;
}
