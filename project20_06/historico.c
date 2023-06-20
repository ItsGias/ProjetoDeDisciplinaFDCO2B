#include <stdio.h>
#include <stdlib.h>
#include "serie.h"
#include "historico.h"

Historico* adicionarAoHistorico(Historico* historico, int* quantidadeHistorico, char* codigoSerie, int temporada, int episodio) {

    int indice = buscarHistorico(historico, *quantidadeHistorico, codigoSerie);
    
    if (indice == -1) {
        *quantidadeHistorico = *quantidadeHistorico + 1;
        historico = realloc(historico, (*quantidadeHistorico) * sizeof(Historico));
        indice = * quantidadeHistorico -1;
    }
    printf("Indice: %d\n", indice);
    strcpy(historico[indice].codigoSerie,codigoSerie);
    historico[indice].ultimaTemporadaAssistida = temporada;
    historico[indice].ultimoEpisodioAssistido = episodio;

    printf("Episódio adicionado ao histórico com sucesso!\n");

    return historico;
    
}

void exibirHistorico(Serie* series, int quantidadeSeries, Historico* historico, int* quantidadeHistorico) {

    if (*quantidadeHistorico == 0) {
        printf("Nenhum episódio assistido ainda!\n");
        return;
    }

    for (int i = 0; i < *quantidadeHistorico; i++) {
        printf("Histórico de Séries Assistidas:\n");
        char codigoSerie[9];
        strcpy(codigoSerie,(historico)[i].codigoSerie);
        int temporada = (historico)[i].ultimaTemporadaAssistida;
        int episodio = (historico)[i].ultimoEpisodioAssistido;

        int indiceSerie = buscarSerie(series, quantidadeSeries, codigoSerie);

        if (indiceSerie != -1) {
            Serie serie = series[indiceSerie];
            printf("Série: %s\n", serie.titulo);
            printf("Última temporada assistida: %d\n", temporada);
            printf("Último episódio assistido: %d\n", episodio);
            printf("\n");
        }
    }
}


int buscarHistorico(Historico* historico, int quantidadeHistorico, int codigoSerie) {
    for (int i = 0; i < quantidadeHistorico; i++) {
        if (historico[i].codigoSerie == codigoSerie) {
            return i;
        }
    }

    return -1;
}
