#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#define SIZE 15
#define ROW 10
#define COLUMN 20
#define NR_OF_BLOCKS 5

struct Block
{
	int x;
	int y;
	const char * s;
	bool solved;
	bool up_to_down;
};

void randomize_grid(void);	// puts random characters in grid
void display_grid(void);
int get_nr_of_words(FILE **fp);
void get_words(char ** words, FILE **fp);	// puts words into word array
int *get_indices(int word_count);		// get random indices for words
bool search(int *indices, int index);		// searches if an int is in an array
void get_blocks(struct Block * blocks, char ** words, int * indices);
void make_block(struct Block * block, int x, int y, bool up_to_down, const char * s);
void write_grid(struct Block * block);
bool over_written(int x, int y, bool up_to_down, int length);	// checks if the word is going to over write a char
void clear_grid(struct Block * block);

char grid[ROW][COLUMN];

int main(void)
{
	srand(time(NULL));
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COLUMN; j++)
			grid[i][j] = ' ';
	}

	FILE *fp = fopen("words.txt", "r");
	int word_count = get_nr_of_words(&fp); // get number of words to allocate precise array length
	char ** words = malloc(sizeof(char*) * word_count);
	get_words(words, &fp);
	int * indices = get_indices(word_count); // get random word indices

	struct Block blocks[NR_OF_BLOCKS]; // structure to store each block of word
	get_blocks(blocks, words, indices); // get x, y, and up_to_down for each block
	randomize_grid();
	display_grid();
	char guess[10]; // char array to store user input
	int score = 0; // int to store user score
	for (;;)
	{
		if (score == NR_OF_BLOCKS) // the user has completely found 5 blocks
			break;
		display_grid();
		printf("Score: %d\n", score);
		printf("Enter the guess: ");
		scanf("%s", guess);
		for (int i = 0; i < NR_OF_BLOCKS; i++)
		{
			if (strcmp(blocks[i].s, guess) == 0 && !blocks[i].solved)
			{
				clear_grid(&blocks[i]);
				blocks[i].solved = true;
				score++;
				printf("You scored a %d\n", score);
			}
		}
		system("clear");
	}
}


void randomize_grid(void)
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COLUMN; j++)
		{
			char cr = 'A' + (rand() % 26);
			if (grid[i][j] == ' ')
				grid[i][j] = cr;
		}
	}
}

void display_grid(void)
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COLUMN; j++)
			printf("%c", grid[i][j]);
		printf("\n");
	}
}

int get_nr_of_words(FILE **fp)
{
	int count = 0;
	char w[SIZE];
	while (fgets(w, SIZE, *fp))
		count++;
	rewind(*fp);
	return count;
}

void get_words(char ** words, FILE **fp)
{
	char * current_word = malloc(SIZE);
	char * p = NULL;
	int word_index = 0;
	while (fgets(current_word, SIZE, *fp))
	{
		p = malloc(strlen(current_word));	// excluded '\n'
		current_word[strlen(current_word)-1] = '\0';
		strcpy(p, current_word);
		words[word_index++] = p;
	}
	free(current_word);
}

int* get_indices(int word_count)
{
	int i,j;
	int *indices = malloc(sizeof(int) * NR_OF_BLOCKS);
	for (i = 0; i < NR_OF_BLOCKS; i++)
		indices[i] = -1;
	for (i = 0; i < NR_OF_BLOCKS; i++)
	{
		int index = rand() % word_count;
		if (!search(indices, index))
			indices[i] = index;
		else
			i--;
	}
	return indices;
}

bool search(int * indices, int index)
{
	for (int i = 0; i < NR_OF_BLOCKS; i++)
		if (indices[i] == index)
			return true;
		else if (indices[i] == -1)
			return false;
	return false;
}

void make_block(struct Block * block, int x, int y, bool up_to_down, const char * s)
{
	block->x = x;
	block->y = y;
	block->up_to_down = up_to_down;
	block->s = s;
	block->solved = false;
}

void get_blocks(struct Block * blocks, char ** words, int * indices)
{
	int i = 0;
	int x,y;
	bool up_to_down;
	int wlen;
	while (i != NR_OF_BLOCKS)
	{
		x = rand() % ROW;
		y = rand() % COLUMN;
		up_to_down = rand() % 2;
		wlen = strlen(words[indices[i]]);
		bool in_bound = up_to_down ? (y + wlen) <= COLUMN : (x + wlen) <= ROW;
		if (in_bound)
		{
			if (over_written(x, y, up_to_down, wlen))
				continue;
			make_block(blocks+i, x, y, up_to_down, words[indices[i]]);
			write_grid(blocks+i);
			i++;
		}
	}
}

void write_grid(struct Block * block)
{
	int i;
	char *ptr = block->s;
	i = 0;
	if (block->up_to_down)
	{
		while (*ptr)
		{
			grid[block->x][block->y + i] = *ptr++;
			i++;
		}
	}
	else
	{
		while (*ptr)
		{
			grid[block->x + i][block->y] = *ptr++;
			i++;
		}
	}
}

bool over_written(int x, int y, bool up_to_down, int length)
{
	if (up_to_down)
	{
		for (int i = 0; i < length; i++)
			if (grid[x][y+i] != ' ')
				return true;
	}
	else
	{
		for (int i = 0; i < length; i++)
			if (grid[x+i][y] != ' ')
				return true;
	}
	return false;
}

void clear_grid(struct Block *block)
{
	if (block->up_to_down)
	{
		for (int i = 0; i < strlen(block->s); i++)
			grid[block->x][block->y+i] = '*';
	}
	else
	{
		for (int i = 0; i < strlen(block->s); i++)
			grid[block->x+i][block->y] = '*';
	}
}
