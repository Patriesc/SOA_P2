#include <stdio.h>
#include <stdlib.h>

#define DIMFILA 10
#define NUMFILAS 20
typedef struct fila{
int vector[DIMFILA];
long suma;
} fila_t;
typedef fila_t* pfila_t; //Puntero a una estructura fila
fila_t matriz[NUMFILAS]; 

void sumaFila(pfila_t);
void muestraMatriz(pfila_t);

int main() {
int f=0, v=0;
  
// Inicializamos la matriz
for(f=0;f<NUMFILAS;f++){
  matriz[v].suma = 0;
  for(v=0;v<DIMFILA;v++){
  matriz[f].vector[v]=10;
  }
}


for(f=0;f<NUMFILAS;f++){
  sumaFila(&matriz[f]);
}
muestraMatriz(matriz);
  

}

void sumaFila(pfila_t pf){
  int v=0;
  for(v=0;v<DIMFILA;v++){
  pf ->suma+=pf->vector[v];

}
}

void muestraMatriz(pfila_t m){
  int f=0, v=0;
  for(f=0;f<NUMFILAS;f++){
    printf("fila %d : %ld ",f, m[f].suma);
    for(v=0;v<DIMFILA;v++){
    printf("%d ", m[f].vector[v]);
    }
    printf("\n");
    
  }
}
