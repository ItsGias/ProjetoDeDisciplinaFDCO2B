#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serie.h"
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
#define RESET "\e[0m"

void cadastrarSerie(Serie **series, int *quantidadeSeries)
{

    Serie serie;

    setbuf(stdin, NULL);
    printf(BBLU "Digite o código da série: " RESET);
    fgets(serie.codigo, sizeof(serie.codigo), stdin);
    serie.codigo[strcspn(serie.codigo, "\n")] = '\0';
    setbuf(stdin, NULL);

    printf(BBLU "Digite o título da série: " RESET);
    fgets(serie.titulo, sizeof(serie.titulo), stdin);
    serie.titulo[strcspn(serie.titulo, "\n")] = '\0';
    setbuf(stdin, NULL);

    printf(BBLU "Digite o gênero da série: " RESET);
    fgets(serie.genero, sizeof(serie.genero), stdin);
    serie.genero[strcspn(serie.genero, "\n")] = '\0';
    setbuf(stdin, NULL);

    printf(BBLU "Digite a classificação indicativa da série: " RESET);
    scanf("%d", &serie.classificacao);
    getchar();

    printf(BBLU "Digite a plataforma de streaming da série: " RESET);
    setbuf(stdin, NULL);
    fgets(serie.plataforma, sizeof(serie.plataforma), stdin);
    serie.plataforma[strcspn(serie.plataforma, "\n")] = '\0';

    printf(BBLU "Digite a duração média dos episódios da série: " RESET);
    scanf("%f", &serie.duracaoMediaEpisodio);
    getchar();

    printf(BBLU "Digite a quantidade de temporadas da série: " RESET);
    scanf("%d", &serie.quantidadeTemporadas);
    getchar();

    serie.episodiosPorTemporada = (int *)malloc(serie.quantidadeTemporadas * sizeof(int));

    for (int i = 0; i < serie.quantidadeTemporadas; i++)
    {
        printf(BBLU "Digite a quantidade de episódios da temporada %d: " RESET, i + 1);
        scanf("%d", &serie.episodiosPorTemporada[i]);
        getchar();
    }

    (*quantidadeSeries)++;
    *series = (Serie *)realloc(*series, (*quantidadeSeries) * sizeof(Serie));
    (*series)[(*quantidadeSeries) - 1] = serie;

    printf(BHGRN "Série cadastrada com sucesso!\n" RESET);
}

void listarSeries(Serie *series, int quantidadeSeries)
{
    printf(BBLU "::======================::\n" RESET);
    printf(BBLU "||" RESET " Listagem de Séries:" BBLU "   ||\n");
    printf("||----------------------||\n");
    printf("||  " RESET "Código" BBLU "  | " RESET " Título " BBLU "||\n" RESET);

    for (int i = 0; i < quantidadeSeries; i++)
    {
        printf(" %8s" BBLU " | " RESET "%s\n", series[i].codigo, series[i].titulo);
    }
    printf("\n");
    printf("\n");
}

void listarSeriesRanqueadas(Serie *series, int quantidadeSeries)
{
    printf(BBLU "::================================::\n" RESET);
    printf(BBLU "||     Listagem de Séries:       || \n" RESET);
    printf(BBLU "||" RESET " Posicao  " BBLU "|" RESET "  Código  " BBLU "|" RESET " Título " BBLU "||\n" RESET);

    for (int i = 0; i < quantidadeSeries; i++)
    {
        if (series[i].ranking > 0)
            printf("#%-7d | %8s | %s\n", series[i].ranking, series[i].codigo, series[i].titulo);
    }
    printf("\n");
    printf("\n");
}

void exibirSerie(Serie *series, int quantidadeSeries, char *codigo)
{
    Serie *serie = buscarSerieCodigo(series, quantidadeSeries, codigo);

    if (serie == NULL)
    {
        printf(BHRED "Série não encontrada.\n" RESET);
        return;
    }

    printf(BBLU "Código: %s\n" RESET, serie->codigo);
    printf(BBLU "Título: %s\n" RESET, serie->titulo);
    printf(BBLU "Gênero: %s\n" RESET, serie->genero);
    printf(BBLU "Classificação indicativa: %d\n", serie->classificacao);
    printf(BBLU "Plataforma: %s\n", serie->plataforma);
    printf(BBLU "\nTop %d no ranking de popularidade do imdB\n" RESET, serie->ranking); // printa ranking
    printf(BBLU "\nnota: %.2f\n" RESET, serie->rating);                                 // printa rating
    printf(BBLU "\nEnredo: %s\n" RESET, serie->enredo);                                 // printa enredo

    for (int j = 0; j < serie->quantAtores; j++)
    {
        printf(BBLU "\nnome:" RESET " " BHCYN " %s\n" RESET, serie->atores[j]); // printa atores
    }

    printf(BBLU "Duração média dos episódios: %.2f minutos\n" RESET, serie->duracaoMediaEpisodio);
    printf(BBLU "Quantidade de temporadas: %d\n" RESET, serie->quantidadeTemporadas);
    printf(BBLU "Episódios por temporada: " RESET);

    for (int i = 0; i < serie->quantidadeTemporadas; i++)
    {
        printf(BHCYN "%d " RESET, serie->episodiosPorTemporada[i]);
    }

    printf("\n");
}

Serie *buscarSerie(Serie *series, int quantidadeSeries, char *titulo)
{
    for (int i = 0; i < quantidadeSeries; i++)
    {
        if (!strcasecmp(series[i].titulo, titulo))
        {
            return &series[i];
        }
    }
    return NULL;
}

Serie *buscarSerieCodigo(Serie *series, int quantidadeSeries, char *codigo)
{
    for (int i = 0; i < quantidadeSeries; i++)
    {
        if (!strcasecmp(series[i].codigo, codigo))
        {
            return &series[i];
        }
    }
    return NULL;
}

void buscarSerieGenero(Serie *series, int quantidadeSeries, char *genero)
{
    for (int i = 0; i < quantidadeSeries; i++)
    {
        if (!strcasecmp(series[i].genero, genero))
        {

            printf("%8s " BBLU "|" RESET " %s\n", series[i].codigo, series[i].titulo);
        }
    }
    printf("\n");
    return NULL;
}

Serie *excluiSerie(Serie *series, char *titulo, int *quantidadeSeries)
{ // Index sera a posição no vetor da série que será excluída
    for (int i = 0; i < *quantidadeSeries; i++)
    {
        if (!strcasecmp(series[i].titulo, titulo))
        {
            for (size_t j = i; j < *quantidadeSeries - 1; j++)
            {
                series[j] = series[j + 1];
            }
            *(quantidadeSeries) = *(quantidadeSeries)-1;
            printf(BBLU "%d" RESET, *quantidadeSeries);
            series = realloc(series, *(quantidadeSeries) * sizeof(Serie));
            return series;
        }
    }
}

Serie *organizarSeries(Serie *series, int *quantidadeSeries)
{
    Serie aux;
    for (int i = 0; i < (*quantidadeSeries) - 1; i++)
    {
        for (int j = 0; j < (*quantidadeSeries) - i - 1; j++)
        {
            if (series[j].ranking > series[j + 1].ranking)
            {
                aux = series[j];
                series[j] = series[j + 1];
                series[j + 1] = aux;
            }
        }
    }
    return series;
}

void editSerie(Serie *series, int quantidadeSeries, char *titulo)
{
    Serie *alterar = buscarSerie(series, quantidadeSeries, titulo);

    int opcao;

    printf(BBLU "::==============" URED "MENU" BBLU "==============::\n" RESET);
    printf(BBLU "||" BCYN "Qual dado da serie voce deseja alterar?" BBLU "  ||\n" RESET);
    printf(BBLU "||" BCYN "1 -" RESET " Titulo" BBLU "                      ||\n" RESET);
    printf(BBLU "||" BCYN "2 -" RESET " genero" BBLU "                      ||\n" RESET);
    printf(BBLU "||" BCYN "3 -" RESET "classificacao" BBLU "                ||\n" RESET);
    printf(BBLU "||" BCYN "4 -" RESET "plataforma" BBLU "                   ||\n" RESET);
    printf(BBLU "||" BCYN "5 -" RESET "duracao media" BBLU "                ||\n" RESET);
    printf(BBLU "||" BCYN "6 -" RESET "temporadas" BBLU "                   ||\n" RESET);
    printf(BBLU "::================================::\n" RESET);

    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
        printf(BBLU "Digite o novo nome da serie:\n" RESET);
        setbuf(stdin, NULL);
        fgets(alterar->titulo, 51, stdin);
        alterar->titulo[strcspn(alterar->titulo, "\n")] = '\0';
        setbuf(stdin, NULL);
        break;
    case 2:
        printf(BBLU "Digite o novo genero da serie:\n" RESET);
        fgets(alterar->genero, 51, stdin);
        alterar->genero[strcspn(alterar->genero, "\n")] = '\0';
        setbuf(stdin, NULL);
        break;
    case 3:
        printf(BBLU "Digite a nova classificacao da serie:\n" RESET);
        scanf("%d", &alterar->classificacao);
        break;
    case 4:
        printf(BBLU "Digite a nova plataforma da serie:\n" RESET);
        fgets(alterar->plataforma, 51, stdin);
        alterar->plataforma[strcspn(alterar->plataforma, "\n")] = '\0';
        setbuf(stdin, NULL);
        break;
    case 5:
        printf(BBLU "Digite a nova duracao media dos ep da serie:\n" RESET);
        scanf("%f", &alterar->duracaoMediaEpisodio);
        break;
    case 6:
        printf(BBLU "Digite o novo numero de temporadas da serie:\n" RESET);
        scanf("%d", &alterar->quantidadeTemporadas);
        break;

    default:
        printf(BHRED "Opção inválida. Digite novamente.\n" RESET);
        break;
    }
}
