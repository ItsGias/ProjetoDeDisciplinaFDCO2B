#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "serie.h"
#include "historico.h"
#include "arquivo.h"
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

void Sleep(int time)
{
    usleep((time - 100) * 1000);
} // Sleep

int main()
{
    system("mpg123 audio.mp3 &"); // sudo apt-get install mpg123
    // foi tentado encontrar um jeito de parar a musica com a finalizacao do programa, porem sem sucesso
    // A musica reproduz ate o seu final, o qual a mesma possui uma duracao de 2 minutos e 22 segundos
    printf("\n\n"); // quebra a linha
    Sleep(500);

    int quantidadeSeries = 0;
    int japa = 1;
    Historico *historico = NULL;
    int quantidadeHistorico = 0;
    Serie *series = NULL;
    char pesquisa[51];
    Serie *found = NULL;

    system("clear");
    series = carregarSeries(&series, &quantidadeSeries);
    carregarHistorico(&historico, &quantidadeHistorico);

    int opcao1, opcao2, opcao3;

    while (japa != 0)
    {

        printf("\n");
        printf(BBLU "::==============" URED "MENU" BBLU "==============::\n" RESET);
        printf(BBLU "||" BCYN "1 -" RESET " Catalogo" BBLU "                    ||\n" RESET);
        printf(BBLU "||" BCYN "2 -" RESET " Historico" BBLU "                   ||\n" RESET);
        printf(BBLU "||" BCYN "3 -" RESET " Salvar Data Base em CSV" BBLU "     ||\n" RESET);
        printf(BBLU "||" BCYN "0 -" RESET " Sair" BBLU "                        ||\n" RESET);
        printf(BBLU "::================================::\n" RESET);
        printf(UMAG "Digite uma opção" RESET ": " RESET);
        scanf("%d", &opcao1);

        switch (opcao1)
        {
        case 1:

            printf("\n");
            printf(BBLU "::==============" URED "MENU" BBLU "==============::\n" RESET);
            printf(BBLU "||" BCYN "1 -" RESET " Inserir série" BBLU "               ||\n" RESET);
            printf(BBLU "||" BCYN "2 -" RESET " Listar séries" BBLU "               ||\n" RESET);
            printf(BBLU "||" BCYN "3 -" RESET " Listar ranqueadas pelo IMDB" BBLU " ||\n" RESET);
            printf(BBLU "||" BCYN "4 -" RESET " Pesquisar série pelo codigo" BBLU " ||\n" RESET);
            printf(BBLU "||" BCYN "5 -" RESET " Pesquisar série pelo titulo" BBLU " ||\n" RESET);
            printf(BBLU "||" BCYN "6 -" RESET " Alterar série" BBLU "               ||\n" RESET);
            printf(BBLU "||" BCYN "7 -" RESET " Excluir série" BBLU "               ||\n" RESET);
            printf(BBLU "||" BCYN "8 -" RESET " Pesquisar série pelo Genero" BBLU " ||\n" RESET);
            printf(BBLU "||" BCYN "0 -" RESET " Voltar" BBLU "                      ||\n" RESET);
            printf(BBLU "::================================::\n" RESET);
            printf("Digite uma opção: ");
            scanf("%d", &opcao2);

            switch (opcao2)
            {
            case 1: // Inserir série
                cadastrarSerie(&series, &quantidadeSeries);
                salvarSeries(series, quantidadeSeries);
                break;

            case 2: // Listar séries
                listarSeries(series, quantidadeSeries);
                break;
            case 3:
                Serie *seriesRanquedas = organizarSeries(series, &quantidadeSeries);
                listarSeriesRanqueadas(seriesRanquedas, quantidadeSeries);
                break;
            case 4: // Exibir série
                char codigo[8];
                printf(BBLU "Digite o código da série: " RESET);
                setbuf(stdin, NULL);
                fgets(codigo, sizeof(codigo), stdin);
                codigo[strcspn(codigo, "\n")] = '\0';
                exibirSerie(series, quantidadeSeries, codigo);
                break;

            case 5: // Pesquisar série
                printf(BBLU "Digite o nome da serie a ser pesquisada:\n" RESET);
                setbuf(stdin, NULL);
                fgets(pesquisa, 51, stdin);
                pesquisa[strcspn(pesquisa, "\n")] = '\0';
                setbuf(stdin, NULL);
                found = buscarSerie(series, quantidadeSeries, pesquisa);

                if (found == NULL)
                {
                    printf("Não localizei\n" RESET);
                    break;
                }

                printf(BBLU "Titulo: %s\n" RESET, found->titulo);
                printf(BBLU "genero: %s\n" RESET, found->genero);
                printf(BBLU "classificacao %d\n" RESET, found->classificacao);
                printf(BBLU "plataforma %s\n" RESET, found->plataforma);
                printf(BBLU "duracao media %.2f\n" RESET, found->duracaoMediaEpisodio);
                printf(BBLU "\nTop " BHMAG "%d" RESET " " BBLU "no ranking de popularidade do imdB\n" RESET, found->ranking); // printa ranking
                printf(BBLU "\nnota: " BHMAG "%.2f\n" RESET, found->rating);                                                  // printa rating

                printf(BBLU "temporadas " BHMAG "%d\n" RESET, found->quantidadeTemporadas);

                for (int i = 0; i < found->quantidadeTemporadas; i++)
                {
                    printf(BHMAG "%d" RESET " " BBLU "Episodios na Temporada " BHMAG "%d\n" RESET, found->episodiosPorTemporada[i], i + 1);
                }

                // printf("\nEnredo: %s\n", found->enredo); //printa enredo

                break;

            case 6: // Alterar série
                printf(BBLU "Digite o nome da serie a ser pesquisada:\n" RESET);
                setbuf(stdin, NULL);
                fgets(pesquisa, 51, stdin);
                pesquisa[strcspn(pesquisa, "\n")] = '\0';
                setbuf(stdin, NULL);
                if (buscarSerie(series, quantidadeSeries, pesquisa) == NULL)
                {
                    printf(BHRED "Não localizei\n" RESET);
                    break;
                }
                editSerie(series, quantidadeSeries, pesquisa);

                break;
            case 7: // Excluir série
                printf(BBLU "Digite o nome da serie a ser pesquisada:\n" RESET);
                setbuf(stdin, NULL);
                fgets(pesquisa, 51, stdin);
                pesquisa[strcspn(pesquisa, "\n")] = '\0';
                setbuf(stdin, NULL);
                printf(BBLU "\n\n%d\n\n" RESET, quantidadeSeries);
                series = excluiSerie(series, pesquisa, &quantidadeSeries);
                listarSeries(series, quantidadeSeries);
                printf(BBLU "\n\n%d\n\n" RESET, quantidadeSeries);
                break;

            case 8: // pesquisar por genero
                printf(BBLU "Digite o genero desejado:\n" RESET);
                setbuf(stdin, NULL);
                fgets(pesquisa, 51, stdin);
                pesquisa[strcspn(pesquisa, "\n")] = '\0';
                setbuf(stdin, NULL);
                printf(BBLU "\n  " RESET "Código " BBLU "|" RESET " Título\n");

                buscarSerieGenero(series, quantidadeSeries, pesquisa);

                break;

            default:
                printf(BHRED "Opção inválida. Digite novamente.\n" RESET);
                break;
            }
            break;

        case 2:
            printf("\n");
            printf(BBLU "::==============" URED "MENU" BBLU "==============::\n" RESET);
            printf(BBLU "||" BCYN "1 -" RESET " Inserir historico" BBLU "           ||\n" RESET);
            printf(BBLU "||" BCYN "2 -" RESET " Exibir historico" BBLU "            ||\n" RESET);
            printf(BBLU "||" BCYN "3 -" RESET " Excluir historico" BBLU "           ||\n" RESET);
            printf(BBLU "||" BCYN "4 -" RESET " Salvar Data Base em CSV" BBLU "     ||\n" RESET);
            printf(BBLU "||" BCYN "0 -" RESET " Voltar" BBLU "                      ||\n" RESET);
            printf(BBLU "::================================::\n" RESET);
            printf(UMAG "Digite uma opção" RESET ": " RESET);
            scanf("%d", &opcao3);

            switch (opcao3)
            {
            case 1: // Inserir historico
                char codigo[9];
                int temporada, episodio;
                setbuf(stdin, NULL);
                printf(BBLU "Digite o código da série: " RESET);
                fgets(codigo, 10, stdin);
                codigo[strcspn(codigo, "\n")] = '\0';
                setbuf(stdin, NULL);

                printf(BBLU "Digite a última temporada assistida: " RESET);
                scanf("%d", &temporada);

                printf(BBLU "Digite o último episódio assistido: " RESET);
                scanf("%d", &episodio);
                printf(BHMAG "%s" RESET, codigo);
                historico = adicionarAoHistorico(historico, &quantidadeHistorico, codigo, temporada, episodio);
                salvarHistorico(historico, quantidadeHistorico);
                break;

            case 2: // Exibir historico
                exibirHistorico(series, quantidadeSeries, historico, &quantidadeHistorico);
                break;

            case 3: // Excluir historico
                quantidadeHistorico = 0;
                break;

            case 0: // voltar
                break;

            default:
                printf(BHRED "Opção inválida." RESET " " BBLU "Digite novamente.\n" RESET);
                break;
            }
            break;
        case 3: // save
            FILE *file = fopen("save.csv", "w");

            if (file == NULL)
            {
                printf(BHRED "Erro ao abrir o arquivo.\n" RESET);
                return 0;
            }

            for (int i = 0; i < quantidadeSeries; i++)
            {
                fprintf(file, "%s %s,%s,%d,%s,%.2f,%d", series[i].codigo, series[i].titulo, series[i].genero, series[i].classificacao, series[i].plataforma, series[i].duracaoMediaEpisodio, series[i].quantidadeTemporadas);
                for (int j = 0; j < series[i].quantidadeTemporadas; j++)
                {
                    fprintf(file, " %d", series[i].episodiosPorTemporada[j]);
                }

                fprintf(file, "\n");
            }

            printf(BHGRN "Dados salvos no CSV.\n" RESET);

            fclose(file);

            break;

        case 0:
            printf(BHRED "Saindo...\n" RESET);

            // sair e criar um arquivo .dat com as informações das series
            FILE *file2 = fopen("series.dat", "wb");

            printf(BBLU "Quantidade de series:" BHCYN " %d\n" RESET, quantidadeSeries);

            fwrite(&quantidadeSeries, sizeof(int), 1, file2);
            fwrite(series, sizeof(Serie), quantidadeSeries, file2);

            fclose(file2);

            japa = 0;

            return 0;
        }
    }

    free(series);
    free(historico);

    return 0;
}
