#include "trie.h"

char digito(char *string, short dig){
    return string[dig];
}

char *delimitaPalavra(char *string, int delim, int tam){
    int i;

    for(i = delim; i < tam; i++)
        string[i] = '\0';

    return string;
}

Trie criaNodo(char *fix){
    int i;
    Trie novoNodo;

    /* Alocação de Memória. */
    novoNodo = (Trie)malloc(sizeof(Nodo));
    if(!(novoNodo)) return NULL;

    /* Definição do Prefixo do Nodo. */
    novoNodo->prefix = strdup(fix);

    /* Inserção dos caractéres válidos. */
    for(i = 0; i < NUMCHARACTERS; i++){
        novoNodo->characters[i] = CHARS[i];
        novoNodo->prox[i] = NULL;
    }

    return novoNodo;
}

char* padronizaString(char* entrada)
{
    size_t tam, wctam;
    wchar_t *letra, *palavra;
    char *nova, *p;
    char *r, *w;
    const char idx[256] =    // mapeia [A-Z,0-9,tab] para [a-z,0-9,' ']
                            // e outros caracteres para '?' (63) 
        {
        0,   1,   2,   3,   4,   5,   6,   7,   8,  32,  10,  11,  12,  13,  14,  15,  // 000-015
        16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  // 016-031
        32,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  // 032-047
        48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  63,  63,  63,  63,  63,  63,  // 048-063
        63,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,  // 064-079
        112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122,  63,  63,  63,  63,  63,  // 080-095
        63,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,  // 096-111
        112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122,  63,  63,  63,  63, 127,  // 112-127
        63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  // 128-143
        63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  // 144-159
        63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  // 160-175
        63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  // 176-191
        97,  97,  97,  97,  97,  97,  97,  99, 101, 101, 101, 101, 105, 105, 105, 105,  // 192-207
        100, 110, 111, 111, 111, 111, 111, 120,  48, 117, 117, 117, 117, 121,  63,  63,  // 208-223
        97,  97,  97,  97,  97,  97,  97,  99, 101, 101, 101, 101, 105, 105, 105, 105,  // 224-239
        111, 110, 111, 111, 111, 111, 111,  63,  48, 117, 117, 117, 117, 121, 112, 121   // 240-255
        }; 

    tam = strlen(entrada);
    wctam = (tam + 1)*4;
    nova = (char*) malloc(tam+1);
    palavra = (wchar_t*) malloc(wctam); 
    mbstowcs(palavra, entrada, wctam);
    p = nova; letra = palavra;
    while (*letra != '\0')
        if(*letra >= 0 && *letra <= 255)
        *p++ = idx[*letra++];
        else{
        *p++ = 63;                     // coloca '?' nos caracteres fora do intervalo [0,255]
        letra++;
        }
    *p = '\0';
    free(palavra);

    /* remove espaços brancos consecutivos. String termina com '\n' ou '\0' */
    r = w = nova;
    while( *r == ' ' && *r!='\0' && *r!='\n') r++;
    while( *r != '\0' && *r!='\n'){
        *w++= *r++;
        if( *r == ' ' ){
        while( *r == ' ' ) r++;
        if( *r != '\0' && *r!= '\n' )
        *w++ = ' ';
        }
    }  
    *w = '\0';
    return nova;
}

char *removeInv(char *string){
    int i, j;

    for(i = 0; string[i] != '\0'; i++){
        if(string[i] == '?'){
            for(j = i; string[j + 1] != '\0'; j++){
                string[j] = string[j + 1];
            }
            string[j] = '\0';
            i--;
        }
    }

    return string;
}

void criaArv(Trie *raiz){
    *raiz = criaNodo("");
}

void freeArv(Trie raiz){
    if(raiz == NULL)
        return;

    /* Chamadas recursivas para liberar a árvore. */
    for(int i = 0; i < NUMCHARACTERS; i++){
        freeArv(raiz->prox[i]);
    }

    free(raiz->prefix);
    free(raiz);
}

Trie insereR(char *string, Trie raiz, short w){
    int i;
    char temp[2];
    char blank[LINESIZE];
    int dig = digito(string, w);
    
    /* Busca o caractér correspondente ao dígito. */
    for(i = 0; i < NUMCHARACTERS; i++)
        if(raiz->characters[i] == dig)
            break;

    /* Concatena o prefixo atual com a letra. */
    temp[0] = raiz->characters[i];
    temp[1] = '\0';
    strcpy(blank, raiz->prefix);
    strcat(blank, temp);

    /* Se o nodo não existe, cria o nodo com o prefixo. */
    if(!(raiz->prox[i]))
        raiz->prox[i] = criaNodo(blank);

    /* Se não é o fim da palavra, chama recursivamente 
     * para o próximo digíto. */
    if(dig != '\0')
        raiz->prox[i] = insereR(string, raiz->prox[i], w + 1);

    return raiz;
}

Trie insere(char *string, Trie raiz){
    char *padronizada;

    /* Padroniza a string com base nos caractéres. */
    padronizada = padronizaString(string);
    /* Chamada da insere recursiva. */
    raiz = insereR(padronizada, raiz, 0);
    /* Liberação de memória. */
    free(padronizada);

    return raiz;
}

Trie busca(Trie raiz, char *string, short dig){
    if(raiz == NULL)
        return NULL;
    if(strcmp(raiz->prefix, string) == 0)
        return raiz;

    for(int i = 0; i < NUMCHARACTERS; i++)
        if(raiz->characters[i] == digito(string, dig))
            return busca(raiz->prox[i], string, dig + 1);
    
    return NULL;
}


void insereLista(Trie raiz, lista *l){
    if(raiz == NULL)
        return;

    for(int i = 0; i < NUMCHARACTERS; i++){
        if(raiz->prox[i]){
            insereLista(raiz->prox[i], l);
            if(i == 0)
                insereL(l, raiz->prefix);
        }
    }
}

void imprimePrefix(Trie raiz, char *prefix){
    int i;

    if(raiz == NULL)
        return;

    /* Chamadas recursivas da função. */
    for(i = 0; i < NUMCHARACTERS; i++)
        imprimePrefix(raiz->prox[i], prefix);

    /* Ao encontrar o prefixo, imprime todas
     * as palavras com o prefixo. */
    if(strcmp(raiz->prefix, prefix) == 0)
        escreve(raiz);
}

void imprimeMaior(Trie raiz, char *prefix, short dig){
    if(raiz == NULL)
        return;

    int i, j;
    int valid = 0;

    /* Se "/0" tem um nodo válido, é o fim
     * de um prefixo do titulo indicado, */
    if(raiz->prox[0]) valid = 0;
    for(j = 1; j < NUMCHARACTERS; j++)
        if(raiz->prox[j]) valid = 1;

    /* Se não há mais nodos e se contém um prefixo, imprime
     * o maior prefixo do título indicado. */
    if(!(valid) && (strlen(raiz->prefix) <= strlen(prefix))){
        printf("%s\n", raiz->prefix);
        return;
    }
    
    /* Chama recursivamente para a próxima letra do título. */
    for(i = 0; i < NUMCHARACTERS; i++)
        if(raiz->characters[i] == digito(prefix, dig))
            imprimeMaior(raiz->prox[i], prefix, dig + 1);
}

void minCharacters(lista *l, char *token, int points){
    char *title;
    short valid;
    int tam_title, tam_token;
    struct nodo *aux, *nodoRem;

    aux = l->prime;
    tam_token = strlen(token);
    while(aux != NULL){
        title = aux->string;
        tam_title = strlen(title);

        valid = (tam_token + points <= tam_title)? 1 : 0; 
        
        aux = aux->prox;

        if(!(valid)){
            nodoRem = removeL(l, title);
            free(nodoRem);
        }
    }
}

void points_asteriskStart(lista *l, char *token, int points){
    int i, j;
    short valid;
    char *title;
    struct nodo *aux, *nodoRem;
    int tam_text, tam_token;

    aux = l->prime;
    tam_token = strlen(token);
    while (aux != NULL){
        valid = 1;
        title = aux->string;
        tam_text = strlen(title);

        if(tam_token <= tam_text){
            j = tam_text - 1 - points;
            for(i = tam_token - 1; i >= 0; i--){
                if(token[i] != title[j]){
                    valid = 0;
                    break;
                }
                j--;
            }
        }else
            valid = 0;

        aux = aux->prox;
        
        if(!(valid)){
            nodoRem = removeL(l, title);
            free(nodoRem);
        }        
    }
}

void onlyPoints(lista *l, char *token, int points){
    char *title;
    short valid;
    struct nodo *aux, *nodoRem;
    int i, tam_text, tam_token;

    aux = l->prime;
    tam_token = strlen(token);
    while(aux != NULL){
        i = 0;
        valid = 1;
        title = aux->string;
        tam_text = strlen(title);

        if(tam_token <= tam_text)
            for(i = 0; i < tam_token; i++){
                if(token[i] != title[i])
                    valid = 0;
            }
        else
            valid = 0;

        if(valid){
            if(tam_text >= tam_token + points){
                title = delimitaPalavra(title, tam_token + points, tam_text);
            }else
                valid = 0;
        }

        aux = aux->prox;
        
        if(!(valid)){
            nodoRem = removeL(l, title);
            free(nodoRem);
        }
    }
}

void asteriskEnd(lista *l, char *token){
    int i;
    short valid;
    char *title;
    struct nodo *aux, *nodoRem;
    int tam_text, tam_token;

    aux = l->prime;
    tam_token = strlen(token);
    while (aux != NULL){
        valid = 1;
        title = aux->string;
        tam_text = strlen(title);

        if(tam_token <= tam_text)
            for(i = 0; i < tam_token; i++){
                if(token[i] != title[i])
                    valid = 0;
            }
        else
            valid = 0;

        aux = aux->prox;
        
        if(!(valid)){
            nodoRem = removeL(l, title);
            free(nodoRem);
        }        
    }
}

void asterisksBetween(lista *l, char *token){
    short valid;
    char *title;
    struct nodo *aux, *nodoRem;
    int tam_text, tam_token;

    aux = l->prime;
    tam_token = strlen(token);
    while (aux != NULL){
        valid = 1;
        title = aux->string;
        tam_text = strlen(title);

        if(tam_token <= tam_text){
            if(!(strstr(title, token)))
                valid = 0; 
        }else
            valid = 0;

        aux = aux->prox;
        
        if(!(valid)){
            nodoRem = removeL(l, title);
            free(nodoRem);
        }        
    }
}

void asterisksStart(lista *l, char *token){
    int i, j;
    short valid;
    char *title;
    struct nodo *aux, *nodoRem;
    int tam_text, tam_token;

    aux = l->prime;
    tam_token = strlen(token);
    while (aux != NULL){
        valid = 1;
        title = aux->string;
        tam_text = strlen(title);

        if(tam_token <= tam_text){
            j = tam_text - 1;
            for(i = tam_token - 1; i >= 0; i--){
                if(token[i] != title[j]){
                    valid = 0;
                    break;
                }
                j--;
            }
        }else
            valid = 0;

        aux = aux->prox;
        
        if(!(valid)){
            nodoRem = removeL(l, title);
            free(nodoRem);
        }        
    }
}

void filtroTitulos(lista *l, char **commands, int tam){
    char *token_atual;
    int i, j, points, asterisks;

    for(i = 0; i < tam; i++){
        asterisks = 0;
        points = 0;
        token_atual = commands[i];
        if(token_atual[0] == '*')
            asterisks = -1;
        for(j = 1; token_atual[j] != '\0'; j++){
            if(token_atual[j] == '.') points++;
            if(token_atual[j] == '*') asterisks += 2;
        }

        token_atual = padronizaString(token_atual);
        token_atual = removeInv(token_atual);

        if((points != 0) && (asterisks == 2)){
            asteriskEnd(l, token_atual);
            minCharacters(l, token_atual, points);
        }
        else if((points != 0) && (asterisks == 1)){
            asterisksBetween(l, token_atual);
            minCharacters(l, token_atual, points);
        }
        else if((points != 0) && (asterisks == -1))
            points_asteriskStart(l, token_atual, points);
        else if((points != 0) && (asterisks == 0))
            onlyPoints(l, token_atual, points); 
        else if((asterisks) == 2)
            asteriskEnd(l, token_atual);
        else if((asterisks == 1))
            asterisksBetween(l, token_atual);
        else if((asterisks == -1) && (i == tam - 1))
            asterisksStart(l, token_atual);
        else if((asterisks == -1))
            asterisksBetween(l, token_atual);

        free(token_atual);
    }

    if(points || asterisks)
        imprimePalavras(l);
}

void functionUnity(Trie raiz, char *string){
    lista *l;
    int spaces, i;
    char *token;
    char **commands;
    char *padronizada;

    if(strlen(string) <= 1) return;

    /* Padronização da String */
    padronizada = padronizaString(string);
    if(padronizada[0] == 'p'){
        token = strtok(padronizada, " ");
        /* Coleta do prefixo. */
        token = strtok(NULL, "\n\0");
        /* Chamada da função. */
        imprimePrefix(raiz, token);
    }else if(padronizada[0] == 'l'){
        token = strtok(padronizada, " ");
        /* Coleta do título. */
        token = strtok(NULL, "\n\0");
        /* Busca pelo prefixo. 
         * Imprime o maior caso não encontre. */
        if(busca(raiz, token, 0)) printf("%s\n", token);
        else imprimeMaior(raiz, token, 0);
    }else if(padronizada[0] == 'c'){
        /* Criação da lista e inserção dos títulos. */
        l = criaLista();
        insereLista(raiz, l);
        /* Contagem dos tokens do comando. */
        spaces = 0;
        for(i = 0; i < strlen(string); i++)
            if(string[i] == ' ') spaces++;
        
        /* Criação do vetor. 
         * Inserção dos Tokens. */
        i = 0;
        commands = malloc(spaces * sizeof(char *));
        token = strtok(string, " ");
        token = strtok(NULL, " \n\0");
        while(token != NULL){
            commands[i] = token;
            token = strtok(NULL, " \n\0");
            i++;
        }

        filtroTitulos(l, commands, i);

        /* Liberação de Memória. */
        free(commands);
        l = destroiLista(l);
    }else{
        printf("Comando inválido!\n");
    }

    free(padronizada);
}

void escreve(Trie raiz){
    if(raiz == NULL)
        return;

    /* Percorre todos os nodos e escreve
     * os titulos ao encontrar o fim do mesmo. */
    for(int i = 0; i < NUMCHARACTERS; i++){
        if(raiz->prox[i]){
            escreve(raiz->prox[i]);
            if(i == 0)
                printf("%s\n", raiz->prefix);
        }
    }
}