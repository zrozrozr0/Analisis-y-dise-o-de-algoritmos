#include <stdio.h>
#define COINS 4
#define CANTIDAD 4
#define MAX 200
  
// All denominations of Indian Currency
int coins[COINS] = { 1, 2, 5, 10};
int cantidad[CANTIDAD] = {8, 20, 50, 30};
int n;
  
void findMin(int cost)
{
    int coinList[MAX] = { 0 };
    int i, a, k = 0;

  
    for (i = COINS - 1; i >= 0; i--) {
    	a = cantidad[i];
        while (cost >= coins[i] && a > 0) {
            cost -= coins[i];
            a--;
            // Add coin in the list
            coinList[k++] = coins[i];
        }
        
    }
  
    for (i = 0; i < k; i++) {
        // Print
        printf("%d ", coinList[i]);
    }
    return;
}
  
int main(void)
{
    
	printf("Ingresa el valor que quieres en cambio \n (debe de ser entero positivo mayor a cero):");
	scanf("%d",&n);  
    printf("El cambio en monedas para un total de %d: ", n);
    findMin(n);
    return 0;
}
