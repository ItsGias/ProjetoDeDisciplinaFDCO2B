#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serie.h"
#include "historico.h"

Serie* carregarSeries(Serie** series, int* quantidadeSeries) {

    Serie* series_local;
    FILE* arquivo = fopen("series.dat","rb");

    if(arquivo == NULL){
        FILE* arquivoTXT = fopen("series.txt", "r");
        printf("Bem vindo ao Streaming Control System!!\n");
        printf("Arquivo de séries não encontrado. Criando um novo arquivo...\n");
        sleep(1);
        printf("Arquivo criado, extraindo informacoes complementares do IMDB...\n");
        sleep(1);

        arquivoTXT = fopen("series.txt", "r");
        if (arquivoTXT == NULL) {
            perror("Erro ao abrir os arquivos\n");
        return;
        }
        
        int token;
        Serie serie;
        while(!feof(arquivoTXT)) {
            fscanf(arquivoTXT, "%[^,],%[^,],%[^,],%d,%[^,],%f,%d,",serie.codigo, serie.titulo, serie.genero, &serie.classificacao, serie.plataforma, &serie.duracaoMediaEpisodio, &serie.quantidadeTemporadas);
            serie.episodiosPorTemporada = (int*)malloc(serie.quantidadeTemporadas * sizeof(int));
            for (int i = 0; i < serie.quantidadeTemporadas; i++) {
                if (i == serie.quantidadeTemporadas - 1)
                    fscanf(arquivoTXT, "%i", &token);
                else
                    fscanf(arquivoTXT, "%i ", &token);
                serie.episodiosPorTemporada[i] = token;
            }
            
            fscanf(arquivoTXT, "\n");
            (*quantidadeSeries)++;
            *series = (Serie*)realloc(*series, (*quantidadeSeries) * sizeof(Serie));
            (*series)[(*quantidadeSeries) - 1] = serie;
            
        }

        series_local = *series;\

        //printf("\nQuantidade de series: %d\n", *quantidadeSeries);
        printf("\n\n");

        float percent;

        for (int i = 0; i < *quantidadeSeries; i++)
        {
            percent = ((i+1)*100)/(*quantidadeSeries);
            printf("Loading %.f%% Ja foram carregadas %d series de %d...\r",percent, i+1, *quantidadeSeries);
            fflush(stdout);
            extraiHTML(series_local,i);
        }

    }else {
        printf("Bem vindo ao Streaming Control System!!\n");
        printf("Arquivo de séries encontrado. Carregando...\n");
        
        fread(quantidadeSeries, sizeof(int), 1, arquivo);
        *series = (Serie*)realloc(*series, (*quantidadeSeries) * sizeof(Serie));
        fread(*series, sizeof(Serie), *quantidadeSeries, arquivo); 
    }

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

void salvaArquivo(Serie* series, int quantidadeSeries){

}