#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
  int m, n, i, j, temp;
  int **grafo_cap;

  scanf("%d %d\n\n", &m, &n);
  if (m < 1 || n < 1) {
    printf("Os valores de m e n devem respeitar as condicoes: m>= 1 e n>= 1.\n");
    return 1;
  }

  // Cria a matriz onde estarao as capacidades das ligacoes
  grafo_cap = (int**) malloc((m*n + 2)*sizeof(int*));
  for (i = 0; i < (m*n + 2); i++) {
    grafo_cap[i] = (int*) malloc((m*n + 2)*sizeof(int));
    for (j = 0; j < (m*n)+2; j++) {
      grafo_cap[i][j] = 0;
    }
  }

  // Le e guarda os pesos de plano --> capacidades de ligar ao vertice P (i=0)
  for (i = 1; i < (m*n)+1; i++) {
    scanf("%d", &grafo_cap[0][i]);
  }

  // Le e guarda os pesos de cenario --> capacidades de ligar ao vertice C (i=(m*n)+1)
  for (i = 1; i < (m*n)+1; i++) {
    scanf("%d", &grafo_cap[(m*n)+1][i]);
  }

  // Le e guarda as capacidades das ligacoes horizontais
  for (i = 1; i < (m*(n-1))+1; i++) {
    scanf("%d", &grafo_cap[i][i+1]);
  }

  // Le e guarda as capacidades das ligacoes verticais
  for (i = 1; i < ((m-1)*n)+1; i++) {
    scanf("%d", &grafo_cap[i][i+n]);
  }

  /* Consideramos que cada vertice (pixel) so liga ao seu vizinho da esquerda
      e ao vizinho de baixo.
     Todos os vertices ligam ao vertice P e C */

  temp = 0;
  printf("%d %d\n\n", m, n);
  for (i = 1; i < (m*n + 1); i++) {
    printf("%d ", grafo_cap[0][i]);
    temp++;
    if (temp == n) {
      printf("\n");
      temp = 0;
    }
  }
  printf("\n");

  temp = 0;
  for (i = 1; i < (m*n + 1); i++) {
    printf("%d ", grafo_cap[(m*n)+1][i]);
    temp++;
    if (temp == n) {
      printf("\n");
      temp = 0;
    }
  }
  printf("\n");

  temp = 0;
  for (i = 1; i < (m*(n-1))+1; i++) {
    printf("%d ", grafo_cap[i][i+1]);
    temp++;
    if (temp == (n-1)) {
      printf("\n");
      temp = 0;
    }
  }
  printf("\n");

  temp = 0;
  for (i = 1; i < ((m-1)*n)+1; i++) {
    printf("%d ", grafo_cap[i][i+n]);
    temp++;
    if (temp == n) {
      printf("\n");
      temp = 0;
    }
  }
  printf("\n");

  return 0;
}
