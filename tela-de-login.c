#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char login[25];
	char senha[25];
} pessoa; pessoa p[1];

int main()
{
	char login[25];
	char senha[25];

	strcpy(p[0].login, "melomorte");
	strcpy(p[0].senha, "melomorte");

	printf("\tLOGIN\n\nlogin: ");
	scanf("%24s", &login);
	printf("\nsenha: ");
	scanf("%24s", &senha);

	if ((strcmp(login,p[0].login)== 0) && (strcmp(senha,p[0].senha)== 0))
	{
		printf("logado com sucesso, %s!\n", login);
	}//else
	else
	{
		printf("login ou senha incorretos!\n");
	}

	return 0;
}
