#include <stdio.h>
#define COINS 4
#define MAX 200

// denominaciones de las monedas
int coins[COINS] = { 1, 2, 5, 10};
int n;

void findMin(int cost)
{
	int coinList[MAX] = { 0 };
	int i, k = 0;

	for (i = COINS - 1; i >= 0; i--) {
		while (cost >= coins[i]) {
			cost -= coins[i];
			// Añadir monedas a la lista
			coinList[k++] = coins[i];
		}
	}

	for (i = 0; i < k; i++) {
		// imprimir lista
		printf("%d ", coinList[i]);
	}
	return;
}

int main(void)
{
	printf("Ingresa el valor que quieres en cambio \n (debe de ser entero positivo mayor a cero):");
	scanf("%d",&n);
	
	//resultado
	printf("El cambio en monedas para un total de %d: ", n);
	findMin(n);
	return 0;
}
