#ifndef HISTORICO_H
#define HISTORICO_H

#include "serie.h"

typedef struct {
    char codigoSerie[9];
    int ultimaTemporadaAssistida;
    int ultimoEpisodioAssistido;
} Historico;

void exibirHistorico(Serie* series, int quantidadeSeries, Historico* historico, int* quantidadeHistorico);

Historico* adicionarAoHistorico(Historico* historico, int* quantidadeHistorico, char* codigoSerie, int temporada, int episodio);

#endif