#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int val1 = 0;
	int val2 = 0;
	int total = 0;
	char op;

	printf("digite o primeiro numero: \n");
	scanf("%d", &val1);
	
	printf("digite o segundo numero numero: \n");
	scanf("%d", &val2);
	
	printf("escolha uma opção:\na - soma\nb - subtrair\nc - multiplicar\nd - dividir\n");
	scanf("%1s", &op);
	op = toupper(op);

	switch(op){
		case 'A':
			total = val1 + val2;
			printf("%d + %d = %d\n", val1, val2, total);
			break;
		case 'B':
			total = val1 - val2;
			printf("%d - %d = %d\n", val1, val2, total);
			break;
		case 'C':
			total = val1 * val2;
			printf("%d * %d = %d\n", val1, val2, total);
			break;
		case 'D':
			total = val1 / val2;
			printf("%d / %d = %d\n", val1, val2, total);
			break;
	}

	return 0;
}
