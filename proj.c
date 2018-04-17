#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
  int m, n, i, j;
  int **peso_plano, **peso_cenario;
  int **pes_lig_hor, **pes_lig_ver;

  scanf("%d %d\n\n", &m, &n);
  if (m < 1 || n < 1) {
    printf("Os valores de m e n devem respeitar as condicoes: m>= 1 e n>= 1.\n");
    return 1;
  }

  peso_plano = (int**) malloc(m * sizeof(int*));
  for (i = 0; i < m; i++) {
    peso_plano[i] = (int*) malloc(n * sizeof(int));
    for (j = 0; j < n; j++) {
      scanf("%d", &peso_plano[i][j]);
    }
  }

  peso_cenario = (int**) malloc(m * sizeof(int*));
  for (i = 0; i < m; i++) {
    peso_cenario[i] = (int*) malloc(n * sizeof(int));
    for (j = 0; j < n; j++) {
      scanf("%d", &peso_cenario[i][j]);
    }
  }

  pes_lig_hor = (int**) malloc(m * sizeof(int*));
  for (i = 0; i < m; i++) {
    pes_lig_hor[i] = (int*) malloc((n-1) * sizeof(int));
    for (j = 0; j < n-1; j++) {
      scanf("%d", &pes_lig_hor[i][j]);
    }
  }

  pes_lig_ver = (int**) malloc((m-1) * sizeof(int*));
  for (i = 0; i < m-1; i++) {
    pes_lig_ver[i] = (int*) malloc(n * sizeof(int));
    for (j = 0; j < n; j++) {
      scanf("%d", &pes_lig_ver[i][j]);
    }
  }


  printf("%d %d\n\n", m, n);

  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      printf("%d ", peso_plano[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      printf("%d ", peso_cenario[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  for (i = 0; i < m; i++) {
    for (j = 0; j < n-1; j++) {
      printf("%d ", pes_lig_hor[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  for (i = 0; i < m-1; i++) {
    for (j = 0; j < n; j++) {
      printf("%d ", pes_lig_ver[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  return 0;
}
