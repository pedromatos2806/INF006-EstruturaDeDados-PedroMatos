#include "R1Q3.h"

int main(){
  char linha[256], *token;
  int i = 0, cont = 0, numero, j = 0;
	FILE *fp_in = fopen("L1Q3.in", "r"); // um vai ser .in // r de read = ler 
	FILE *fp_out = fopen("L1Q3.out", "w");// vai ser .out // w de write = escrever
	if (fp_in == NULL || fp_out == NULL){ //teste para saber se o arquivo foi aberto
		printf("Arquivos não podem ser abertos.");
		return EXIT_FAILURE; // se não for aberto, vai retornar 1!
	}
  int* vetorInt = (int*)malloc(sizeof(int)*100);
  float* vetorFloat = (float*)malloc(sizeof(float)*100);
  
  while(fgets (linha,	256, fp_in)	!= NULL){
    printf("*******1********\n");
    i = 0; j = 0;
    token = strtok(linha, " ");
    while(token != NULL){
      printf("*******2********\n");
			int tamanho	=	strlen(token);
			if (token[tamanho-1]	==	'\n'){
				// observei que as vezes a string vem com '\n' no final, aqui estou fazendo o teste, se tiver \n 
				token[tamanho-1]	=	'\0';
			}
      printf("*******3********\n");
      verifica_caracter(token, &cont); 
      if(cont == E_CARACTERE){
        printf("*******4********\n");
        cont = 0;  
      }else{
        printf("*******5********\n");
      	double numero = atof(token);
       	int retorno	=	 intOrFloat	(numero);
					if (retorno	==	INTEIRO){
            printf("int: %d\n", (int)numero);
						vetorInt[i] = (int)numero;
            i++;
					}else{
						vetorFloat[j] = (float)numero;
            printf("float: %.2f\n", (float)numero);
            j++;
					}
      }
      printf("----------------------\n");
      token = strtok(NULL, " ");
    }
    printf("------------1----------\n");
    printf("valor de i: %d\n", i);
    inicioSublista* sublista = (inicioSublista*)malloc(sizeof(inicioSublista)*i);
    for(int y = 0; y < i; y++){
      printf("------------2----------\n");
      sublista[y].qtdElementos = 0;
      sublista[y].primeiroElemento = NULL;
    }
    printf("------------3----------\n");
    inicio* lista = (inicio*)malloc(sizeof(inicio));
    lista->qtdElementos = 0;
    lista->primeiroElemento = NULL;
    printf("------------4----------\n");
    insertionSort(vetorInt, i);
    insertionSortFloat(vetorFloat, j);

    for(int k = 0; k < i; k++){
      inserirElementoFinal(lista, vetorInt[k], &sublista[k]);
      for(int h = 0; h < j; h++){
        if(vetorFloat[h]<vetorInt[k])
          continue;
        else if(vetorFloat[h]>vetorInt[k] && vetorFloat[h]<vetorInt[k]+1)
          inserirElemento(&sublista[k], vetorFloat[h]);
      }
    }
    for(int k = 0; k < i; k++)
      imprimir(lista, &sublista[k], fp_out);
  }

  
	fclose(fp_out);
	fclose(fp_in);
}


// (int)numero