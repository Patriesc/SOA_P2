
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define DIMFILA 100000
#define NUMFILAS 2000

typedef struct fila{
 int vector[DIMFILA];
 long suma;
} fila_t;

typedef fila_t * pfila_t; //Puntero a una estructura fila
fila_t matriz[NUMFILAS];

void sumaFila(pfila_t);
void muestraMatriz(pfila_t);

int main(){
  int fd, i;
  pfila_t p;
  
  int f=0, v=0;
  for(;f<NUMFILAS; f++){
	matriz[f].suma=0;
	for(v=0;v<DIMFILA; v++){
		matriz[f].vector[v]=10;
	}
   }
  printf("Matriz inicializada\n");
  fd=open ("archivo", O_RDWR | O_CREAT, 0600);
  if(fd==-1){
    perror("Fallo en open");
    exit(1); 
  }

  printf("Archivo Abierto. Suma size: %ld Matriz size: %ld\n", sizeof(matriz[0].suma), sizeof(matriz));
    printf("Archivo Abierto. matriz[0] size: %ld Vector size: %ld\n", sizeof(matriz[0]), sizeof(matriz[0].vector));
  write(fd, &matriz, sizeof(matriz));
  printf("Archivo Abierto\n");
  p=mmap(NULL, sizeof(matriz), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(p==MAP_FAILED){
    perror("Fallo en mmap");
    exit(1);
  }
  
  printf("Estructura en archivo\n");
  muestraMatriz(p);
  
    for (int i = 0; i < NUMFILAS; i++) {
        if (fork() == 0) {
            for (int j = 0; j < DIMFILA; j++) {
                p[i].suma += p[i].vector[j];
            }
            exit(0);
        }
    }
    for (int i = 0; i < NUMFILAS; i++) {
        wait(NULL);
    }
  muestraMatriz(p);
     
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
	printf("\n");
   }
}
