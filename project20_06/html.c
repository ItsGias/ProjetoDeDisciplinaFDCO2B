#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h> //sudo apt install libcurl4-openssl-dev
#include "serie.h"
#include  "html.h"

#define MAX_URL_LENGTH 500

char** buscaatores(const char *str,int* quantAtores)
{
    
    //printf("buscando atores...\n");
    const char *ptr = str;
    int count = 0;

    //aloca a matriz de atores
    char **nome = (char **) malloc(50 * sizeof(char*));
    for (int l = 0; l < 50; l++){
        nome[l] = (char *) malloc(100 * sizeof(char));
    }// for

    while ((ptr = strstr(ptr, "sc-bfec09a1-1 fUguci")) != NULL) {

        int i;
        // ptr esta apontadno para "sc-bfec09a1-1 fUguci...", ent a gente pula 22 caracteres alem do ptr
        ptr += 22;

        for (i = 0; i < 999; i++)
        {
            if(ptr[i] == '<') break;

            if (ptr[i] == '&') {
                // Verifica se o caractere seguinte é '#x27;'
                if (ptr[i+1] == '#' && ptr[i+2] == 'x' && ptr[i+3] == '2' && ptr[i+4] == '7' && ptr[i+5] == ';') {
                    
                    ptr += 6;

                }
            }

            //adiciona o caracter atual do nome na posição exata no vetor de nomes
            nome[count][i] = ptr[i];
        }

        //realoca o numero de caracteres do nome
        nome[count] = (char*) realloc(nome[count], strlen(nome[count]) + 1);

        nome[count][i] = '\0';

        count++;
        
    }

    //realoca o a quantidade de atores baseado no contador de elementos no codigo html
    nome = (char **) realloc (nome, (count+1)*sizeof(char*));

    *quantAtores = count;

    return nome;


}

float buscarating(const char *str)
{
    //printf("buscando notas no imdb...\n");
    const char *ptr = str;
    float rating;

    while ((ptr = strstr(ptr, "sc-bde20123-1 iZlgcd")) != NULL) {
                               
        // ptr esta apontadno para "sc-bde20123-1 iZlgcd...", ent a gente pula 22 caracteres alem do ptr
        ptr += 22;

        rating = strtof (ptr,NULL);
        
    }
    //printf("rating do imbd%f \n",rating);

    return rating;
}

int buscaranking(const char *str)
{
    
    const char *ptr = str;
    char aux[10];
    int ranking, aux2 = -1, i, j = 0, f;

    while ((ptr = strstr(ptr, "sc-5f7fb5b4-1 bhuIgW")) != NULL) {
        j = 1;       
        // ptr está apontando para "sc-bde20123-1 iZlgcd...", então pulamos 22 caracteres além de ptr
        ptr += 22;

        int aux2 = 0; // Variável auxiliar para acompanhar o índice de preenchimento em aux

        for (i = 0; i < 999; i++) {
            if (ptr[i] == '<') {
                break;
            }
            if (ptr[i] == ',') {
                continue;
            }

            aux[aux2] = ptr[i];
            aux2++;
        }

        aux[aux2] = '\0'; // Adiciona o caractere nulo para indicar o final da string em aux
    }

    

    if (!j) return 0;

    /*for (int j = 0; j < i; j++) {
        if (aux[j] == ',') {
            for (f = j; f < i; f++)
            {
                aux[f] = aux[f + 1];
            }    
        }
    }*/

    //printf("\n%s\n", aux);
    ranking = atoi(aux);

    //printf("ranking do imbd%d \n",ranking);

    return ranking;
}

char* buscaenredo(const char *str)
{
    //printf("buscando enredo das series...\n");
    const char *ptr = str;

    //aloca vetor do enredo
    int enredoLength = strlen(ptr);
    char *enredo = (char*) malloc((enredoLength + 1) * sizeof(char));
    int x;

    if ((ptr = strstr(ptr, "presentation")) != NULL) {
        ptr = strstr(ptr, "sc-cd57914c-2 cXtXlS");
        int i;
        ptr += 22;

        for (i = 0; i < 999; i++) {
            if (ptr[i] == '<')
                break;

            if (ptr[i] == '&') {
                // Verifica se o caractere seguinte é '#x27;'
                if (ptr[i+1] == '#' && ptr[i+2] == 'x' && ptr[i+3] == '2' && ptr[i+4] == '7' && ptr[i+5] == ';') {
                    ptr += 6;
                }
            }

            enredo[i] = ptr[i];
        }

        enredo[i] = '\0';
        enredo = (char*) realloc(enredo, i * sizeof(char));
    }


    return enredo;

}

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    size_t realsize = size * nmemb;
    Buffer *buffer = (Buffer *)userdata;

    char *new_data = realloc(buffer->data, buffer->size + realsize + 1);
    if (new_data == NULL) {
        perror("Erro de alocação de memoria:");
        return 0;
    }

    buffer->data = new_data;
    memcpy(&(buffer->data[buffer->size]), ptr, realsize);
    buffer->size += realsize;
    buffer->data[buffer->size] = '\0';

    return realsize;
}

void extraiHTML(Serie serie[], int i) {
    
    CURL *curl;
    CURLcode res;
    Buffer buffer = {NULL, 0};
    char url[MAX_URL_LENGTH];



    curl = curl_easy_init();//inicializa a lib curl

        

        if (curl) {

            //adiciona o id na url do imdb
            snprintf(url, MAX_URL_LENGTH, "https://www.imdb.com/title/tt%s/",serie[i].codigo);

            //define a url a ser lida pela licurl 
            curl_easy_setopt(curl, CURLOPT_URL, url);


            //requisita e le o codigo html da pagina selecionada
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);


            //escreve todo o codigo html da url no buffer 
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&buffer);

            //verifica se a requisição deu certo
            res = curl_easy_perform(curl);

            //caso n tenha dado certo ele avisara no terminal e encerrara o programa 
            if (res != CURLE_OK) {
                printf("Erro na solicitação: %s\n", curl_easy_strerror(res));//caso n tenha dado certo ele avisara no terminal e encerrara o programa 
                return 0;
            }

            
        }

        curl_easy_cleanup(curl);//limpa todos os dados da libcurl
        
        FILE *arq;
        int resultado;
        // Abre o arquivo
        arq = fopen("arquivo.txt","w");
        if(arq == NULL){
            perror("Erro na abertura do arquivo");
            exit(1); //finaliza o programa
            }//if

        resultado = fputs(buffer.data, arq);// Escreve o texto do arquivo
        if (resultado == EOF) {
            perror("Erro na gravação do arquivo");
        }
         
            //salva nome dos atores
            serie[i].atores = buscaatores(buffer.data,&serie[i].quantAtores);       
            
            //salva enredo
            serie[i].enredo = buscaenredo(buffer.data);
            

            //salva rating
            serie[i].rating = buscarating(buffer.data);

            //salva ranking
            serie[i].ranking = buscaranking(buffer.data);

            /*for (int j = 0; j < serie[i].quantAtores; j++)
            {
                printf("\nnome: %s\n",serie[i].atores[j]); //printa atores
            }

            printf("\nEnredo: %s\n", serie[i].enredo); //printa enredo

            printf("\nnota: %.2f\n",serie[i].rating); //printa rating

            printf("\nTop %d no ranking de popularidade do imdB\n",serie[i].ranking); //printa ranking*/

            fclose(arq); //Fecha o arquivo

            //Liberar a memória alocada
            free(buffer.data);
    
    return 0;
}