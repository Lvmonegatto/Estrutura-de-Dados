#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float *dados;
    int tamanho;
    int capacidade;
} Vetor;

Vetor* inicializar_array(int capacidade) {
    Vetor *v = malloc(sizeof(Vetor));

    v->dados = malloc(capacidade * sizeof(float));
    v->tamanho = 0;
    v->capacidade = capacidade;

    return v;
}

void inserir(Vetor *v, float valor) {
    v->dados[v->tamanho] = valor;
    v->tamanho++;
}

void imprimir(Vetor *v) {
    printf("[");
    
    for (int i = 0; i < v->tamanho; i++) {
        printf("%.2f", v->dados[i]);

        if (i < v->tamanho - 1)
            printf(", ");
    }

    printf("]\n");
}

int buscar(Vetor *v, float valor) {
    for (int i = 0; i < v->tamanho; i++) {
        if (v->dados[i] == valor)
            return i;
    }

    return -1;
}

void remover(Vetor *v, int indice) {
    for (int i = indice; i < v->tamanho - 1; i++)
        v->dados[i] = v->dados[i + 1];

    v->tamanho--;
}

Vetor* multiplicar_escalar(Vetor *v, float escalar) {
    Vetor *resultado = inicializar_array(v->tamanho);

    for (int i = 0; i < v->tamanho; i++)
        inserir(resultado, v->dados[i] * escalar);

    return resultado;
}

Vetor* somar_vetores(Vetor *a, Vetor *b) {
    if (a->tamanho != b->tamanho)
        return NULL;

    Vetor *resultado = inicializar_array(a->tamanho);

    for (int i = 0; i < a->tamanho; i++)
        inserir(resultado, a->dados[i] + b->dados[i]);

    return resultado;
}

float produto_escalar(Vetor *a, Vetor *b) {
    float resultado = 0;

    if (a->tamanho != b->tamanho)
        return 0;

    for (int i = 0; i < a->tamanho; i++)
        resultado += a->dados[i] * b->dados[i];

    return resultado;
}

float norma(Vetor *v) {
    float soma = 0;

    for (int i = 0; i < v->tamanho; i++)
        soma += v->dados[i] * v->dados[i];

    return sqrt(soma);
}

float similaridade_cosseno(Vetor *a, Vetor *b) {
    float norma_a;
    float norma_b;
    float produto;

    if (a->tamanho != b->tamanho)
        return -1;

    norma_a = norma(a);
    norma_b = norma(b);

    if (norma_a == 0 || norma_b == 0)
        return -1;

    produto = produto_escalar(a, b);

    return produto / (norma_a * norma_b);
}

int maior_similaridade(Vetor *vetores[], int quantidade, Vetor *consulta) {
    int melhor = -1;
    float maior = -1;

    for (int i = 0; i < quantidade; i++) {
        float similaridade = similaridade_cosseno(vetores[i], consulta);

        if (similaridade > maior) {
            maior = similaridade;
            melhor = i;
        }
    }

    return melhor;
}

void testes() {
    Vetor *a = inicializar_array(3);
    Vetor *b = inicializar_array(3);

    inserir(a, 1);
    inserir(a, 2);
    inserir(a, 3);

    inserir(b, 4);
    inserir(b, 5);
    inserir(b, 6);

    printf("\n Testes do enunciado \n");

    printf("Vetor A: ");
    imprimir(a);

    printf("Vetor B: ");
    imprimir(b);

    Vetor *resultado = multiplicar_escalar(a, 2);

    printf("A * 2: ");
    imprimir(resultado);

    free(resultado->dados);
    free(resultado);

    resultado = somar_vetores(a, b);

    printf("A + B: ");
    imprimir(resultado);

    free(resultado->dados);
    free(resultado);

    printf("Produto escalar: %.2f\n", produto_escalar(a, b));

    printf("Norma de A: %.4f\n", norma(a));

    printf("Similaridade: %.4f\n", similaridade_cosseno(a, b));

    printf("Busca pelo valor 2: indice %d\n", buscar(a, 2));

    remover(a, 1);

    printf("A depois de remover o indice 1: ");
    imprimir(a);

    free(a->dados);
    free(a);

    free(b->dados);
    free(b);
}

int main() {
    Vetor *vetores[100];
    Vetor *consulta;
    Vetor *resultado;

    int quantidade = 0;
    int tamanho = 0;
    int opcao;

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Criar vetores\n");
        printf("2 - Exibir vetores\n");
        printf("3 - Multiplicar vetor por escalar\n");
        printf("4 - Somar dois vetores\n");
        printf("5 - Produto escalar\n");
        printf("6 - Norma de um vetor\n");
        printf("7 - Similaridade de cosseno\n");
        printf("8 - Maior similaridade\n");
        printf("9 - Buscar valor\n");
        printf("10 - Remover valor\n");
        printf("11 - Executar testes\n");
        printf("0 - Sair\n");

        printf("\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                printf("Tamanho dos vetores: ");
                scanf("%d", &tamanho);

                printf("Quantidade de vetores: ");
                scanf("%d", &quantidade);

                for (int i = 0; i < quantidade; i++) {
                    vetores[i] = inicializar_array(tamanho);

                    printf("\nVetor %d:\n", i);

                    for (int j = 0; j < tamanho; j++) {
                        float valor;

                        printf("Valor %d: ", j);
                        scanf("%f", &valor);

                        inserir(vetores[i], valor);
                    }
                }

                break;

            case 2:
                for (int i = 0; i < quantidade; i++) {
                    printf("Vetor %d: ", i);
                    imprimir(vetores[i]);
                }

                break;

            case 3: {
                int indice;
                float escalar;

                printf("Indice do vetor: ");
                scanf("%d", &indice);

                printf("Valor do escalar: ");
                scanf("%f", &escalar);

                resultado = multiplicar_escalar(vetores[indice], escalar);

                printf("Resultado: ");
                imprimir(resultado);

                free(resultado->dados);
                free(resultado);

                break;
            }

            case 4: {
                int a, b;

                printf("Indice do primeiro vetor: ");
                scanf("%d", &a);

                printf("Indice do segundo vetor: ");
                scanf("%d", &b);

                resultado = somar_vetores(vetores[a], vetores[b]);

                if (resultado == NULL) {
                    printf("Os vetores possuem tamanhos diferentes.\n");
                } else {
                    printf("Resultado: ");
                    imprimir(resultado);

                    free(resultado->dados);
                    free(resultado);
                }

                break;
            }

            case 5: {
                int a, b;

                printf("Indice do primeiro vetor: ");
                scanf("%d", &a);

                printf("Indice do segundo vetor: ");
                scanf("%d", &b);

                if (vetores[a]->tamanho != vetores[b]->tamanho)
                    printf("Os vetores possuem tamanhos diferentes.\n");
                else
                    printf("Produto escalar: %.4f\n",
                           produto_escalar(vetores[a], vetores[b]));

                break;
            }

            case 6: {
                int indice;

                printf("Indice do vetor: ");
                scanf("%d", &indice);

                printf("Norma: %.4f\n", norma(vetores[indice]));

                break;
            }

            case 7: {
                int a, b;
                float resultado;

                printf("Indice do primeiro vetor: ");
                scanf("%d", &a);

                printf("Indice do segundo vetor: ");
                scanf("%d", &b);

                resultado = similaridade_cosseno(
                    vetores[a],
                    vetores[b]
                );

                if (resultado == -1)
                    printf("Operacao invalida.\n");
                else
                    printf("Similaridade: %.4f\n", resultado);

                break;
            }

            case 8: {
                int melhor;

                consulta = inicializar_array(tamanho);

                printf("\nVetor de consulta:\n");

                for (int i = 0; i < tamanho; i++) {
                    float valor;

                    printf("Valor %d: ", i);
                    scanf("%f", &valor);

                    inserir(consulta, valor);
                }

                melhor = maior_similaridade(
                    vetores,
                    quantidade,
                    consulta
                );

                if (melhor == -1) {
                    printf("Nenhum vetor valido encontrado.\n");
                } else {
                    printf("Vetor mais similar: %d\n", melhor);
                    printf("Vetor: ");
                    imprimir(vetores[melhor]);
                }

                free(consulta->dados);
                free(consulta);

                break;
            }

            case 9: {
                int vetor;
                float valor;

                printf("Indice do vetor: ");
                scanf("%d", &vetor);

                printf("Valor a buscar: ");
                scanf("%f", &valor);

                printf("Indice encontrado: %d\n",
                       buscar(vetores[vetor], valor));

                break;
            }

            case 10: {
                int vetor;
                int indice;

                printf("Indice do vetor: ");
                scanf("%d", &vetor);

                printf("Indice a remover: ");
                scanf("%d", &indice);

                remover(vetores[vetor], indice);

                printf("Vetor depois da remocao: ");
                imprimir(vetores[vetor]);

                break;
            }

            case 11:
                testes();
                break;

            case 0:
                printf("Programa encerrado.\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    for (int i = 0; i < quantidade; i++) {
        free(vetores[i]->dados);
        free(vetores[i]);
    }

    return 0;
}