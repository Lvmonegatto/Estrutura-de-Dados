# Tabela Hash com Encadeamento Externo

## Sobre o projeto

Este projeto implementa uma **Tabela Hash** utilizando **encadeamento externo** para tratar colisões.

A função hash utilizada é:

```text
h(k) = k mod 7
```

A tabela possui **7 posições**, numeradas de `0` até `6`.

Os valores utilizados no exercício são:

```text
{190, 322, 172, 89, 13, 4, 769, 61, 15, 76}
```

A implementação foi desenvolvida em **C**, utilizando `structs`, ponteiros, listas encadeadas e alocação dinâmica de memória.

---

## Objetivo

O objetivo do projeto é compreender:

* o funcionamento de uma função hash;
* o cálculo do índice de armazenamento;
* o tratamento de colisões;
* o encadeamento externo;
* a inserção de elementos;
* a remoção de elementos;
* o fator de carga da tabela.

---

## Função Hash

A função utilizada é:

```text
h(k) = k mod 7
```

O resultado da função determina em qual posição da tabela o elemento será armazenado.

Por exemplo:

```text
190 mod 7 = 1
```

Portanto:

```text
190 → posição 1
```

---

## Cálculo da função Hash

Os valores fornecidos foram calculados da seguinte forma:

| Valor |       Cálculo | Posição |
| ----: | ------------: | ------: |
|   190 | 190 mod 7 = 1 |       1 |
|   322 | 322 mod 7 = 0 |       0 |
|   172 | 172 mod 7 = 4 |       4 |
|    89 |  89 mod 7 = 5 |       5 |
|    13 |  13 mod 7 = 6 |       6 |
|     4 |   4 mod 7 = 4 |       4 |
|   769 | 769 mod 7 = 6 |       6 |
|    61 |  61 mod 7 = 5 |       5 |
|    15 |  15 mod 7 = 1 |       1 |
|    76 |  76 mod 7 = 6 |       6 |

Portanto:

```text
190 → 1
322 → 0
172 → 4
89  → 5
13  → 6
4   → 4
769 → 6
61  → 5
15  → 1
76  → 6
```

---

## Estrutura de dados

A tabela utiliza três estruturas principais.

### Nó

Cada elemento da lista encadeada é representado por um nó:

```c
typedef struct No {
    int valor;
    struct No *proximo;
} No;
```

Cada nó possui:

* `valor`: valor armazenado;
* `proximo`: ponteiro para o próximo nó.

### Lista

Cada posição da tabela possui uma lista:

```c
typedef struct {
    No *inicio;
} Lista;
```

O atributo `inicio` aponta para o primeiro nó da lista.

### Hash

A tabela Hash é representada por:

```c
typedef struct {
    Lista *tabela[TAM];
} Hash;
```

Como `TAM` é igual a `7`, a tabela possui sete posições:

```text
0
1
2
3
4
5
6
```

---

## Encadeamento externo

Quando dois ou mais valores possuem o mesmo resultado na função hash, ocorre uma colisão.

Neste projeto, as colisões são tratadas através de **listas encadeadas**.

Por exemplo:

```text
172 mod 7 = 4
4 mod 7 = 4
```

Os dois valores pertencem à posição `4`:

```text
4 → [172] → [4] → NULL
```

Outro exemplo:

```text
13 mod 7 = 6
769 mod 7 = 6
76 mod 7 = 6
```

Então:

```text
6 → [13] → [769] → [76] → NULL
```

---

## Tabela Hash resultante

Como a função hash é `k mod 7`, os valores ficam distribuídos da seguinte forma:

```text
0 → 322

1 → 190 → 15

2 → NULL

3 → NULL

4 → 172 → 4

5 → 89 → 61

6 → 13 → 769 → 76
```

Como a implementação realiza a inserção **no início da lista**, a ordem em que os elementos aparecem no programa é invertida dentro de cada cadeia:

```text
0 → 322

1 → 15 → 190

2 → NULL

3 → NULL

4 → 4 → 172

5 → 61 → 89

6 → 76 → 769 → 13
```

Essa diferença ocorre porque cada novo elemento é colocado no início da lista.

---

## Operações

O programa implementa as principais operações da tabela:

```text
inicializar_hash
inserir
remover
imprimir
liberar
```

### `inicializar_hash`

Cria a tabela Hash e inicializa suas sete posições.

```c
Hash* inicializar_hash()
```

Cada posição começa com uma lista vazia:

```text
0 → NULL
1 → NULL
2 → NULL
3 → NULL
4 → NULL
5 → NULL
6 → NULL
```

---

### `inserir`

Insere um novo valor na tabela.

```c
void inserir(Hash *hash, int valor)
```

Primeiro é calculado o índice:

```c
int indice = valor % TAM;
```

Depois é criado um novo nó e inserido no início da lista correspondente.

Por exemplo, para inserir `15`:

```text
15 mod 7 = 1
```

O elemento será inserido na posição `1`.

---

### `remover`

Remove um valor da tabela.

```c
void remover(Hash *hash, int valor)
```

Primeiro é calculada a posição do valor.

Depois a lista daquela posição é percorrida até encontrar o elemento.

A remoção pode ocorrer:

* no início da lista;
* no meio da lista;
* no final da lista.

Após a remoção, o nó é liberado utilizando `free()`.

---

### `imprimir`

Exibe todas as posições da tabela:

```c
void imprimir(Hash *hash)
```

Exemplo:

```text
0 -> 322
1 -> 15 190
2 ->
3 ->
4 -> 4 172
5 -> 61 89
6 -> 76 769 13
```

---

### `liberar`

Libera os nós das listas e a memória utilizada pela tabela:

```c
void liberar(Hash *hash)
```

Essa função percorre todas as listas e libera os nós utilizando `free()`.

---

# Simulação

## Inserção

Os valores são inseridos na seguinte ordem:

```text
190
322
172
89
13
4
769
61
15
76
```

Após todas as inserções:

```text
0 → 322

1 → 15 → 190

2 → NULL

3 → NULL

4 → 4 → 172

5 → 61 → 89

6 → 76 → 769 → 13
```

---

## Remoção

No programa, o valor escolhido para remoção é:

```text
15
```

Primeiro calculamos sua posição:

```text
15 mod 7 = 1
```

Portanto, o programa procura o valor `15` na posição `1`.

Antes da remoção:

```text
1 → 15 → 190
```

Depois da remoção:

```text
1 → 190
```

A tabela passa a ser:

```text
0 → 322

1 → 190

2 → NULL

3 → NULL

4 → 4 → 172

5 → 61 → 89

6 → 76 → 769 → 13
```

---

# Fator de carga

O fator de carga é calculado através da fórmula:

$$
\alpha = \frac{n}{m}
$$

Onde:

* `n` = número de elementos armazenados;
* `m` = número de posições da tabela.

Neste exercício:

```text
n = 10
m = 7
```

Portanto:

$$
\alpha = \frac{10}{7}
$$

$$
\alpha \approx 1,43
$$

Assim, o **fator de carga inicial é aproximadamente 1,43**.

Mesmo sendo maior que `1`, isso é possível porque a tabela utiliza **encadeamento externo**, permitindo que uma mesma posição possua vários elementos.

### Após a remoção

Como o programa remove o valor `15`, passam a existir 9 elementos:

$$
\alpha = \frac{9}{7}
$$

$$
\alpha \approx 1,29
$$

Portanto, após a remoção de `15`, o fator de carga passa a ser aproximadamente:

```text
1,29
```

---

# Exemplo de execução

Ao executar o programa:

```text
Tabela inicial:
0 -> 322
1 -> 15 190
2 ->
3 ->
4 -> 4 172
5 -> 61 89
6 -> 76 769 13

Removendo 15:
0 -> 322
1 -> 190
2 ->
3 ->
4 -> 4 172
5 -> 61 89
6 -> 76 769 13
```

---

# Testes realizados

### Teste 1 — Inicialização da tabela

**Situação:** criar uma nova tabela Hash.

**Resultado esperado:** todas as posições devem iniciar vazias.

```text
0 → NULL
1 → NULL
2 → NULL
3 → NULL
4 → NULL
5 → NULL
6 → NULL
```

**Resultado:** aprovado.

---

### Teste 2 — Inserção de 190

**Situação:**

```text
190 mod 7 = 1
```

**Resultado esperado:**

```text
1 → 190
```

**Resultado:** aprovado.

---

### Teste 3 — Inserção de 322

**Situação:**

```text
322 mod 7 = 0
```

**Resultado esperado:**

```text
0 → 322
```

**Resultado:** aprovado.

---

### Teste 4 — Colisão na posição 4

**Situação:** inserir `172` e `4`.

```text
172 mod 7 = 4
4 mod 7 = 4
```

**Resultado esperado:**

```text
4 → 4 → 172
```

**Resultado:** aprovado.

---

### Teste 5 — Colisão na posição 5

**Situação:** inserir `89` e `61`.

```text
89 mod 7 = 5
61 mod 7 = 5
```

**Resultado esperado:**

```text
5 → 61 → 89
```

**Resultado:** aprovado.

---

### Teste 6 — Três elementos na mesma posição

**Situação:** inserir `13`, `769` e `76`.

```text
13 mod 7 = 6
769 mod 7 = 6
76 mod 7 = 6
```

**Resultado esperado:**

```text
6 → 76 → 769 → 13
```

**Resultado:** aprovado.

---

### Teste 7 — Remoção de 15

**Situação:** remover o valor `15`.

**Resultado esperado:**

Antes:

```text
1 → 15 → 190
```

Depois:

```text
1 → 190
```

**Resultado:** aprovado.

---

### Teste 8 — Fator de carga

**Situação:** analisar os 10 valores inseridos em uma tabela com 7 posições.

**Cálculo:**

```text
α = 10 / 7
α ≈ 1,43
```

**Resultado:** fator de carga calculado corretamente.

---

## Tecnologias utilizadas

* **Linguagem:** C
* **Estrutura de dados:** Tabela Hash
* **Tratamento de colisões:** Encadeamento externo
* **Estrutura utilizada:** Lista encadeada
* **Alocação de memória:** `malloc` e `free`
* **Compilador:** GCC
* **Controle de versão:** Git / GitHub

---

## Estrutura do projeto

```text
Tabela-hash/
│
├── hash.c
└── README.md
```

---

## Compilação

Para compilar o programa utilizando o GCC:

```bash
cd Tabela Hash
```

```bash
gcc hash.c -o hash
```

---

## Execução

### Windows

```bash
tabela_hash.exe
```

### Linux / macOS

```bash
./tabela_hash
```

---

## Conclusão

O projeto demonstra a implementação de uma **Tabela Hash com função `h(k) = k mod 7` e tratamento de colisões por encadeamento externo**.

Os valores são distribuídos entre as sete posições da tabela de acordo com o resultado da função hash. Quando ocorre uma colisão, os valores são armazenados em uma lista encadeada na mesma posição.

Também foram implementadas as operações de inserção, remoção, impressão e liberação da tabela, permitindo observar na prática o funcionamento das colisões e do encadeamento.

Para o conjunto de 10 valores inicialmente inseridos, o fator de carga é aproximadamente **1,43**. Após a remoção do valor `15`, o fator de carga passa a ser aproximadamente **1,29**.
