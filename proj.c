#include <stdio.h>
#include <stdlib.h>



/* ------------------------------ Constantes ------------------------------ */
#define P 0
#define CIMA 1
#define DIR 2
#define BAIXO 3
#define ESQ 4
#define C 5

#define BRANCO 0
#define CINZA 1
#define PRETO 2
/* ------------------------------------------------------------------------- */



/* ------------------------------ Estruturas ------------------------------ */
typedef struct no {
  int id;
  struct no *next;
} No;
/* ------------------------------------------------------------------------- */




/* --------------------------- Variaveis Globais --------------------------- */
int n_colunas, n_linhas;
int n_vertices; /* --> ja conta com o vertice P (source) */
int **grafo_cap;
int *peso_plano, *peso_cenario;

int fluxoMin;
int *cor, *dist, *pais;
No  *lista_incio, *lista_fim;
/* ------------------------------------------------------------------------- */




/* ------------------------- Biblioteca de Funcoes ------------------------- */

/* - - - - - - - - - - - - - Funcoes auxiliares - - - - - - - - - - - - - */
/* min(a, b) --> retorna o menor numero entre a e b. */
int min(int a, int b) {
  return (a < b ? a : b);
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


/* - - - - - - Funcoes para controlo da matriz das capacidades - - - - - - */

/* up(i) --> Funcao que da o vertice na posicao a cima do vertice i. */
int up(int i) {
  int res = i - n_colunas;
  return (res <= 0 ? -1 : res);
}

/* down(i) --> Funcao que da o vertice na posicao a baixo do vertice i. */
int down(int i) {
  int res = i + n_colunas;
  return (res > (n_vertices-1) ? -1 : res);
}

/* left(i) --> Funcao que da o vertice na posicao esquerda do vertice i. */
int left(int i)  { return (((i % n_colunas) == 1) ? -1 : i-1); }

/* right(i) --> Funcao que da o vertice na posicao direita do vertice i. */
int right(int i) { return (((i % n_colunas) == 0) ? -1 : i+1); }

/* encontraVizinho(i,u) --> Funcao que decide a que vizinho de u corresponde i. */
int encontraVizinho(int i, int u) {
  switch (i) {
    case P:     return P;
    case CIMA:  return up(u);
    case DIR:   return right(u);
    case BAIXO: return down(u);
    case ESQ:   return left(u);
    case C:     return n_vertices;
  }
  return -1; /* E suposto nunca acontecer. */
}

/* ligacaoReversa(ligacao) --> retorna a ligacao no sentido contrario; */
int ligacaoReversa(int ligacao) {
  switch (ligacao) {
    case CIMA:  return BAIXO;
    case DIR:   return ESQ;
    case BAIXO: return CIMA;
    case ESQ:   return DIR;
  }
  return -1; /* E suposto nunca acontecer. */
}

/* encontraLigacao(pai, filho) --> retorna o tipo de ligacao entre pai e filho. */
int encontraLigacao(int pai, int filho) {
  if (pai == P)                      { return filho-1; }
  else if (filho == P)               { return P;       }
  else if ((pai-n_colunas) == filho) { return CIMA;    }
  else if ((pai+n_colunas) == filho) { return BAIXO;   }
  else if ((pai-1) == filho)         { return ESQ;     }
  else if ((pai+1) == filho)         { return DIR;     }
  else { return -1; }
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


/* - - - - Funcoes para controlo da lista de vertices descobertos - - - - */

/* enqueque(int i) --> guarda o vertice i na lista. */
void enqueque(int i) {
  No *novo = (No*) malloc(sizeof(No));

  novo->id = i;
  novo->next = NULL;

  if (lista_incio == NULL) {
    lista_incio = novo;
    lista_fim   = novo;
  } else {
    lista_fim->next = novo;
    lista_fim = novo;
  }
}

/* dequeque() --> retira o primeiro elemento da lista e devolve o seu id. */
int dequeque() {
  No *temp = lista_incio;
  int res  = lista_incio->id;

  lista_incio = lista_incio->next;
  free(temp);
  return res;
}

/* freeLista() --> Liberta a memoria reservada para a lista; */
void freeLista() {
  if (lista_incio != NULL) {
    No *temp = lista_incio->next;
    free(lista_incio);
    lista_incio = temp;
    freeLista();
  }
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */



/* - - - - - - - - - - - - - Funcoes sobre o fluxo - - - - - - - - - - - - - */

/* BFS() --> Encontra o caminho mais curto entre os vertices P e C. */
int BFS() {
  int i, u, v, n_vizinhos;

  for (i = 1; i < n_vertices; i++) {
    cor[i]  = BRANCO;
    dist[i] = -1;
    pais[i] = -1;
  }

  cor[P]  = CINZA;
  dist[P] = 0;
  pais[P] = -1;

  lista_incio = NULL;
  lista_fim   = NULL;
  enqueque(P);

  while (lista_incio != NULL) {
    u = dequeque();
    n_vizinhos = (u == P ? n_vertices-1 : 6);

    for (i = 0; i < n_vizinhos; i++) {

      if (grafo_cap[u][i] > 0) { /* As ligacoes com capacidade 0 nao contam. */
        if (u != P) {
          if (i == C) {

            freeLista();
            return u; /* Chegou-se ao target (C). */
          }

          v = encontraVizinho(i, u);

        } else { v = i+1; }

        if (cor[v] == BRANCO) {
          cor[v]  = CINZA;
          dist[v] = dist[u] + 1;
          pais[v] = u;
          enqueque(v);
        }
      }
    }

    cor[u] = PRETO;
  }

  return -1;  /* ja nao e possivel chegar de P a C.
                  ja nao ha caminhos de aumento. */
}

/* encontraFluxoMin(pai, filho) --> Funcao que encontra o fluxo que se pode
                                   aumentar no caminho encontrado. */
void encontraFluxoMin(int pai, int filho) {
  if (pai == P) {
    fluxoMin = min(fluxoMin, grafo_cap[P][filho-1]);
  } else if (filho == n_vertices) {
    fluxoMin = grafo_cap[pai][C];
    encontraFluxoMin(pais[pai], pai);
  } else {
    int lig = encontraLigacao(pai, filho);
    fluxoMin = min(fluxoMin, grafo_cap[pai][lig]);
    encontraFluxoMin(pais[pai], pai);
  }
}

/* edmonds_Karp() --> Calcula a divisao entre pontos de cenario e de primeiro
                      plano a partir de fluxos. */
void edmonds_Karp() {
  int i, paiTarget, atual, lig;

  cor  = (int*) malloc(n_vertices * sizeof(int));
  dist = (int*) malloc(n_vertices * sizeof(int));
  pais = (int*) malloc(n_vertices * sizeof(int));

  for (i = 1; i < n_vertices; i++) {
    fluxoMin = min(grafo_cap[P][i-1], grafo_cap[i][C]);
    grafo_cap[i][P] += fluxoMin;
    grafo_cap[P][i-1] -= fluxoMin;
    grafo_cap[i][C] -= fluxoMin;
  }

  for (paiTarget = BFS(); paiTarget != -1; paiTarget = BFS()) {

    encontraFluxoMin(paiTarget, n_vertices);

    grafo_cap[paiTarget][C] -= fluxoMin;

    for(atual = paiTarget; atual != P; atual = pais[atual]) {
      lig = encontraLigacao(atual, pais[atual]);
      grafo_cap[atual][lig] += fluxoMin;
      lig = encontraLigacao(pais[atual], atual);
      grafo_cap[pais[atual]][lig] -= fluxoMin;
    }
  }
  free(cor);
  free(pais);
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/* ------------------------------------------------------------------------- */



int main(int argc, char const *argv[]) {
  int i, j, viz, lig, temp;

  scanf("%d %d\n\n", &n_linhas, &n_colunas);
  if (n_linhas < 1 || n_colunas < 1) {
    printf("Os valores de m e n devem respeitar as condicoes: m >= 1 e n >= 1.\n");
    return 1;
  }

  /* Cria a matriz onde estarao as capacidades das ligacoes. */
  n_vertices = (n_linhas * n_colunas) + 1;
  grafo_cap  = (int**) malloc(n_vertices * sizeof(int*));

  grafo_cap[P] = (int*) malloc((n_vertices-1)*sizeof(int));
  for (i = 1; i < n_vertices; i++) {
    grafo_cap[i] = (int*) malloc(6*sizeof(int));
    for (j = 0; j < 6; j++) {
      grafo_cap[i][j] = 0;
    }
  }

  peso_plano   = (int*) malloc((n_vertices-1)*sizeof(int));
  peso_cenario = (int*) malloc((n_vertices-1)*sizeof(int));


  /* Le e guarda os pesos de 1 plano --> capacidades de ligar ao vertice P. */
  for (i = 0; i < (n_vertices-1); i++) {
    scanf("%d", &grafo_cap[P][i]);
    grafo_cap[i+1][P] = 0;
    peso_plano[i] = grafo_cap[P][i];
  }

  /* Le e guarda os pesos de cenario --> capacidades de ligar ao vertice C. */
  for (i = 1; i < n_vertices; i++) {
    scanf("%d", &grafo_cap[i][C]);
    peso_cenario[i-1] = grafo_cap[i][C];
  }

  /* Le e guarda as capacidades das ligacoes horizontais. */
  for (i = 1; i < n_vertices; i++) {
    j = right(i);
    if (j == -1) {
      grafo_cap[i][DIR] = 0;
    } else {
      scanf("%d", &grafo_cap[i][DIR]);
      grafo_cap[j][ESQ] = grafo_cap[i][DIR];
    }
  }

  /* Le e guarda as capacidades das ligacoes verticais. */
  for (i = 1; i < n_vertices; i++) {
    j = down(i);
    if (j == -1) {
      grafo_cap[i][BAIXO] = 0;
    } else {
      scanf("%d", &grafo_cap[i][BAIXO]);
      grafo_cap[j][CIMA] = grafo_cap[i][BAIXO];
    }
  }

  /* Calcula a divisao entre pontos de cenario e de primeiro plano a partir de fluxos. */
  edmonds_Karp();

  temp = 0;
  for (i = 1; i < n_vertices; i++) {
    if (dist[i] == -1) {
      temp += peso_plano[i-1];

      for (j = 1; j < 5; j++) {
        viz = encontraVizinho(j, i);

        if (viz > 0) {  /* se tiver vizinho --> a source (P) nao conta. */
          if (dist[viz] != -1) {  /* se ele estiver do outro lado do corte. */
            lig = encontraLigacao(i, viz);
            if (grafo_cap[i][lig] == 0) { /* se a capacidade da ligacao for 0
                                             entao o valor da ligacao e metade
                                             da ligacao contraria. */
              temp += (grafo_cap[viz][ligacaoReversa(lig)])/2;
            }
            else { temp += (grafo_cap[i][lig])/2; }
          }
        }
      }
    }
    else { temp += peso_cenario[i-1]; }
  }


  printf("%d\n\n", temp);

  temp = 0;
  for (i = 1; i < n_vertices; i++) {
    if (dist[i] == -1) { printf("P "); }
    else { printf("C "); }

    temp++;
    if (temp == n_colunas) {
      printf("\n");
      temp = 0;
    }
  }

  for (i = 0; i < n_vertices; i++) {
    free(grafo_cap[i]);
  }
  free(grafo_cap);

  free(dist);

  free(peso_plano);
  free(peso_cenario);

  return 0;
}
