#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CHAR_COUNT 1000
int get_nr_of_lines(FILE ** fpp);
void get_lines(char ** lines, FILE ** fpp);

int main(int argc, char *argv[])
{
	char ** lines;
	FILE *fp = fopen(argv[1], "r");
	if (fp == NULL)
	{
		fprintf(stderr, "can't open %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	int nr_lines = get_nr_of_lines(&fp);
	lines = malloc(sizeof(char*) * nr_lines);
	get_lines(lines, &fp);

	for (int i = 0; i < nr_lines; i++)
		puts(lines[i]);
}

int get_nr_of_lines(FILE ** fpp)
{
	int count = 0;
	char temp[CHAR_COUNT];
	while (fgets(temp, CHAR_COUNT, *fpp))
		count++;
	rewind(*fpp);
	return count;
}

void get_lines(char ** lines, FILE ** fpp)
{
	char current_line[CHAR_COUNT];
	char * p = NULL;
	int i = 0;
	while (fgets(current_line, CHAR_COUNT, *fpp))
	{
		p = malloc(strlen(current_line));
		current_line[strlen(current_line)-1] = '\0';
		strcpy(p, current_line);
		lines[i] = p;
		i++;
	}
}
