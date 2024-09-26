#include<stdio.h>

int main ()
{
  int n;
  printf("Ingresa el valor de 'n' (debe de ser entero positivo mayor a cero):");
  scanf("%d",&n);
  printf("%d", fib(n));
  getchar();
  return 0;
}

int fib(int n)
{
   if (n <= 1)
      return n;
   return fib(n-1) + fib(n-2);
}


