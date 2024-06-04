#include "io.h"

arq_csv *abre(char *file_name){
    arq_csv *arquivo;

    /* Alocação de Memória. */
    arquivo = malloc(sizeof(arq_csv));
    if(!(arquivo)) return NULL;

    /* Abertura do arquivo. */    
    arquivo->arq = fopen(file_name, "r");
    if(!(arquivo->arq)){
        free(arquivo);
        perror("Erro ao abrir arquivo.\n");
        exit(1);
    }

    /* Chamada de verificação. */
    arquivo = verifica(arquivo);
    if(!(arquivo)) return NULL;

    return arquivo;
}

arq_csv *verifica(arq_csv *arquivo){
    lista *l;
    int i, j, k;
    struct nodo *aux;
    char *token, *prox;
    char line[LINESIZE + 1];

    l = criaLista();
    if(!(l)){
        printf("Não foi possível criar a lista.\n");
        return NULL;
    }

    j = 0;
    i = 0;

    /* Conta a quantidade de colunas. */
    fgets(line, LINESIZE, arquivo->arq);
    insereL(l, line, 0);
    token = strtok(line, ",");
    while(token != NULL){
        j++;
        token = strtok(NULL, ",");
    }

    /* Aloca a memória para os campos. */
    arquivo->fields = malloc(j * sizeof(char *));
    if(!(arquivo->fields)){
        printf("Não foi possível alocar memória para os campos.\n");
        free(l);
        return NULL;
    }   

    /* Copia a primeira linha e remove da lista. */
    aux = removeL(l);
    strcpy(line, aux->string);
    free(aux->string);
    free(aux);

    /* Insere no vetor os campos do arquivo CSV. */
    k = 0;
    token = strtok(line, ",");
    while(token != NULL){
        arquivo->fields[k] = strdup(token);
        token = strtok(NULL, ",\n");
        k++;
    }

    /* Inicializa o vetor de tipos com o tipo string. */
    arquivo->tipos = malloc(j * sizeof(char));
    if(!(arquivo->tipos)){
        free(l);
        libera_strings(arquivo->fields, j);
        free(arquivo->fields);
        printf("Não foi possível alocar memória para os tipos.\n");
        return NULL;
    }

    /* Define todos os tipos como string. */
    for(k = 0; k < j; k++) arquivo->tipos[k] = 'S';

    /* Percorre o arquivo, conta as linhas, insere na lista
     * e valida corretamente os tipos do arquivo. */
    while(fgets(line, LINESIZE, arquivo->arq) != NULL){
        insereL(l, line, i);
        i++;
        k = 0;
        prox = line;
        while(prox){
            token = prox;
            prox = separa(token);
            if(atof(token))
                arquivo->tipos[k] = 'N'; /* Corrige o tipo. */
            k++;
        }
    }

    arquivo->files = malloc(i * sizeof(char *));
    arquivo->aux_files = malloc(i * sizeof(int));

    if(!(arquivo->files) || !(arquivo->aux_files)){
        printf("Não foi possível alocar memória para os arquivos.\n");
        free(l);
        libera_strings(arquivo->fields, j);
        free(arquivo->fields);
        free(arquivo->tipos);
        if(arquivo->files) free(arquivo->files);
        if(arquivo->aux_files) free(arquivo->aux_files);
        return NULL;
    }

    /* Insere as linhas em um vetor, enquanto 
     * libera a memória ocupada pela lista. */
    for(k = 0; k < i; k++){
        aux = removeL(l);
        arquivo->files[k] = strdup(aux->string);
        arquivo->aux_files[k] = k;
        free(aux->string);
        free(aux);
    }

    /* Atribuição de valores. */
    arquivo->linhas = i;
    arquivo->colunas = j;
    arquivo->linhas_totais = i;

    l = destroiLista(l);

    return arquivo;
}

void sumario(arq_csv *arquivo){
    unsigned int i;

    printf("=== SUMÁRIO ===\n");

    for(i = 0; i < arquivo->colunas; i++){
        printf("%s [%c]\n", arquivo->fields[i], arquivo->tipos[i]);
    }

    printf("%ld variaveis encontradas\n", arquivo->colunas);
    printf("\nPressione ENTER para continuar\n");
    getchar();
}

char *formata(char *string, int *sizes){
    int i, tam;
    char vet[100] = "";
    char blank[LINESIZE];
    char *token, *prox, *nova;

    /* Inicializa o vetor em branco. */
    strcpy(blank, vet);
    i = 0;
    prox = string;
    /* Coleta os campos da string e os formata
     * adequadamente. Caso o campo esteja vazio
     * insere NaN no lugar do campo correspondente. */
    while(prox){
        token = prox;
        prox = separa(token);
        /* Verifica se o campo está vazio. */
        if(token[0] == '\n') token = "NaN\n";
        if(strlen(token) == 0) token = "  NaN";
        /* Calcula a quantidade de espaços. */
        tam = (sizes[i] - strlen(token) + 3);
        preenche_vetor(vet, tam, ' ');
        strcat(vet, token);
        strcat(blank, vet);
        i++;
    }
    
    /* Retorna a string formatada. */
    nova = strdup(blank);

    return nova;
}

void exibe(arq_csv *arquivo){

    imprime(arquivo->fields, arquivo->files, arquivo->aux_files, arquivo->linhas, arquivo->colunas);
    printf("\nPressione ENTER para continuar\n");
    getchar();
}

void imprime(char **fields, char **files, int *ind, int lin, int col){
    int i, j, qtd, spaces;
    int *sizes;
    char *token, *prox;
    char line[LINESIZE + 1];

    /* Alocação do vetor de tamanhos de palavras.
     * Define tamanho mínimo 3 para casos de NAN. */
    qtd = col;
    sizes = malloc(qtd * sizeof(int));
    if(!(sizes)) return;
    for(j = 0; j < qtd; j++){
        sizes[j] = (strlen(fields[j]) > 3)? strlen(fields[j]) : 3;
    }

    if(lin == 0){
        printf("Arquivo apenas com rôtulos\n");
        free(sizes);
        return;
    }

    /* Preenche o vetor com o tamanho das maiores palavras
     * das primeiras cinco linhas. */
    for(i = 0; i < lin && i < 10; i++){
        j = 0;
        strcpy(line, files[ind[i]]);
        prox = line;
        while(prox){
            token = prox;
            prox = separa(token);
            if(sizes[j] < strlen(token))
                sizes[j] = strlen(token);
            j++;
        }
    }

    /* Verifica o tamanho das palavras das últimas cinco
     * linhas e atualiza os tamanhos caso encontre maior. */
    if(lin > 10){
        for(i = 5; i > 0; i--){
            j = 0;
            strcpy(line, files[ind[lin - i]]);
            prox = line;
            while(prox){
                token = prox;
                prox = separa(token);
                if(sizes[j] < strlen(token))
                    sizes[j] = strlen(token);
                j++;
            }
        }
    }

    /* Insere espaços em branco na primeira linha. */
    spaces = conta_digitos(lin);
    cria_espacos(spaces);

    /* Gera a linha com os campos do arquivo CSV. */
    j = 1;
    strcpy(line, fields[0]);
    while(j < col){
        strcat(line, ",");
        strcat(line, fields[j]);
        j++;
    }
    strcat(line, "\n");

    /* Formata a linha e a imprime. */
    token = formata(line, sizes);
    printf("%s", token);
    free(token);

    /* Coleta as primeiras linhas do arquivo
     * e as imprime formatadas. */
    if(lin <= 10){
        for(i = 0; i < lin; i++){
            strcpy(line, files[ind[i]]);
            token = formata(line, sizes);
            printf("%d", ind[i]);
            cria_espacos(spaces - conta_digitos(ind[i]));
            printf("%s", token);
            free(token);
        }
    }

    /* Imprime as primeiras cinco linhas formatadas. */
    if(lin > 10){
        for(i = 0; i < 5; i++){
            strcpy(line, files[ind[i]]);
            token = formata(line, sizes);
            printf("%d", ind[i]);
            cria_espacos(spaces - conta_digitos(ind[i]));
            printf("%s", token);
            free(token);
        }

        /* Cria a linha intermediária entre as linhas. */
        printf("...");
        cria_espacos(spaces - 3);
        strcpy(line, "...");
        for(j = 1; j < col; j++){
            strcat(line, ",");
            strcat(line, "...");
        }
        strcat(line, "\n");

        /* Formata a linha de forma adequada. */
        token = formata(line, sizes);
        printf("%s", token);
        free(token);

        /* Imprime as últimas linhas do arquivo. */
        for(i = lin - 5; i < lin; i++){
            strcpy(line, files[ind[i]]);
            token = formata(line, sizes);
            printf("%d", ind[i]);
            cria_espacos(spaces - conta_digitos(ind[i]));
            printf("%s", token);
            free(token);
        }
    }

    free(sizes);

    printf("\n[%d rows x %d columns]\n", lin, col);

}

void filtro(arq_csv *arq, int indice, OpFiltro filtrador, char *valor){
    char line[LINESIZE + 1];
    char *token, *campo_atual;
    int i, cont, *linhas_filtradas, tam, salvou;

    /* Alocação de Memória. */
    linhas_filtradas = malloc(arq->linhas * sizeof(int));
    if(!(linhas_filtradas)){
        printf("Não foi possível alocar o vetor de linhas.\n");
        return;
    }

    /* Percorre todas as linhas e coleta os campos. */
    tam = 0;
    for(i = 0; i < arq->linhas; i++){
        cont = 0;
        strcpy(line, arq->files[arq->aux_files[i]]);
        token = line;
        while(cont <= indice){
            campo_atual = token;
            token = separa(campo_atual);
            cont++;
        }
        /* Se o campo for vazio, insere NaN para comparações. */
        if((strlen(campo_atual) == 0) || campo_atual[0] == '\n')
            campo_atual = "NaN"; 
        token = strtok(campo_atual, "\n");
        /* Insere o índice da linha no vetor caso filtrador retorne 1. */
        if(filtrador(token, valor)){
            linhas_filtradas[tam] = arq->aux_files[i];
            tam++;
        }
    }

    imprime(arq->fields, arq->files, linhas_filtradas, tam, arq->colunas);
    printf("\n");

    salvou = salvar_arq(arq, linhas_filtradas, tam);

    if(!(salvou)) free(linhas_filtradas);
}

void unidade_de_filtro(arq_csv *arquivo){
    int ind_campo;
    OpFiltro ptrFiltro;
    char coluna[100], valor[100], fil[5];

    printf("Entre com a variavel: ");
    scanf("%s", coluna);

    /* Busca o campo inserido pelo usuário. */
    ind_campo = 0;
    while(ind_campo < arquivo->colunas){
        if(strcmp(coluna, arquivo->fields[ind_campo]) == 0){
            break;
        }
        ind_campo++;
    }

    /* Validação do campo. */
    if(ind_campo == arquivo->colunas){
        printf("Variável inválida.\n\n");
        return;
    }

    printf("Escolha um filtro ( == > >= <= < != ): ");
    scanf("%s", fil);

    /* Validação do filtro. */
    ptrFiltro = retornaFiltro(fil);
    if(ptrFiltro == NULL){
        printf("Filtro inválido.\n\n");
        return;
    }

    printf("Digite um valor: ");
    scanf(" %[^\n]", valor);

    /* Chamada da função principal de filtro. */
    filtro(arquivo, ind_campo, ptrFiltro, valor);

    printf("\nPressione ENTER para continuar\n");
    getchar();
    getchar();
}

void vetor_info(char **v, int tam, int *ind, char type){
    int i, qtd, temp, cont;
    char *moda, *atual, **unicos;
    double media, desvio, valor;

    /* Alocação de Memória. */
    unicos = malloc(tam * sizeof(char *));
    if(!(unicos)){
        printf("Não foi possível alocar memória para o vetor de únicos.\n");
        return;
    }

    /* Coleta as informações correspondentes quando a coluna
     * é de valores string. */
    if(type == 'S'){
        moda = v[ind[0]];
        qtd = 1;
        atual = v[ind[0]];
        temp = 0;
        cont = 0;
        /* Calcula a moda salvando o valor
         * que mais aparece e comparando com o anterior. */
        for(i = 0; i < tam; i++){
            if(strcmp(atual, v[ind[i]]) == 0){
                temp++;
            }else{
                if(qtd < temp){
                    moda = atual;
                    qtd = temp;
                }
                if(temp >= 1){
                    unicos[cont] = atual;
                    cont++;
                }

                atual = v[ind[i]];
                temp = 1;
            }
        }

        if(qtd < temp){
            moda = atual;
            qtd = temp;
        }

        if(temp >= 1){
            unicos[cont] = atual;
            cont++;
        }

        /* Impressão dos dados. */
        printf("Contador: %d\n", tam);
        printf("Moda: %s %d\n", moda, qtd);
        printf("Valores unicos: [");
        if(cont > 0){
            for(i = 0; i < cont - 1; i++) printf("'%s', ", unicos[i]);
            printf("'%s']\n", unicos[i]);
        }else{
            printf(" Nenhum valor unico ]\n");
        }
    }else{
        /* Coleta as informações correspondentes quando a coluna
         * contém valores númericos. */
        moda = v[ind[0]];
        qtd = 1;
        atual = v[ind[0]];
        temp = 0;
        cont = 0;
        media = 0;
        desvio = 0;
        /* Calcula a moda salvando o valor
         * que mais aparece e comparando com o anterior. */
        for(i = 0; i < tam; i++){
            valor = atof(v[ind[i]]);
            media = media + valor;
            desvio = desvio + valor * valor;
            if(atof(atual) == valor){
                temp++;
            }else{
                if(qtd < temp){
                    moda = atual;
                    qtd = temp;
                }
                if(temp >= 1){
                    unicos[cont] = atual;
                    cont++;
                }

                atual = v[ind[i]];
                temp = 1;
            }
        }

        if(temp >= 1){
            unicos[cont] = atual;
            cont++;
        }
        media = media / tam;
        desvio = (desvio - tam * media * media)/tam;
        desvio = sqrt(desvio);

        /* Impressão dos dados. */
        printf("Contador: %d\n", tam);
        printf("Media: %.2f\n", media);
        printf("Desvio: %.2f\n", desvio);
        printf("Mediana: %s\n", v[ind[(tam-1)/2]]);
        printf("Moda: %s %d vezes\n", moda, qtd);
        printf("Min.: %s\n", v[ind[0]]);
        printf("Max.: %s\n", v[ind[tam - 1]]);
        printf("Valores unicos: [");
        if(cont > 0){
            for(i = 0; i < cont - 1; i++) printf("'%s', ", unicos[i]);
            printf("'%s']\n", unicos[i]);
        }else{
            printf(" Nenhum valor unico ]\n");
        }
    }

    free(unicos);
}

void descricao(char *col_selec, arq_csv *arq){
    int i, cont, tam;
    int ind_campo, *aux;
    char *token;
    char *campo_atual;
    char **coluna;
    char line[LINESIZE + 1];

    /*  Validação do Campo inserido pelo usuário  */
    ind_campo = 0;
    while(ind_campo < arq->colunas){
        if(strcmp(col_selec, arq->fields[ind_campo]) == 0){
            break;
        }
        ind_campo++;
    }

    if(ind_campo == arq->colunas){
        printf("Variavel inválida.\n\n");
        return;
    }

    /* Alocação de Memória. */
    coluna = malloc(arq->linhas * sizeof(char *));
    aux = malloc(arq->linhas * sizeof(int));

    if(!(aux) || !(coluna)){
        printf("Não foi possível alocar memória para os vetores.\n");
        if(aux) free(aux);
        if(coluna) free(coluna);
        return;
    }

    tam = 0;
    /* Coleta cada palavra da coluna e insere no vetor. */
    for(i = 0; i < arq->linhas; i++){
        cont = 0;
        strcpy(line, arq->files[arq->aux_files[i]]);
        token = line;
        while(cont <= ind_campo){
            campo_atual = token;
            token = separa(campo_atual);
            cont++;
        }
        /* Insere apenas os valores válidos da coluna no vetor. */
        if((strlen(campo_atual) > 0) && (campo_atual[0] != '\n')){
            token = strtok(campo_atual, "\n");
            coluna[tam] = strdup(token);
            aux[tam] = tam;
            tam++;
        }
    }

    /* Ordenação dos dados. */
    Merge_Sort(coluna, 0, tam-1, aux);

    /* Chamada para imprimir as estatísticas. */
    vetor_info(coluna, tam, aux, arq->tipos[ind_campo]);

    /* Liberação de Memória. */
    libera_strings(coluna, tam);

    free(aux);
    free(coluna);

    printf("\nPressione ENTER para continuar\n");
    getchar();
    getchar();    
}

void ordenacao(char *col_selec, arq_csv *arq){
    int salvou;
    int i, cont, tam;
    int ind_campo;
    int *novo_aux;
    char type[10];
    char line[LINESIZE + 1];
    char *token, *campo_atual, **coluna;

    /* Verificação do campo. */
    ind_campo = 0;
    while(ind_campo < arq->colunas){
        if(strcmp(col_selec, arq->fields[ind_campo]) == 0){
            break;
        }
        ind_campo++;
    }

    if(ind_campo == arq->colunas){
        printf("Variavel inválida!\n\n");
        return; 
    }

    printf("Selecione uma opcao [A]scendente ou [D]ecrescente: ");
    scanf("%s", type);

    /* Verificação da opção. */
    if(strcmp(type, "A") && (strcmp(type, "D"))){
        printf("Opção inválida.\n\n");
        return;
    }

    /* Alocação de Memória. */
    coluna = malloc(arq->linhas_totais * sizeof(char *));
    novo_aux = malloc(arq->linhas * sizeof(int));

    if(!(coluna) || !(novo_aux)){
        printf("Não foi possível alocar memória para os vetores\n");
        if(coluna) free(coluna);
        if(novo_aux) free(novo_aux);
        return;
    }

    /* Percorre as linhas armazenando as palavras da coluna. */
    tam = 0;
    for(i = 0; i < arq->linhas_totais; i++){
        cont = 0;
        strcpy(line, arq->files[i]);
        token = line;
        while(cont <= ind_campo){
            campo_atual = token;
            token = separa(campo_atual);
            cont++;
        }
        /* Se o campo estiver vazio, preenche com NaN para comparações. */
        if((strlen(campo_atual) > 0) && (campo_atual[0] != '\n')){
            token = strtok(campo_atual, "\n");
        }else{
            token = "NaN";
        }
        coluna[tam] = strdup(token);
        tam++;
    }

    /* Transposição do aux_files para um auxiliar. */
    for(i = 0; i < arq->linhas; i++)
        novo_aux[i] = arq->aux_files[i];

    /* Ordena as colunas baseadas no vetor auxiliar. */
    Merge_Sort(coluna, 0, arq->linhas - 1, novo_aux);
    imprime(arq->fields, arq->files, novo_aux, arq->linhas, arq->colunas);
    printf("\n");

    salvou = salvar_arq(arq, novo_aux, arq->linhas);

    if(!(salvou)) free(novo_aux);

    libera_strings(coluna, tam);

    free(coluna);

    printf("\nPressione ENTER para continuar\n");
    getchar();
    getchar();
}

void selecao(char *variaveis, arq_csv *arq){
    short *priori;
    int ind, i, j, k, *new_ind;
    char empty[] = "";
    char *token, *prox, **words;
    char info[100];
    char line[LINESIZE + 1];
    char blank[LINESIZE + 1];
    char **colunas_selecionadas, **campos;

    /* Alocações de memória. */
    priori = malloc(arq->colunas * sizeof(short));
    words = malloc(arq->colunas * sizeof(char *));
    campos = malloc(arq->colunas * sizeof(char *));
    colunas_selecionadas = malloc(arq->linhas * sizeof(char *));
    new_ind = malloc(arq->linhas * sizeof(int));

    if(!(priori) || !(words) || !(campos) || !(colunas_selecionadas) || !(new_ind)){
        printf("Não foi possível alocar memória para os vetores de seleção.\n");
        if(priori) free(priori);
        if(words) free(words);
        if(campos) free(campos);
        if(colunas_selecionadas) free(colunas_selecionadas);
        if(new_ind) free(new_ind);

        return;
    }

    /* Lógica para definir prioridade de selecao
     * baseado na ordem de colunas inserida pelo usuário. */
    ind = 0;
    token = strtok(variaveis, " \n");
    while(token != NULL){
        i = 0;
        while(i < arq->colunas){
            if(strcmp(token, arq->fields[i]) == 0){
                campos[ind] = strdup(arq->fields[i]);
                priori[ind] = i;
                ind++;
            }
            i++;
        }
        token = strtok(NULL, " \n");
    }

    /* Percorre todas as linhas, montando as linhas 
     * de acordo com a ordem informada em seleção. 
     * E seguindo a prioridade de argumentos. */
    for(i = 0; i < arq->linhas; i++){
        j = 0;
        strcpy(blank, empty);
        strcpy(line, arq->files[arq->aux_files[i]]);
        line[strlen(line) - 1] = '\0';
        prox = line;
        /* Insere as palavras no vetor. */
        while(prox){
            token = prox;
            prox = separa(token);
            words[j] = strdup(token);
            j++;
        }

        /* Monta a linha com as palavras do vetor. */
        for(k = 0; k < ind; k++){
            strcat(blank, words[priori[k]]);
            strcat(blank, ",");
        }
        blank[strlen(blank) - 1] = '\n';

        libera_strings(words, arq->colunas);

        /* Preenche um vetor com as linhas contendo
         * as colunas selecionadas. */
        colunas_selecionadas[i] = strdup(blank);
        new_ind[i] = i;
    }

    printf("\n");
    imprime(campos, colunas_selecionadas, new_ind, arq->linhas, ind);

    printf("\nDeseja gravar um arquivo com as variáveis selecionadas? [S|N]: ");
    scanf("%s", info);

    if(strcmp(info, "S") == 0){
        printf("Entre com o nome do arquivo: ");
        scanf("%s", info);
        if(gera_arquivo(info, campos, colunas_selecionadas, new_ind, arq->linhas, ind))
            printf("Arquivo gravado com sucesso\n");
    }else{
        if(strcmp(info, "N"))
            printf("Opção inválida.\n");
    }
    printf("\n");

    /* Liberação de Memória. */
    libera_strings(campos, ind);
    libera_strings(colunas_selecionadas, arq->linhas);

    free(words);
    free(priori);
    free(campos);
    free(new_ind);
    free(colunas_selecionadas);

    printf("Pressione ENTER para continuar\n");
    getchar();
    getchar();
}

void dados_faltantes(arq_csv *arq){
    int salvou;
    double_media *medias;
    int *linhas_invalidas;
    int tam, temp, op, new;

    /* Alocação de Memória. */
    salvou = 0;
    linhas_invalidas = malloc(arq->linhas * sizeof(int));
    medias = malloc(arq->colunas * sizeof(double_media));

    if(!(linhas_invalidas) || !(medias)){
        printf("Não foi possível alocar os vetores para os dados faltantes\n");
        if(linhas_invalidas) free(linhas_invalidas);
        if(medias) free(medias);
        return;
    }

    tam = procura_dados(arq, linhas_invalidas, medias);

    /* Repetição de opções até sair da função. */
    do{
        printf("1) Listar registros com NaN\n");
        printf("2) Substituir pela media\n");
        printf("3) Substituir pelo proximo valor valido\n");
        printf("4) Remover registros com NaN\n");
        printf("5) Voltar ao menu principal\n");
        printf("Selecione a opcao: ");
        scanf("%d", &op);
        printf("\n");

        switch(op){
            case 1:
                tam = procura_dados(arq, linhas_invalidas, medias);
                imprime(arq->fields, arq->files, linhas_invalidas, tam, arq->colunas);
                printf("\n");
                salvou = salvar_arq(arq, linhas_invalidas, tam);
                break;
            case 2:
                substituir_media(arq->files, arq->tipos, linhas_invalidas, medias, tam, arq->colunas);
                break;
            case 3:
                temp = tam;
                /* Descarta a última linha do vetor, caso seja inválida. */
                if(linhas_invalidas[temp - 1] == arq->aux_files[arq->linhas - 1]) temp--;
                substituir_valor(arq->files, linhas_invalidas, temp, arq->colunas);
                break;
            case 4:
                new = remove_invalidos(arq->aux_files, arq->files, arq->fields, linhas_invalidas, arq->linhas, tam, arq->colunas);
                if(new >= 0) arq->linhas = new;
                break;
            case 5:
                break;
            default:
                printf("Selecione uma opção válida.\n");
        }
    }while(op != 5);

    /* Liberação de Memória. */
    if(!(salvou)) free(linhas_invalidas);
    free(medias);
}

int procura_dados(arq_csv *arq, int *invalidas, double_media *medias){
    int tam;
    char line[LINESIZE + 1];
    char *token, *campo_atual;
    int i, j, ind_campo, invalid;

    /* Inicialização das médias. */
    for(j = 0; j < arq->colunas; j++){
        medias[j].qtd = 0;
        medias[j].soma = 0;
    }

    /* Percorre as linhas do arquivo. */
    tam = 0;
    for(i = 0; i < arq->linhas; i++){
        invalid = 0;
        ind_campo = 0;
        strcpy(line, arq->files[arq->aux_files[i]]);
        token = line;
        while(token){
            campo_atual = token;
            token = separa(campo_atual);
            /* Se o campo é inválido, o define como NaN. */
            /* Se for válido e númerico, soma o campo para calcular média. */
            if((strlen(campo_atual) == 0) || campo_atual[0] == '\n'){
                campo_atual = "NaN";
                invalid = 1;
            }else{
                if(arq->tipos[ind_campo] == 'N'){
                    medias[ind_campo].qtd++;
                    medias[ind_campo].soma += atof(campo_atual);
                }
            }
            ind_campo++;
        }
        /* Preenche o vetor de indíces de linhas inválidas. */
        if(invalid){
            invalidas[tam] = arq->aux_files[i];
            tam++;
        }
    }

    /* Divide a soma pela quantidade de elementos. */
    for(j = 0; j < arq->colunas; j++){
        medias[j].soma = medias[j].soma / medias[j].qtd;
    }

    return tam;
}

void substituir_media(char **files, char *tipos, int *invalidas, double_media *medias, int lin, int col){
    int i, ind_campo;
    char number[100];
    char line[LINESIZE + 1];
    char blank[LINESIZE + 1];
    char *token, *campo, empty[] = "";

    /* Percorre as linhas. */
    for(i = 0; i < lin; i++){
        ind_campo = 0;
        strcpy(blank, empty);
        strcpy(line, files[invalidas[i]]);
        line[strlen(line) - 1] = '\0';
        token = line;
        while(token){
            campo = token;
            token = separa(campo);
            /* Se o campo for inválido e númerico, insere sua média. */
            if((strlen(campo) == 0) || (campo[0] == '\n')){
                if(tipos[ind_campo] == 'N'){
                    sprintf(number, "%.2f", medias[ind_campo].soma);
                    campo = number;
                }
            }
            /* Monta as nova linha válida. */
            strcat(blank, campo);
            strcat(blank, ",");
            ind_campo++;
        }
        /* Insere a linha válida no arquivo e
         * libera a linha inválida anterior. */
        blank[strlen(blank) - 1] = '\n';
        free(files[invalidas[i]]);
        files[invalidas[i]] = strdup(blank);
    }
}

void substituir_valor(char **files, int *invalidas, int lin, int col){
    int i, j, ind_campo;
    char **words;
    char line[LINESIZE + 1];
    char prox[LINESIZE + 1];
    char blank[LINESIZE + 1];
    char *token, *campo, empty[] = "";

    /* Alocação de Memória. */
    words = malloc(col * sizeof(char *));
    if(!(words)){
        printf("Não foi possível alocar memória para o vetor de palavras\n");
        return;
    }

    /* Inicializa as palavras com NULL. */
    for(j = 0; j < col; j++) words[j] = NULL;

    /* Percorre o vetor ao contrário. */
    for(i = lin - 1; i >= 0; i--){
        ind_campo = 0;
        strcpy(blank, empty);
        strcpy(line, files[invalidas[i]]);
        strcpy(prox, files[invalidas[i] + 1]);
        cria_vetor(words, col, prox);
        /* Insere as palavras da próxima linha no vetor. */
        line[strlen(line) - 1] = '\0';
        prox[strlen(prox) - 1] = '\0';
        token = line;
        while(token){
            campo = token;
            token = separa(campo);
            /* Se o campo for vazio, atravês do índice
             * insere o próximo valor válido. */
            if((strlen(campo) == 0) || (campo[0] == '\n')){
                campo = words[ind_campo];
            }
            /* Monta a nova linha válida. */
            strcat(blank, campo);
            strcat(blank, ",");
            ind_campo++;
        }
        /* Insere no vetor de linhas principal. */
        libera_strings(words, col);
        blank[strlen(blank) - 1] = '\n';
        free(files[invalidas[i]]);
        files[invalidas[i]] = strdup(blank);
    }
    free(words);
}

int remove_invalidos(int *indices, char **files, char **fields, int *invalidos, int tamInd, int tamInv, int col){
    short rem;
    int op, i, j;
    int *priori, ind_campo;
    int novo_tam, *novos_validos;
    char variaveis[LINESIZE + 1];
    char line[LINESIZE + 1], *token, *campo;

    printf("1) Todas as linhas inválidas.\n");
    printf("2) Selecionar colunas para remoção.\n");
    printf("Selecione sua opção: ");
    scanf("%d", &op);
    printf("\n");

    /* Validação da opção. */
    if(op <= 0 || op >= 3){
        printf("Opção inválida.\n\n");
        return -1;
    }

    /* Alocação de Memória. */
    priori = malloc(col * sizeof(int));
    if(!(priori)){
        printf("Não foi possível alocar memória para o vetor de prioridades\n");
        return -1;
    }

    /* Inicializa todas as prioridades com zero. */
    for(j = 0; j < col; j++) priori[j] = 0;

    /* Prioridade máxima na remoção de linhas. */
    if(op == 1)
        for(j = 0; j < col; j++) priori[j] = 1;

    /* Verificação das colunas selecionadas. */
    if(op == 2){
        printf("Selecione as colunas (separadas por espaços): ");
        scanf(" %[^\n]", variaveis);
        token = strtok(variaveis, " \n");
        while(token){
            j = 0;
            while(j < col){
                if(strcmp(token, fields[j]) == 0)
                    priori[j] = 1;
                j++;
            }
            token = strtok(NULL, " \n");
        }
    }

    novos_validos = malloc(tamInd * sizeof(int));
    if(!(novos_validos)){
        printf("Não foi possível alocar memória para o vetor de válidos\n");
        free(priori);
        return -1;
    }

    /* Percorre o vetor auxiliar de índices. */
    j = 0;
    novo_tam = 0;
    for(i = 0; i < tamInd; i++){
        if(indices[i] == invalidos[j]){
            rem = 0;
            ind_campo = 0;
            strcpy(line, files[invalidos[j]]);
            line[strlen(line) - 1] = '\0';
            token = line;
            while(token){
                campo = token;
                token = separa(campo);
                /* Se o campo estiver no vetor de prioridades
                 * marca a linha para remoção */
                if(strlen(campo) == 0 || campo[0] == '\n'){
                    if(priori[ind_campo] == 1){
                        rem = 1;
                    }
                }
                ind_campo++;
            }
            /* Se rem == 0, insere o índice da linha no vetor. */
            if(!(rem)){
                novos_validos[novo_tam] = indices[i];
                novo_tam++;
            }
            j++;
        }else{
            /* Sempre insere os campos válidos. */
            novos_validos[novo_tam] = indices[i];
            novo_tam++;
        }
    }

    /* Transfere os novos índices para o vetor. */
    for(i = 0; i < novo_tam; i++)
        indices[i] = novos_validos[i];

    free(priori);
    free(novos_validos);

    /* Retorna o novo tamanho do vetor auxiliar. */
    return novo_tam;
}

void salvar_dados(char *file_name, arq_csv *arquivo){

    if(gera_arquivo(file_name, arquivo->fields, arquivo->files, arquivo->aux_files, arquivo->linhas, arquivo->colunas)){
        printf("\nArquivo gravado com sucesso!\n");
    }else{
        printf("\nFalha ao gravar arquivo!\n");
    }
    printf("\nPressione ENTER para continuar\n");
    getchar();
    getchar();
}

int salvar_arq(arq_csv *arq, int *aux, int tam){
    char info[10];
    char file_name[LINESIZE + 1];

    printf("Deseja gravar um arquivo com os dados filtrados/ordenados? [S|N]: ");
    scanf("%s", info);

    /* Verifica se a opção inserida é válida. */
    if(strcmp(info, "S") == 0){
        printf("Entre com o nome do arquivo: ");
        scanf("%s", file_name);
        if(gera_arquivo(file_name, arq->fields, arq->files, aux, tam, arq->colunas)){
            printf("Arquivo gravado com sucesso.\n");
        }
    }else{
        if(strcmp(info, "N"))
        printf("Opção inválida.\n");
    }

    printf("Deseja descartar os dados originais? [S|N]: ");
    scanf("%s", info);

    /* Verifica se a opção inserida é válida. */
    if(strcmp(info, "S") == 0){
        free(arq->aux_files);
        arq->aux_files = aux;
        arq->linhas = tam;

        return 1;
    }else{
        if(strcmp(info,"N"))
            printf("Opção inválida.\n");
        return 0;
    }
}

int gera_arquivo(char *file_name, char **fields, char **files, int *ind, int lin, int col){
    int i;
    FILE *novo_arquivo;

    /* Cria o novo arquivo. */
    novo_arquivo = fopen(file_name, "w");
    if(!(novo_arquivo)){
        perror("Erro ao criar arquivo.\n");
        return 0;
    }

    /* Insere os campos do arquivo. */
    fputs(fields[0], novo_arquivo);
    for(i = 1; i < col; i++){
        fputs(",", novo_arquivo);
        fputs(fields[i], novo_arquivo);
    }
    fputs("\n\0", novo_arquivo);

    /*Insere as linhas no arquivo. */
    for(i = 0; i < lin; i++){
        fputs(files[ind[i]], novo_arquivo);
    }

    fclose(novo_arquivo);

    return 1;

}

arq_csv *fecha(arq_csv *arquivo){

    fclose(arquivo->arq);

    libera_strings(arquivo->files, arquivo->linhas_totais);
    libera_strings(arquivo->fields, arquivo->colunas);

    free(arquivo->aux_files);
    free(arquivo->files);
    free(arquivo->fields);
    free(arquivo->tipos);
    free(arquivo);

    return NULL;
}