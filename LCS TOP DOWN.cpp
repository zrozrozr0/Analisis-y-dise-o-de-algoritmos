#include <bits/stdc++.h>
using namespace std;

// regresa el tamaño del LCS para X[0..m-1], Y[0..n-1]

int lcs(string X, string Y, int m, int n)
{
	if (m == 0 || n == 0)
		return 0;

	if (X[m - 1] == Y[n - 1])
		return 1 + lcs(X, Y, m - 1, n - 1);
	else
		return max(lcs(X, Y, m, n - 1),
				lcs(X, Y, m - 1, n));
}

/* introducir datos para probar el programa */

int main()
{
	string X = "MATEMATICAS";
	string Y = "ASTRONOMIA";

	// busca el tamaño de la cadena
	int m = X.length();
	int n = Y.length();

	cout << "Tamaño del LCS: " << lcs(X, Y, m, n);

	return 0;
}

