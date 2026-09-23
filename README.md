# 🚀 Projetos e Algoritmos em C (Sistemas de Informação)

Este repositório reúne projetos práticos desenvolvidos durante o Bacharelado em Sistemas de Informação, focados no aprendizado de **Estruturas de Dados**, **Análise de Complexidade de Algoritmos**, **Gerenciamento de Memória** e **Arquitetura de Computadores**.

Todos os projetos foram refatorados atendendo ao padrão ISO **C99**, compilados estritamente com as flags `-Wall -Wextra` para garantia de zero warnings/erros, alocação segura de memória e boas práticas de engenharia de software acadêmica.

---

## 📚 Projetos Incluídos

### 1. 🛠️ Montador Neander (`montador_neander.c`)
- **Domínio**: Arquitetura de Computadores / Compiladores e Montadores (Assemblers).
- **Descrição**: Um montador para a arquitetura didática **Neander**. Lê um arquivo-fonte em Assembly Neander (`.txt`), processa a tabela de símbolos e gera a imagem de memória codificada (`.mem`) pronta para execução em simuladores da arquitetura Neander.
- **Destaques Técnicos**: Manipulação segura de arquivos, parsing de opcodes/operandos, tratamento de maiúsculas/minúsculas portátil e validação de limites de memória.

### 2. 📊 Algoritmos de Ordenação e Análise de Complexidade (`algoritmos_ordenacao.c`)
- **Domínio**: Estrutura de Dados e Análise de Algoritmos.
- **Descrição**: Suite interativa para comparação de desempenho entre diversos algoritmos de ordenação em vetores estáticos e dinâmicos.
- **Algoritmos Implementados**:
  - *Quadráticos $O(n^2)$*: Bubble Sort, Selection Sort, Insertion Sort.
  - *Logarítmicos / Eficientes $O(n \log n)$*: Quick Sort, Merge Sort.
  - *Não-Comparativo*: Radix Sort (LSD).
- **Destaques Técnicos**: Medição de tempo real de execução, interface ANSI portátil para limpeza de tela e animação visual de etapas de ordenação.

### 3. 🥞 Tipos Abstratos de Dados: Fila e Pilha (`estruturas_fila_pilha.c`)
- **Domínio**: Estruturas de Dados Lineares (TADs).
- **Descrição**: Implementação modularizada dos Tipos Abstratos de Dados (TAD) **Fila (Queue)** e **Pilha (Stack)**.
- **Destaques Técnicos**: Encapsulamento de dados, manipulação de ponteiros com validações defensivas de ponteiro nulo (`NULL`), eliminação completa de variáveis globais e desacoplamento entre lógica de negócios e I/O.

### 4. 📇 Gerenciador de Contatos Persistente (`agenda_contatos.c`)
- **Domínio**: Gerenciamento de Memória e Armazenamento em Arquivo.
- **Descrição**: Sistema de gestão de contatos com operações de CRUD (Criar, Listar, Buscar, Atualizar, Remover) e persistência em arquivo de texto.
- **Destaques Técnicos**: Otimização do layout de `struct` em memória, passagem de parâmetros por referência (`const Contato *`) para economizar *stack frame*, sanitização de entrada com `fgets`/`sscanf` prevenindo *buffer overflow*.

---

## 🛠️ Boas Práticas e Padrões Aplicados

- **Padrão ISO C99**: Código portável e compatível com compiladores modernos.
- **Zero Warnings**: Compilação limpa utilizando `gcc -Wall -Wextra -std=c99`.
- **Código Limpo e Seguro**: Substituição de funções legadas/inseguras (`gets`, `fflush(stdin)`, `<conio.h>`) por alternativas padronizadas (`fgets`, `to_upper_str`, sequências de escape ANSI).
- **Modularidade & Automação**: Automação completa do ciclo de build via `Makefile`.

---

## ⚙️ Como Compilar e Executar

### Pré-requisitos
- Compilador GCC instalado.
- Utilitário `make`.

### Compilação Automática (Todos os Projetos)
Para compilar todos os programas de uma só vez:
```bash
make all
```

### Compilando um Projeto Específico
```bash
make agenda_contatos
make algoritmos_ordenacao
make estruturas_fila_pilha
make montador_neander
```

### Executando os Programas
```bash
./agenda_contatos
./algoritmos_ordenacao
./estruturas_fila_pilha
./montador_neander <arquivo_assembly.txt>
```

### Limpeza de Artefatos de Build
Para remover os binários e arquivos temporários de compilação:
```bash
make clean
```

---

## 👤 Autoria
Desenvolvido por **Elton Araújo** no âmbito do Bacharelado em Sistemas de Informação.

---

## 🤖 Nota de Transparência e Uso de IA

> [!NOTE]
> A reestruturação da base de código, padronização ISO C99, criação dos scripts de automação de build (`Makefile`) e a elaboração desta documentação contaram com o auxílio de **Inteligência Artificial (Google Antigravity AI Agent)** como ferramenta de assistência no processo de refatoração e boas práticas de engenharia de software.


