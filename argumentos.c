#include <conio.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	int cont;
	for(cont = 0; cont < argc; cont++){
		printf("%d parametros: %s\n", cont, argv[cont]);
	}

	getch();
	return 0;
}

//gcc argumentos. -o argumentos.exe
//argumentos.exe 0 1 2 3 4 5 6 7 8 9 10
