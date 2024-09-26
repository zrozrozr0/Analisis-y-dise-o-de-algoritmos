/*
Programa que ordena n cantidad de numeros a partir del ordenamiento mezcla
Fecha: 20 de juenio del 2021
Compilación 
gcc MergeSort.c -o me.exe 
*/

#include<stdlib.h>
#include<stdio.h>
#include<time.h>


void MergeSort(int *num, int p, int r);
int Merge(int *num, int p, int q, int r);

int main (int argc, char* argv[])
{
    // Variables para tomar el  tiempo
    clock_t t_inicio, t_final;
    double t_intervalo;
// Variables del algoritmo
    int n,i,*num;
//Recibir por argumento el tamaño de n
    if(argc !=2)
    {
        exit(1); // Ejemplo: nombre.exe n <archivo.txt
    }

    //Tomamos los argumentos de main
    n=atoi(argv[1]); //tama�o del arreglo

    num=(int*)malloc(n*sizeof(int)); //Apartar memoria para n
    if(num==NULL)
    {
        exit(1);
    }
    //leer n y colocarlos en num
    for(i=0;i<n;i++)
        scanf("%d",&num[i]);
//Inicia medición del tiempo
    t_inicio = clock();

      MergeSort(num,0,n);
 //Termina medición del tiempo
    t_final = clock();
    t_intervalo = (double)(t_final - t_inicio) / CLOCKS_PER_SEC;
    printf("\nTiempo medido: %.10f segundos.", t_intervalo);
return 0;
}
void MergeSort(int *num, int p, int r)
{
    int q;
    if(p<r)
    {
        q=p+(r-p)/2;
        MergeSort(num,r,q);
        MergeSort(num,q+1,r);
        Merge(num,p,q,r);
    }
}
int Merge(int *num, int p, int q, int r)
{
    int i, j, k, t, d;
    t=q-p+1; d=r-q;
    int ai[t], ad[d];
    for(i=0; i<t;i++)
        ai[i]=num[p+i];
    for(j=0; j<d; j++)
        ad[j]=num[q+1+j];
    i=0; j=0; k=p;

    while(i<t && j<d)
    {
        if(ai[i] <= ad[j])
        {
            num[k] =ai[i];
            i++;
        }
        else{
            num[k]= ad[j];
            j++;

        }
        k++;
    }
    while(i<t)
    {
        num[k] =ai[i];
        i++; k++;

    }
    while(j<d)
    {
        num[k] = ad[j];
        j++; k++;
    }

    for(i=0;i<r;i++)
    {
        printf("\n%d",num[i]);
    }
    
     
}



