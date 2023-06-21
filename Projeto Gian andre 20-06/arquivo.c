#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serie.h"
#include "historico.h"
// Texto Colorido Comum
#define BLK "\e[0;30m" // Preto
#define RED "\e[0;31m" // Vermelho
#define GRN "\e[0;32m" // Verde
#define YEL "\e[0;33m" // Amarelo
#define BLU "\e[0;34m" // Azul
#define MAG "\e[0;35m" // Magenta
#define CYN "\e[0;36m" // Ciano
#define WHT "\e[0;37m" // Branco

// Texto Negrito
#define BBLK "\e[1;30m" // Preto Negrito
#define BRED "\e[1;31m" // Vermelho Negrito
#define BGRN "\e[1;32m" // Verde Negrito
#define BYEL "\e[1;33m" // Amarelo Negrito
#define BBLU "\e[1;34m" // Azul Negrito
#define BMAG "\e[1;35m" // Magenta Negrito
#define BCYN "\e[1;36m" // Ciano Negrito
#define BWHT "\e[1;37m" // Branco Negrito

// Texto Sublinhado
#define UBLK "\e[4;30m" // Preto Sublinhado
#define URED "\e[4;31m" // Vermelho Sublinhado
#define UGRN "\e[4;32m" // Verde Sublinhado
#define UYEL "\e[4;33m" // Amarelo Sublinhado
#define UBLU "\e[4;34m" // Azul Sublinhado
#define UMAG "\e[4;35m" // Magenta Sublinhado
#define UCYN "\e[4;36m" // Ciano Sublinhado
#define UWHT "\e[4;37m" // Branco Sublinhado

// Cor do fundo
#define BLKB "\e[40m" // Fundo Preto
#define REDB "\e[41m" // Fundo Vermelho
#define GRNB "\e[42m" // Fundo Verde
#define YELB "\e[43m" // Fundo Amarelo
#define BLUB "\e[44m" // Fundo Azul
#define MAGB "\e[45m" // Fundo Magenta
#define CYNB "\e[46m" // Fundo Ciano
#define WHTB "\e[47m" // Fundo Branco

// Cor fundo cor intensa
#define BLKHB "\e[0;100m" // Fundo Intenso Preto
#define REDHB "\e[0;101m" // Fundo Intenso Vermelho
#define GRNHB "\e[0;102m" // Fundo Intenso Verde
#define YELHB "\e[0;103m" // Fundo Intenso Amarelo
#define BLUHB "\e[0;104m" // Fundo Intenso Azul
#define MAGHB "\e[0;105m" // Fundo Intenso Magenta
#define CYNHB "\e[0;106m" // Fundo Intenso Ciano
#define WHTHB "\e[0;107m" // Fundo Intenso Branco

// Texto Cor intensa
#define HBLK "\e[0;90m" // Preto Intenso
#define HRED "\e[0;91m" // Vermelho Intenso
#define HGRN "\e[0;92m" // Verde Intenso
#define HYEL "\e[0;93m" // Amarelo Intenso
#define HBLU "\e[0;94m" // Azul Intenso
#define HMAG "\e[0;95m" // Magenta Intenso
#define HCYN "\e[0;96m" // Ciano Intenso
#define HWHT "\e[0;97m" // Branco Intenso

// Texto Negrito Cor intensa
#define BHBLK "\e[1;90m" // Preto Intenso Negrito
#define BHRED "\e[1;91m" // Vermelho Intenso Negrito
#define BHGRN "\e[1;92m" // Verde Intenso Negrito
#define BHYEL "\e[1;93m" // Amarelo Intenso Negrito
#define BHBLU "\e[1;94m" // Azul Intenso Negrito
#define BHMAG "\e[1;95m" // Magenta Intenso Negrito
#define BHCYN "\e[1;96m" // Ciano Intenso Negrito
#define BHWHT "\e[1;97m" // Branco Intenso Negrito

// Reseta as cores - texto branco fundo preto
#define RESET "\e[0m"

Serie *carregarSeries(Serie **series, int *quantidadeSeries)
{

    Serie *series_local;
    FILE *arquivo = fopen("series.dat", "rb");

    if (arquivo == NULL)
    {
        FILE *arquivoTXT = fopen("series.txt", "r");
        printf(BHBLU "Bem vindo ao" BHCYN " Streaming Control System!!\n" RESET);
        printf(BHRED "Arquivo de séries não encontrado." BHCYN "Criando" BHBLU "um novo arquivo...\n" RESET);
        sleep(1);
        printf(BHGRN "Arquivo criado, extraindo informacoes complementares do IMDB...\n" RESET);
        sleep(1);

        arquivoTXT = fopen("series.txt", "r");
        if (arquivoTXT == NULL)
        {
            perror(BHRED "Erro ao abrir os arquivos\n" RESET);
            return;
        }

        int token;
        Serie serie;
        while (!feof(arquivoTXT))
        {
            fscanf(arquivoTXT, "%[^,],%[^,],%[^,],%d,%[^,],%f,%d,", serie.codigo, serie.titulo, serie.genero, &serie.classificacao, serie.plataforma, &serie.duracaoMediaEpisodio, &serie.quantidadeTemporadas);
            serie.episodiosPorTemporada = (int *)malloc(serie.quantidadeTemporadas * sizeof(int));
            for (int i = 0; i < serie.quantidadeTemporadas; i++)
            {
                if (i == serie.quantidadeTemporadas - 1)
                    fscanf(arquivoTXT, "%i", &token);
                else
                    fscanf(arquivoTXT, "%i ", &token);
                serie.episodiosPorTemporada[i] = token;
            }

            fscanf(arquivoTXT, "\n");
            (*quantidadeSeries)++;
            *series = (Serie *)realloc(*series, (*quantidadeSeries) * sizeof(Serie));
            (*series)[(*quantidadeSeries) - 1] = serie;
        }

        series_local = *series;

        // printf("\nQuantidade de series: %d\n", *quantidadeSeries);
        printf("\n\n");

        float percent;

        for (int i = 0; i < *quantidadeSeries; i++)
        {
            percent = ((i + 1) * 100) / (*quantidadeSeries);
            printf(BHBLU "Loading" BHCYN " %.f%% " BHBLU "Ja foram carregadas" BHCYN " %d " BHBLU "series de" BHCYN
                         "%d" BHCYN "...\r " RESET,
                   percent,
                   i + 1, *quantidadeSeries);
            fflush(stdout);
            extraiHTML(series_local, i);
        }
    }
    else
    {
        printf(BHBLU "Bem vindo ao" BHCYN " Streaming Control System!!\n" RESET);
        printf(BHGRN "Arquivo de séries encontrado. Carregando...\n" RESET);

        fread(quantidadeSeries, sizeof(int), 1, arquivo);
        *series = (Serie *)realloc(*series, (*quantidadeSeries) * sizeof(Serie));
        fread(*series, sizeof(Serie), *quantidadeSeries, arquivo);
    }

    return *series;
}

void salvarSeries(Serie *series, int quantidadeSeries)
{
    FILE *arquivo = fopen("series.csv", "w");
    if (arquivo == NULL)
    {
        printf(BHRED "Erro ao abrir o arquivo de séries para escrita.\n" RESET);
        return;
    }

    for (int i = 0; i < quantidadeSeries; i++)
    {
        fprintf(arquivo, "%d,%s,%s,%d,%s,%.2f,%d,", series[i].codigo, series[i].titulo, series[i].genero, series[i].classificacao, series[i].plataforma, series[i].duracaoMediaEpisodio, series[i].quantidadeTemporadas);

        for (int j = 0; j < series[i].quantidadeTemporadas; j++)
        {
            fprintf(arquivo, "%d ", series[i].episodiosPorTemporada[j]);
        }

        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
}

void carregarHistorico(Historico **historico, int *quantidadeHistorico)
{
    FILE *arquivo = fopen("historico.bin", "rb");
    if (arquivo == NULL)
    {
        printf(BHRED "Arquivo de séries não encontrado.\n" BHCYN "Criando" BHBLU " um novo arquivo...\n" RESET);
        return;
    }

    fread(quantidadeHistorico, sizeof(int), 1, arquivo);
    *historico = (Historico *)malloc((*quantidadeHistorico) * sizeof(Historico));
    fread(*historico, sizeof(Historico), *quantidadeHistorico, arquivo);

    fclose(arquivo);
}

void salvarHistorico(Historico *historico, int quantidadeHistorico)
{
    FILE *arquivo = fopen("historico.bin", "wb");
    if (arquivo == NULL)
    {
        printf(BHRED "Erro ao abrir o arquivo de histórico para escrita.\n" RESET);
        return;
    }

    fwrite(&quantidadeHistorico, sizeof(int), 1, arquivo);
    fwrite(historico, sizeof(Historico), quantidadeHistorico, arquivo);

    fclose(arquivo);
}

void salvaArquivo(Serie *series, int quantidadeSeries)
{
}