#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char const *argv[])
{
	printf("\tMelomorte running...\n\n");

	FILE *fp; //criar um arquivo de texto para guardar os diretorios.

	fp = fopen("dir.txt", "w");

	//passo 1 - listar os diretorios.
	DIR *dir;
	struct dirent *lsdir;

	dir =  opendir("c:\\");
	
	//impressão de diretorios na tela:
	while ( (lsdir = readdir(dir) )!= NULL)
	{
		printf("%s\n", lsdir->d_name); //imprime os diretorios no cmd.
		fprintf(fp, "%s\n", lsdir->d_name); //grava os diretorios em um arquivo "dir.txt".
	}
	
	fclose(fp); //fecha fopen.
	
	closedir(dir); //finaliza a função.

	return 0;
}
