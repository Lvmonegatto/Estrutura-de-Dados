#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct No {
    char cor[20];
    struct No *proximo;
} No;

typedef struct {
    No *inicio;
    No *fim;
    int quantidade;
} Fila;

Fila inicializar_fila() {
    Fila fila;
    fila.inicio = NULL;
    fila.fim = NULL;
    fila.quantidade = 0;
    return fila;
}

void enfileirar(Fila *fila, char cor[]) {
    No *novo = malloc(sizeof(No));

    strcpy(novo->cor, cor);
    novo->proximo = NULL;

    if (fila->fim == NULL) {
        fila->inicio = novo;
        fila->fim = novo;
    }
    else {
        fila->fim->proximo = novo;
        fila->fim = novo;
    }

    fila->quantidade++;
}

char* desenfileirar(Fila *fila) {
    No *aux = fila->inicio;
    char *cor = malloc(20 * sizeof(char));

    strcpy(cor, aux->cor);

    fila->inicio = aux->proximo;

    if (fila->inicio == NULL)
        fila->fim = NULL;

    free(aux);
    fila->quantidade--;

    return cor;
}

char* frente(Fila *fila) {
    if (fila->inicio == NULL)
        return NULL;

    return fila->inicio->cor;
}

void imprimir(Fila *fila) {
    No *atual = fila->inicio;

    while (atual != NULL) {
        printf("%s ", atual->cor);
        atual = atual->proximo;
    }

    printf("\n");
}

void liberar_fila(Fila *fila) {
    while (fila->inicio != NULL)
        free(desenfileirar(fila));
}

char* sortear_cor() {
    char *cores[] = {
        "VERDE",
        "VERMELHO",
        "AZUL",
        "AMARELO"
    };

    char *cor = malloc(20 * sizeof(char));

    strcpy(cor, cores[rand() % 4]);

    return cor;
}

void mostrar_sequencia(Fila *fila) {
    No *atual = fila->inicio;

    printf("\nSequencia:\n");

    while (atual != NULL) {
        printf("%s", atual->cor);

        if (atual->proximo != NULL)
            printf(" -> ");

        atual = atual->proximo;
    }

    printf("\n");
}

int jogar_rodada(Fila *fila) {
    No *atual = fila->inicio;
    char cor[20];

    printf("\nRepita a sequencia:\n");

    while (atual != NULL) {
        printf("Cor: ");
        scanf("%s", cor);

        if (strcmp(cor, atual->cor) != 0)
            return 0;

        atual = atual->proximo;
    }

    return 1;
}

void nova_partida(Fila *fila) {
    liberar_fila(fila);

    *fila = inicializar_fila();

    char *cor = sortear_cor();

    enfileirar(fila, cor);

    free(cor);
}

void testes() {
    Fila fila = inicializar_fila();

    printf("\n===== TESTES =====\n");

    printf("\n1. Fila vazia\n");
    imprimir(&fila);

    printf("\n2. Enfileirar primeira cor\n");
    enfileirar(&fila, "VERDE");
    imprimir(&fila);

    printf("\n3. Enfileirar varias cores\n");
    enfileirar(&fila, "AZUL");
    enfileirar(&fila, "VERMELHO");
    imprimir(&fila);

    printf("\n4. Consultar frente\n");
    printf("Frente: %s\n", frente(&fila));

    printf("\n5. Desenfileirar\n");
    char *cor = desenfileirar(&fila);
    printf("Removida: %s\n", cor);
    free(cor);
    imprimir(&fila);

    printf("\n6. Quantidade\n");
    printf("Quantidade: %d\n", fila.quantidade);

    printf("\n7. Fila vazia\n");
    liberar_fila(&fila);
    imprimir(&fila);

    printf("\n8. Desenfileirar fila vazia\n");
    if (fila.inicio == NULL)
        printf("Fila vazia.\n");

    printf("\n9. Nova partida\n");
    nova_partida(&fila);
    imprimir(&fila);

    liberar_fila(&fila);
}

int main() {
    srand(time(NULL));

    Fila fila = inicializar_fila();

    int opcao;
    int pontuacao = 0;

    nova_partida(&fila);

    do {
        printf("\n===== GENIUS =====\n");
        printf("1 - Mostrar sequencia\n");
        printf("2 - Jogar rodada\n");
        printf("3 - Mostrar pontuacao\n");
        printf("4 - Nova partida\n");
        printf("5 - Executar testes\n");
        printf("0 - Encerrar\n");

        printf("\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                mostrar_sequencia(&fila);
                break;

            case 2: {
                mostrar_sequencia(&fila);

                if (jogar_rodada(&fila)) {
                    pontuacao++;

                    char *cor = sortear_cor();
                    enfileirar(&fila, cor);
                    free(cor);

                    printf("\nSequencia correta!\n");
                    printf("Nova cor adicionada.\n");
                    printf("Pontuacao: %d\n", pontuacao);
                }
                else {
                    printf("\nSequencia incorreta!\n");
                    printf("FIM DE JOGO\n");
                    printf("Pontuacao final: %d\n", pontuacao);

                    nova_partida(&fila);
                    pontuacao = 0;
                }

                break;
            }

            case 3:
                printf("Pontuacao: %d\n", pontuacao);
                break;

            case 4:
                nova_partida(&fila);
                pontuacao = 0;
                printf("Nova partida iniciada.\n");
                break;

            case 5:
                testes();
                break;

            case 0:
                printf("Jogo encerrado.\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    liberar_fila(&fila);

    return 0;
}