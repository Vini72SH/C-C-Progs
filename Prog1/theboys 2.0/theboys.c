#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "conjunto.h"
#include "fila.h"
#include "lef.h"

#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000 
#define N_HABILIDADES 10
#define N_HEROIS N_HABILIDADES * 5
#define N_BASES N_HEROIS / 6
#define N_MISSOES T_FIM_DO_MUNDO / 100

struct local{
    int x;
    int y;
};

struct Heroi{
    int ID; /*Identificador do Herói.*/
    int pac; /*Indica a Paciência do Herói.*/
    int velocidade; /*Velocidade de Deslocamento.*/
    int exp; /*Experiência do Herói.*/
    int base; /*Indica a base atual.*/
    struct local baseAtual; /*Coordenadas da base atual.*/
    struct conjunto *habilidades; /*Conjunto de Habilidades.*/
};

struct Base{
    int ID; /*Identificador da Base.*/
    int max; /*N° Max de Heróis.*/
    struct local coord; /*Localização da base.*/
    struct fila *fila; /*Fila de Espera.*/
    struct conjunto *herois; /*Herois presentes.*/
};

struct Missao{
    int ID; /*Identificador da Missão.*/
    struct local coord; /*Local da Missão.*/
    struct conjunto *requisitos; /*Conjunto de Requisitos.*/
};

struct Mundo{
    int NHerois; /*N° de Heróis.*/
    int NBases; /*N° de Bases.*/
    int NMissoes; /*N° de Missões.*/
    int NHabilidades; /*N° de Habilidades.*/
    int Msucesso; /*N° de Missões bem-sucedidas.*/
    int Mtentativas; /*N° de tentativas de missões.*/
    int tamanho; /*Tamanho do Mundo.*/
    int clock; /*Tempo do Mundo.*/
    struct lef_t *lef; /*Lista de Eventos Futuros.*/
    struct Base *Bases; /*Vetor de Bases.*/
    struct Heroi *Herois; /*Vetor de Heróis.*/
    struct Missao *Missoes; /*Vetor de Missões.*/
};

/*Devolve um número aleatório entre min e max, inclusive.*/
int aleat(int min, int max){
    int i;
    i = max - min + 1;

    return (rand() % i + min);
}

/*Devolve a distãncia entre dois pontos.*/
int dist(struct local a, struct local b){

    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

/*Preenche o vetor de habilidades.*/
void preenche_hab(struct conjunto *c){
    int i;

    if(c != NULL){
        for(i = 0; i < c->max; i++){
            insere_cjt(c, aleat(0, N_HABILIDADES-1));
        }
    }
}

/*Cria um novo herói.*/
struct Heroi cria_Heroi(int ID){
    struct Heroi novo_heroi;

    novo_heroi.ID = ID;
    novo_heroi.pac = aleat(0, 100);
    novo_heroi.velocidade = aleat(50, 5000);
    novo_heroi.exp = 0;
    novo_heroi.habilidades = cria_cjt(aleat(1, 3));
    preenche_hab(novo_heroi.habilidades);

    return novo_heroi;
}

/*Cria uma nova base.*/
struct Base cria_Base(int ID){
    struct Base nova_base;

    nova_base.ID = ID;
    nova_base.max = aleat(3, 10);
    nova_base.coord.x = aleat(0, N_TAMANHO_MUNDO-1);
    nova_base.coord.y = aleat(0, N_TAMANHO_MUNDO-1);
    nova_base.fila = fila_cria();
    nova_base.herois = cria_cjt(nova_base.max);

    return nova_base;
}

/*Cria uma nova missão.*/
struct Missao cria_Missao(int ID){
    struct Missao nova_missao;

    nova_missao.ID = ID;
    nova_missao.coord.x = aleat(0, N_TAMANHO_MUNDO-1);
    nova_missao.coord.y = aleat(0, N_TAMANHO_MUNDO-1);
    nova_missao.requisitos = cria_cjt(aleat(6, 10));
    preenche_hab(nova_missao.requisitos);

    return nova_missao;
}

/*Insere os herois, bases e missoes nos
 respectivos vetores do mundo.*/
void insere_elementos(struct Mundo m){
    int i;

    for(i = 0; i < m.NHerois; i++){
        m.Herois[i] = cria_Heroi(i);
    }

    for(i = 0; i < m.NBases; i++){
        m.Bases[i] = cria_Base(i);
    }

    for(i = 0; i < m.NMissoes; i++){
        m.Missoes[i] = cria_Missao(i);
    }
}

/*Inicializa todas as entidades do mundo.*/
struct Mundo cria_Mundo(){
    struct Mundo novo_mundo;

    novo_mundo.NHerois = N_HEROIS;
    novo_mundo.NBases = N_BASES;
    novo_mundo.NMissoes = N_MISSOES;
    novo_mundo.NHabilidades = N_HABILIDADES;
    novo_mundo.tamanho = N_TAMANHO_MUNDO;
    novo_mundo.Msucesso = 0;
    novo_mundo.Mtentativas = 0;
    novo_mundo.clock = T_INICIO;
    novo_mundo.lef = cria_lef();

    novo_mundo.Herois = malloc(N_HEROIS * sizeof(struct Heroi));
    if(novo_mundo.Herois == NULL){
        printf("Falha na alocação do vetor de heróis.\n");
        exit(1);
    }

    novo_mundo.Bases = malloc(N_BASES * sizeof(struct Base));
    if(novo_mundo.Bases == NULL){
        printf("Falha na alocação do vetor de bases.\n");
        free(novo_mundo.Herois);
        exit(1);
    }

    novo_mundo.Missoes = malloc(N_MISSOES * sizeof(struct Missao));
    if(novo_mundo.Missoes == NULL){
        printf("Falha na alocação do vetor de missoes.\n");
        free(novo_mundo.Herois);
        free(novo_mundo.Bases);
        exit(1);
    }

    insere_elementos(novo_mundo);

    return novo_mundo;
}

/*Libera toda a memória do mundo.*/
void destroi_Mundo(struct Mundo m){
    int i;

    for(i = 0; i < m.NHerois; i++){
        destroi_cjt(m.Herois[i].habilidades);
    }

    for(i = 0; i < m.NBases; i++){
        destroi_cjt(m.Bases[i].herois);
        fila_destroi(&(m.Bases[i].fila));
    }

    for(i = 0; i < m.NMissoes; i++){
        destroi_cjt(m.Missoes[i].requisitos);
    }

    m.lef = destroi_lef(m.lef);

    free(m.Herois);
    free(m.Bases);
    free(m.Missoes);
}

void imprime_herois(struct Mundo m){
    int i, id, pac, s, exp;

    for(i = 0; i < m.NHerois; i++){
        id = m.Herois[i].ID;
        pac = m.Herois[i].pac;
        s = m.Herois[i].velocidade;
        exp = m.Herois[i].exp;
        printf("HEROI %2d PAC %3d VEL %4d EXP %4d HABS ", id, pac, s, exp);
        imprime_cjt(m.Herois[i].habilidades);
    }
}

/*Busca um elemento no vetor.*/
int search(int v[], int tam, int x){
    int i;

    for(i = 0; i < tam; i++){
        if(v[i] == x){
            return i;
        }
    }

    return -1;
}

/*Une todas as habiliades dos heróis em uma base em um
 único conjunto.*/
struct conjunto *habilidades_base(struct Mundo m, struct Base b){
    int i, j, id;
    struct conjunto *c;

    c = cria_cjt(N_HABILIDADES);

    for(i = 0; i < b.herois->card; i++){
        id = b.herois->v[i];
        for(j = 0; j < m.Herois[id].habilidades->card; j++){
            insere_cjt(c, m.Herois[id].habilidades->v[j]);
        }
    }

    return c;
}

/*Incrementa a experiência dos heróis da base.*/
void incrementa_exp(struct Mundo m, struct Base b){
    int i, id;

    for(i = 0; i < b.herois->card; i++){
        id = b.herois->v[i];
        m.Herois[id].exp++;
    }
}

void Merge(int v[], int a, int m, int b) {
    int i, j, k;
    int n1 = m - a + 1;
    int n2 = b - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = v[a + i];
    for (j = 0; j < n2; j++)
        R[j] = v[m + 1 + j];

    i = 0; 
    j = 0;
    k = a; 
    while (i < n1 && j < n2){
        if (L[i] <= R[j]) {
            v[k] = L[i];
            i++;
        } else {
            v[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        v[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        v[k] = R[j];
        j++;
        k++;
    }
}

/*Algoritmo de Ordenação.*/
void MergeSort(int v[], int a, int b) {
    if (a < b) {
        int m = a + (b - a) / 2;
        MergeSort(v, a, m);
        MergeSort(v, m + 1, b);
        Merge(v, a, m, b);
    }
}

/*Evento Final.*/
/*Estatísticas da Simulação.*/
void evento_fim(struct Mundo m, int tempo){
    double tentativ, cumpri;

    printf("%6d: FIM\n", tempo);
    imprime_herois(m);
    cumpri = ((m.Msucesso*100.00) / m.NMissoes);
    tentativ = ((m.Mtentativas)*100.00 / m.NMissoes)/100.00;
    printf("%d/%d MISSOES CUMPRIDAS ", m.Msucesso, m.NMissoes);
    printf("(%.2f%%), MEDIA %.2f TENTATIVAS/MISSAO\n", cumpri, tentativ);
}

/*Evento Missão.*/
/*Evento Tipo 8.*/
void evento_missao(struct Mundo *m, int tempo, struct Missao ms){
    int i, d, base, cumprida, id, t;
    int bases[N_BASES];
    int distan[N_BASES];
    struct conjunto *habs;
    struct evento_t *e;

    id = ms.ID;
    t = tempo;
    m->Mtentativas++;
    cumprida = -1;
    printf("%6d: MISSAO %d HAB REQ: ", t, id);
    imprime_cjt(ms.requisitos);

    /*Preenche dois vetores com as distãncias e ordena um deles.*/
    for(i = 0; i < m->NBases; i++){
        d = dist(m->Bases[i].coord, ms.coord);
        bases[i] = d;
        distan[i] = d;
    }

    MergeSort(distan, 0, N_BASES-1);

    for(i = 0; i < m->NBases; i++){
        base = search(bases, N_BASES, distan[i]);
        habs = habilidades_base(*m, m->Bases[base]);
        printf("%6d: MISSAO %d HAB BASE %d:", t, id, base);
        imprime_cjt(habs);
        if(contido_cjt(ms.requisitos, habs)){
            if(cumprida == -1){
                /*Salva a ID da primeira base compatível.*/
                cumprida = base;
            }
        }
        destroi_cjt(habs);        
    }

    /*Marca a missão como cumprida ou impossível.*/
    if(cumprida >= 0){
        m->Msucesso++;
        printf("%6d: MISSAO %d CUMPRIDA BASE %d HEROIS:", t, id, cumprida);
        imprime_cjt(m->Bases[cumprida].herois);
        incrementa_exp(*m, m->Bases[cumprida]);
    }else{
        printf("%6d: MISSAO %d IMPOSSIVEL\n", t, id);
        e = cria_evento(t + 24*60, 8, id, 0);
        insere_lef(m->lef, e);
    }
}

/*Herói sai da Base.*/
/*Evento Tipo 7.*/
void evento_sai(struct Mundo *m, int tempo, struct Heroi h, struct Base b){
    int base;
    struct evento_t *e;

    base = aleat(0, N_BASES-1);
    retira_cjt(b.herois, h.ID);

    printf("%6d: SAI    HEROI %2d", tempo, h.ID);
    printf(" BASE %d (%2d/%2d)\n", b.ID, b.herois->card, b.herois->max);

    /*Cria evento_viaja.*/
    e = cria_evento(tempo, 5, h.ID, base);
    insere_lef(m->lef, e);
    /*Cria evento_avisa*/
    e = cria_evento(tempo, 4, h.ID, b.ID);
    insere_lef(m->lef, e);
}

/*Herói entra na base B.*/
/*Evento Tipo 6.*/
void evento_entra(struct Mundo *m, int tempo, struct Heroi h, struct Base b){
    int tpb, card, max, t;
    struct evento_t *e;

    tpb = 15 + h.pac * aleat(1, 20);

    t = tempo;
    card = b.herois->card;
    max = b.herois->max;
    printf("%6d: ENTRA  HEROI %2d", t, h.ID);
    printf(" BASE %d (%2d/%2d) SAI %d\n", b.ID, card, max, t + tpb);

    /*Cria evento_sai.*/
    e = cria_evento(t + tpb, 7, h.ID, b.ID);
    insere_lef(m->lef, e);
}

/*Herói viaja para outra base.*/
/*Evento Tipo 5.*/
void evento_viaja(struct Mundo *m, int tempo, struct Heroi h, struct Base b){
    int t, dur, dis, speed;
    struct evento_t *e;

    t = tempo;
    speed = h.velocidade;
    /*Distância e Duração da viagem.*/
    dis = dist(h.baseAtual, b.coord);
    dur = dis / h.velocidade;

    printf("%6d: VIAJA  HEROI %2d BASE %d", t, h.ID, h.base);
    printf(" BASE %d DIST %d VEL %d CHEGA %d\n", b.ID, dis, speed, t + dur);
    /*Cria evento_chega.*/
    e = cria_evento(t + dur, 1, h.ID, b.ID);
    insere_lef(m->lef, e);
}

/*Atualiza o porteiro sobre a base.*/
/*Evento Tipo 4.*/
void evento_avisa(struct Mundo *m, int tempo, struct Base b){
    int id, t, c, mx;
    struct evento_t *e;

    t = tempo;
    c = b.herois->card;
    mx = b.herois->max;
    printf("%6d: AVISA PORTEIRO BASE %d (%2d/%2d) FILA: ", t, b.ID, c, mx);
    fila_imprime(b.fila);
    while((b.herois->card < b.herois->max) && (!(fila_vazia(b.fila)))){
        dequeue(b.fila, &id);
        insere_cjt(b.herois, id);
        printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d\n", t, b.ID, id);
        /*Cria evento_entra.*/
        e = cria_evento(t, 6, id, b.ID);
        insere_lef(m->lef, e);
    }
}

/*Herói desiste e viaja para outra base.*/
/*Evento Tipo 3.*/
void evento_desiste(struct Mundo *m, int tempo, struct Heroi h, struct Base b){
    int base;
    struct evento_t *e;

    printf("%6d: DESISTE HEROI %2d BASE %d\n", tempo, h.ID, b.ID);

    base = aleat(0, N_BASES-1);

    /*Cria evento_viaja.*/
    e = cria_evento(tempo, 5, h.ID, base);
    insere_lef(m->lef, e);
}

/*Herói espera para entrar na Base.*/
/*Evento Tipo 2.*/
void evento_espera(struct Mundo *m, int tempo, struct Heroi h, struct Base b){
    int t, tam;
    struct evento_t *e;

    t = tempo;
    tam = b.fila->tamanho;
    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", t, h.ID, b.ID, tam);

    enqueue(b.fila, h.ID);

    /*Cria evento_avisa.*/
    e = cria_evento(t, 4, 0, b.ID);
    insere_lef(m->lef, e);
}

/*Chegada do Herói em uma Base.*/
/*Evento Tipo 1.*/
void evento_chega(struct Mundo *m, int tempo, struct Heroi h, struct Base b){
    int t, c, mx, espera;
    struct evento_t *e;

    /*Atualiza a base do herói.*/
    m->Herois[h.ID].base = b.ID;
    m->Herois[h.ID].baseAtual.x = b.coord.x;
    m->Herois[h.ID].baseAtual.y = b.coord.y;

    t = tempo;
    c = b.herois->card;
    mx = b.herois->max;
    /*Define se o herói espera ou não.*/
    if((b.herois->card < b.herois->max) && (!(fila_vazia(b.fila)))){
        espera = 1;
    }else{
        espera = (h.pac) > (10 * b.fila->tamanho);
    }

    if(espera){
        /*Cria evento_espera.*/
        e = cria_evento(t, 2, h.ID, b.ID);
        insere_lef(m->lef, e);
        printf("%6d: CHEGA HEROI %2d", t, h.ID);
        printf(" BASE %d (%2d/%2d) ESPERA\n", b.ID, c, mx);
    }else{
        /*Cria evento_desiste.*/
        e = cria_evento(t, 3, h.ID, b.ID);
        insere_lef(m->lef, e); 
        printf("%6d: CHEGA HEROI %2d", t, h.ID);
        printf(" BASE %d (%2d/%2d) DESISTE\n", b.ID, c, mx);
    }
}

int main(){
    srand(0);
    int i, t, b;
    struct Mundo mundo;
    struct evento_t *e;
    struct nodo_lef_t *aux;

    mundo = cria_Mundo();

    /*Evento Fim do Mundo.*/
    e = cria_evento(T_FIM_DO_MUNDO, 10, 99999, 99999);
    insere_lef(mundo.lef, e);

    /*Inicialização da chegada dos heróis.*/
    for(i = 0; i < mundo.NHerois; i++){
        t = aleat(0, 4320);;
        b = aleat(0, N_BASES-1);
        e = cria_evento(t, 1, mundo.Herois[i].ID, b);
        insere_lef(mundo.lef, e);
    }

    /*Inicialização das missões.*/
    for(i = 0; i < mundo.NMissoes; i++){
        t = aleat(0, T_FIM_DO_MUNDO);
        e = cria_evento(t, 8, mundo.Missoes[i].ID, 0);
        insere_lef(mundo.lef, e);
    }

    /*Loop de Simulação.*/
    while(mundo.clock < T_FIM_DO_MUNDO){
        aux = mundo.lef->primeiro;

        /*Garante que os eventos ocorram na ordem correta
         e no tempo correto.*/
        if(aux->evento->tempo <= mundo.clock){
            e = retira_lef(mundo.lef);
            t = e->tempo;
            switch(e->tipo){
                case 1:
                    evento_chega(&mundo, t, mundo.Herois[e->dado1], mundo.Bases[e->dado2]);
                    break;
                case 2:
                    evento_espera(&mundo, t, mundo.Herois[e->dado1], mundo.Bases[e->dado2]);
                    break;
                case 3:
                    evento_desiste(&mundo, t, mundo.Herois[e->dado1], mundo.Bases[e->dado2]);
                    break;
                case 4:
                    evento_avisa(&mundo, t, mundo.Bases[e->dado2]);
                    break;
                case 5:
                    evento_viaja(&mundo, t, mundo.Herois[e->dado1], mundo.Bases[e->dado2]);
                    break;
                case 6:
                    evento_entra(&mundo, t, mundo.Herois[e->dado1], mundo.Bases[e->dado2]);
                    break;
                case 7:
                    evento_sai(&mundo, t, mundo.Herois[e->dado1], mundo.Bases[e->dado2]);
                    break;
                case 8:
                    evento_missao(&mundo, t, mundo.Missoes[e->dado1]);
                    break;
                default:
                    printf("Evento Inválido.\n");
            }
            destroi_evento(e);
            aux = mundo.lef->primeiro;
            mundo.clock--;
        }
        mundo.clock++;
    }
    e = retira_lef(mundo.lef);
    evento_fim(mundo, e->tempo);
    destroi_evento(e);
    destroi_Mundo(mundo);

    return 0;
}