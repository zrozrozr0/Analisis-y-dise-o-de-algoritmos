/* Irving Omar Ruiz Vivaldo
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define TRUE 1
#define FALSE 0
#define INFINITO 1000000000

typedef struct arista{
  int x;
  int y;
  int peso;
  char marca;
}arco;

typedef struct header {
  struct nodo1 *liga;
}head;

typedef struct nodo1 {
  struct nodo1 *izq;
  struct nodo2 *der;
}indice;

typedef struct nodo2 {
  struct nodo2 *liga;
  int dato;
}elemento;

head   *unir(head *apuntlista, indice *w1, indice *w2);
arco   *pares(int numNod, int **Matriz, int numArc);
arco   *kruskal(arco *R, int numNod, int numArc);
indice *buscar(head *apuntlista, int elemento);
int    distintos(indice *A, indice *B);
void   imprimeDatos(head *apuntlista);
int    cardinalidad(head *auntlista);
arco   minimo(arco *Q, int numArc);
head   *inicial(int numNod);


main()
{
  int i,j,numNod,numArc, **M=NULL;
  arco *arc=NULL, *Q=NULL;
  char lt='a';
  setlocale(LC_ALL, "spanish");
  printf("\n Programa que emplea el algoritmo de Kruskal para\n"
         " hallar el Árbol Abarcador Minimal. Usa -1 para infinito\n\n");
  printf(" Ingresa el Número de nodos: ");
  scanf(" %d", &numNod);
  numArc=0;
  /* Crear la matriz de nxn */
  M = (int **) malloc(numNod*sizeof(int *));
  for (i=0;i<numNod;i++)
    M[i] = (int *) malloc(numNod*sizeof(int));
  /* LLenar la Matriz */
  printf("\n Ingresa la Matriz Triangular\n");
  for(i=0; i<numNod; i++)
    for(j=i; j<numNod; j++)
    {
      scanf(" %d",&M[i][j]);
      M[j][i] = M[i][j];
      numArc++;
      if(M[i][j] <= 0)
       numArc--;
      if(M[i][j] < 0)
        M[i][j] = INFINITO;
    }

  printf("\n\n Matriz de Adyacencia\n");
  for(i=0; i<numNod; i++)
    {
      for(j=0; j<numNod; j++)
      {
        if(M[i][j] == INFINITO)
          printf(" 8 ");
        else
          printf(" %d ",M[i][j]);
      }
      printf("\n");
    }
  /* Calcular los arcos y el peso de cada uno, mostrarlos*/
  printf("\n\n Los arcos son:\n");
  arc = pares(numNod,M,numArc);
  for(i=0; i<numArc; i++)
   printf(" %c - %c: %d\n", lt+arc[i].x, lt+arc[i].y, arc[i].peso);

  /* Calcular El Arbol Abarcador Minimal y mostrar los datos */
  printf("\n\n Los arcos del Árbol Abarcador Minimal son:\n");
  Q = kruskal(arc,numNod,numArc);
  for(i=0; i<numNod-1; i++)
   printf(" Arco %c - %c, Peso: %d\n", lt+Q[i].x, lt+Q[i].y, Q[i].peso);
  printf(" \n\n");
}

/* Calcula el arbol abarcador minimal, guarda los vertices en Q */
arco *kruskal(arco *R, int numNod, int numArc)
{
  int pos=0;
  arco t, *Q=NULL;
  head *VS=NULL;
  indice *w1=NULL,*w2=NULL;

  /* Arbol tiene numNod-1 aristas*/
  Q = (struct arista *) malloc(sizeof(arco)*(numNod-1));

  VS = inicial(numNod);
  while(cardinalidad(VS) > 1)
  {
    t = minimo(R, numArc);
    w1 = buscar(VS,t.x);
    w2 = buscar(VS,t.y);
    if(distintos(w1,w2) == TRUE)
    {
      VS = unir(VS,w1,w2);
      Q[pos].x = t.x;
      Q[pos].y = t.y;
      Q[pos].peso = t.peso;
      pos++;
    }
  }
  return Q;
}

/* Devuelve las aristas (pares de nodos) y su peso asociado */
arco *pares(int numNod, int **Matriz, int numArc)
{
  arco *R=NULL;
  int i,j,k=0;

  R = (struct arista *) malloc(sizeof(arco)*numArc);

  for(i=0; i<numNod; i++)
    for(j=i+1; j<numNod; j++)
      if(Matriz[i][j] != INFINITO)
      {
        R[k].x = i;
        R[k].y = j;
        R[k].peso = Matriz[i][j];
        k++;
      }
  return R;
}

/* Devuelve el arco de menor peso no marcado en R, lo marca */
arco minimo(arco *R, int numArc)
{
  int k,t,pos;
  k=0; t=-1;
  do{
    if(R[k].marca != '*')
    {
      t = R[k].peso;
      pos = k;
    }
    k++;
  }while(t==-1 && k<numArc);

  for(k=0; k<numArc; k++)
    if(R[k].marca != '*')
      if(t > R[k].peso)
      {
        t = R[k].peso;
        pos = k;
      }
  R[pos].marca = '*';
  return R[pos];
}

/* Crea el conjunto inicial */
head *inicial(int numNod)
{
  int k;
  head *lp=NULL;
  indice *tmp=NULL;
  elemento *tmpp=NULL;

  lp = (struct header *) malloc(sizeof(head));
  lp->liga = (struct nodo1 *) malloc(sizeof(indice));
  tmp = lp->liga;
  for(k=0; k<numNod; k++)
  {
    tmp->der = (struct nodo2 *) malloc(sizeof(elemento));
    tmpp = tmp->der;
    tmpp->dato = k;
    tmpp->liga = NULL;
    tmp->izq = (struct nodo1 *) malloc(sizeof(indice));
    if(k == numNod-1)
      tmp->izq = NULL;
    else
      tmp = tmp->izq;
  }

  return lp;
}

/* Busca x en el conjunto de conjuntos y devuelve el conjunto al que pertenece x*/
indice *buscar(head *apuntlista, int x)
{
  int f;
  indice *tmp=NULL;
  elemento *tmpp=NULL;

  f=0;
  tmp = apuntlista->liga;
  while(tmp != NULL && f==0)
  {
    tmpp = tmp->der;
    while(tmpp != NULL && f==0)
      if(tmpp->dato == x)
      {
        f=1;
        return tmp;
      }
      else
        tmpp = tmpp->liga;
    tmp = tmp->izq;
  }
}

/* Sustituye w1 por w1Uw2 y elimina w2 */
head *unir(head *apuntlista, indice *w1, indice *w2)
{
  int f,f2;
  indice *tmp=NULL, *tmp1=NULL;
  elemento *tmpp=NULL;

  // Buscar al conjunto w2
  f=f2=0;
  tmp = apuntlista->liga;
  while(f==0 && tmp != NULL)
  {
    if(distintos(w2,tmp) == FALSE)
      f = 1;
    else{
      f2 = 1;
      tmp1 = tmp;
      tmp = tmp->izq;
    }
  }
  // Elminar al Conjunto w2
  if(f2 == 0){
    apuntlista->liga = tmp->izq;
    tmp = apuntlista->liga;
  }
  else{
    tmp1->izq = tmp->izq;
    tmp = apuntlista->liga;
  }
  // Sustituir w1 por w1Uw2
  f=0;
  while(f==0 && tmp!=NULL)
    if(distintos(w1,tmp) == FALSE)
      f = 1;
    else
      tmp = tmp->izq;

  tmpp = tmp->der;
  while(tmpp->liga != NULL)
    tmpp = tmpp->liga;
  tmpp->liga = w2->der;

  return apuntlista;
}

/* Devuelve TRUE si dos listas de tipo elemento
   son distintas FALSE en caso contrario */
int distintos(indice *A, indice *B)
{
  int f = TRUE;
  int nA,nB;
  nA=nB=0;
  elemento *tm, *tm2;
  tm = A->der; tm2 = B->der;
  while(tm != NULL)
  { nA++; tm = tm->liga; }
  while(tm2 != NULL)
  { nB++; tm2 = tm2->liga; }
  if(nA == nB)
  {
    tm = A->der; tm2 = B->der;
    while(tm != NULL && f == TRUE)
    {
      if(tm->dato == tm2->dato)
        f = FALSE;
      tm = tm->liga; tm2 = tm2->liga;
    }
  }
  return f;
}

/* Devuelve el numero de elementos de tipo indice almacenados */
int cardinalidad(head *apuntlista)
{
  int cont=0;
  indice *lp=NULL;
  if(apuntlista == NULL)
   return 0;
  else{
    lp = apuntlista->liga;
    while(lp != NULL)
    {
      cont++;
      lp = lp->izq;
    }
    return cont;
  }
}

/* Imprime el contenido de la lista */
void imprimeDatos(head *apuntlista)
{
  char let = 'a';
  indice *tmp=NULL;
  elemento *tmpp=NULL;

  if(apuntlista == NULL)
    printf("\n No Hay Datos\n");
  else{
    tmp = apuntlista->liga;
    while(tmp != NULL)
    {
       tmpp = tmp->der;
       printf(" Elementos: ");
       while(tmpp != NULL)
       {
         printf("%c\t", let+tmpp->dato);
         tmpp = tmpp->liga;
       }
       printf("\n");
       tmp = tmp->izq;
    }
    printf("\n");
  }
}
