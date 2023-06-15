#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serie.h"

void cadastrarSerie(Serie** series, int* quantidadeSeries) {
    
    Serie serie;    
    
    setbuf(stdin, NULL);
    printf("Digite o código da série: ");
    fgets(serie.codigo, sizeof(serie.codigo), stdin);
    serie.codigo[strcspn(serie.codigo, "\n")] = '\0';
    setbuf(stdin, NULL);

    printf("Digite o título da série: ");
    fgets(serie.titulo, sizeof(serie.titulo), stdin);
    serie.titulo[strcspn(serie.titulo, "\n")] = '\0';
    setbuf(stdin, NULL);

    printf("Digite o gênero da série: ");
    fgets(serie.genero, sizeof(serie.genero), stdin);
    serie.genero[strcspn(serie.genero, "\n")] = '\0';
    setbuf(stdin, NULL);

    printf("Digite a classificação indicativa da série: ");
    scanf("%d", &serie.classificacao);
    getchar();

    printf("Digite a plataforma de streaming da série: ");
    fgets(serie.plataforma, sizeof(serie.plataforma), stdin);
    serie.plataforma[strcspn(serie.plataforma, "\n")] = '\0';

    printf("Digite a duração média dos episódios da série: ");
    scanf("%f", &serie.duracaoMediaEpisodio);
    getchar();

    printf("Digite a quantidade de temporadas da série: ");
    scanf("%d", &serie.quantidadeTemporadas);
    getchar();

    serie.episodiosPorTemporada = (int*)malloc(serie.quantidadeTemporadas * sizeof(int));

    for (int i = 0; i < serie.quantidadeTemporadas; i++) {
        printf("Digite a quantidade de episódios da temporada %d: ", i + 1);
        scanf("%d", &serie.episodiosPorTemporada[i]);
        getchar();
    }

    (*quantidadeSeries)++;
    *series = (Serie*)realloc(*series, (*quantidadeSeries) * sizeof(Serie));
    (*series)[(*quantidadeSeries) - 1] = serie;

    printf("Série cadastrada com sucesso!\n");


}

void listarSeries(Serie* series, int quantidadeSeries) {
    printf("Listagem de Séries:\n");
    printf("  Código  | Título\n");

    for (int i = 0; i < quantidadeSeries; i++) {
        printf(" %8s | %s\n", series[i].codigo, series[i].titulo);
    }
    printf("\n");
    printf("\n");
}

void exibirSerie(Serie* series, int quantidadeSeries, char* codigo) {
    Serie* serie = buscarSerieCodigo(series, quantidadeSeries, codigo);

    if (serie == NULL) {
        printf("Série não encontrada.\n");
        return;
    }

    printf("Código: %s\n", serie->codigo);
    printf("Título: %s\n", serie->titulo);
    printf("Gênero: %s\n", serie->genero);
    printf("Classificação indicativa: %d\n", serie->classificacao);
    printf("Plataforma: %s\n", serie->plataforma);
    printf("Duração média dos episódios: %.2f minutos\n", serie->duracaoMediaEpisodio);
    printf("Quantidade de temporadas: %d\n", serie->quantidadeTemporadas);
    printf("Episódios por temporada: ");

    for (int i = 0; i < serie->quantidadeTemporadas; i++) {
        printf("%d ", serie->episodiosPorTemporada[i]);
    }

    printf("\n");
}

Serie* buscarSerie(Serie* series, int quantidadeSeries, char* titulo) {
    for (int i = 0; i < quantidadeSeries; i++) {
        if (!strcmp(series[i].titulo, titulo)) {
            return &series[i];
        }
    }
    return NULL;
}

Serie* buscarSerieCodigo(Serie* series, int quantidadeSeries, char* codigo) {
    for (int i = 0; i < quantidadeSeries; i++) {
        if (!strcmp(series[i].codigo,codigo)) {
            return &series[i];
        }
    }
    return NULL;
}

void buscarSerieGenero(Serie* series, int quantidadeSeries, char* genero) {
    for (int i = 0; i < quantidadeSeries; i++) {
        if (!strcmp(series[i].genero, genero)) {
            
            printf("%8s | %s\n", series[i].codigo, series[i].titulo);
            
        }
    }
    printf("\n");
    return NULL;
}

Serie* excluiSerie(Serie* series, char* titulo, int* quantidadeSeries){ //Index sera a posição no vetor da série que será excluída
    for (int i = 0; i < *quantidadeSeries; i++) {
        if (!strcmp(series[i].titulo, titulo)) {
            for (size_t j = i; j < *quantidadeSeries - 1; j++)
            {
                series[j] = series[j+1];
            }
            *(quantidadeSeries) = *(quantidadeSeries) - 1;
            printf("%d", *quantidadeSeries);
            series = realloc(series, *(quantidadeSeries) * sizeof(Serie));
            return series;
        }
    }
}

void editSerie(Serie* series, int quantidadeSeries, char* titulo) {
    Serie* alterar = buscarSerie(series, quantidadeSeries, titulo);

    int opcao;

    printf("::================= MENU ==================::\n");
    printf("||Qual dado da serie voce deseja alterar?  ||\n");
    printf("||1 - Titulo                               ||\n");
    printf("||2 - genero                               ||\n");
    printf("||3 - classificacao                        ||\n");
    printf("||4 - plataforma                           ||\n");
    printf("||5 - duracao media                        ||\n");
    printf("||6 - temporadas                           ||\n");
    printf("::=========================================::\n");


    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
        printf("Digite o novo nome da serie:\n");
        setbuf(stdin, NULL);
        fgets(alterar->titulo, 51, stdin);
        alterar->titulo[strcspn(alterar->titulo,"\n")]='\0';
        setbuf(stdin, NULL);
        break;
    case 2:
        printf("Digite o novo genero da serie:\n");
        fgets(alterar->genero, 51, stdin);
        alterar->genero[strcspn(alterar->genero,"\n")]='\0';
        setbuf(stdin, NULL);
        break;
    case 3:
        printf("Digite a nova classificacao da serie:\n");
        scanf("%d",&alterar->classificacao);
        break;
    case 4:
        printf("Digite a nova plataforma da serie:\n");
        fgets(alterar->plataforma, 51, stdin);
        alterar->plataforma[strcspn(alterar->plataforma,"\n")]='\0';
        setbuf(stdin, NULL);
        break;
    case 5:
        printf("Digite a nova duracao media dos ep da serie:\n");
        scanf("%f",&alterar->duracaoMediaEpisodio);
        break;
    case 6:
        printf("Digite o novo numero de temporadas da serie:\n");
        scanf("%d",&alterar->quantidadeTemporadas);
        break;
        
    default:
        printf("Opção inválida. Digite novamente.\n");
        break;
    }
}
