# Genius

## Sobre o projeto

Este projeto implementa o jogo **Genius** utilizando uma **fila dinâmica** como estrutura de dados.

O jogo apresenta ao jogador uma sequência de cores que deve ser repetida exatamente na mesma ordem. A cada rodada, uma nova cor é adicionada à sequência.

A sequência é armazenada em uma **fila baseada em nós encadeados**, utilizando ponteiros e alocação dinâmica de memória.

A implementação foi desenvolvida em **C**, utilizando `structs`, ponteiros, `malloc` e `free`.

---

## Regras do jogo

O jogo funciona da seguinte forma:

1. Uma nova partida é iniciada.
2. O jogo apresenta uma sequência de cores.
3. O jogador deve repetir a sequência na mesma ordem.
4. Se a sequência estiver correta, uma nova cor é adicionada.
5. Uma nova rodada é iniciada.
6. O processo continua até que o jogador erre.
7. Ao errar, a partida é encerrada e a pontuação final é apresentada.

Exemplo:

```text
VERDE → VERMELHO → AZUL
```

O jogador deverá informar:

```text
VERDE → VERMELHO → AZUL
```

Se a sequência estiver correta, uma nova cor será adicionada para a próxima rodada.

---

## Estrutura de dados

A sequência de cores é armazenada utilizando uma **fila dinâmica baseada em nós encadeados**.

### Nó

Cada nó possui uma cor e uma referência para o próximo nó:

```c
typedef struct No {
    char cor[20];
    struct No *proximo;
} No;
```

Cada nó possui:

* `cor`: cor armazenada;
* `proximo`: ponteiro para o próximo nó da fila.

### Fila

A fila possui referências para o primeiro e o último elemento:

```c
typedef struct {
    No *inicio;
    No *fim;
    int quantidade;
} Fila;
```

A estrutura possui:

* `inicio`: primeiro nó da fila;
* `fim`: último nó da fila;
* `quantidade`: quantidade de cores armazenadas.

A representação da fila é:

```text
inicio
  ↓
[VERDE] → [VERMELHO] → [AZUL] → NULL
                                  ↑
                                 fim
```

---

## Funcionamento da fila

A fila segue o princípio **FIFO (First In, First Out)**.

Isso significa que o primeiro elemento inserido é o primeiro elemento removido.

Por exemplo:

```text
Enfileirar:

VERDE → VERMELHO → AZUL
  ↑                    ↑
inicio                fim
```

Ao realizar um `desenfileirar`, a cor `VERDE` será removida primeiro:

```text
VERMELHO → AZUL
    ↑         ↑
  inicio     fim
```

---

## Operações da fila

As operações utilizadas no projeto são:

### `inicializar_fila`

Cria uma fila vazia.

```c
Fila inicializar_fila()
```

Inicialmente:

```text
inicio = NULL
fim = NULL
quantidade = 0
```

---

### `enfileirar`

Adiciona uma nova cor no final da fila.

```c
void enfileirar(Fila *fila, char cor[])
```

O novo nó passa a ser o último elemento da fila.

---

### `desenfileirar`

Remove a primeira cor da fila.

```c
char* desenfileirar(Fila *fila)
```

A referência `inicio` passa para o próximo nó.

O nó removido é liberado utilizando `free()`.

---

### `frente`

Consulta a primeira cor da fila sem removê-la.

```c
char* frente(Fila *fila)
```

---

### `imprimir`

Percorre a fila e apresenta todas as cores armazenadas.

```c
void imprimir(Fila *fila)
```

---

## Funcionalidades

O jogo possui as seguintes funcionalidades:

1. Iniciar uma nova partida.
2. Visualizar a sequência de cores.
3. Informar a sequência apresentada.
4. Avançar para a próxima rodada quando a sequência estiver correta.
5. Atualizar a pontuação.
6. Informar quando uma sequência estiver incorreta.
7. Informar o encerramento da partida.
8. Reiniciar uma partida.
9. Encerrar o jogo.

---

## Menu do programa

Ao iniciar o programa, o menu é apresentado:

```text
===== GENIUS =====
1 - Mostrar sequencia
2 - Jogar rodada
3 - Mostrar pontuacao
4 - Nova partida
0 - Encerrar

Escolha:
```

### Mostrar sequência

A opção `1` apresenta a sequência atual:

```text
===== SEQUENCIA =====
VERDE VERMELHO AZUL
=====================
```

A sequência deve ser visualizada antes de o jogador tentar reproduzi-la.

---

### Jogar rodada

A opção `2` inicia a reprodução da sequência.

Exemplo:

```text
===== RODADA =====

Sequencia:
VERDE VERMELHO

Informe a sequencia:

Cor 1: VERDE
Cor 2: VERMELHO

Sequencia correta!
Nova cor adicionada.
```

Uma nova cor será adicionada para a próxima rodada.

---

### Pontuação

A opção `3` apresenta a pontuação atual:

```text
Pontuacao: 2
```

A pontuação é atualizada a cada rodada concluída corretamente.

---

### Nova partida

A opção `4` reinicia o jogo.

A sequência anterior é removida e uma nova sequência é criada.

```text
Nova partida iniciada.
```

---

### Encerrar

A opção `0` encerra o programa:

```text
Jogo encerrado.
```

---

## Exemplo de execução

Uma partida pode começar com uma única cor:

```text
===== GENIUS =====

Sequencia:
VERDE
```

O jogador informa:

```text
Cor 1: VERDE

Sequencia correta!
```

Uma nova cor é adicionada:

```text
Sequencia:
VERDE AZUL
```

O jogador precisa repetir toda a sequência:

```text
Cor 1: VERDE
Cor 2: AZUL

Sequencia correta!
```

Na rodada seguinte:

```text
Sequencia:
VERDE AZUL VERMELHO
```

Caso o jogador informe uma sequência diferente:

```text
Cor 1: VERDE
Cor 2: VERMELHO
```

O programa informa:

```text
Sequencia incorreta!

FIM DE JOGO
Pontuacao final: 2
```

---

## Validação da sequência

Durante cada rodada, as cores informadas pelo jogador são comparadas com a sequência armazenada na fila.

A fila é percorrida seguindo a ordem em que as cores foram inseridas.

Por exemplo:

```text
Fila:

VERDE → AZUL → VERMELHO
```

O jogador precisa informar exatamente:

```text
VERDE
AZUL
VERMELHO
```

Caso informe:

```text
VERDE
VERMELHO
AZUL
```

a sequência será considerada incorreta.

---

## Testes realizados

Foram realizados testes para verificar as operações da fila e o funcionamento do jogo.

### Teste 1 — Fila vazia

**Situação:** iniciar uma nova partida.

**Resultado esperado:** a fila deve estar vazia antes da primeira cor ser adicionada.

**Resultado:** aprovado.

---

### Teste 2 — Primeira cor

**Situação:** iniciar a primeira rodada.

**Resultado esperado:** uma cor é adicionada à fila.

Exemplo:

```text
VERDE
```

**Resultado:** aprovado.

---

### Teste 3 — Várias cores

**Situação:** adicionar novas cores durante as rodadas.

**Resultado esperado:** as cores devem permanecer armazenadas na ordem em que foram inseridas.

Exemplo:

```text
VERDE → AZUL → VERMELHO
```

**Resultado:** aprovado.

---

### Teste 4 — Enfileirar

**Situação:** inserir uma nova cor no final da fila.

**Resultado esperado:** a nova cor deve ocupar a posição final.

**Resultado:** aprovado.

---

### Teste 5 — Desenfileirar

**Situação:** remover uma cor da fila.

**Resultado esperado:** a primeira cor inserida deve ser removida primeiro.

**Resultado:** aprovado.

---

### Teste 6 — Consulta da frente

**Situação:** consultar a primeira cor da fila.

**Resultado esperado:** retornar a primeira cor sem removê-la.

**Resultado:** aprovado.

---

### Teste 7 — Impressão da sequência

**Situação:** utilizar a opção de visualizar a sequência.

**Resultado esperado:** todas as cores devem ser apresentadas na ordem correta.

**Resultado:** aprovado.

---

### Teste 8 — Sequência correta

**Situação:** o jogador informa toda a sequência corretamente.

**Resultado esperado:** a rodada é concluída e uma nova cor é adicionada.

**Resultado:** aprovado.

---

### Teste 9 — Sequência incorreta

**Situação:** o jogador informa uma cor diferente da esperada.

**Resultado esperado:** a partida é encerrada e a pontuação final é apresentada.

**Resultado:** aprovado.

---

### Teste 10 — Pontuação

**Situação:** completar duas rodadas corretamente.

**Resultado esperado:**

```text
Pontuacao: 2
```

**Resultado:** aprovado.

---

### Teste 11 — Nova partida

**Situação:** selecionar a opção de nova partida após realizar algumas rodadas.

**Resultado esperado:** a sequência anterior é removida e uma nova partida é iniciada.

**Resultado:** aprovado.

---

### Teste 12 — Encerramento

**Situação:** selecionar a opção `0`.

**Resultado esperado:**

```text
Jogo encerrado.
```

**Resultado:** aprovado.

---

## Tecnologias utilizadas

* **Linguagem:** C
* **Estrutura de dados:** Fila dinâmica
* **Implementação:** Nós encadeados
* **Alocação de memória:** `malloc` e `free`
* **Ponteiros:** utilizados para conectar os nós
* **Compilador:** GCC
* **Controle de versão:** Git / GitHub

---

## Estrutura do projeto

```text
genius/
│
├── main.c
└── README.md
```

---

## Compilação

Para compilar o programa utilizando o GCC:

```bash
gcc main.c -o genius
```

---

## Execução

### Windows

```bash
genius.exe
```

### Linux / macOS

```bash
./genius
```

---

## Conclusão

O projeto demonstra a utilização de uma **fila dinâmica baseada em nós e ponteiros** para armazenar a sequência de cores do jogo Genius.

As operações de `enfileirar` e `desenfileirar` realizam explicitamente as alterações nas referências entre os nós, seguindo o princípio **FIFO (First In, First Out)**.

O projeto também implementa as principais funcionalidades do jogo, incluindo criação da sequência, reprodução pelo jogador, validação das respostas, pontuação, reinício da partida e encerramento do jogo.
