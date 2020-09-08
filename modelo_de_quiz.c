#include <stdio.h>
#include <string.h>

int main(void)
{
	//variaveis.
	int pontos = 0;
	int erros = 0;
	int acertos = 0;
	int pergunta = 0;
	int resposta[10] = {2,3,1,2,3,2,4,4,2,1};
	int contador = 0;
	char classificacao[20];
	char nome[10];
	char excelente[] = "Excelente";
	char otimo[] = "Otimo";
	char bom[] = "Bom";
	char regular[] = "Regular";
	char pessimo[] = "`Pessimo";

	printf("\tQUIZ\n");
	printf("digite seu nome: ");
	scanf("%s", &nome);
	system("cls");

	//inicio do quiz.
	printf("\tescolha uma altermativa:\n");

	//---------------------------------------------------------------------------------------------
	pergunta = pergunta + 1;
	printf("pergunta %d: xxxxxxxxxxxxx\n1 - xxxxx\n2 - xxxxx\n3 - xxxxx\n4 - xxxxx\n", pergunta);
	scanf("%d", &resposta[contador]);
	if(resposta[contador] == 2)
	{
		pontos = pontos + 10;
		acertos = acertos + 1;
	}
	else
	{
		erros = erros + 1;
		putchar(7);
	}
	contador = contador + 1;
	system("cls");

	//---------------------------------------------------------------------------------------------
	pergunta = pergunta + 1;
	printf("pergunta %d: xxxxxxxxxxxxx\n1 - xxxxx\n2 - xxxxx\n3 - xxxxx\n4 - xxxxx\n", pergunta);
	scanf("%d", &resposta[contador]);
	if(resposta[contador] == 3)
	{
		pontos = pontos + 10;
		acertos = acertos + 1;
	}
	else
	{
		erros = erros + 1;
		putchar(7);
	}
	contador = contador + 1;
	system("cls");

	//---------------------------------------------------------------------------------------------
	pergunta = pergunta + 1;
	printf("pergunta %d: xxxxxxxxxxxxx\n1 - xxxxx\n2 - xxxxx\n3 - xxxxx\n4 - xxxxx\n", pergunta);
	scanf("%d", &resposta[contador]);
	if(resposta[contador] == 1)
	{
		pontos = pontos + 10;
		acertos = acertos + 1;
	}
	else
	{
		erros = erros + 1;
		putchar(7);
	}
	contador = contador + 1;
	system("cls");

	//---------------------------------------------------------------------------------------------
	pergunta = pergunta + 1;
	printf("pergunta %d: xxxxxxxxxxxxx\n1 - xxxxx\n2 - xxxxx\n3 - xxxxx\n4 - xxxxx\n", pergunta);
	scanf("%d", &resposta[contador]);
	if(resposta[contador] == 2)
	{
		pontos = pontos + 10;
		acertos = acertos + 1;
	}
	else
	{
		erros = erros + 1;
		putchar(7);
	}
	contador = contador + 1;
	system("cls");

	//---------------------------------------------------------------------------------------------
	pergunta = pergunta + 1;
	printf("pergunta %d: xxxxxxxxxxxxx\n1 - xxxxx\n2 - xxxxx\n3 - xxxxx\n4 - xxxxx\n", pergunta);
	scanf("%d", &resposta[contador]);
	if(resposta[contador] == 3)
	{
		pontos = pontos + 10;
		acertos = acertos + 1;
	}
	else
	{
		erros = erros + 1;
		putchar(7);
	}
	contador = contador + 1;
	system("cls");

	//---------------------------------------------------------------------------------------------
	pergunta = pergunta + 1;
	printf("pergunta %d: xxxxxxxxxxxxx\n1 - xxxxx\n2 - xxxxx\n3 - xxxxx\n4 - xxxxx\n", pergunta);
	scanf("%d", &resposta[contador]);
	if(resposta[contador] == 2)
	{
		pontos = pontos + 10;
		acertos = acertos + 1;
	}
	else
	{
		erros = erros + 1;
		putchar(7);
	}
	contador = contador + 1;
	system("cls");

	//---------------------------------------------------------------------------------------------
	pergunta = pergunta + 1;
	printf("pergunta %d: xxxxxxxxxxxxx\n1 - xxxxx\n2 - xxxxx\n3 - xxxxx\n4 - xxxxx\n", pergunta);
	scanf("%d", &resposta[contador]);
	if(resposta[contador] == 4)
	{
		pontos = pontos + 10;
		acertos = acertos + 1;
	}
	else
	{
		erros = erros + 1;
		putchar(7);
	}
	contador = contador + 1;
	system("cls");

	//---------------------------------------------------------------------------------------------
	pergunta = pergunta + 1;
	printf("pergunta %d: xxxxxxxxxxxxx\n1 - xxxxx\n2 - xxxxx\n3 - xxxxx\n4 - xxxxx\n", pergunta);
	scanf("%d", &resposta[contador]);
	if(resposta[contador] == 4)
	{
		pontos = pontos + 10;
		acertos = acertos + 1;
	}
	else
	{
		erros = erros + 1;
		putchar(7);
	}
	contador = contador + 1;
	system("cls");

	//---------------------------------------------------------------------------------------------
	pergunta = pergunta + 1;
	printf("pergunta %d: xxxxxxxxxxxxx\n1 - xxxxx\n2 - xxxxx\n3 - xxxxx\n4 - xxxxx\n", pergunta);
	scanf("%d", &resposta[contador]);
	if(resposta[contador] == 2)
	{
		pontos = pontos + 10;
		acertos = acertos + 1;
	}
	else
	{
		erros = erros + 1;
		putchar(7);
	}
	contador = contador + 1;
	system("cls");

	//---------------------------------------------------------------------------------------------
	pergunta = pergunta + 1;
	printf("pergunta %d: xxxxxxxxxxxxx\n1 - xxxxx\n2 - xxxxx\n3 - xxxxx\n4 - xxxxx\n", pergunta);
	scanf("%d", &resposta[contador]);
	if(resposta[contador] == 1)
	{
		pontos = pontos + 10;
		acertos = acertos + 1;
	}
	else
	{
		erros = erros + 1;
		putchar(7);
	}
	contador = contador + 1;
	system("cls");

	
	//Classificacao.
	if(pontos == 100)
	{
		strcpy(classificacao, excelente);
	}

	if((pontos <= 99) && (pontos >= 75))
	{
		strcpy(classificacao, otimo);
	}

	if((pontos <= 74) && (pontos >= 50))
	{
		strcpy(classificacao, bom);
	}

	if((pontos <= 49) && (pontos >= 25))
	{
		strcpy(classificacao, regular);
	}

	if(pontos <= 24)
	{
		strcpy(classificacao, pessimo);
	}

	//---------------------------------------------------------------------------------------------
	printf("Resultado do jogador: %s\n - Classificacao: %s!\n - PONTOS: %d\n - Numero de acertos: %d\n - Numero de erros: %d\n", nome, classificacao, pontos, acertos, erros);

	getch(); //aperte alguma tecla para finalizar o executavel.
	return 0;
}
