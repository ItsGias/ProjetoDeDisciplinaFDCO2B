#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "serie.h"
#include "historico.h"

Serie* carregarSeries(Serie** series, int* quantidadeSeries);
void salvarSeries(Serie* series, int quantidadeSeries);
void carregarHistorico(Historico** historico, int* quantidadeHistorico);
void salvarHistorico(Historico* historico, int quantidadeHistorico);

#endif
