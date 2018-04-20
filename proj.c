 #include <stdio.h>
#include <stdlib.h>



// -------------------------------- Constantes --------------------------------
#define P 0
#define CIMA 1
#define DIR 2
#define BAIXO 3
#define ESQ 4
#define C 5
// ----------------------------------------------------------------------------



// -------------------------------- Estruturas --------------------------------
typedef struct no {
  int id;
  struct no *next;
} Lista;
// ----------------------------------------------------------------------------




// ---------------------------- Variaveis Globais ----------------------------
int n_colunas, n_linhas;
int **grafo_cap;
int *peso_plano, *peso_cenario;
// ----------------------------------------------------------------------------




// -------------------------- Biblioteca de Funcoes --------------------------


// - - - - - - - Funcoes para controlo da matriz das capacidades - - - - - - -

// up(i) --> Funcao que da o vertice na posicao a cima do vertice i.
int up(int i) {
  int res = i-n_colunas;
  return (res < 0 ? -1 : res);
}

// down(i) --> Funcao que da o vertice na posicao a baixo do vertice i.
int down(int i) {
  int res = i + n_colunas;
  return (res >= (n_linhas * n_colunas) ? -1 : res);
}

// left(i) --> Funcao que da o vertice na posicao esquerda do vertice i.
int left(int i)  {
  return (((i % n_colunas) == 0) ? -1 : i-1);
}

// right(i) --> Funcao que da o vertice na posicao direita do vertice i.
int right(int i) {
  return (((i % n_colunas) == (n_colunas-1)) ? -1 : i+1);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


// - - - - - - - - - - - - - Funcoes sobre o fluxo - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// ----------------------------------------------------------------------------



int main(int argc, char const *argv[]) {
  int i, j, temp;

  scanf("%d %d\n\n", &n_linhas, &n_colunas);
  if (n_linhas < 1 || n_colunas < 1) {
    printf("Os valores de m e n devem respeitar as condicoes: m >= 1 e n >= 1.\n");
    return 1;
  }

  // Cria a matriz onde estarao as capacidades das ligacoes.
  grafo_cap = (int**) malloc((n_linhas*n_colunas)*sizeof(int*));
  for (i = 0; i < (n_linhas*n_colunas); i++) {
    grafo_cap[i] = (int*) malloc(6*sizeof(int));
    for (j = 0; j < 6; j++) {
      grafo_cap[i][j] = 0;
    }
  }

  peso_plano   = (int*) malloc(n_linhas*n_colunas*sizeof(int));
  peso_cenario = (int*) malloc(n_colunas*n_linhas*sizeof(int));


  // Le e guarda os pesos de 1 plano --> capacidades de ligar ao vertice P.
  for (i = 0; i < n_linhas*n_colunas; i++) {
    scanf("%d", &grafo_cap[i][P]);
    peso_plano[i] = grafo_cap[i][P];
  }

  // Le e guarda os pesos de cenario --> capacidades de ligar ao vertice C.
  for (i = 0; i < n_linhas*n_colunas; i++) {
    scanf("%d", &grafo_cap[i][C]);
    peso_cenario[i] = grafo_cap[i][C];
  }

  // Le e guarda as capacidades das ligacoes horizontais.
  for (i = 0; i < n_linhas*n_colunas; i++) {
    j = right(i);
    if (j == -1) {
      grafo_cap[i][DIR] = 0;
    } else {
      scanf("%d", &grafo_cap[i][DIR]);
      grafo_cap[j][ESQ] = grafo_cap[i][DIR];
    }
  }

  // Le e guarda as capacidades das ligacoes verticais.
  for (i = 0; i < n_linhas*n_colunas; i++) {
    j = down(i);
    if (j == -1) {
      grafo_cap[i][BAIXO] = 0;
    } else {
      scanf("%d", &grafo_cap[i][BAIXO]);
      grafo_cap[j][CIMA] = grafo_cap[i][BAIXO];
    }
  }


  // - - - - - - - Imprimir o input - - - - - - -
  printf("%d %d\n\n", n_linhas, n_colunas);

  printf("Pesos de plano:\n");
  temp = 0;
  for (i = 0; i < n_linhas*n_colunas; i++) {
    printf("%d ", grafo_cap[i][P]);
    temp++;
    if (temp == n_colunas) {
      printf("\n");
      temp = 0;
    }
  }
  printf("\n");

  printf("Pesos de cenario\n");
  temp = 0;
  for (i = 0; i < n_linhas*n_colunas; i++) {
    printf("%d ", grafo_cap[i][C]);
    temp++;
    if (temp == n_colunas) {
      printf("\n");
      temp = 0;
    }
  }
  printf("\n");

  printf("Ligacoes Para a direita (a ultima coluna e suposto ser 0):\n");
  temp = 0;
  for (i = 0; i < n_linhas*n_colunas; i++) {
    printf("%d ", grafo_cap[i][DIR]);
    temp++;
    if (temp == n_colunas) {
      printf("\n");
      temp = 0;
    }
  }
  printf("\n");

  printf("Ligacoes Para a esquerda (a primeira coluna e suposto ser 0):\n");
  temp = 0;
  for (i = 0; i < n_linhas*n_colunas; i++) {
    printf("%d ", grafo_cap[i][ESQ]);
    temp++;
    if (temp == n_colunas) {
      printf("\n");
      temp = 0;
    }
  }
  printf("\n");

  printf("Ligacoes para baixo (a ultima linha e suposto ser 0):\n");
  temp = 0;
  for (i = 0; i < n_linhas*n_colunas; i++) {
    printf("%d ", grafo_cap[i][BAIXO]);
    temp++;
    if (temp == n_colunas) {
      printf("\n");
      temp = 0;
    }
  }
  printf("\n");

  printf("Ligacoes para cima (a primeira linha e suposto ser 0):\n");
  temp = 0;
  for (i = 0; i < n_linhas*n_colunas; i++) {
    printf("%d ", grafo_cap[i][CIMA]);
    temp++;
    if (temp == n_colunas) {
      printf("\n");
      temp = 0;
    }
  }
  printf("\n");

  return 0;
}
