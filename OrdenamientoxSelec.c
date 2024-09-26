#include<stdlib.h>
#include<stdio.h>
#include<time.h>
/*
Alumna: Zepeda Cano Jessica del Carmen
Programa que ordena n cantidad de numeros a partir del ordenamiento por seleccion
Fecha: 20 de juenio del 2021
Compilación 
gcc OrdenamientoB.c -o bu.exe 
*/

int Selec(int *num, int n);
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

      Selec(num,n);
//Termina medición del tiempo
    t_final = clock();
    t_intervalo = (double)(t_final - t_inicio) / CLOCKS_PER_SEC;
    printf("\nTiempo medido: %.10f segundos.", t_intervalo);
return 0;
}

int Selec(int *num, int n)
{
    int i, j, p, aux;
    for(i=0;i<n-1;i++)
    {
        j=i;
        for(p=i+1;p<n;p++)
        {
            if((num[p])<(num[j]))
            {
                j=p;
            }
        }
        aux=num[j];
        num[j]=num[i];
        num[i]=aux;
    }

    for(i=0;i<n;i++)
    {
        printf("\n%d",num[i]);
    }

}