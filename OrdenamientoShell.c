/*
Alumna: Zepeda Cano Jessica del Carmen
Programa que ordena n cantidad de numeros a partir del ordenamiento shell
Fecha: 20 de juenio del 2021
Compilación 
gcc OrdenamientoShell.c -o she.exe
*/
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include <math.h>




int Shell(int *num, int n);
int main (int argc, char* argv[])
{
    // Variables para tomar el  tiempo
    clock_t t_inicio, t_final;
    double t_intervalo;
 // Variables del algoritmo
    int n,i,*num;
 //Recibir por argumento el tamaño de 
    if(argc !=2)
    {
        exit(1); // Ejemplo: nombre.exe n <archivo.txt
    }

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

      Shell(num,n);
//Termina medición del tiempo
    t_final = clock();
    t_intervalo = (double)(t_final - t_inicio) / CLOCKS_PER_SEC;
    printf("\nTiempo medido: %.10f segundos.", t_intervalo);
return 0;
}

int Shell(int *num, int n)
{
      
    int incr = n / 2, p, j;
    int tmp;
do
{
for (p = incr; p < n; p++)
{
tmp = num[p];
j = p - incr;
while ((j >= 0) && (tmp < num[j]))
{
num[j + incr] = num[j];


j -= incr;
}
num[j+incr] = tmp;
}
incr /= 2;
}
while (incr > 0);


    for(int i=0;i<n;i++)
    {
        printf("\n%d",num[i]);
    }



}
