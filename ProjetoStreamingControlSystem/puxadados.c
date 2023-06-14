#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h> //sudo apt install libcurl4-openssl-dev

#define MAX_URL_LENGTH 500

struct Buffer {
    char *data;
    size_t size;
};

typedef struct 
{
    char nome[41];
    char id[8];
    int ranking;
    float rating;//
    char **atores;//
    char *enredo;//

}Media;

char** buscaatores(const char *str)
{

    const char *ptr = str;
    int count = 0;

    //aloca a matriz de atores
    char **nome = (char **) malloc(21 * sizeof(char*));
    for (int l = 0; l < 21; l++){
        nome[l] = (char *) malloc(51 * sizeof(char));
    }// for

    while ((ptr = strstr(ptr, "sc-bfec09a1-1 fUguci")) != NULL) {
        int i;
        // ptr esta apontadno para "sc-bfec09a1-1 fUguci...", ent a gente pula 22 caracteres alem do ptr
        ptr += 22;


        for (i = 0; i < 999; i++)
        {
            if(ptr[i] == '<') break;

            //adiciona o caracter atual do nome na posição exata no vetor de nomes
            nome[count][i] = ptr[i];

        }

        //realoca o numero de caracteres do nome
        nome[count] = (char*) realloc (nome[count], i*sizeof(char));

        nome[count][i] = '\0';

        count++;
    }

    //realoca o a quantidade de atores baseado no contador de elementos no codigo html
    nome = (char **) realloc (nome, (count+1)*sizeof(char*));

    return nome;
}

float buscarating(const char *str)
{

    const char *ptr = str;
    float rating;

    while ((ptr = strstr(ptr, "sc-bde20123-1 iZlgcd")) != NULL) {
                               
        // ptr esta apontadno para "sc-bde20123-1 iZlgcd...", ent a gente pula 22 caracteres alem do ptr
        ptr += 22;

        rating = strtof (ptr,NULL);
        
    }

    return rating;
}

int buscaranking(const char *str)
{

    const char *ptr = str;
    int ranking;

    while ((ptr = strstr(ptr, "sc-5f7fb5b4-1 bhuIgW")) != NULL) {
                               
        // ptr esta apontadno para "sc-bde20123-1 iZlgcd...", ent a gente pula 22 caracteres alem do ptr
        ptr += 22;

        ranking = atoi (ptr);
        
    }

    return ranking;
}

char* buscaenredo(const char *str)
{

    const char *ptr = str;

    //aloca vetor do enredo
    char *enredo = (char*) malloc(500 * sizeof(char));
    int x;

    if ((ptr = strstr(ptr, "presentation")) != NULL) { //esta puxando errado pois a formatacao no html é diferente pro enredo

        ptr = strstr(ptr, "sc-2eb29e65-2 jBnwaA");
        int i;

        // ptr esta apontadno para "ipc-html-content-inner-div", ent a gente pula 22 caracteres alem do ptr
        ptr += 22;

        for (i = 0; i < 999; i++)
        {
            if(ptr[i] == '<') break;

            //adiciona o caracter atual do nome na posição exata no vetor de nomes
            enredo[i] = ptr[i];
    
        }

            enredo[i] = '\0';


            //realoca o numero de caracteres do nome
            enredo = (char*) realloc (enredo, i*sizeof(char));

    }

    return enredo;

}

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    size_t realsize = size * nmemb;
    struct Buffer *buffer = (struct Buffer *)userdata;

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

int extraiHTML() {
    
    CURL *curl;
    CURLcode res;
    struct Buffer buffer = {NULL, 0};
    Media serie;
    char url[MAX_URL_LENGTH];

    /*printf("define id:\n");
    fgets(serie.id, 8, stdin);
    serie.id[strcspn(serie.id,"\n")]='\0';
    setbuf(stdin, NULL);*/

    printf("Loading...\n");

    curl = curl_easy_init();//inicializa a lib curl

    if (curl) {

        //adiciona o id na url do imdb
        //snprintf(url, MAX_URL_LENGTH, "https://www.imdb.com/title/tt%s/", serie.id);
        snprintf(url, MAX_URL_LENGTH, "https://www.imdb.com/title/tt0460649/");

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
    }//for

    //salva nome dos atores
    serie.atores = buscaatores(buffer.data);
    
    //salva enredo
    serie.enredo = buscaenredo(buffer.data);

    //salva rating
    serie.rating = buscarating(buffer.data);

    //salva ranking
    serie.ranking = buscaranking(buffer.data);

    for (int i = 0; i < 18; i++)
    {
        printf("\nnome: %s\n",serie.atores[i]); //printa atores
    }  

    printf("\nEnredo: %s\n", serie.enredo); //printa enredo

    printf("\nnota: %.2f\n",serie.rating); //printa rating

    printf("\nTop %d no ranking de popularidade do imdB\n",serie.ranking); //printa ranking

    fclose(arq); //Fecha o arquivo

    // Liberar a memória alocada
    free(buffer.data);

    return 0;
}