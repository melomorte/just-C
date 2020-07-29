#include <conio.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	FILE *fp;

	fp = fopen(argv[1], "rb");

	if (fp != NULL)
	{
		printf("sucesso!\n");
	}
	else
	{
		printf("erro!\n");
	}

	getch();

	fclose(fp);

	printf("arquivo fechado!\n");

	return 0;
}

//gcc openbin.c -o openbin.exe
//openbin.exe program.exe
