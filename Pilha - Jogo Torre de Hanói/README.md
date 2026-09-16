# Torre de Hanói

## Sobre o projeto

Este projeto implementa o jogo **Torre de Hanói** utilizando **pilhas dinâmicas** como estrutura de dados.

O jogo possui três torres, representadas por pilhas encadeadas. Inicialmente, os quatro discos ficam na primeira torre, organizados do maior para o menor, com o menor disco no topo.

O objetivo é mover todos os discos da primeira torre para a terceira torre, respeitando as regras do jogo.

A implementação foi desenvolvida em **C**, utilizando `structs`, ponteiros, nós encadeados e alocação dinâmica de memória.

---

## Regras do jogo

Durante a partida, devem ser respeitadas as seguintes regras:

* Somente o disco que está no topo de uma torre pode ser movimentado.
* Somente um disco pode ser movimentado por vez.
* Um disco maior não pode ser colocado sobre um disco menor.
* Não é possível retirar um disco de uma torre vazia.

Com quatro discos, a solução mínima para completar o jogo é de:

```text
2⁴ - 1 = 15 movimentos
```

---

## Estrutura de dados

Cada disco é armazenado em um nó da pilha.

### Nó

```c
typedef struct No {
    int disco;
    struct No *proximo;
} No;
```

Cada nó possui:

* `disco`: número que representa o disco;
* `proximo`: ponteiro para o próximo nó da pilha.

### Pilha

```c
typedef struct {
    No *topo;
    int quantidade;
} Pilha;
```

Cada pilha possui:

* `topo`: referência para o nó que está no topo;
* `quantidade`: quantidade de discos armazenados.

As três torres são representadas por três pilhas:

```text
Torre A        Torre B        Torre C

  topo           topo           topo
   ↓              ↓              ↓
  [1]            NULL           NULL
  [2]
  [3]
  [4]
```

---

## Operações da pilha

As principais operações utilizadas no projeto são:

### `inicializar_pilha`

Cria uma pilha vazia.

```c
Pilha inicializar_pilha()
```

Inicialmente:

```text
topo = NULL
quantidade = 0
```

### `empilhar`

Adiciona um disco no topo da pilha.

```c
void empilhar(Pilha *pilha, int disco)
```

O novo nó passa a ser o topo da pilha.

### `desempilhar`

Remove o disco que está no topo da pilha.

```c
int desempilhar(Pilha *pilha)
```

O nó removido é liberado utilizando `free()`.

### `topo`

Consulta o disco que está no topo da pilha.

```c
int topo(Pilha *pilha)
```

### `imprimir`

Percorre a pilha e mostra os discos armazenados.

```c
void imprimir(Pilha *pilha)
```

---

## Funcionalidades

O jogo possui as seguintes funcionalidades:

1. Mostrar o estado atual das três torres.
2. Escolher uma torre de origem.
3. Escolher uma torre de destino.
4. Realizar movimentos entre as torres.
5. Impedir movimentos inválidos.
6. Exibir a quantidade de movimentos realizados.
7. Iniciar uma nova partida.
8. Detectar a vitória do jogador.
9. Encerrar o jogo.

---

## Menu do programa

Ao iniciar o programa, o seguinte menu é apresentado:

```text
===== TORRE DE HANOI =====
1 - Mostrar torres
2 - Fazer movimento
3 - Quantidade de movimentos
4 - Nova partida
0 - Encerrar

Escolha:
```

### Mostrar torres

A opção `1` mostra o estado atual das três torres.

Exemplo:

```text
===== TORRES =====
Torre A: 1 2 3 4
Torre B:
Torre C:
==================
```

### Fazer movimento

A opção `2` permite escolher a torre de origem e a torre de destino.

Exemplo:

```text
Torre de origem (A/B/C): A
Torre de destino (A/B/C): B

Movimento realizado.
```

### Consultar movimentos

A opção `3` mostra a quantidade de movimentos realizados:

```text
Movimentos realizados: 5
```

### Nova partida

A opção `4` reinicia o jogo, colocando novamente os quatro discos na Torre A.

```text
Nova partida iniciada.
```

### Encerrar

A opção `0` encerra o programa:

```text
Jogo encerrado.
```

---

## Exemplo de execução

Uma nova partida começa com todos os discos na Torre A:

```text
===== TORRES =====
Torre A: 1 2 3 4
Torre B:
Torre C:
==================
```

O jogador pode realizar um movimento:

```text
Torre de origem (A/B/C): A
Torre de destino (A/B/C): C

Movimento realizado.
```

Estado das torres:

```text
Torre A: 2 3 4
Torre B:
Torre C: 1
```

Caso o jogador tente fazer um movimento inválido:

```text
Torre de origem (A/B/C): A
Torre de destino (A/B/C): C

Movimento invalido: um disco maior nao pode ficar sobre um menor.
```

Nesse caso, o movimento não é realizado e a quantidade de movimentos não é incrementada.

Ao completar o jogo:

```text
PARABENS! Voce venceu!
Quantidade de movimentos: 15
```

---

## Compilação

Para compilar o programa utilizando o GCC:

```bash
gcc main.c -o hanoi
```

---

## Execução

### Windows

```bash
hanoi.exe
```

### Linux / macOS

```bash
./hanoi
```

---

## Testes realizados

Foram realizados testes para verificar o funcionamento das operações da pilha e das regras do jogo.

### Teste 1 — Nova partida

**Situação:** iniciar o programa.

**Resultado esperado:**

```text
Torre A: 1 2 3 4
Torre B:
Torre C:
```

**Resultado:** aprovado.

---

### Teste 2 — Visualização das torres

**Situação:** utilizar a opção de visualizar as torres.

**Resultado esperado:** as três torres são exibidas corretamente.

**Resultado:** aprovado.

---

### Teste 3 — Movimento válido

**Situação:** mover o disco 1 da Torre A para a Torre B.

**Resultado esperado:**

```text
Torre A: 2 3 4
Torre B: 1
```

**Resultado:** aprovado.

---

### Teste 4 — Retirar disco de torre vazia

**Situação:** tentar mover um disco da Torre B quando ela está vazia.

**Resultado esperado:**

```text
Movimento invalido: a torre de origem esta vazia.
```

**Resultado:** aprovado.

---

### Teste 5 — Disco maior sobre disco menor

**Situação:** colocar um disco maior sobre um disco menor.

**Resultado esperado:**

```text
Movimento invalido: um disco maior nao pode ficar sobre um menor.
```

**Resultado:** aprovado.

---

### Teste 6 — Movimentos entre as torres

**Situação:** realizar diversos movimentos válidos.

**Resultado esperado:** os discos devem ser transferidos corretamente entre as três torres.

**Resultado:** aprovado.

---

### Teste 7 — Contagem de movimentos

**Situação:** realizar cinco movimentos válidos.

**Resultado esperado:**

```text
Movimentos realizados: 5
```

**Resultado:** aprovado.

---

### Teste 8 — Nova partida

**Situação:** realizar alguns movimentos e selecionar a opção de nova partida.

**Resultado esperado:** os quatro discos retornam para a Torre A e a contagem de movimentos é zerada.

**Resultado:** aprovado.

---

### Teste 9 — Vitória

**Situação:** transferir os quatro discos para a Torre C.

**Resultado esperado:**

```text
PARABENS! Voce venceu!
Quantidade de movimentos: 15
```

**Resultado:** aprovado.

---

### Teste 10 — Encerramento

**Situação:** selecionar a opção `0`.

**Resultado esperado:**

```text
Jogo encerrado.
```

**Resultado:** aprovado.

---

## Tecnologias utilizadas

* **Linguagem:** C
* **Estrutura de dados:** Pilha dinâmica
* **Implementação:** Nós encadeados
* **Alocação de memória:** `malloc` e `free`
* **Compilador:** GCC
* **Controle de versão:** Git / GitHub

---

## Estrutura do projeto

```text
torre-de-hanoi/
│
├── main.c
└── README.md
```

---

## Conclusão

O projeto demonstra a utilização de uma **pilha dinâmica baseada em nós e ponteiros** para implementar as três torres do jogo Torre de Hanói.

As operações de `empilhar` e `desempilhar` alteram diretamente as referências entre os nós, seguindo o princípio **LIFO (Last In, First Out)**.

Além da implementação da estrutura de dados, o projeto também apresenta as regras do jogo, validação dos movimentos, contagem de movimentos, reinício da partida e identificação da vitória.
