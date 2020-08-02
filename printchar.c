#include <stdio.h>

int main(int argc, char const *argv[])
{

   int i;
   int x;
   int cont = 0;

   printf("quantos caracteres? \n");
   scanf("%100000d", &x);

   for (cont, x; cont < x; cont++)
   {
   		printf("%d - %c\n", i, i);
   		i++;
   }
	return 0;
}
