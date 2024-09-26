
/*Alumno: Noé Rodríguez Olmos
  Algoritmo de strassen para multiplicacion rapida de matrices
  Método: Divide y vencerás
  Fecha: 20 de oct 2021 */

#include <stdio.h>

int power(int base, int exp){
    int i=0, p=1;
    while(++i<exp+1 && 1*(p*=base));
    return p;
}

void Madd(int* A, int* B, int* C, int n, int x){
    int i,j, m=x>0?n/2:n;
    for (i=0;i<m;i++)
        for (j=0;j<m;j++)
            *(C+i*m+j) = *(A+i*n+j) + *(B+i*n+j);
}

void Msub(int* A, int* B, int* C, int n, int x){
    int i,j, m=x>0?n/2:n;
    for (i=0;i<m;i++)
        for (j=0;j<m;j++)
            *(C+i*m+j) = *(A+i*n+j) - *(B+i*n+j);
}

void strassen(int* A, int* B, int* C, int n){
    int i,j;
    if(n==2){
        int P=(*A+*(A+n+1))*(*B+*(B+n+1));  //P=(A[0][0]+A[1][1])*(B[0][0]+B[1][1])
        int Q=(*(A+n)+*(A+n+1))*(*B);   //Q=(A[1][0]+A[1][1])*B[0][0]
        int R=(*A)*(*(B+1)-*(B+n+1));   //R=A[0][0]*(B[0][1]-B[1][1])
        int S=(*(A+n+1))*(*(B+n)-*B);   //S=A[1][1]*(B[1][0]-B[0][0])
        int T=(*A+*(A+1))*(*(B+n+1));   //T=(A[0][0]+A[0][1])*B[1][1]
        int U=(*(A+n)-*A)*(*B+*(B+1));  //U=(A[1][0]-A[0][0])*(B[0][0]+B[0][1])
        int V=(*(A+1)-*(A+n+1))*(*(B+n)+*(B+n+1));  //V=(A[0][1]-A[1][1])*(B[1][0]+B[1][1])

        *C=P+S-T+V;
        *(C+1)=R+T;
        *(C+n)=Q+S;
        *(C+n+1)=P+R-Q+U;
    }
    else{
        int m=n/2, x[m][m], y[m][m], o[n][n];
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                o[i][j]=0;

        /*P=(A[0][0]+A[1][1])*(B[0][0]+B[1][1])*/
        int P[m][m];
        Madd(A, A+m*(n+1), x, n, 1);
        Madd(B, B+m*(n+1), y, n, 1);
        strassen(x, y, P, m);

        /*Q=(A[1][0]+A[1][1])*B[0][0]*/
        int Q[m][m];
        Madd(A+m*n, A+m*(n+1), x, n, 1);
        Madd(B, o, y, n, 1);
        strassen(x, y, Q, m);

        /*R=A[0][0]*(B[0][1]-B[1][1])*/
        int R[m][m];
        Madd(A, o, x, n, 1);
        Msub(B+m, B+m*(n+1), y, n, 1);
        strassen(x, y, R, m);

        /*S=A[1][1]*(B[1][0]-B[0][0])*/
        int S[m][m];
        Madd(A+m*(n+1), o, x, n, 1);
        Msub(B+m*n, B, y, n, 1);
        strassen(x, y, S, m);

        /*T=(A[0][0]+A[0][1])*B[1][1]*/
        int T[m][m];
        Madd(A, A+m, x, n, 1);
        Madd(B+m*(n+1), o, y, n, 1);
        strassen(x, y, T, m);

        /*U=(A[1][0]-A[0][0])*(B[0][0]+B[0][1])*/
        int U[m][m];
        Msub(A+m*n, A, x, n, 1);
        Madd(B, B+m, y, n, 1);
        strassen(x, y, U, m);

        /*V=(A[0][1]-A[1][1])*(B[1][0]+B[1][1])*/
        int V[m][m];
        Msub(A+m, A+m*(n+1), x, n, 1);
        Madd(B+m*n, B+m*(n+1), y, n, 1);
        strassen(x, y, V, m);


        /*Calcular las 4 partes para la matriz resultante*/
        int W[m][m], X[m][m], Y[m][m], Z[m][m];
        Msub(V,T,x,m,0);
        Madd(S,x,y,m,0);
        Madd(P,y,W,m,0); // W=P+S-T+V
        Madd(R,T,X,m,0); // X==R+T
        Madd(Q,S,Y,m,0); // Y=Q+S
        Msub(U,Q,x,m,0);
        Madd(R,x,y,m,0);
        Madd(P,y,Z,m,0); // Z=P+R-Q+U

        /*Concatenar los resultados para la matriz resultante*/
        for (i=0;i<m;i++)
            for (j=0;j<m;j++){
                *(C+i*n+j) = W[i][j]; //C[0][0]=W
                *(C+i*n+j+m) = X[i][j]; //C[0][1]=X
                *(C+(i+m)*n+j) = Y[i][j]; //C[1][0]=Y
                *(C+(i+m)*n+j+m) = Z[i][j]; //C[1][1]=Z
            }
    }
}

void main()
{
    int i,j,k,m,n,n1,n2,n3,n4,o=0;

    /*Introducir los datos de la primera matriz*/
    printf("Introduce el tamaño de la primera matriz \n (no. fila despues enter. no. columna despues enter):");
    scanf("%d%d",&n1,&n2);
    int A[n1][n2];
    printf("\n Introduce la primera matriz:\n\n");
    for(i=0;i<n1;i++){
        printf("Ingresa los elementos de la %d-a fila:",i+1);
        for(j=0;j<n2;j++)
            scanf(" %d",&A[i][j]);
    }

    /*Introducir los datos de la segunda matriz*/
    printf("\n\nIntroduce el numero de columnas de la 2da matriz:");
    scanf("%d",&n3);
    int B[n2][n3];
    printf("\nIntroduce la segunda matriz:\n\n");
    for(i=0;i<n2;i++){
        printf("Ingresa los elementos de la %d-th fila:",i+1);
        for(j=0;j<n3;j++)
           scanf(" %d",&B[i][j]);
    }

    /*Creacion de la matriz cuadrada de orden 2^n para todo y rellenando los huecos con 0, excepto los que tienen numero*/
    n4=n1>n2?n1:n2;
    n=n3>n4?n3:n4;
    while(n>(m=power(2,++o)));
    int a[m][m],b[m][m],C[m][m];
    for(i=0;i<m;i++)
        for(j=0;j<m;j++){
            a[i][j]=0;
            b[i][j]=0;
        }
    for(i=0;i<n1;i++)
        for(j=0;j<n2;j++)
            a[i][j]=A[i][j];
    for(i=0;i<n2;i++)
        for(j=0;j<n3;j++)
            b[i][j]=B[i][j];

    /*Opcional : imprimir la primera matriz*/
    printf("\nThis is the first matrix:");
    for(i=0;i<n1;i++){
        printf("\n\n\n");
        for(j=0;j<n2;j++)
            printf("\t%d",a[i][j]);
    }
    /*Opcional : imprimir la segunda matriz*/
    printf("\n\n\nThis is the second matrix:");
    for(i=0;i<n2;i++){
        printf("\n\n\n");
        for(j=0;j<n3;j++)
            printf("\t%d",b[i][j]);
    }

    strassen(a,b,C,m);    //Llamada a la función

    /*Imprimiendo la matriz resultante o matriz final*/
    printf("\n\n\n Esta es la matriz resultante:");
    for(i=0;i<n1;i++){
        printf("\n\n\n");
        for(j=0;j<n3;j++)
            printf("\t%d",C[i][j]);
    }
}
