#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

char grid[9] = {'_', '_', '_', '_', '_', '_', '_', '_', '_'};

int game_over(void);
void computer_play(void);
void get_human(void);
void display_grid(void);

int main(void)
{
	srand(time(NULL));
	bool computer_turn = rand() % 2;
	int status;
	
	while (!(status = game_over()))
	{
		if (computer_turn)
			computer_play();
		else
			get_human();
		display_grid();
		computer_turn = !computer_turn;
	}

	if (status == 1)
		printf("Computer wins!\n");
	else if (status == 2)
		printf("You wins!\n");
	else
		printf("Draw!\n");
}

void computer_play(void)
{
	int index;
	do
	{
		index = rand() % 10;
	} while (grid[index] != '_');

	grid[index] = 'O';
	printf("Computer chosen index %d\n", index+1);
}

void get_human(void)
{
	int index;
	do
	{
		printf("Enter your chosen index: ");
		scanf(" %d", &index);
	} while (grid[index-1] != '_');
	grid[index-1] = 'X';
}

int game_over(void)
{
	char c[] = {'X', 'O'};
	for (int i = 0; i < 2; i++)
	{
		int total = c[i] * 3;
		if (	grid[0] + grid[1] + grid[2] == total ||
			grid[3] + grid[4] + grid[5] == total ||
			grid[6] + grid[7] + grid[8] == total ||

			grid[0] + grid[3] + grid[6] == total ||
			grid[1] + grid[4] + grid[7] == total ||
			grid[2] + grid[5] + grid[8] == total ||

			grid[0] + grid[4] + grid[8] == total ||
			grid[2] + grid[4] + grid[6] == total )
			return c[i] == 'O' ? 1 : 2;
	}
	return 0;
}

void display_grid(void)
{
	printf("#### GRID ####\n");
	for (int i = 0; i < 9; i+=3)
	{
		printf("     ");
		printf("%c %c %c\n", grid[i], grid[i+1], grid[i+2]);
	}
}
