#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main(int argc, char const *argv[])
{
	int vetor[3]; //recebe um maximo de 3 inteiros + null;
	int x = 0; //contador;
	int soma = 0; //vai alocar a soma dos vetores;
	int i = 0; //auxiliar no laço for;

	printf("entre com um numero de tres unidades e pressione a tecla 'enter' duas vezes: \n");
	do{
		for (i; i < 3; i++)
		{
			scanf("%1d", &vetor[x]); //"%1d" vai garantir que apenas um int será armazenado em cada posição no vetor por loop;
			x++;
		}
	}
	while(getche() != '\r'); //'r' = enter

	soma = (vetor[0] + vetor[1]) + vetor[2];

	printf("o numero digitado foi: %d%d%d\n", vetor[0], vetor[1], vetor[2]);
	printf("a soma de %d + %d + %d = %d\n", vetor[0], vetor[1], vetor[2], soma);

	return 0;
}
