#include <bits/stdc++.h>

using namespace std;
// Compilaci�n: g++ "Mochila Fraccionada2.cpp" -o m2
/*Estructura de un art�culo que almacena el peso y
valor recurrente del art�culo*/
struct Item {
int value, weight;
// Constructor
Item(int value, int weight)
{
this->value=value;
this->weight=weight;
}
};
//Funci�n de comparaci�n para ordenar el art�culo seg�n la relaci�n valor/peso
bool cmp(struct Item a, struct Item b)
{
double r1 = (double)a.value / (double)a.weight;
double r2 = (double)b.value / (double)b.weight;
return r1 > r2;
}
// Funci�n principal greddy para resolver el problema
double fractionalKnapsack(int W, struct Item arr[], int n)
{
// ordenar el art�culo en funci�n de la proporci�n
sort(arr, arr + n, cmp);

int curWeight = 0; // Peso actual de la mochila
double finalvalue = 0.0; // Resultado
// Bucle a trav�s de todos los elementos
for (int i = 0; i < n; i++) {
//Si no sobrepasa el peso, agregarlo por compelto
if (curWeight + arr[i].weight <= W) {
curWeight += arr[i].weight;
finalvalue += arr[i].value;
}

// Si sobrepasa el peso, fraccional el elemento
else {
int remain = W - curWeight;
finalvalue += arr[i].value
* ((double)remain
/ (double)arr[i].weight);
break;
}
}
// regresar el valor final
return finalvalue;
}
//programa principal
int main()
{
int W;// Peso de la mochila
Item arr[] = { { 300000, 120 }, { 1000000, 96}, {30000000, 4000} };
int n = sizeof(arr) / sizeof(arr[0]);

printf("\n Introduce el numero de equipos:\t");
scanf("%d",&W);
// Llamando a la funci�n

cout << "Valor maximo que podemos obtener = "
<< fractionalKnapsack(W, arr, n);
return 0;
}

