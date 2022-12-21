#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

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

int main(){
  int fd, i, cero=0;
  pfila_t p;
  int status;
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
  
  int x = 0;
  for(x=0; x<NUMFILAS;x++){
  int n=fork();
  int valoresFork[NUMFILAS] = n;
  if(n == -1){
     perror("Fallo en fork()...");
     exit(-1);
  } else if (n == 0){
     printf ("Proceso hijo con pid: %d\n", getpid());
     p[x].suma=22;
     close(fd);
     printf ("Proceso hijo con pid: %d termina\n", getpid());
     exit(0);
   }else{
     wait(&status);
     printf ("Proceso padre con pid: %d\n", getpid());
     p[x].suma=222;
     close(fd);
   }
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
