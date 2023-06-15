#include <stdio.h>
#include <stdlib.h>
#include "serie.h"
#include "historico.h"
#include "arquivo.h"

int main() {
    int quantidadeSeries = 0;
    int japa =1;
    Historico* historico = NULL;
    int quantidadeHistorico = 0;
    Serie* series = NULL;
    char pesquisa[51];
    Serie* found = NULL;

    

    series = carregarSeries(&series, &quantidadeSeries);
    carregarHistorico(&historico, &quantidadeHistorico);

    int opcao1,opcao2,opcao3;
    printf("\nQuantidade de series: %d\n", quantidadeSeries);

    while(japa!=0) {

        

        printf("::========== MENU ===========::\n");
        printf("||1 - Inserir historico      ||\n");
        printf("||2 - Exibir historico       ||\n");
        printf("||3 - Excluir historico      ||\n");
        printf("||4 - Salvar Data Base em CSV||\n");
        printf("||0 - Voltar                 ||\n");
        printf("::===========================::\n");
        printf("Digite uma opção:\n");
        scanf("%d", &opcao1);

        switch (opcao1) {
            case 1:

                printf("::============= MENU =============::\n");
                printf("||1 - Inserir série               ||\n");
                printf("||2 - Listar séries               ||\n");
                printf("||3 - Pesquisar série pelo codigo ||\n");
                printf("||4 - Pesquisar série pelo titulo ||\n");
                printf("||5 - Alterar série               ||\n");
                printf("||6 - Excluir série               ||\n");
                printf("||7 - Pesquisar série pelo Genero ||\n");
                printf("||0 - Voltar                      ||\n");
                printf("::================================::\n");
                printf("Digite uma opção:\n");
                scanf("%d", &opcao2);

                switch (opcao2)
                {
                case 1://Inserir série
                    cadastrarSerie(&series, &quantidadeSeries);
                    salvarSeries(series, quantidadeSeries);
                    break;

                case 2://Listar séries 
                    listarSeries(series, quantidadeSeries);
                    break;

                case 3://Exibir série  
                    char codigo[8];
                    printf("Digite o código da série: ");
                    fgets(codigo, sizeof(codigo), stdin);
                    codigo[strcspn(codigo, "\n")] = '\0';
                    exibirSerie(series, quantidadeSeries, codigo);
                    break;

                case 4://Pesquisar série
                    printf("digite o nome da serie a ser pesquisada:\n");
                    setbuf(stdin, NULL);
                    fgets(pesquisa, 51, stdin);
                    pesquisa[strcspn(pesquisa,"\n")]='\0';
                    setbuf(stdin, NULL);
                    found = buscarSerie(series, quantidadeSeries, pesquisa);
                    
                    if(found == NULL) {
                        printf("Não localizei\n");
                        break;   
                    }

                    printf("Titulo: %s\n", found->titulo);
                    printf("genero: %s\n", found->genero);
                    printf("classificacao %d\n",found->classificacao);
                    printf("plataforma %s\n", found->plataforma);
                    printf("duracao media %.2f\n", found->duracaoMediaEpisodio);
                    printf("temporadas %d\n",found->quantidadeTemporadas);

                    for (int i = 0; i < found->quantidadeTemporadas ; i++)
                    {
                        printf("%d Episodios na Temporada %d\n",found->episodiosPorTemporada[i],i+1);
                    }
                    break;

                case 5://Alterar série 
                    printf("digite o nome da serie a ser pesquisada:\n");
                    setbuf(stdin, NULL);
                    fgets(pesquisa, 51, stdin);
                    pesquisa[strcspn(pesquisa,"\n")]='\0';
                    setbuf(stdin, NULL);
                    if(buscarSerie(series, quantidadeSeries, pesquisa) == NULL) {
                        printf("Não localizei\n");
                        break;   
                    }
                    editSerie(series, quantidadeSeries, pesquisa);

                    break;
                case 6://Excluir série
                    printf("digite o nome da serie a ser pesquisada:\n");
                    setbuf(stdin, NULL);
                    fgets(pesquisa, 51, stdin);
                    pesquisa[strcspn(pesquisa,"\n")]='\0';
                    setbuf(stdin, NULL);
                    printf("\n\n%d\n\n", quantidadeSeries);
                    series = excluiSerie(series,pesquisa, &quantidadeSeries);
                    listarSeries(series, quantidadeSeries);
                    printf("\n\n%d\n\n", quantidadeSeries);
                    break;

                case 7://pesquisar por genero
                    printf("digite o genero desejado:\n");
                    setbuf(stdin, NULL);
                    fgets(pesquisa, 51, stdin);
                    pesquisa[strcspn(pesquisa,"\n")]='\0';
                    setbuf(stdin, NULL);
                    printf("\n Código | Título\n");
                    
                    buscarSerieGenero(series,quantidadeSeries,pesquisa);
                    
                    break;

                default:
                    printf("Opção inválida. Digite novamente.\n");
                    break;
                }
                break;

            case 2:
                printf("::========== MENU ===========::\n");
                printf("||1 - Inserir historico      ||\n");
                printf("||2 - Exibir historico       ||\n");
                printf("||3 - Excluir historico      ||\n");
                printf("||4 - Salvar Data Base em CSV||\n");
                printf("||0 - Voltar                 ||\n");
                printf("::===========================::\n");
                printf("Digite uma opção:\n");
                scanf("%d", &opcao3);

                switch (opcao3)
                {
                case 1://Inserir historico
                    char codigo[9];
                    int temporada, episodio;
                    setbuf(stdin, NULL);
                    printf("Digite o código da série: ");
                    fgets(codigo, 10, stdin);
                    codigo[strcspn(codigo,"\n")]='\0';
                    setbuf(stdin, NULL);
                    
                    printf("Digite a última temporada assistida: ");
                    scanf("%d", &temporada);
                    
                    printf("Digite o último episódio assistido: ");
                    scanf("%d", &episodio);
                    printf("%s",codigo);
                    historico = adicionarAoHistorico(historico, &quantidadeHistorico, codigo, temporada, episodio);
                    salvarHistorico(historico, quantidadeHistorico);
                    break;

                case 2://Exibir historico
                    exibirHistorico(series, quantidadeSeries, historico, &quantidadeHistorico);
                    break;

                case 3://Excluir historico
                    quantidadeHistorico = 0;
                    break;

                case 0://voltar
                     
                    break;
                default:

                printf("Opção inválida. Digite novamente.\n");
                    break;
                }
                break;
            case 3: //curl
                
                break;
            case 4://save
                FILE* file = fopen("save.csv", "w");
                if(file == NULL) {
                    printf("Erro ao abrir o arquivo.\n");
                    return 0;
                }
                for(int i = 0; i < quantidadeSeries; i++) {
                    fprintf(file, "%s %s,%s,%d,%s,%.2f,%d", series[i].codigo, series[i].titulo, series[i].genero, series[i].classificacao, series[i].plataforma, series[i].duracaoMediaEpisodio, series[i].quantidadeTemporadas);
                    for(int j = 0; j < series[i].quantidadeTemporadas; j++) {
                        fprintf(file, " %d", series[i].episodiosPorTemporada[j]);
                    }
                    fprintf(file, "\n");
                }
                printf("Dados salvos no CSV.\n");
                fclose(file);
                break;
            case 0:
                printf("Saindo...\n");
                //sair e criar um arquivo .dat com as informações das series
                FILE* file2 = fopen("series.dat", "wb");
                printf("Quantidade de series: %d\n", quantidadeSeries);
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
