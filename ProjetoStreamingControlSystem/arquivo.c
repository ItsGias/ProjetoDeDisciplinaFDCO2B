#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serie.h"
#include "historico.h"

Serie* carregarSeries(Serie** series, int* quantidadeSeries) {
    printf("HEY");

    FILE* arquivo = fopen("./series.txt", "r");
    if (arquivo == NULL) {
        printf("Arquivo de séries não encontrado. Criando um novo arquivo...\n");
        return;
    }

    int token;
    Serie serie;
    
    while(!feof(arquivo)) {
        fscanf(arquivo, "%[^,],%[^,],%d,%[^,],%f,%d,", serie.titulo, serie.genero, &serie.classificacao, serie.plataforma, &serie.duracaoMediaEpisodio, &serie.quantidadeTemporadas);
        printf("%d", serie.quantidadeTemporadas);
        serie.episodiosPorTemporada = (int*)malloc(serie.quantidadeTemporadas * sizeof(int));
        for (int i = 0; i < serie.quantidadeTemporadas; i++) {
            if (i == serie.quantidadeTemporadas - 1)
                fscanf(arquivo, "%i\n", &token);
            else
                fscanf(arquivo, "%i ", &token);
            serie.episodiosPorTemporada[i] = token;
        }
        fscanf(arquivo, "\n");
        serie.codigo = 0;
        (*quantidadeSeries)++;
        *series = (Serie*)realloc(*series, (*quantidadeSeries) * sizeof(Serie));
        (*series)[(*quantidadeSeries) - 1] = serie;     
    }

    fclose(arquivo);
    return *series;
}

void salvarSeries(Serie* series, int quantidadeSeries) {
    FILE* arquivo = fopen("series.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de séries para escrita.\n");
        return;
    }

    for (int i = 0; i < quantidadeSeries; i++) {
        fprintf(arquivo, "%d,%s,%s,%d,%s,%.2f,%d,", series[i].codigo, series[i].titulo, series[i].genero, series[i].classificacao, series[i].plataforma, series[i].duracaoMediaEpisodio, series[i].quantidadeTemporadas);

        for (int j = 0; j < series[i].quantidadeTemporadas; j++) {
            fprintf(arquivo, "%d ", series[i].episodiosPorTemporada[j]);
        }

        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
}

void carregarHistorico(Historico** historico, int* quantidadeHistorico) {
    FILE* arquivo = fopen("historico.bin", "rb");
    if (arquivo == NULL) {
        printf("Arquivo de histórico não encontrado. Criando um novo arquivo...\n");
        return;
    }

    fread(quantidadeHistorico, sizeof(int), 1, arquivo);
    *historico = (Historico*)malloc((*quantidadeHistorico) * sizeof(Historico));
    fread(*historico, sizeof(Historico), *quantidadeHistorico, arquivo);

    fclose(arquivo);
}

void salvarHistorico(Historico* historico, int quantidadeHistorico) {
    FILE* arquivo = fopen("historico.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de histórico para escrita.\n");
        return;
    }

    fwrite(&quantidadeHistorico, sizeof(int), 1, arquivo);
    fwrite(historico, sizeof(Historico), quantidadeHistorico, arquivo);

    fclose(arquivo);
}
