# Playlist de Músicas

Programa desenvolvido em C para armazenar e manipular músicas utilizando uma **lista dinâmica encadeada** como estrutura de dados.

Cada nó da lista armazena uma música e uma referência para o próximo nó, permitindo que a playlist cresça e diminua dinamicamente.

## Funcionalidades

### Operações da estrutura de dados

O programa implementa as seguintes operações:

* `inicializar_lista` — cria e inicializa uma playlist vazia;
* `inserir` — insere uma música em uma determinada posição;
* `imprimir` — exibe todas as músicas da playlist;
* `buscar` — procura uma música pelo ID;
* `remover` — remove uma música pelo ID.

### Funcionalidades da playlist

O programa permite:

1. Inicializar uma playlist vazia;
2. Cadastrar uma nova música;
3. Inserir uma música no início da playlist;
4. Inserir uma música no final da playlist;
5. Inserir uma música em uma posição determinada;
6. Exibir todas as músicas armazenadas;
7. Buscar uma música pelo ID;
8. Buscar músicas pelo nome do artista;
9. Remover uma música pelo ID;
10. Informar a quantidade de músicas;
11. Informar a duração total da playlist.

## Estrutura utilizada

A música é representada por uma estrutura contendo:

```c
typedef struct {
    int id;
    char titulo[100];
    char artista[100];
    char album[100];
    int duracao;
} Musica;
```

Cada elemento da lista é representado por um nó:

```c
typedef struct No {
    Musica musica;
    struct No *proximo;
} No;
```

A lista possui um ponteiro para o primeiro nó e a quantidade de músicas:

```c
typedef struct {
    No *primeiro;
    int quantidade;
} Lista;
```

A representação da lista é:

```text
primeiro
   ↓
[Música 1] → [Música 2] → [Música 3] → NULL
```

Os nós são criados dinamicamente utilizando `malloc` e conectados por meio de ponteiros.

## Compilação

O programa utiliza a linguagem C e as bibliotecas padrão `stdio.h`, `stdlib.h` e `string.h`.

### GCC

Para compilar utilizando o GCC:

```bash
gcc main.c -o playlist
```

### Execução

No Linux ou macOS:

```bash
./playlist
```

No Windows:

```bash
playlist.exe
```

## Exemplo de execução

Ao iniciar o programa, o usuário encontrará o seguinte menu:

```text
===== MENU =====
1 - Cadastrar musica no inicio
2 - Cadastrar musica no final
3 - Cadastrar musica em uma posicao
4 - Exibir playlist
5 - Buscar musica por ID
6 - Buscar musica por artista
7 - Remover musica por ID
8 - Quantidade de musicas
9 - Duracao total da playlist
10 - Executar testes
0 - Sair
```

### Cadastro de uma música

Exemplo:

```text
ID: 1
Titulo: Blinding Lights
Artista: The Weeknd
Album: After Hours
Duracao em segundos: 200
```

A música é armazenada em um novo nó da lista.

### Inserção no início

Ao selecionar:

```text
1 - Cadastrar musica no inicio
```

a nova música é colocada antes da primeira música existente.

Exemplo:

```text
Antes:

[Música 1] → [Música 2] → NULL


Depois:

[Nova Música] → [Música 1] → [Música 2] → NULL
```

### Inserção no final

Ao selecionar:

```text
2 - Cadastrar musica no final
```

a nova música é adicionada depois do último nó.

Exemplo:

```text
Antes:

[Música 1] → [Música 2] → NULL


Depois:

[Música 1] → [Música 2] → [Nova Música] → NULL
```

### Inserção em uma posição

Ao selecionar:

```text
3 - Cadastrar musica em uma posicao
```

o usuário informa a posição em que deseja inserir a música.

Exemplo:

```text
Antes:

[Música 1] → [Música 2] → [Música 3] → NULL


Inserindo na posição 1:


Depois:

[Música 1] → [Nova Música] → [Música 2] → [Música 3] → NULL
```

### Exibição da playlist

Ao selecionar:

```text
4 - Exibir playlist
```

as músicas são percorridas desde o primeiro nó até `NULL`.

Exemplo:

```text
===== PLAYLIST =====
ID: 1
Titulo: Musica 1
Artista: Artista A
Album: Album A
Duracao: 200 segundos
--------------------
ID: 2
Titulo: Musica 2
Artista: Artista B
Album: Album B
Duracao: 180 segundos
--------------------
```

### Busca por ID

Ao informar um ID existente:

```text
ID da musica: 2
```

o programa apresenta os dados da música encontrada.

Caso o ID não exista:

```text
Musica nao encontrada.
```

### Busca por artista

O usuário informa o nome do artista:

```text
Nome do artista: Artista A
```

O programa percorre toda a lista e exibe as músicas pertencentes ao artista informado.

### Remoção

A remoção é realizada informando o ID da música:

```text
ID da musica: 2
```

O nó correspondente é retirado da lista e os ponteiros são ajustados.

### Quantidade de músicas

A opção:

```text
8 - Quantidade de musicas
```

exibe a quantidade atual de elementos armazenados na playlist.

Exemplo:

```text
Quantidade de musicas: 3
```

### Duração total

A opção:

```text
9 - Duracao total da playlist
```

percorre todos os nós e soma a duração de cada música.

Exemplo:

```text
Duracao total: 620 segundos
```

## Testes realizados

O programa possui uma opção de testes que verifica as principais funcionalidades da estrutura de dados e da playlist.

Para executar os testes, basta selecionar:

```text
10 - Executar testes
```

### Teste 1 — Criação de playlist vazia

Uma nova lista é inicializada.

**Resultado esperado:**

```text
primeiro = NULL
quantidade = 0
```

A playlist deve iniciar sem nenhuma música.

### Teste 2 — Inserção da primeira música

É inserida uma primeira música no início da playlist.

**Resultado esperado:**

```text
[Música 1] → NULL
```

A lista deve possuir uma música.

### Teste 3 — Inserção de várias músicas

São adicionadas várias músicas utilizando a inserção no final.

**Resultado esperado:**

```text
[Música 1] → [Música 2] → [Música 3] → NULL
```

### Teste 4 — Inserção no início

Uma nova música é inserida na primeira posição.

**Resultado esperado:**

```text
[Nova Música] → [Música 1] → [Música 2] → NULL
```

O ponteiro `primeiro` deve passar a apontar para a nova música.

### Teste 5 — Inserção no final

Uma nova música é adicionada depois do último elemento.

**Resultado esperado:**

```text
[Música 1] → [Música 2] → [Nova Música] → NULL
```

### Teste 6 — Inserção no meio

Uma música é inserida em uma posição intermediária.

**Resultado esperado:**

```text
[Música 1] → [Música 2] → [Nova Música] → [Música 3] → NULL
```

Os ponteiros devem ser ajustados para incluir o novo nó.

### Teste 7 — Busca de música existente

É realizada uma busca utilizando um ID existente.

Exemplo:

```text
ID: 2
```

**Resultado esperado:**

```text
Musica encontrada.
```

### Teste 8 — Busca de música inexistente

É realizada uma busca utilizando um ID que não está presente na lista.

Exemplo:

```text
ID: 99
```

**Resultado esperado:**

```text
Musica nao encontrada.
```

### Teste 9 — Busca por artista

É realizada uma busca pelo nome de um artista presente na playlist.

Exemplo:

```text
Artista: Artista A
```

**Resultado esperado:** todas as músicas desse artista devem ser exibidas.

### Teste 10 — Remoção da primeira música

A primeira música da playlist é removida pelo ID.

**Resultado esperado:** o ponteiro `primeiro` passa a apontar para o segundo nó.

```text
Antes:

[Música 1] → [Música 2] → [Música 3] → NULL


Depois:

[Música 2] → [Música 3] → NULL
```

### Teste 11 — Remoção de música intermediária

Uma música que está no meio da lista é removida.

**Resultado esperado:** o nó anterior passa a apontar para o nó seguinte.

```text
Antes:

[Música 1] → [Música 2] → [Música 3] → NULL


Depois:

[Música 1] → [Música 3] → NULL
```

### Teste 12 — Remoção da última música

A última música da playlist é removida.

**Resultado esperado:** o nó anterior passa a apontar para `NULL`.

```text
Antes:

[Música 1] → [Música 2] → [Música 3] → NULL


Depois:

[Música 1] → [Música 2] → NULL
```

### Teste 13 — Remoção da única música

É criada uma playlist contendo apenas uma música e essa música é removida.

**Resultado esperado:**

```text
primeiro = NULL
quantidade = 0
```

A playlist deve voltar a ficar vazia.

### Teste 14 — Tentativa de remoção de música inexistente

É realizada uma tentativa de remoção utilizando um ID que não está na playlist.

Exemplo:

```text
ID: 99
```

**Resultado esperado:** nenhuma música deve ser removida e a quantidade de elementos deve permanecer a mesma.

### Teste 15 — Cálculo da quantidade de músicas

A quantidade de músicas armazenadas é consultada.

Exemplo:

```text
Quantidade de musicas: 3
```

**Resultado esperado:** o valor informado deve corresponder ao número de nós existentes na lista.

### Teste 16 — Cálculo da duração total

A duração de todas as músicas é somada.

Exemplo:

```text
Musica 1: 200 segundos
Musica 2: 180 segundos
Musica 3: 240 segundos
```

**Resultado esperado:**

```text
Duracao total: 620 segundos
```

## Tecnologias utilizadas

* Linguagem C
* Structs
* Ponteiros
* Lista encadeada dinâmica
* Alocação dinâmica de memória
* `malloc`
* `free`
* `stdio.h`
* `stdlib.h`
* `string.h`

## Autor

Projeto desenvolvido como atividade acadêmica para a disciplina de Estrutura de Dados do Centro Universitário FEI.
