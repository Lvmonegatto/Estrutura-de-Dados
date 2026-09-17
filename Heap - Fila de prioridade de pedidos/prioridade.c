#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char descricao[100];
    int prioridade;
} Pedido;

typedef struct {
    Pedido *dados;
    int tamanho;
    int capacidade;
} Heap;

Heap* inicializar_heap(int capacidade) {
    Heap *heap = malloc(sizeof(Heap));

    heap->dados = malloc(capacidade * sizeof(Pedido));
    heap->tamanho = 0;
    heap->capacidade = capacidade;

    return heap;
}

void trocar(Pedido *a, Pedido *b) {
    Pedido aux = *a;
    *a = *b;
    *b = aux;
}

void max_heapfy(Heap *heap, int i) {
    int maior = i;
    int esquerdo = 2 * i + 1;
    int direito = 2 * i + 2;

    if (esquerdo < heap->tamanho &&
        heap->dados[esquerdo].prioridade > heap->dados[maior].prioridade) {
        maior = esquerdo;
    }

    if (direito < heap->tamanho &&
        heap->dados[direito].prioridade > heap->dados[maior].prioridade) {
        maior = direito;
    }

    if (maior != i) {
        trocar(&heap->dados[i], &heap->dados[maior]);
        max_heapfy(heap, maior);
    }
}

void construir(Heap *heap) {
    for (int i = heap->tamanho / 2 - 1; i >= 0; i--) {
        max_heapfy(heap, i);
    }
}

void inserir(Heap *heap, Pedido pedido) {
    if (heap->tamanho >= heap->capacidade) {
        heap->capacidade *= 2;
        heap->dados = realloc(
            heap->dados,
            heap->capacidade * sizeof(Pedido)
        );
    }

    int i = heap->tamanho;

    heap->dados[i] = pedido;
    heap->tamanho++;

    while (i > 0) {
        int pai = (i - 1) / 2;

        if (heap->dados[pai].prioridade >= heap->dados[i].prioridade)
            break;

        trocar(&heap->dados[pai], &heap->dados[i]);

        i = pai;
    }
}

Pedido remover(Heap *heap) {
    Pedido removido = heap->dados[0];

    heap->dados[0] = heap->dados[heap->tamanho - 1];
    heap->tamanho--;

    if (heap->tamanho > 0)
        max_heapfy(heap, 0);

    return removido;
}

void print_heap(Heap *heap) {
    printf("\n===== PEDIDOS =====\n");

    for (int i = 0; i < heap->tamanho; i++) {
        printf("ID: %d | Descricao: %s | Prioridade: %d\n",
               heap->dados[i].id,
               heap->dados[i].descricao,
               heap->dados[i].prioridade);
    }

    printf("===================\n");
}

Pedido cadastrar_pedido() {
    Pedido pedido;

    printf("ID: ");
    scanf("%d", &pedido.id);

    printf("Descricao: ");
    scanf(" %[^\n]", pedido.descricao);

    printf("Prioridade: ");
    scanf("%d", &pedido.prioridade);

    return pedido;
}

void liberar_heap(Heap *heap) {
    free(heap->dados);
    free(heap);
}

void testes() {
    Heap *heap = inicializar_heap(5);

    Pedido p1 = {1, "Pedido A", 2};
    Pedido p2 = {2, "Pedido B", 5};
    Pedido p3 = {3, "Pedido C", 3};
    Pedido p4 = {4, "Pedido D", 8};
    Pedido p5 = {5, "Pedido E", 1};

    printf("\n===== TESTES =====\n");

    printf("\n1. Heap vazio\n");
    print_heap(heap);

    printf("\n2. Insercao do primeiro pedido\n");
    inserir(heap, p1);
    print_heap(heap);

    printf("\n3. Insercao de varios pedidos\n");
    inserir(heap, p2);
    inserir(heap, p3);
    inserir(heap, p4);
    inserir(heap, p5);
    print_heap(heap);

    printf("\n4. Construir Heap\n");
    construir(heap);
    print_heap(heap);

    printf("\n5. Remover maior prioridade\n");
    Pedido removido = remover(heap);

    printf("Pedido atendido:\n");
    printf("ID: %d | Descricao: %s | Prioridade: %d\n",
           removido.id,
           removido.descricao,
           removido.prioridade);

    print_heap(heap);

    printf("\n6. Insercao apos construir Heap\n");

    Pedido p6 = {6, "Pedido F", 10};

    inserir(heap, p6);
    print_heap(heap);

    printf("\n7. Remover ate esvaziar\n");

    while (heap->tamanho > 0) {
        removido = remover(heap);

        printf("Atendido: ID %d | Prioridade %d\n",
               removido.id,
               removido.prioridade);
    }

    printf("\nQuantidade final: %d\n", heap->tamanho);

    liberar_heap(heap);
}

int main() {
    Heap *heap = inicializar_heap(5);

    int opcao;

    do {
        printf("\n===== SISTEMA DE PEDIDOS =====\n");
        printf("1 - Cadastrar pedido\n");
        printf("2 - Atender pedido\n");
        printf("3 - Exibir pedidos\n");
        printf("4 - Exibir quantidade de pedidos\n");
        printf("5 - Construir Heap\n");
        printf("6 - Executar testes\n");
        printf("0 - Sair\n");

        printf("\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1: {
                Pedido pedido = cadastrar_pedido();
                inserir(heap, pedido);

                printf("Pedido cadastrado.\n");
                break;
            }

            case 2: {
                if (heap->tamanho == 0) {
                    printf("Nao existem pedidos aguardando atendimento.\n");
                }
                else {
                    Pedido pedido = remover(heap);

                    printf("\nPedido atendido:\n");
                    printf("ID: %d\n", pedido.id);
                    printf("Descricao: %s\n", pedido.descricao);
                    printf("Prioridade: %d\n", pedido.prioridade);
                }

                break;
            }

            case 3:
                print_heap(heap);
                break;

            case 4:
                printf("Quantidade de pedidos: %d\n", heap->tamanho);
                break;

            case 5:
                construir(heap);
                printf("Max-Heap construido.\n");
                print_heap(heap);
                break;

            case 6:
                testes();
                break;

            case 0:
                printf("Programa encerrado.\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    liberar_heap(heap);

    return 0;
}