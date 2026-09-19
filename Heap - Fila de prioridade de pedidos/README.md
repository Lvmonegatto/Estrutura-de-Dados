# Sistema de Gerenciamento de Pedidos

## Sobre o projeto

Este projeto implementa um sistema de **gerenciamento de pedidos** utilizando um **Max-Heap** como estrutura de dados.

Cada pedido possui:

* ID;
* Descrição;
* Prioridade.

A prioridade é representada por um valor inteiro. Quanto maior o valor da prioridade, maior será a prioridade do pedido.

O sistema utiliza um **vetor dinâmico** para armazenar os pedidos e mantém a propriedade do Max-Heap após as operações de inserção e remoção.

A implementação foi desenvolvida em **C**, utilizando `structs`, vetores, ponteiros e alocação dinâmica de memória.

---

## Objetivo

O objetivo do sistema é garantir que o pedido de **maior prioridade esteja sempre na primeira posição do Heap**.

Por exemplo:

```text
ID    Descrição          Prioridade

1     Pedido A              2
2     Pedido B              5
3     Pedido C              3
4     Pedido D              8
5     Pedido E              1
```

Após a organização como Max-Heap:

```text
[8, 5, 3, 2, 1]
```

Representação:

```text
          [8]
         /   \
       [5]   [3]
       / \
     [2] [1]
```

O pedido de prioridade `8` fica na raiz e será o próximo pedido atendido.

---

## Estrutura de dados

O Heap é representado por uma estrutura contendo um vetor de pedidos:

```c
typedef struct {
    Pedido *dados;
    int tamanho;
    int capacidade;
} Heap;
```

A estrutura possui:

* `dados`: vetor que armazena os pedidos;
* `tamanho`: quantidade atual de pedidos;
* `capacidade`: capacidade atual do vetor.

Cada pedido é representado por:

```c
typedef struct {
    int id;
    char descricao[100];
    int prioridade;
} Pedido;
```

---

## Representação do Heap

O Heap é armazenado em um vetor.

Por exemplo:

```text
[8, 5, 3, 2, 1]
```

A representação como árvore é:

```text
              8
            /   \
           5     3
          / \
         2   1
```

Os índices do vetor são utilizados para representar os relacionamentos entre pai e filhos.

Para um elemento localizado no índice `i`:

```text
pai       = (i - 1) / 2
esquerdo  = 2 * i + 1
direito   = 2 * i + 2
```

---

## Propriedade do Max-Heap

Em um Max-Heap, cada elemento pai deve possuir prioridade maior ou igual à prioridade de seus filhos.

Por exemplo:

```text
          8
        /   \
       5     3
      / \
     2   1
```

As prioridades respeitam:

```text
8 > 5
8 > 3
5 > 2
5 > 1
```

Portanto, o elemento de maior prioridade está sempre na raiz.

---

## Operações do Heap

O projeto implementa as operações exigidas:

```text
inicializar_heap
inserir
remover
max_heapfy
construir
print_heap
```

### `inicializar_heap`

Cria um Heap vazio com uma capacidade inicial definida.

```c
Heap* inicializar_heap(int capacidade)
```

Inicialmente:

```text
tamanho = 0
capacidade = valor definido
dados = vetor alocado dinamicamente
```

---

### `inserir`

Adiciona um novo pedido no Heap.

```c
void inserir(Heap *heap, Pedido pedido)
```

O pedido é colocado inicialmente no final do vetor.

Depois, ele é comparado com seu pai e sobe no Heap enquanto possuir uma prioridade maior.

Exemplo:

```text
Antes:

[8, 5, 3, 2]

Inserindo prioridade 10:

[8, 5, 3, 2, 10]
```

O novo elemento é comparado com o pai:

```text
[8, 5, 3, 10, 2]
```

Depois:

```text
[8, 10, 3, 5, 2]
```

E finalmente:

```text
[10, 8, 3, 5, 2]
```

O Max-Heap é restaurado.

---

### `remover`

Remove o pedido de maior prioridade.

```c
Pedido remover(Heap *heap)
```

Como o maior elemento sempre está na raiz, o pedido removido é:

```text
heap->dados[0]
```

Depois, o último elemento do vetor ocupa a posição da raiz e o `max_heapfy` reorganiza o Heap.

Exemplo:

```text
Antes:

[10, 8, 5, 3, 2]
```

Após remover `10`:

```text
[2, 8, 5, 3]
```

Depois do `max_heapfy`:

```text
[8, 3, 5, 2]
```

---

### `max_heapfy`

Reorganiza o Heap a partir de uma determinada posição.

```c
void max_heapfy(Heap *heap, int i)
```

A função compara o elemento com seus filhos e troca com o filho de maior prioridade quando necessário.

Essa operação é utilizada principalmente após a remoção da raiz.

---

### `construir`

Constrói um Max-Heap a partir dos elementos que já estão armazenados no vetor.

```c
void construir(Heap *heap)
```

A função percorre os elementos a partir da metade do vetor e aplica `max_heapfy`.

---

### `print_heap`

Exibe os pedidos armazenados atualmente no Heap.

```c
void print_heap(Heap *heap)
```

Exemplo:

```text
===== PEDIDOS =====
ID: 104 | Descricao: Pedido urgente | Prioridade: 8
ID: 102 | Descricao: Pedido de 5 produtos | Prioridade: 5
ID: 103 | Descricao: Pedido de 20 produtos | Prioridade: 3
ID: 101 | Descricao: Pedido de 10 produtos | Prioridade: 2
===================
```

---

## Crescimento dinâmico

O vetor possui uma capacidade inicial.

Quando a quantidade de pedidos atinge essa capacidade, o vetor é aumentado utilizando `realloc`.

Por exemplo:

```text
Capacidade inicial: 5

Pedidos:
1
2
3
4
5
```

Ao inserir o sexto pedido:

```text
Capacidade: 10
```

Dessa forma, novos pedidos podem continuar sendo cadastrados sem substituir a estrutura de dados por uma estrutura pronta de biblioteca.

---

## Funcionalidades

O sistema permite:

1. Cadastrar pedidos;
2. Informar ID, descrição e prioridade;
3. Exibir os pedidos armazenados;
4. Atender o pedido de maior prioridade;
5. Exibir qual pedido foi atendido;
6. Exibir a quantidade de pedidos aguardando atendimento;
7. Construir um Max-Heap;
8. Continuar cadastrando pedidos após a construção;
9. Atender pedidos até o Heap ficar vazio;
10. Executar testes;
11. Encerrar o programa.

---

## Menu do programa

Ao iniciar o programa:

```text
===== SISTEMA DE PEDIDOS =====
1 - Cadastrar pedido
2 - Atender pedido
3 - Exibir pedidos
4 - Exibir quantidade de pedidos
5 - Construir Heap
6 - Executar testes
0 - Sair

Escolha:
```

---

## Exemplo de cadastro

Selecionando a opção `1`:

```text
Escolha: 1

ID: 101
Descricao: Pedido de 10 produtos
Prioridade: 2

Pedido cadastrado.
```

Outro pedido:

```text
Escolha: 1

ID: 102
Descricao: Pedido de 5 produtos
Prioridade: 5

Pedido cadastrado.
```

Outro pedido:

```text
Escolha: 1

ID: 103
Descricao: Pedido de 20 produtos
Prioridade: 3

Pedido cadastrado.
```

E um pedido urgente:

```text
Escolha: 1

ID: 104
Descricao: Pedido urgente
Prioridade: 8

Pedido cadastrado.
```

---

## Exemplo de visualização

Selecionando a opção `3`:

```text
===== PEDIDOS =====
ID: 104 | Descricao: Pedido urgente | Prioridade: 8
ID: 102 | Descricao: Pedido de 5 produtos | Prioridade: 5
ID: 103 | Descricao: Pedido de 20 produtos | Prioridade: 3
ID: 101 | Descricao: Pedido de 10 produtos | Prioridade: 2
===================
```

O pedido `104`, com prioridade `8`, está na raiz do Heap.

---

## Exemplo de atendimento

Selecionando a opção `2`:

```text
Escolha: 2

Pedido atendido:
ID: 104
Descricao: Pedido urgente
Prioridade: 8
```

O pedido de maior prioridade é sempre atendido primeiro.

Depois da remoção, o Heap é reorganizado automaticamente.

---

## Exemplo de quantidade

Selecionando a opção `4`:

```text
Quantidade de pedidos: 3
```

A quantidade corresponde ao atributo `tamanho` do Heap.

---

## Exemplo de construção do Heap

Pedidos inseridos inicialmente no vetor:

```text
[2, 5, 3, 8, 1]
```

Após utilizar `construir`:

```text
[8, 5, 3, 2, 1]
```

Representação:

```text
          [8]
         /   \
       [5]   [3]
       / \
     [2] [1]
```

O maior elemento passa a ocupar a raiz.

---

# Testes realizados

Foram realizados testes para verificar as operações do Max-Heap e as funcionalidades do sistema.

### Teste 1 — Heap vazio

**Situação:** iniciar o programa sem cadastrar pedidos.

**Resultado esperado:**

```text
===== PEDIDOS =====
===================
```

**Resultado:** aprovado.

---

### Teste 2 — Inserção do primeiro pedido

**Situação:** cadastrar apenas um pedido.

```text
ID: 1
Descricao: Pedido A
Prioridade: 2
```

**Resultado esperado:**

```text
[2]
```

**Resultado:** aprovado.

---

### Teste 3 — Inserção de vários pedidos

**Situação:** cadastrar pedidos com prioridades diferentes.

```text
Prioridades:
2, 5, 3, 8, 1
```

**Resultado esperado:** o pedido de prioridade `8` deve ficar na raiz.

**Resultado:** aprovado.

---

### Teste 4 — Inserção com prioridade maior

**Situação:** inserir um pedido com prioridade maior que a raiz atual.

**Resultado esperado:** o novo pedido deve subir até a posição correta do Max-Heap.

**Resultado:** aprovado.

---

### Teste 5 — Remoção do maior pedido

**Situação:** atender um pedido.

**Resultado esperado:** o pedido de maior prioridade deve ser removido.

Exemplo:

```text
Prioridades:
8, 5, 3, 2, 1
```

Pedido atendido:

```text
Prioridade: 8
```

**Resultado:** aprovado.

---

### Teste 6 — Reorganização após remoção

**Situação:** remover o elemento da raiz.

**Resultado esperado:** o último elemento deve ocupar a raiz e o Heap deve ser reorganizado através do `max_heapfy`.

**Resultado:** aprovado.

---

### Teste 7 — Construção do Heap

**Situação:** inserir vários pedidos e executar `construir`.

**Resultado esperado:** os pedidos devem ser reorganizados mantendo a propriedade de Max-Heap.

**Resultado:** aprovado.

---

### Teste 8 — Inserção após construir

**Situação:** construir o Heap e depois cadastrar um novo pedido.

**Resultado esperado:** o novo pedido deve ser inserido corretamente e o Max-Heap deve continuar válido.

**Resultado:** aprovado.

---

### Teste 9 — Aumento da capacidade

**Situação:** inserir mais pedidos do que a capacidade inicial.

**Resultado esperado:** o vetor deve aumentar sua capacidade utilizando `realloc`.

**Resultado:** aprovado.

---

### Teste 10 — Atendimento até esvaziar

**Situação:** remover todos os pedidos do Heap.

**Resultado esperado:** os pedidos devem ser atendidos em ordem decrescente de prioridade.

Exemplo:

```text
Prioridades:
8 → 5 → 3 → 2 → 1
```

**Resultado:** aprovado.

---

### Teste 11 — Heap vazio após remoções

**Situação:** atender todos os pedidos.

**Resultado esperado:**

```text
Quantidade de pedidos: 0
```

**Resultado:** aprovado.

---

### Teste 12 — Consulta da quantidade

**Situação:** cadastrar quatro pedidos.

**Resultado esperado:**

```text
Quantidade de pedidos: 4
```

**Resultado:** aprovado.

---

## Tecnologias utilizadas

* **Linguagem:** C
* **Estrutura de dados:** Max-Heap
* **Armazenamento:** Vetor dinâmico
* **Alocação de memória:** `malloc`, `realloc` e `free`
* **Compilador:** GCC
* **Controle de versão:** Git / GitHub

---

## Estrutura do projeto

```text
Heap - Fila de prioridade de pedidos/
│
├── main.c
└── README.md
```

---

## Compilação

Para compilar o programa utilizando o GCC:

```bash
cd Fila de prioridade de pedidos
```

```bash
gcc main.c -o fila_prioridade
```

---

## Execução

### Windows

```bash
fila_prioridade.exe
```

### Linux / macOS

```bash
./fila_prioridade
```

---

## Conclusão

O projeto demonstra a utilização de um **Max-Heap armazenado em um vetor dinâmico** para realizar o gerenciamento de pedidos.

A estrutura mantém o pedido de maior prioridade na primeira posição do vetor, permitindo que o atendimento seja realizado sempre pelo pedido mais prioritário.

As operações de inserção e remoção reorganizam explicitamente os elementos do vetor para manter a propriedade do Max-Heap.

O projeto também implementa a construção de um Heap a partir de elementos já armazenados, o crescimento dinâmico do vetor, o atendimento dos pedidos e o controle da quantidade de pedidos aguardando atendimento.
