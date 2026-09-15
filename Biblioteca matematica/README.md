# Vetores e Similaridade de Cosseno

Programa desenvolvido em C para armazenar e manipular vetores de números reais utilizando arrays como estrutura de dados.

O programa implementa as operações básicas da estrutura de dados solicitadas na atividade e também operações matemáticas entre vetores, incluindo o cálculo da similaridade de cosseno.

## Funcionalidades

### Operações da estrutura de dados

O programa implementa as seguintes operações:

* `inicializar_array` — cria e inicializa um vetor;
* `inserir` — insere um valor no vetor;
* `imprimir` — exibe os valores armazenados;
* `buscar` — procura um valor no vetor e retorna seu índice;
* `remover` — remove um elemento do vetor.

### Operações matemáticas

O programa também permite:

1. Criar dois ou mais vetores;
2. Informar os valores reais de cada vetor;
3. Exibir os vetores armazenados;
4. Multiplicar um vetor por um valor escalar;
5. Calcular a soma de dois vetores;
6. Calcular o produto escalar entre dois vetores;
7. Calcular a norma euclidiana de um vetor;
8. Calcular a similaridade de cosseno entre dois vetores;
9. Encontrar, em um conjunto de vetores, aquele que possui maior similaridade com um vetor de consulta.

## Estrutura utilizada

Os vetores são representados por uma estrutura contendo:

```c
typedef struct {
    float *dados;
    int tamanho;
    int capacidade;
} Vetor;
```

Os valores são armazenados em um array de números reais (`float`).

As operações matemáticas percorrem diretamente os elementos armazenados no array utilizando seus índices.

## Compilação

O programa utiliza a linguagem C e a biblioteca matemática `math.h`.

### GCC

Para compilar utilizando o GCC:

```bash
gcc main.c -o vetores -lm
```

O parâmetro `-lm` é utilizado para realizar a ligação com a biblioteca matemática, necessária para o cálculo da raiz quadrada utilizado na norma dos vetores.

### Execução

No Linux ou macOS:

```bash
./vetores
```

No Windows:

```bash
vetores.exe
```

## Exemplo de execução

Ao iniciar o programa, o usuário encontrará o seguinte menu:

```text
===== MENU =====
1 - Criar vetores
2 - Exibir vetores
3 - Multiplicar vetor por escalar
4 - Somar dois vetores
5 - Produto escalar
6 - Norma de um vetor
7 - Similaridade de cosseno
8 - Maior similaridade
9 - Buscar valor
10 - Remover valor
11 - Executar testes
0 - Sair
```

### Criando vetores

Exemplo utilizando dois vetores de tamanho 3:

```text
Tamanho dos vetores: 3
Quantidade de vetores: 2

Vetor 0:
Valor 0: 1
Valor 1: 2
Valor 2: 3

Vetor 1:
Valor 0: 4
Valor 1: 5
Valor 2: 6
```

Os vetores armazenados serão:

```text
Vetor 0: [1.00, 2.00, 3.00]
Vetor 1: [4.00, 5.00, 6.00]
```

### Multiplicação por escalar

Para o vetor:

```text
[1.00, 2.00, 3.00]
```

utilizando o escalar `2`:

```text
Resultado: [2.00, 4.00, 6.00]
```

### Soma de vetores

Considerando:

```text
A = [1.00, 2.00, 3.00]
B = [4.00, 5.00, 6.00]
```

o resultado é:

```text
Resultado: [5.00, 7.00, 9.00]
```

### Produto escalar

Para:

```text
A = [1.00, 2.00, 3.00]
B = [4.00, 5.00, 6.00]
```

o cálculo realizado é:

```text
(1 × 4) + (2 × 5) + (3 × 6) = 32
```

Resultado:

```text
Produto escalar: 32.0000
```

### Norma

Para o vetor:

```text
A = [1.00, 2.00, 3.00]
```

a norma é:

```text
√(1² + 2² + 3²) = 3.7417
```

Resultado:

```text
Norma: 3.7417
```

### Similaridade de cosseno

Para dois vetores de mesma dimensão, o programa calcula:

```text
similaridade = produto_escalar / (norma_A × norma_B)
```

O resultado é apresentado com quatro casas decimais.

Caso um dos vetores seja nulo, a operação é considerada inválida.

### Maior similaridade

O usuário pode informar um vetor de consulta.

O programa calcula a similaridade entre o vetor de consulta e cada vetor armazenado e identifica aquele que possui o maior valor de similaridade.

Exemplo:

```text
Vetor de Consulta:
[1.00, 0.00, 0.00]

Vetor 0:
[0.50, 0.50, 0.00]

Vetor 1:
[0.90, 0.10, 0.10]

Vetor 2:
[0.00, 1.00, 0.00]
```

O programa compara todos os vetores e informa:

```text
Vetor mais similar: 1
Vetor: [0.90, 0.10, 0.10]
```

## Testes realizados

O programa possui uma opção de testes que permite verificar as principais funcionalidades implementadas.

Para executar os testes, basta selecionar:

```text
11 - Executar testes
```

### Teste 1 — Inicialização e inserção

São criados vetores e valores são inseridos utilizando a operação `inserir`.

Exemplo:

```text
Vetor A: [1.00, 2.00, 3.00]
Vetor B: [4.00, 5.00, 6.00]
```

**Resultado esperado:** os valores devem ser armazenados e exibidos corretamente.

### Teste 2 — Impressão

Os vetores armazenados são exibidos utilizando a função `imprimir`.

**Resultado esperado:**

```text
Vetor A: [1.00, 2.00, 3.00]
Vetor B: [4.00, 5.00, 6.00]
```

### Teste 3 — Busca

É realizada uma busca pelo valor `2` no vetor:

```text
[1.00, 2.00, 3.00]
```

**Resultado esperado:**

```text
Busca pelo valor 2: indice 1
```

### Teste 4 — Remoção

É removido o elemento do índice `1`:

```text
Antes:
[1.00, 2.00, 3.00]

Depois:
[1.00, 3.00]
```

**Resultado esperado:** o elemento é removido e os elementos seguintes são deslocados uma posição para a esquerda.

### Teste 5 — Multiplicação por escalar

Entrada:

```text
A = [1.00, 2.00, 3.00]
k = 2
```

**Resultado esperado:**

```text
[2.00, 4.00, 6.00]
```

### Teste 6 — Soma de vetores

Entrada:

```text
A = [1.00, 2.00, 3.00]
B = [4.00, 5.00, 6.00]
```

**Resultado esperado:**

```text
[5.00, 7.00, 9.00]
```

Também é testada a situação em que os vetores possuem dimensões diferentes.

**Resultado esperado:**

```text
Os vetores possuem tamanhos diferentes.
```

### Teste 7 — Produto escalar

Entrada:

```text
A = [1.00, 2.00, 3.00]
B = [4.00, 5.00, 6.00]
```

**Resultado esperado:**

```text
Produto escalar: 32.0000
```

### Teste 8 — Norma do vetor

Entrada:

```text
A = [1.00, 2.00, 3.00]
```

**Resultado esperado:**

```text
Norma: 3.7417
```

### Teste 9 — Similaridade de cosseno

São utilizados dois vetores de mesma dimensão e não nulos.

**Resultado esperado:** o programa deve calcular e apresentar a similaridade com pelo menos quatro casas decimais.

### Teste 10 — Vetor nulo

É testada a similaridade entre um vetor não nulo e:

```text
[0.00, 0.00, 0.00]
```

**Resultado esperado:**

```text
Operacao invalida.
```

A similaridade não deve ser calculada quando um dos vetores possui norma igual a zero.

### Teste 11 — Maior similaridade

É criado um conjunto de vetores e um vetor de consulta.

O programa calcula a similaridade entre a consulta e cada vetor e retorna o vetor com maior similaridade.

**Resultado esperado:** o índice do vetor com maior similaridade deve ser apresentado junto com seus valores.

## Tecnologias utilizadas

* Linguagem C
* Arrays
* Structs
* Ponteiros
* Alocação dinâmica de memória
* Biblioteca padrão `stdio.h`
* Biblioteca `stdlib.h`
* Biblioteca matemática `math.h`

## Autor

Projeto desenvolvido como atividade acadêmica para a disciplina de Estrutura de Dados do Centro Universitário FEI.
