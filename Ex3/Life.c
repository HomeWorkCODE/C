#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* dimensions of the screen */

#define BOARD_WIDTH		(70)
#define BOARD_HEIGHT	(70)

#define KGRN  "\x1B[32m"
#define KMAG  "\x1B[35m"

/* set everthing to zero */
void initializeBoard (int board[][BOARD_HEIGHT]) 
{
	memset(board,0,sizeof(int)*BOARD_HEIGHT*BOARD_HEIGHT);
}


/* return the number of live cells in the neighborhood of the i,j cell */
int liveNeighbors(int board[][BOARD_HEIGHT],int i,int j)
{
	int k,l;
	int count = 0;

	/* go around the cell */

	for (k=-1; k<=1; k++)
	{
		for (l=-1; l<=1; l++)
		{
			if ((((i+k)< BOARD_WIDTH)
				&&
				((j+l) < BOARD_HEIGHT))
				&&
				((i+k) >= 0)
				&&
				((j+l) >= 0)
				&&
				((k||l)))
					if (board[i+k][j+l])
						count ++;
		}
	}

	return count;
}

void play(int board[][BOARD_HEIGHT])
{
/* 
	-A dead cell with exactly three live neighbors becomes a live cell (birth).
	-A live cell with two or three live neighbors stays alive (survival).
	-In all other cases, a cell dies or remains dead (overcrowding or loneliness).
*/
	int i,j;
	int live_neighbors  = 0;
	int nextGenaration[BOARD_WIDTH][BOARD_HEIGHT];

	/* for each cell, apply the rules of Life */

	for (i=0; i<BOARD_HEIGHT; i++) 
		for (j=0; j<BOARD_WIDTH; j++) 
		{
			live_neighbors = liveNeighbors(board, i, j);
			// printf("%d - > (%d,%d)\n",live_neighbors,i,j);

			if(live_neighbors == 2)
				nextGenaration[i][j] = board[i][j];

			if(live_neighbors == 3)
				nextGenaration[i][j] = 1;

			if(live_neighbors < 2)
				nextGenaration[i][j] = 0;

			if(live_neighbors > 3)
				nextGenaration[i][j] = 0;
		}

	memcpy(board,nextGenaration,sizeof(int)*BOARD_HEIGHT*BOARD_HEIGHT);
}

/* print the life board */

void print(int board[][BOARD_HEIGHT]) 
{
	int	i, j;

	for(i=0; i<BOARD_HEIGHT; i++)
	{

		for(j=0; j<BOARD_WIDTH; j++) 
			printf ("%c",board[i][j] ? 'x' : ' ');

		printf ("\n");
	}
}

/* read a file into the life board */

void read_file(int board[][BOARD_HEIGHT], char *name)
{
	FILE * f;
	int	i, j;
	char c;

	f = fopen (name, "r");
	for(i=0; i<BOARD_HEIGHT; i++) 
	{
		for(j=0; j<BOARD_WIDTH; j++)
		{
			c = fgetc(f);
			board[i][j] = (c == 'x');
		}
		fgetc(f); /*jump over the \n*/
	}

	fclose (f);
}

/* create a board file */

void creat_file()
{
	FILE * f;
	int	i, j;

	f = fopen ("board_.txt", "w+");
	for(i=0; i<BOARD_HEIGHT; i++) 
	{

		for(j=0; j<BOARD_WIDTH; j++)
		{
			fputc('.',f);
		}
		fputc('\n',f);

	}

	fclose (f);
}

int main(int argc, char *argv[]) 
{

	if (strcmp(argv[1], "create") == 0)
	{
		creat_file();
		return 0;
	}
	else if (argc != 3)
	{	
		printf("usage: Life <number of generations to run> <file>\nOR\nusage: Life create");
		return 1;
	}

	int	board[BOARD_WIDTH][BOARD_HEIGHT];
	int i, j;

	initializeBoard (board);
	read_file (board, argv[2]);

	/*board[50][51] = 1;
	board[51][53] = 1;
	board[52][50] = 1;
	board[52][51] = 1;
	board[52][54] = 1;
	board[52][55] = 1;
	board[52][56] = 1;
*/
		

	for (i=0; i<=atoi(argv[1]); i++) 
	{
		print(board);
		play(board);

		/* clear the screen using VT100 escape codes */
		printf("\t\t\t\t\tGenerations: %d\n", i);
		/*sleep(1);*/
		puts ("\033[H\033[J");
		//printf("__________\n");
	}
	return 0;
}