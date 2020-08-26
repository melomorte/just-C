#include <stdio.h>
#include <stdlib.h>

char grade[3][3];

void main(void)
{
	int x, y, line, colun, count = 0;

	//desenho da grade.
	for (x = 0; x < 3; x++)
	{
		putchar('\n');
		for(y = 0; y < 3; y++)
		{
			putchar('\t');
			grade[x][y] = '-';
			printf("%c", grade[x][y]);
		}
		putchar('\n');
		putchar('\n');
	}

	for(count = 0; count < 9; count++)
	{
		printf("line: \n");
		scanf("%2d", &line);
		fflush(stdout);
		line--;

		printf("colun: \n");
		scanf("%2d", &colun);
		fflush(stdout);
		colun--;
		system("cls");

		putchar('\n');
		if(grade[line][colun] == '-')
		{
			if(count % 2)
			{
				grade[line][colun] = 'O';
			}
			else
			{
				grade[line][colun] = 'X';
			}
			for(x = 0; x < 3; x++)
			{
				putchar('\n');
				for(y = 0; y < 3; y++)
				{
					putchar('\t');
					printf("%c", grade[x][y]);
				}
				putchar('\n');
				putchar('\n');
			}
			if((grade[0][0] == grade[0][1] && grade[0][0] == grade[0][2] && grade[0][0] != '-')||
			   (grade[0][0] == grade[1][1] && grade[0][0] == grade[2][2] && grade[0][0] != '-')||
			   (grade[0][0] == grade[1][0] && grade[0][0] == grade[2][0] && grade[0][0] != '-')||
			   (grade[0][1] == grade[1][1] && grade[0][1] == grade[2][1] && grade[0][1] != '-')||
			   (grade[0][2] == grade[1][2] && grade[0][2] == grade[2][2] && grade[0][2] != '-')||
			   (grade[1][0] == grade[1][1] && grade[1][0] == grade[1][2] && grade[1][0] != '-')||
			   (grade[2][0] == grade[2][1] && grade[2][0] == grade[2][2] && grade[2][0] != '-')||
			   (grade[2][0] == grade[1][1] && grade[2][0] == grade[0][2] && grade[2][0] != '-'))
			{
				putchar(8);
				printf("player %d win!\n", (count % 2) + 1);
				exit(0);
			}
		}
		else
		{
			putchar(8);
			printf("posicao invalida!\n");
			count--;
		}
	}
	putchar(8);
	printf("draw!\n");
	return;
}
