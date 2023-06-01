#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <locale.h>

enum	{ INTEIRO	=	-3 , FLOAT , E_CARACTERE};

typedef struct eleLista{
  int chaveDecimal;
  struct eleLista* prox;
  int index;
}noSublista;

typedef struct inicioSublista{
  int qtdElementos;
  noSublista* primeiroElemento;
}inicioSublista;

typedef struct elemento{
  int chaveInteira;
  struct elemento* anterior;
  struct elemento* prox;
  int index;
  inicioSublista* subLista;
}no;

typedef struct inicio{
  int qtdElementos;
  no* primeiroElemento;
}inicio;

// protótipo das funções:

void verifica_caracter(char *token, int* cont);
int intOrFloat(double numero);
void inserirElementoFinal(inicio* lista, int chave, inicioSublista* sublista);
void inserirElemento(inicioSublista* lista, int chave);
void imprimir(inicio* lista, inicioSublista* subLista, FILE* fp_out);
void insertionSort(int* vetor, int tam);
  void insertionSortFloat(float* vetor, int tam);
// Funções:

void verifica_caracter(char *token, int* cont){
  if((token[0] > 64 &&	token[0] < 91 ) || (token[0] > 96 &&	token[0] < 123  ))
     *cont = E_CARACTERE;
}

int intOrFloat(double numero){
    double fracao;
    fracao = modf	(numero, &numero); // modf -> é da biblioteca math.h

    if (fracao == 0.0) {
			//printf("O número é inteiro.\n");
			return INTEIRO;
    } else {
			//printf("O número é float.\n");
			return FLOAT;
    }
}

void inserirElementoFinal(inicio* lista, int chave, inicioSublista* sublista) {
  printf("#####1#####\n");
  no* novoElemento = (no*)malloc(sizeof(no));
  if (novoElemento == NULL) {
      perror("Erro ao alocar memória");
      return;
  }
  novoElemento->chaveInteira = chave;
  novoElemento->anterior = NULL;
  novoElemento->prox = NULL;
  novoElemento->index = lista->qtdElementos;
  novoElemento->subLista = sublista;

  if (lista->primeiroElemento == NULL) {
      lista->primeiroElemento = novoElemento;
  } else {
      no* atual = lista->primeiroElemento;
      while (atual->prox != NULL) {
        
          atual = atual->prox;
      }
      atual->prox = novoElemento;
      novoElemento->anterior = atual;
  }
  lista->qtdElementos++;
}

void inserirElemento(inicioSublista* lista, int chave) {
  printf("#####2#####\n");
  noSublista* novoElemento = (noSublista*)malloc(sizeof(noSublista));
  if (novoElemento == NULL) {
      perror("Erro ao alocar memória");
      return;
  }
  novoElemento->chaveDecimal = chave;
  novoElemento->prox = NULL;
  novoElemento->index = lista->qtdElementos;

  if (lista->primeiroElemento == NULL) {
    lista->primeiroElemento = novoElemento;
  } else {
    noSublista* atual = lista->primeiroElemento;
    while (atual->prox != NULL) {
      printf("teste\n");
      atual = atual->prox;
    }
    atual->prox = novoElemento;
  }
  lista->qtdElementos++;
}

//refazer essa função
void imprimir(inicio* lista, inicioSublista* subLista, FILE* fp_out){
  printf("#####3#####\n");
  no* novoElemento = (no*)malloc(sizeof(no));
  noSublista* novoSubLista = (noSublista*)malloc(sizeof(noSublista));
  
  if (novoElemento == NULL || novoSubLista == NULL) {
      perror("Erro ao alocar memória");
      return;
  }
  
  if(lista->primeiroElemento == NULL){
    //printf("lista principal vazia");
  }
  novoElemento = lista->primeiroElemento;
	
  while(novoElemento->prox != NULL){
    printf("-------|1|-----\n");
    // no* atual = novoElemento->prox;
    fprintf(fp_out, "[%d(", novoElemento->chaveInteira);
    novoSubLista = novoElemento->subLista->primeiroElemento;
    while(novoSubLista->index < novoElemento->subLista->qtdElementos){
      printf("-------|2|-----\n");
      // noSublista* atualSub = novoSubLista;
      fprintf(fp_out, "%d", novoSubLista->chaveDecimal);
      novoSubLista = novoSubLista->prox;
      if(novoSubLista->index < novoElemento->subLista->qtdElementos)
        fprintf(fp_out, "->");
    }
  }
}


void insertionSort(int* vetor, int tam) {
  int j;
  for (j = 1; j < tam; j++) {
    int key = vetor[j];
    int i = j - 1;
    while ((i >= 0) && (vetor[i] > key)) {
      vetor[i + 1] = vetor[i];
      i = i - 1;
    }
    vetor[i + 1] = key;
  }
}

void insertionSortFloat(float* vetor, int tam) {
  int j;
  for (j = 1; j < tam; j++) {
    float key = vetor[j];
    int i = j - 1;
    while ((i >= 0) && (vetor[i] > key)) {
      vetor[i + 1] = vetor[i];
      i = i - 1;
    }
    vetor[i + 1] = key;
  }
}