#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
* Para sacar el mínimo de 3 numerosse utilizaran estas macros,
* que reducen el tiempo de ejecución en comparacion a usar
* una función que saque el mínimo.
*/
#define MIN2(a,b) (a < b ? a:b)
#define MIN3(a,b,c) (MIN2(MIN2(a,b),c))

#define data_t int

/*
* Estructura que envuelve la solucion al problema.
*/
struct Solution {
  data_t size, row, col;
};

/*
* Función que realizara el algoritmo y nos entregara el resultado.
* El algoritmo modifica la matriz original, que nos sirve tambíen
* como matriz para guardar resultados, con el fin de ahorrar memoria y tiempo.
*/
struct Solution solve(data_t **matrix, data_t h, data_t w);

int main(int argc, char *argv[]) {
  data_t h,w; // Alto y ancho de la matriz.
  data_t **matrix, aux;

  // Chequear si venia un argumento con el archivo.
  if (argc != 2) {
     printf("¡¡ERROR!!\n"
         "Por favor llama a este programa con un solo parametro que \n"
         "debe ser el nombre del archivo de prueba.\n\n");
     exit(1);
   }

   // Cargar archivo
   FILE *file = fopen( argv[1], "r" );
   if ( file == 0 ) {
     printf( "No se pudo abrir el archivo.\n" );
     exit(1);
   }

  fscanf(file, "%d %d", &h, &w);
  matrix = (data_t**) malloc(h * sizeof(data_t*));
  for(data_t i = 0; i < h; i++) {
    matrix[i] = (data_t*) malloc(w * sizeof(data_t));
  }

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      fscanf (file, "%d", &aux);
      // Se dan vuelta los numeros para facilitar el algoritmo.
      // El resultado sera el mismo.
      if (aux == 0) {
        matrix[i][j] = 1;
      } else {
        matrix[i][j] = 0;
      }

    }
  }

  // Tiempo antes de iniciar el algoritmo
  clock_t tic = clock();

  // Algoritmo
  struct Solution sol;
  sol = solve(matrix, h, w);

  // Tiempo al finalizar el algoritmo
  clock_t toc = clock();

  printf("%d %d %d\n", sol.col , sol.row, sol.size);
  printf("Tiempo: %.2f segundos\n", (double)(toc - tic) / CLOCKS_PER_SEC);
  return 0;
}

// Función que realiza el algoritmo sobre la matriz
struct Solution solve(data_t **matrix, data_t h, data_t w) {
  data_t max_size = 0, max_row = -1, max_col = -1;
  for (int i = 1; i < h; i++) {
    for (int j = 1; j < w; j++) {
      if (matrix[i][j] != 0) {
        matrix[i][j] = MIN3(matrix[i-1][j], matrix[i-1][j-1], matrix[i][j-1]) + 1;
        if (matrix[i][j] > max_size) {
          max_row = i;
          max_col = j;
          max_size = matrix[i][j];
        }
      }
    }
  }
  max_col = max_col - max_size + 1;
  max_row = max_row - max_size + 1;

  struct Solution sol;
  sol.col = max_col;
  sol.row = max_row;
  sol.size = max_size;
  return sol;
}
