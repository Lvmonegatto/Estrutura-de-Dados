#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int disco;
    struct No *proximo;
} No;

typedef struct {
    No *topo;
    int quantidade;
} Pilha;

Pilha inicializar_pilha() {
    Pilha pilha;
    pilha.topo = NULL;
    pilha.quantidade = 0;
    return pilha;
}

void empilhar(Pilha *pilha, int disco) {
    No *novo = malloc(sizeof(No));

    novo->disco = disco;
    novo->proximo = pilha->topo;
    pilha->topo = novo;
    pilha->quantidade++;
}

int desempilhar(Pilha *pilha) {
    No *aux = pilha->topo;
    int disco = aux->disco;

    pilha->topo = aux->proximo;
    free(aux);
    pilha->quantidade--;

    return disco;
}

int topo(Pilha *pilha) {
    return pilha->topo->disco;
}

void imprimir(Pilha *pilha) {
    No *atual = pilha->topo;

    while (atual != NULL) {
        printf("%d ", atual->disco);
        atual = atual->proximo;
    }

    printf("\n");
}

void mostrar_torres(Pilha *A, Pilha *B, Pilha *C) {
    printf("\n===== TORRES =====\n");

    printf("Torre A: ");
    imprimir(A);

    printf("Torre B: ");
    imprimir(B);

    printf("Torre C: ");
    imprimir(C);

    printf("==================\n");
}

Pilha* escolher_torre(Pilha *A, Pilha *B, Pilha *C, char torre) {
    if (torre == 'A')
        return A;

    if (torre == 'B')
        return B;

    if (torre == 'C')
        return C;

    return NULL;
}

int mover(Pilha *origem, Pilha *destino) {
    if (origem->topo == NULL) {
        printf("Movimento invalido: a torre de origem esta vazia.\n");
        return 0;
    }

    if (destino->topo != NULL && topo(origem) > topo(destino)) {
        printf("Movimento invalido: um disco maior nao pode ficar sobre um menor.\n");
        return 0;
    }

    int disco = desempilhar(origem);
    empilhar(destino, disco);

    return 1;
}

void liberar_pilha(Pilha *pilha) {
    while (pilha->topo != NULL)
        desempilhar(pilha);
}

void nova_partida(Pilha *A, Pilha *B, Pilha *C) {
    liberar_pilha(A);
    liberar_pilha(B);
    liberar_pilha(C);

    *A = inicializar_pilha();
    *B = inicializar_pilha();
    *C = inicializar_pilha();

    for (int i = 4; i >= 1; i--)
        empilhar(A, i);
}

int main() {
    Pilha A = inicializar_pilha();
    Pilha B = inicializar_pilha();
    Pilha C = inicializar_pilha();

    int movimentos = 0;
    int opcao;

    nova_partida(&A, &B, &C);

    do {
        printf("\n===== TORRE DE HANOI =====\n");
        printf("1 - Mostrar torres\n");
        printf("2 - Fazer movimento\n");
        printf("3 - Quantidade de movimentos\n");
        printf("4 - Nova partida\n");
        printf("0 - Encerrar\n");

        printf("\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                mostrar_torres(&A, &B, &C);
                break;

            case 2: {
                char origem, destino;

                printf("Torre de origem (A/B/C): ");
                scanf(" %c", &origem);

                printf("Torre de destino (A/B/C): ");
                scanf(" %c", &destino);

                if (origem != 'A' && origem != 'B' && origem != 'C' ||
                    destino != 'A' && destino != 'B' && destino != 'C') {
                    printf("Torre invalida.\n");
                    break;
                }

                if (origem == destino) {
                    printf("Movimento invalido: origem e destino sao iguais.\n");
                    break;
                }

                Pilha *pilha_origem = escolher_torre(&A, &B, &C, origem);
                Pilha *pilha_destino = escolher_torre(&A, &B, &C, destino);

                if (mover(pilha_origem, pilha_destino)) {
                    movimentos++;
                    printf("Movimento realizado.\n");

                    mostrar_torres(&A, &B, &C);

                    if (C.quantidade == 4) {
                        printf("\nPARABENS! Voce venceu!\n");
                        printf("Quantidade de movimentos: %d\n", movimentos);
                    }
                }

                break;
            }

            case 3:
                printf("Movimentos realizados: %d\n", movimentos);
                break;

            case 4:
                nova_partida(&A, &B, &C);
                movimentos = 0;
                printf("Nova partida iniciada.\n");
                break;

            case 0:
                printf("Jogo encerrado.\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    liberar_pilha(&A);
    liberar_pilha(&B);
    liberar_pilha(&C);

    return 0;
}