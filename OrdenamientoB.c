
/*
Alumna: Zepeda Cano Jessica del Carmen
Programa que ordena n cantidad de numeros a partir del ordenamiento burbuja
Fecha: 20 de juenio del 2021
Compilación
gcc OrdenamientoB.c -o bu.exe
*/
#include<stdlib.h>
#include<stdio.h>
#include<time.h>


int Bubble(int *num,int n);
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
    n=atoi(argv[1]); //tama�o del arreglo n

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

      Bubble(num,n);
    //Termina medición del tiempo
    t_final = clock();
    t_intervalo = (double)(t_final - t_inicio) / CLOCKS_PER_SEC;
    printf("\nTiempo medido: %.10f segundos.", t_intervalo);
return 0;
}

int Bubble(int *num,int n)
{
    int i,j;
    int aux;
     for(i=0;i<n-1;i++)
    {
        for(j=0;j<n;j++)
        {
            if(num[j]>num[j+1])
            {
                aux=num[j];
                num[j]=num[j+1];
                num[j+1]=aux;
            }
        }

    }

    for(i=0;i<n;i++)
    {
        printf("\n%d",num[i]);
    }


}


