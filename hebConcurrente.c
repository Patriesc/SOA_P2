#include <stdio.h>
#include <pthread.h>

#define DIMFILA 10
#define NUMFILAS 20
typedef struct fila{
 int vector[DIMFILA];
 long suma;
} fila_t;

typedef fila_t * pfila_t; //Puntero a una estructura fila
fila_t matriz[NUMFILAS];

void sumaFila(pfila_t);
void muestraMatriz(pfila_t);

void * sumaFilaHeb(void *);

int main(){
  int f=0, v=0;
  for(f=0;f<NUMFILAS; f++){
	matriz[f].suma=0;
	for(v=0;v<DIMFILA; v++){
		matriz[f].vector[v]=10;
	}
   }
  pthread_t hebras[NUMFILAS];

  for(f=0;f<NUMFILAS; f++){
	  if (pthread_create(&hebras[f], NULL, sumaFilaHeb, (void *) &matriz[f]) == -1){
	      perror("Error en pthread_create hebra...");
	  }
  }
  
  for(f=0;f<NUMFILAS; f++){
	  if (pthread_join(hebras[f], NULL) == -1){
	      perror("Error en pthread_join hebra...");
	  }
  }

  
  muestraMatriz(matriz);
     
}

void sumaFila(pfila_t pf){
   int v=0;
   for(;v<DIMFILA; v++){
	pf->suma+=pf->vector[v];
   }
}

void muestraMatriz(pfila_t m){
  int f=0, v=0;
  for(;f<NUMFILAS; f++){
	printf("fila %d: %ld ", f, m[f].suma);
	/*for(v=0;v<DIMFILA; v++){
		printf("%d ", m[f].vector[v]);
	}*/
	printf("\n");
   }
}

void * sumaFilaHeb(void *p){
  pfila_t m= (pfila_t) p;
   int f=0, v=0;
  for(;f<NUMFILAS;f++){
    m[f].suma=0;
        for(v=0;v<DIMFILA;v++){
      m[f].suma+=m[f].vector[v];
    }
  }
  /*
      for(v=0;v<DIMFILA; v++){
	m[f].suma+=m[f].vector[v];
      }
  */
  
}