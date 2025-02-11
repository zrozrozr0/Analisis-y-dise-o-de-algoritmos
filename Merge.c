#include <stdio.h>
#include <stdlib.h>
  
// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
  
    /* create temp arrays */
    int L[n1], R[n2];
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0;
    j = 0; //mezcla
    k = l; 
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

  /*Ya se ha recorrido R[] añadimos
a arr[], los elementos de L[] que
están ordenados*/
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
  
    /* Ya se ha recorrido L[] añadimos
        a arr[] los elementos de R[] que
        están ordenados */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* Divide al vector en dos partes iguales,
y se realiza la llamada recursiva a un
método merge que seguirá dividiendo
y mezcla*/
void mergeSort(int arr[], int l, int r)
{
    if (l < r) {
        
        int m = l + (r - l) / 2;
  
        
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
  
        merge(arr, l, m, r);
    }
}
  
/*Función que imprime el areglo*/
void printArray(int A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}
  

int main()
{
    int arr[] = { 12, 11, 13, 5, 6, 7 };
    int arr_size = sizeof(arr) / sizeof(arr[0]);
  
    printf("Arreglo desordenado \n");
    printArray(arr, arr_size);
  
    mergeSort(arr, 0, arr_size - 1);
  
    printf("\nArreglo ordenado \n");
    printArray(arr, arr_size);
    return 0;
}

