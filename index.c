#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nomeDaSerie[30];
    char genero[30];
    int classificacao;
    char plataforma[30];
    int duracaoMedia;
    int quantTemporada;
    char episodiosPorTemporada[100];
} Serie;

int main()
{
    Serie *serie = (Serie *)calloc(258, sizeof(Serie));
    FILE *arquivo;
    arquivo = fopen("streaming.txt", "r");

    if (arquivo == NULL)
    {
        perror("O arquivo nao pode ser aberto: \n");
        exit(1);
    } // Testa se existe algum erro

    for (int i = 0; i < 258; i++)
    {
        int result = fscanf(arquivo, "%[^,],%[^,],%d,%[^,],%d,%d,%[^\n]\n",
                            serie[i].nomeDaSerie,
                            serie[i].genero,
                            &serie[i].classificacao,
                            serie[i].plataforma,
                            &serie[i].duracaoMedia,
                            &serie[i].quantTemporada,
                            serie[i].episodiosPorTemporada);

    } // for para escanear os dados do arquivo streaming

    for (int i = 0; i < 258; i++)
    {
        printf("Nome da Serie: %s\n", serie[i].nomeDaSerie);
        printf("Genero: %s\n", serie[i].genero);
        printf("Classificaçao: %d\n", serie[i].classificacao);
        printf("Plataforma: %s\n", serie[i].plataforma);
        printf("Duraçao Media: %d\n", serie[i].duracaoMedia);
        printf("Quantidade de Temporadas: %d\n", serie[i].quantTemporada);
        printf("Episodios por Temporada: %s\n ", serie[i].episodiosPorTemporada);
        printf("\n\n");
    }

    free(serie);
    fclose(arquivo);

    return 0;
} // main