#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    char nomeDaSerie[30];
    char genero[30];
    int classificacao;
    char plataforma[30];
    int duracaoMedia;
    int quantTemporada;
    int* episodiosPorTemporada;
} Serie;

int main()
{
    Serie serie[258];

    FILE* arquivo;
    arquivo = fopen("streaming.txt", "r");

    if (arquivo == NULL) {
        printf("O arquivo nao pode ser aberto.");
        exit(1);
    }

    for (int i = 0; i < 258; i++) {
        fscanf(arquivo, "%[^,],%[^,],%[^,],%d,%[^,],%d,%d,",
            serie[i].nomeDaSerie,
            serie[i].genero,
            &serie[i].classificacao,
            serie[i].plataforma,
            &serie[i].duracaoMedia,
            &serie[i].quantTemporada);
        

        serie[i].episodiosPorTemporada = malloc(serie[i].quantTemporada * sizeof(int));
    }

    for (int i = 0; i < 258; i++) {
        printf("Nome da Serie: %s\n", serie[i].nomeDaSerie);
        printf("Genero: %s\n", serie[i].genero);
        printf("Classificaçao: %d\n", serie[i].classificacao);
        printf("Plataforma: %s\n", serie[i].plataforma);
        printf("Duraçao Media: %d\n", serie[i].duracaoMedia);
        printf("Quantidade de Temporadas: %d\n", serie[i].quantTemporada);
        printf("Episodios por Temporada: ");
        for (int j = 0; j < serie[i].quantTemporada; j++) {
            printf("%d ", serie[i].episodiosPorTemporada[j]);
        }
        printf("\n\n");
    }

    for (int i = 0; i < 258; i++) {
        free(serie[i].episodiosPorTemporada);
    }

    fclose(arquivo);

    return 0;
}