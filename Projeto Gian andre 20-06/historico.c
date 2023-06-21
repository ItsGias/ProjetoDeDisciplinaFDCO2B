#include <stdio.h>
#include <stdlib.h>
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

Historico *adicionarAoHistorico(Historico *historico, int *quantidadeHistorico, char *codigoSerie, int temporada, int episodio)
{

    int indice = buscarHistorico(historico, *quantidadeHistorico, codigoSerie);

    if (indice == -1)
    {
        *quantidadeHistorico = *quantidadeHistorico + 1;
        historico = realloc(historico, (*quantidadeHistorico) * sizeof(Historico));
        indice = *quantidadeHistorico - 1;
    }
    printf(BBLU "Indice: %d\n" RESET, indice);
    strcpy(historico[indice].codigoSerie, codigoSerie);
    historico[indice].ultimaTemporadaAssistida = temporada;
    historico[indice].ultimoEpisodioAssistido = episodio;

    printf(BHGRN "Episódio adicionado ao histórico com sucesso!\n" RESET);

    return historico;
}

void exibirHistorico(Serie *series, int quantidadeSeries, Historico *historico, int *quantidadeHistorico)
{

    if (*quantidadeHistorico == 0)
    {
        printf(BHWHT "Nenhum" BHCYN " episódio assistido ainda!\n" RESET);
        return;
    }

    for (int i = 0; i < *quantidadeHistorico; i++)
    {
        printf(BBLU "::==================================::\n" RESET);
        printf(BBLU "||  " RESET "Histórico de Séries Assistidas" BBLU "||\n" RESET);
        printf(BBLU "::==================================::\n" RESET);
        char codigoSerie[9];
        strcpy(codigoSerie, (historico)[i].codigoSerie);
        int temporada = (historico)[i].ultimaTemporadaAssistida;
        int episodio = (historico)[i].ultimoEpisodioAssistido;

        int indiceSerie = buscarSerie(series, quantidadeSeries, codigoSerie);

        if (indiceSerie != -1)
        {
            Serie serie = series[indiceSerie];
            printf(BBLU "Série: " BHWHT "%s\n" RESET, serie.titulo);
            printf(BBLU "Última temporada assistida:" BHWHT " %d\n" RESET, temporada);
            printf(BBLU "Último episódio assistido:" BHWHT " %d\n" RESET, episodio);
            printf("\n");
        }
    }
}

int buscarHistorico(Historico *historico, int quantidadeHistorico, int codigoSerie)
{
    for (int i = 0; i < quantidadeHistorico; i++)
    {
        if (historico[i].codigoSerie == codigoSerie)
        {
            return i;
        }
    }

    return -1;
}
