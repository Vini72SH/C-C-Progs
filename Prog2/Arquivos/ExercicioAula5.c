#include <stdio.h>
#include <stdlib.h>

struct citzen{
  char name[11];
  int hacking;
  int criminal;
};
typedef struct citzen citzen;

struct population{
  citzen *person;
  struct population *next;
};
typedef struct population population;

population* read_file(char *file_name){
  FILE *file_data;
  population *head = NULL, *tail = NULL;

  file_data = fopen(file_name, "r");
  if (!file_data) return NULL;

  while(1){
    population *add = (population*) malloc(sizeof(population));
    add->person = (citzen*) malloc(sizeof(citzen));

    if (!fread(add->person, sizeof(citzen), 1, file_data)){
        free(add->person);
        free(add);
        break;
    }

    add->next = NULL;

    if (head == NULL){
      head = add;
      tail = add;
    }
    else{
      tail->next = add;
      tail = add;
    }
  }

  fclose(file_data);
  return head;
}

void free_population(population *head){
  population *i;

  i = head;
  while(head){
    i = head->next;
    free(head->person);
    free(head);
    head = i;
  }
}

void print_information(population *head){
  int total_citzens, dangerous_citzens;
  float hacking_mean;

  total_citzens = 0;
  hacking_mean = 0;
  dangerous_citzens = 0;

  printf("=========== SUMARIO DA POPULACAO ===========\n");
  while(head){
    total_citzens += 1;
    hacking_mean += head->person->hacking;
    if (head->person->criminal > 5) dangerous_citzens += 1;

    printf("--\n");
    printf("Nome: %s\n", head->person->name);
    printf("Hacking: %d\n", head->person->hacking);
    printf("--\n");

    head = head->next;
  }
  printf("============================================\n\n");

  printf("-> TOTAL DE CIDADAOS: %d\n", (int) total_citzens);
  printf("-> MEDIA DE HAB. DE HACKING: %.2f\n", hacking_mean/total_citzens);
  printf("-> CIDADAOS PERIGOSOS: %d\n", dangerous_citzens);
}

int main(void){
  population *head;

  head = read_file("citizens.bin");
  print_information(head);
  free_population(head);

  return 0;
}
