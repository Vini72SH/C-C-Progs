#include "filtros.h"

int filtraIgual(char *s1, char *valor){
    if(strcmp(s1, "NaN") == 0){
        if(strcmp(valor, "NaN") == 0)
            return 1;
        return 0;
    }

    if(!(atoi(s1) && atoi(valor)))
        return (strcmp(s1, valor) == 0);

    return (atof(s1) == atof(valor));
}

int filtraMaior(char *s1, char *valor){
    if(strcmp(s1, "NaN") == 0)
        return 0;

    if(!(atoi(s1) && atoi(valor)))
        return (strcmp(s1, valor) > 0);

    return (atof(s1) > atof(valor));
}

int filtraMaiorIgual(char *s1, char *valor){
    if(strcmp(s1, "NaN") == 0)
        return 0;

    if(!(atoi(s1) && atoi(valor)))
        return (strcmp(s1, valor) >= 0);

    return (atof(s1) >= atof(valor));
}

int filtraMenorIgual(char *s1, char *valor){
    if(strcmp(s1, "NaN") == 0)
        return 1;

    if(!(atoi(s1) && atoi(valor)))
        return (strcmp(s1, valor) <= 0);

    return (atof(s1) <= atof(valor));
}

int filtraMenor(char *s1, char *valor){
    if(strcmp(s1, "NaN") == 0)
        return 1;

    if(!(atoi(s1) && atoi(valor)))
        return (strcmp(s1, valor) < 0);

    return (atof(s1) < atof(valor));
}

int filtraDiferente(char *s1, char *valor){
    if(strcmp(s1, "NaN") == 0){
        if(strcmp(valor, "NaN") == 0)
            return 0;
        return 1;
    }

    if(!(atoi(s1) && atoi(valor)))
        return (strcmp(s1, valor));

    return (atof(s1) != atof(valor));
}

OpFiltro retornaFiltro(char *fil){
    if(strcmp(fil, "==") == 0)
        return filtraIgual;
    else if(strcmp(fil, ">") == 0)
        return filtraMaior;
    else if(strcmp(fil, ">=") == 0)
        return filtraMaiorIgual;
    else if(strcmp(fil, "<=") == 0)
        return filtraMenorIgual;
    else if(strcmp(fil, "<") == 0)
        return filtraMenor;
    else if(strcmp(fil, "!=") == 0)
        return filtraDiferente;
    else
        printf("Filtro Inválido!\n");
    return NULL;
}