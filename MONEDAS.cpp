#include <bits/stdc++.h>

using namespace std;

const int N = 4;
const int INF = 1000000;

int monedas[N] = {1, 3, 4, 5};  // tipos de monedas
int memoria[100001];            // maximo valor que se puede pedir
int valor;
// funcion de retorno de cambio de monedas
int cambio (int valor){
    //retorno si valor < 0
	if (valor <0) return INF;
	//retorno si valor = 0
	if (valor == 0) return 0;
	//retorno si valor > 0
	if (memoria[valor] != -1) return memoria[valor]; // verificar que no exceda el valor

	int res = INF;
	for (int i = 0; i < N; i++){
		res = min(res, cambio(valor - monedas[i]));
	}
	return memoria[valor] = res + 1;                // se almacenan los valores
}

int main(){

	memset(memoria, -1, sizeof memoria);

    printf("Ingresa el valor que quieres en cambio \n (debe de ser entero positivo mayor a cero):");
	scanf("%d",&valor);                             //pide el valor
	for (int i = 0; i <= valor; i++){              // bucle para ver los cambios
		cout << i << " = " << cambio(i) << endl;   // se imprime el valor y se concatena con el cambio
	}
	return 0;
}

