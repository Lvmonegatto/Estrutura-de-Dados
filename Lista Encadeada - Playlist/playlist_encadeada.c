#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char titulo[100];
    char artista[100];
    char album[100];
    int duracao;
} Musica;

typedef struct No {
    Musica musica;
    struct No *proximo;
} No;

typedef struct {
    No *primeiro;
    int quantidade;
} Lista;

Lista inicializar_lista() {
    Lista lista;

    lista.primeiro = NULL;
    lista.quantidade = 0;

    return lista;
}

No* criar_no(Musica musica) {
    No *novo = malloc(sizeof(No));

    novo->musica = musica;
    novo->proximo = NULL;

    return novo;
}

void inserir(Lista *lista, Musica musica, int posicao) {
    No *novo = criar_no(musica);

    if (posicao <= 0 || lista->primeiro == NULL) {
        novo->proximo = lista->primeiro;
        lista->primeiro = novo;
    }
    else {
        No *atual = lista->primeiro;

        for (int i = 0; i < posicao - 1 && atual->proximo != NULL; i++)
            atual = atual->proximo;

        novo->proximo = atual->proximo;
        atual->proximo = novo;
    }

    lista->quantidade++;
}

void imprimir(Lista *lista) {
    No *atual = lista->primeiro;

    printf("\n===== PLAYLIST =====\n");

    while (atual != NULL) {
        printf("ID: %d\n", atual->musica.id);
        printf("Titulo: %s\n", atual->musica.titulo);
        printf("Artista: %s\n", atual->musica.artista);
        printf("Album: %s\n", atual->musica.album);
        printf("Duracao: %d segundos\n", atual->musica.duracao);
        printf("--------------------\n");

        atual = atual->proximo;
    }
}

No* buscar(Lista *lista, int id) {
    No *atual = lista->primeiro;

    while (atual != NULL) {
        if (atual->musica.id == id)
            return atual;

        atual = atual->proximo;
    }

    return NULL;
}

void remover(Lista *lista, int id) {
    No *atual = lista->primeiro;
    No *anterior = NULL;

    while (atual != NULL && atual->musica.id != id) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL)
        return;

    if (anterior == NULL)
        lista->primeiro = atual->proximo;
    else
        anterior->proximo = atual->proximo;

    free(atual);

    lista->quantidade--;
}

void buscar_artista(Lista *lista, char artista[]) {
    No *atual = lista->primeiro;
    int encontrou = 0;

    while (atual != NULL) {
        if (strcmp(atual->musica.artista, artista) == 0) {
            printf("ID: %d | %s | %s\n",
                   atual->musica.id,
                   atual->musica.titulo,
                   atual->musica.album);

            encontrou = 1;
        }

        atual = atual->proximo;
    }

    if (!encontrou)
        printf("Nenhuma musica encontrada.\n");
}

int duracao_total(Lista *lista) {
    No *atual = lista->primeiro;
    int total = 0;

    while (atual != NULL) {
        total += atual->musica.duracao;
        atual = atual->proximo;
    }

    return total;
}

void inserir_inicio(Lista *lista, Musica musica) {
    inserir(lista, musica, 0);
}

void inserir_final(Lista *lista, Musica musica) {
    inserir(lista, musica, lista->quantidade);
}

Musica cadastrar_musica() {
    Musica musica;

    printf("ID: ");
    scanf("%d", &musica.id);

    printf("Titulo: ");
    scanf(" %[^\n]", musica.titulo);

    printf("Artista: ");
    scanf(" %[^\n]", musica.artista);

    printf("Album: ");
    scanf(" %[^\n]", musica.album);

    printf("Duracao em segundos: ");
    scanf("%d", &musica.duracao);

    return musica;
}

void testes() {
    Lista lista = inicializar_lista();

    Musica m1 = {1, "Musica 1", "Artista A", "Album A", 200};
    Musica m2 = {2, "Musica 2", "Artista B", "Album B", 180};
    Musica m3 = {3, "Musica 3", "Artista A", "Album C", 240};
    Musica m4 = {4, "Musica 4", "Artista C", "Album D", 210};

    printf("\n ===Lista de Testes passadas no enunciado=== \n");

    printf("\n1. Playlist vazia\n");
    imprimir(&lista);

    printf("\n2. Insercao da primeira musica\n");
    inserir_inicio(&lista, m1);
    imprimir(&lista);

    printf("\n3. Insercao de varias musicas\n");
    inserir_final(&lista, m2);
    inserir_final(&lista, m3);
    imprimir(&lista);

    printf("\n4. Insercao no inicio\n");
    inserir_inicio(&lista, m4);
    imprimir(&lista);

    printf("\n5. Insercao no final\n");
    inserir_final(&lista, m1);
    imprimir(&lista);

    printf("\n6. Insercao no meio\n");
    inserir(&lista, m2, 2);
    imprimir(&lista);

    printf("\n7. Busca de musica existente\n");
    if (buscar(&lista, 2) != NULL)
        printf("Musica encontrada.\n");
    else
        printf("Musica nao encontrada.\n");

    printf("\n8. Busca de musica inexistente\n");
    if (buscar(&lista, 99) != NULL)
        printf("Musica encontrada.\n");
    else
        printf("Musica nao encontrada.\n");

    printf("\n9. Busca por artista\n");
    buscar_artista(&lista, "Artista A");

    printf("\n10. Remocao da primeira musica\n");
    remover(&lista, 4);
    imprimir(&lista);

    printf("\n11. Remocao de musica intermediaria\n");
    remover(&lista, 2);
    imprimir(&lista);

    printf("\n12. Remocao da ultima musica\n");
    remover(&lista, 1);
    imprimir(&lista);

    printf("\n13. Quantidade de musicas\n");
    printf("Quantidade: %d\n", lista.quantidade);

    printf("\n14. Duracao total\n");
    printf("Duracao total: %d segundos\n", duracao_total(&lista));

    printf("\n15. Remocao de musica inexistente\n");
    remover(&lista, 99);
    printf("Quantidade apos tentativa: %d\n", lista.quantidade);

    while (lista.primeiro != NULL)
        remover(&lista, lista.primeiro->musica.id);

    printf("\n16. Remocao da unica musica\n");
    inserir_inicio(&lista, m1);
    remover(&lista, 1);

    if (lista.primeiro == NULL)
        printf("Playlist vazia.\n");
}

int main() {
    Lista lista = inicializar_lista();

    int opcao;

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Cadastrar musica no inicio\n");
        printf("2 - Cadastrar musica no final\n");
        printf("3 - Cadastrar musica em uma posicao\n");
        printf("4 - Exibir playlist\n");
        printf("5 - Buscar musica por ID\n");
        printf("6 - Buscar musica por artista\n");
        printf("7 - Remover musica por ID\n");
        printf("8 - Quantidade de musicas\n");
        printf("9 - Duracao total da playlist\n");
        printf("10 - Executar testes\n");
        printf("0 - Sair\n");

        printf("\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1: {
                Musica musica = cadastrar_musica();

                inserir_inicio(&lista, musica);

                break;
            }

            case 2: {
                Musica musica = cadastrar_musica();

                inserir_final(&lista, musica);

                break;
            }

            case 3: {
                Musica musica;
                int posicao;

                musica = cadastrar_musica();

                printf("Posicao: ");
                scanf("%d", &posicao);

                inserir(&lista, musica, posicao);

                break;
            }

            case 4:
                imprimir(&lista);
                break;

            case 5: {
                int id;

                printf("ID da musica: ");
                scanf("%d", &id);

                No *resultado = buscar(&lista, id);

                if (resultado != NULL) {
                    printf("\nMusica encontrada:\n");
                    printf("ID: %d\n", resultado->musica.id);
                    printf("Titulo: %s\n", resultado->musica.titulo);
                    printf("Artista: %s\n", resultado->musica.artista);
                    printf("Album: %s\n", resultado->musica.album);
                    printf("Duracao: %d segundos\n",
                           resultado->musica.duracao);
                }
                else {
                    printf("Musica nao encontrada.\n");
                }

                break;
            }

            case 6: {
                char artista[100];

                printf("Nome do artista: ");
                scanf(" %[^\n]", artista);

                buscar_artista(&lista, artista);

                break;
            }

            case 7: {
                int id;

                printf("ID da musica: ");
                scanf("%d", &id);

                remover(&lista, id);

                break;
            }

            case 8:
                printf("Quantidade de musicas: %d\n",
                       lista.quantidade);
                break;

            case 9:
                printf("Duracao total: %d segundos\n",
                       duracao_total(&lista));
                break;

            case 10:
                testes();
                break;

            case 0:
                printf("Programa encerrado.\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    while (lista.primeiro != NULL)
        remover(&lista, lista.primeiro->musica.id);

    return 0;
}