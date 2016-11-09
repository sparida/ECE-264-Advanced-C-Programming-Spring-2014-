#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

void printHelp();
int catFile(char *, FILE *);

int main(int argc, char **argv)
{
	int i;
	for(i = 1;i < argc; i++)
	{
		if(strcmp(argv[i], "--help") == 0)
		{
			printHelp();
			return EXIT_SUCCESS;
		}
	}
	if(argc == 1)
	{
		if(catFile("-", stdout) == FALSE)
		{
			fprintf(stderr, "cat cannot open stdin\n");
			return EXIT_FAILURE;
		}
	}
	else
	{
		for(i = 1;i < argc; i++)
		{
			if(catFile(argv[i], stdout) == FALSE)
			{
				fprintf(stderr, "cat cannot open %s\n", argv[i]);
				return EXIT_FAILURE;
			}
		}
	}
	return EXIT_SUCCESS;
}

void printHelp()
{
	printf("Usage: cat-lite [--help] [FILE]...\n");
	printf("With no FILE, or when FILE is -, read standard input.\n\n");
	printf("Examples:\n");
	printf("  cat-lite README   Print the file README to standard output.\n");
	printf("  cat-lite f - g    Print f's contents, then standard input, \n");
	printf("                    then g's contents.\n");
	printf("  cat-lite          Copy standard input to standard output.\n\n");
	return;
}

int catFile(char *fName, FILE *outType)
{
	FILE *fin;
	char ch;
	if(strcmp(fName, "-") == 0)
	{
		fin = stdin;
	}
	else
	{
		fin = fopen(fName, "r");
	}

	if(fin == NULL)
	{
		return FALSE;
	}
	else
	{
		do 
		{
			ch = fgetc(fin);
			if(ch != EOF)
			{
				fputc(ch, stdout);
			}
			
		} 
		while (ch != EOF);
		fclose(fin);
	}

	return TRUE;
}
