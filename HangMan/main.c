#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define NR_OF_LETTERS 15
#define CHAR_SIZE 100
struct Word
{
	char * word;
	char * hint;
};
int get_nr_of_lines(FILE **fpp)
{
	int count = 0;
	char s[CHAR_SIZE];
	while (fgets(s, CHAR_SIZE, *fpp))
		count++;
	rewind(*fpp);
	return count;
}
void get_lines(char ** lines, FILE ** fpp)
{
	char current_line[CHAR_SIZE];
	int i = 0;
	char * p = NULL;
	while (fgets(current_line, CHAR_SIZE, *fpp))
	{
		p = malloc(strlen(current_line));
		current_line[strlen(current_line)-1] = '\0'; // excluding '\n'
		strcpy(p, current_line);
		lines[i++] = p;
	}
}
struct Word * words;
int nr_words;
int init_words(const char * fn)
{
	// initialize the words dynamic array by reading the csv file
	FILE *fp = fopen(fn, "r");
	const int nr_lines = get_nr_of_lines(&fp);

	words = malloc(sizeof(struct Word) * nr_lines);

	char ** lines = malloc(sizeof(char*) * nr_lines);
	get_lines(lines, &fp);

	int i, j;
	for (i = 0; i < nr_lines; i++)
	{
		j = 0;
		words[i].word = &lines[i][j];
		while (lines[i][j++] != ',')
			;
		lines[i][--j] = '\0';
		words[i].hint = &lines[i][++j];
	}
	return nr_lines;
}
void start_game(void);
void clear_buffer(void);
int main(void)
{
	nr_words = init_words("words.csv");
	int i;
	while (1)
	{
		printf("Enter 1 to start, 0 to quit");
		scanf("%d", &i);
		clear_buffer();
		if (i == 1)
			start_game();
		else
			break;
	}
}
void hangman(int wrong)
{
// yeah i copied and paste this piece of code
     if(wrong == 1) {

	printf(" ________  \n");
	printf("|       |\n");
	printf("|      \n");
	printf("|      \n");
	printf("|      \n");
	printf("|      \n");
	printf("|___________|      \n");
	printf("|___________|");

    } else if(wrong == 2) {

	printf(" ________  \n");
	printf("|       |\n");
	printf("|       0 \n");
	printf("|      \n");
	printf("|      \n");
	printf("|      \n");
	printf("|___________|      \n");
	printf("|___________|");

    } else if(wrong == 3) {
	printf(" ________  \n");
	printf("|       |\n");
	printf("|       0 \n");
	printf("|      \\|/   \n");
	printf("|      \n");
	printf("|      \n");
	printf("|___________|      \n");
	printf("|___________|");

    } else if(wrong == 4) {

	 printf(" ________  \n");
	printf("|       |\n");
	printf("|       0 \n");
	printf("|      \\|/   \n");
	printf("|       |\n");
	printf("|      /\n");
	printf("|___________|      \n");
	printf("|___________|");

    } else if(wrong == 5) {

	printf(" ________  \n");
	printf("|       |\n");
	printf("|       0 \n");
	printf("|      \\|/   \n");
	printf("|       |\n");
	}
}
void clear_buffer(void)
{
	while(getchar() != '\n')
		;
}
void start_game(void)
{
	int r = rand() % nr_words; // random number, index of the word
	char * word = words[r].word;
	char display[strlen(word)+1]; // string that represent the progress
	int i;
	for (i = 0; i <strlen(word); i++)
		if (word[i] != ' ')
			display[i] = '_';
		else
			display[i] = ' ';
	display[i] = '\0';

	int wrong = 0;
	char c;

	while (1)
	{
		hangman(wrong);
		if (wrong == 5 || strchr(display, '_') == NULL)
			break;

		printf("\n\nWrong attempts: %d\n", wrong);
		printf("CURRENT WORD --> %s\n", display);
		printf("HINT -> %s\n", words[r].hint);
		printf("Enter your guess: ");
		c = getchar();
		clear_buffer();
		if (strchr(word, c) == NULL)
			wrong++;
		else
		{
			// making the character visible
			for (i = 0; word[i] != '\0'; i++)
				if (word[i] == c)
					display[i] = c;
		}
	}

	if (wrong == 5)
	{
		printf("YOU FUCKING LOSE!\n");
		printf("The word was %s\n", word);
	}
	else
		printf("You won!\n");
}
