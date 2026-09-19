#include <stdio.h>
#include <stdlib.h>

#define TAM 7

typedef struct No {
    int valor;
    struct No *proximo;
} No;

typedef struct {
    No *inicio;
} Lista;

typedef struct {
    Lista *tabela[TAM];
} Hash;

Hash* inicializar_hash() {
    Hash *hash = malloc(sizeof(Hash));

    for (int i = 0; i < TAM; i++) {
        hash->tabela[i] = malloc(sizeof(Lista));
        hash->tabela[i]->inicio = NULL;
    }

    return hash;
}

void inserir(Hash *hash, int valor) {
    int indice = valor % TAM;

    No *novo = malloc(sizeof(No));

    novo->valor = valor;
    novo->proximo = hash->tabela[indice]->inicio;

    hash->tabela[indice]->inicio = novo;
}

void remover(Hash *hash, int valor) {
    int indice = valor % TAM;

    No *atual = hash->tabela[indice]->inicio;
    No *anterior = NULL;

    while (atual != NULL && atual->valor != valor) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL)
        return;

    if (anterior == NULL)
        hash->tabela[indice]->inicio = atual->proximo;
    else
        anterior->proximo = atual->proximo;

    free(atual);
}

void imprimir(Hash *hash) {
    for (int i = 0; i < TAM; i++) {
        printf("%d -> ", i);

        No *atual = hash->tabela[i]->inicio;

        while (atual != NULL) {
            printf("%d ", atual->valor);
            atual = atual->proximo;
        }

        printf("\n");
    }
}

void liberar(Hash *hash) {
    for (int i = 0; i < TAM; i++) {
        No *atual = hash->tabela[i]->inicio;

        while (atual != NULL) {
            No *aux = atual;
            atual = atual->proximo;
            free(aux);
        }

        free(hash->tabela[i]);
    }

    free(hash);
}

int main() {
    Hash *hash = inicializar_hash();

    int valores[] = {
        190, 322, 172, 89, 13,
        4, 769, 61, 15, 76
    };

    int tamanho = sizeof(valores) / sizeof(int);

    for (int i = 0; i < tamanho; i++)
        inserir(hash, valores[i]);

    printf("Tabela inicial:\n");
    imprimir(hash);

    printf("\nRemovendo 15:\n");
    remover(hash, 15);

    imprimir(hash);

    liberar(hash);

    return 0;
}
//Respondendo as perguntas depois do andamento do código
// 1. Calcule h(k) para cada valor
//Cálculo 
// 190 mod 7 = 1, ou seja h(k) = 1 
// 322 mod 7 = 0 ou seja h(k) = 0
// 172 mod 7 = 4 ou seja h(k) = 4
// 89 mod 7 = 5  ou seja h(k) = 5
// 13 mod 7 = 6 , ou seja h(k) = 6 
// 4 mod 7 = 4 , ou seja h(k) = 4  
// 769 mod 7 = 6 , ou seja h(k) = 6 
// 61 mod 7 = 5 , ou seja h(k) = 5 
// 15 mod 7 = 1 , ou seja h(k) = 1  
// 76 mod 7 = 6 , ou seja h(k) = 6  

// 2. Desenhe a tabela hash resultante
//Tabela inicial com as colisõesÇ
// 0 -> 322 
// 1 -> 15 190 
// 2 -> 
// 3 -> 
// 4 -> 4 172 
// 5 -> 61 89 
// 6 -> 76 769 13 

//Tabela hash com os valores encadeados
// Índice 0 → 322 → NULL

// Índice 1 → 190 → 15 → NULL

// Índice 2 → NULL

// Índice 3 → NULL

// Índice 4 → 172 → 4 → NULL

// Índice 5 → 89 → 61 → NULL

// Índice 6 → 13 → 769 → 76 → NULL

// 3. Simule inserção e remoção
//Teste feito no main, inserção e remoção de valores

// 4. Analise o fator de carga final
// Como o fator de carga final é calculado por α = n/m, n sendo o numero de elementos que foram armazenados
// e m sendo o numero de posições totais da tabela, a conta ficaria α = 10/7 , o que da aproximadamente 1,43.