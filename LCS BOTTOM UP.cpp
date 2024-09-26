
#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;

// regresa el tamaño del LCS para X[0..m-1], Y[0..n-1]
void lcs( char *X, char *Y, int m, int n )
{
int L[m+1][n+1];

/* siguiendo los pasos se construye L[m+1][n+1] por metodo bottom up
	dandonos cuenta que L[i][j] contiene el tamaño de LCS de X[0..i-1]
	y Y[0..j-1] */
for (int i=0; i<=m; i++)
{
	for (int j=0; j<=n; j++)
	{
	if (i == 0 || j == 0)
		L[i][j] = 0;
	else if (X[i-1] == Y[j-1])
		L[i][j] = L[i-1][j-1] + 1;
	else
		L[i][j] = max(L[i-1][j], L[i][j-1]);
	}
}

int index = L[m][n];

//crea un array para almacenar los datos

char lcs[index+1];
lcs[index] = '\0'; // se establece el caracter terminal

/* se empieza por lo que está más a la derecha del borde y
 uno por uno se guardan los caracteres en lcs[] */
int i = m, j = n;
while (i > 0 && j > 0)
{
	/* si el caracter actual en X[] y Y son los mismos,
	   entonces el caracter principal es parte del LCS */
	if (X[i-1] == Y[j-1])
	{
		lcs[index-1] = X[i-1]; // agrega el caracter al resultado
		i--; j--; index--;	 // reduce los valores de i, j y el index
	}

	/* si no son los mismos, entonces busca la mas larga de dos y
	   va en direccion del valor más grande */
	else if (L[i-1][j] > L[i][j-1])
		i--;
	else
		j--;
}

// imprime el resultado del LCS
cout << "LCS de " << X << " y " << Y << " es " << lcs;
}

// introducir datos para probar el programa
int main()
{
char X[] = "MATEMATICAS";
char Y[] = "ASTRONOMIA";
int m = strlen(X);
int n = strlen(Y);
lcs(X, Y, m, n);
return 0;
}
