#ifndef SERIE_H
#define SERIE_H

typedef struct {
    char codigo[10];
    char titulo[100];
    char genero[50];
    int classificacao;
    char plataforma[50];
    float duracaoMediaEpisodio;
    int quantidadeTemporadas;
    int* episodiosPorTemporada;
} Serie;

Serie* buscarSerie(Serie* series, int quantidadeSeries, char* titulo);
Serie* excluiSerie(Serie* series, char* titulo, int* quantidadeSeries);
void editSerie(Serie* series, int quantidadeSeries, char* titulo);
void exibirSerie(Serie* series, int quantidadeSeries, char* codigo);
Serie* buscarSerieCodigo(Serie* series, int quantidadeSeries, char* codigo);
void buscarSerieGenero(Serie* series, int quantidadeSeries, char* titulo);

#endif