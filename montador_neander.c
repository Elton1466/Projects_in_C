/*
 * ============================================================================
 * Programa: Montador / Assembler para a Arquitetura Neander
 * Objetivo: Converte um arquivo de texto (.txt) contendo instrucoes Assembly 
 *           Neander em um arquivo binario (.mem) compativel com o simulador.
 * ============================================================================
 * Exemplo de entrada (.txt):
 *   LDA 80
 *   NOT
 *   ADD 81
 *   STA 83
 *   HLT
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Valores de opcode das instrucoes na Arquitetura Neander
static const int INST[11] = {0, 16, 32, 48, 64, 80, 96, 128, 144, 160, 240};

// Cabecalho padrao exigido pelo simulador Neander (.mem)
static const unsigned char CABECALHO[4] = {3, 78, 68, 82};

// Converte string para maiusculas de forma portavel (ISO C)
static void to_upper_str(char *str) {
    if (!str) return;
    for (int i = 0; str[i]; i++) {
        str[i] = (char)toupper((unsigned char)str[i]);
    }
}

// Converte string hexadecimal para numero decimal
static int hex_para_decimal(const char *hex) {
    int decimal = 0;
    if (hex && sscanf(hex, "%x", &decimal) == 1) {
        return decimal;
    }
    return 0;
}

int main() {
    FILE *arquivo = NULL;
    FILE *neander = NULL;
    char nome[100];
    char opcode[16];
    char endereco[16];
    int num;

    printf("Digite o nome do arquivo txt (deve estar no mesmo diretorio): ");
    if (scanf("%99s", nome) != 1) {
        puts("\nErro ao ler o nome do arquivo.\n");
        return 1;
    }

    arquivo = fopen(nome, "r");
    if (arquivo == NULL) {
        printf("\nErro: Arquivo '%s' nao encontrado.\n", nome);
        return 1;
    }

    neander = fopen("prog1.mem", "wb");
    if (neander == NULL) {
        puts("\nErro: Nao foi possivel criar o arquivo 'prog1.mem'.\n");
        fclose(arquivo);
        return 1;
    }

    printf("\nGerando prog1.mem ...\n");

    // Escreve o cabecalho fixo no arquivo .mem
    fwrite(CABECALHO, sizeof(unsigned char), sizeof(CABECALHO), neander);

    // Le e processa instrucao por instrucao
    while (fscanf(arquivo, "%15s", opcode) == 1) {
        to_upper_str(opcode);

        if (strcmp(opcode, "NOP") == 0) {
            fwrite(&INST[0], 2, 1, neander);
        } else if (strcmp(opcode, "STA") == 0) {
            fwrite(&INST[1], 2, 1, neander);
            if (fscanf(arquivo, "%15s", endereco) == 1) {
                num = hex_para_decimal(endereco);
                fwrite(&num, 2, 1, neander);
            }
        } else if (strcmp(opcode, "LDA") == 0) {
            fwrite(&INST[2], 2, 1, neander);
            if (fscanf(arquivo, "%15s", endereco) == 1) {
                num = hex_para_decimal(endereco);
                fwrite(&num, 2, 1, neander);
            }
        } else if (strcmp(opcode, "ADD") == 0) {
            fwrite(&INST[3], 2, 1, neander);
            if (fscanf(arquivo, "%15s", endereco) == 1) {
                num = hex_para_decimal(endereco);
                fwrite(&num, 2, 1, neander);
            }
        } else if (strcmp(opcode, "OR") == 0) {
            fwrite(&INST[4], 2, 1, neander);
            if (fscanf(arquivo, "%15s", endereco) == 1) {
                num = hex_para_decimal(endereco);
                fwrite(&num, 2, 1, neander);
            }
        } else if (strcmp(opcode, "AND") == 0) {
            fwrite(&INST[5], 2, 1, neander);
            if (fscanf(arquivo, "%15s", endereco) == 1) {
                num = hex_para_decimal(endereco);
                fwrite(&num, 2, 1, neander);
            }
        } else if (strcmp(opcode, "NOT") == 0) {
            fwrite(&INST[6], 2, 1, neander);
        } else if (strcmp(opcode, "JMP") == 0) {
            fwrite(&INST[7], 2, 1, neander);
            if (fscanf(arquivo, "%15s", endereco) == 1) {
                num = hex_para_decimal(endereco);
                fwrite(&num, 2, 1, neander);
            }
        } else if (strcmp(opcode, "JN") == 0) {
            fwrite(&INST[8], 2, 1, neander);
            if (fscanf(arquivo, "%15s", endereco) == 1) {
                num = hex_para_decimal(endereco);
                fwrite(&num, 2, 1, neander);
            }
        } else if (strcmp(opcode, "JZ") == 0) {
            fwrite(&INST[9], 2, 1, neander);
            if (fscanf(arquivo, "%15s", endereco) == 1) {
                num = hex_para_decimal(endereco);
                fwrite(&num, 2, 1, neander);
            }
        } else if (strcmp(opcode, "HLT") == 0) {
            fwrite(&INST[10], 2, 1, neander);
        }
    }

    fclose(arquivo);
    fclose(neander);
    printf("Arquivo 'prog1.mem' gerado com sucesso!\n");
    return 0;
}
