#include <stdio.h>

int main()
{
    int n;
    int k;
	printf("Ingresa el valor de 'n' (debe de ser entero positivo mayor a cero):");
    scanf("%d",&n);
    printf("Ingresa el valor de 'k' (debe de ser entero positivo mayor a cero):");
    scanf("%d",&k);
	printf("El valor de C (%d, %d) es = %d ", n, k,
		binomialCoeff(n, k));
	return 0;
}

// Devuleve el valor del coeficiente binomial = C(n, k)

int binomialCoeff(int n, int k)
{
	// Base Cases
	if (k > n)
		return 0;
	if (k == 0 || k == n)
		return 1;

	// Recur
	return binomialCoeff(n - 1, k - 1)
		+ binomialCoeff(n - 1, k);
}
