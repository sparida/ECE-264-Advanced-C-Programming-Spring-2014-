#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define ERROR_CODE 2
#define BUFFER_SIZE 2048

void printHelp()
{
	printf("Usage: grep-lite [OPTION]... PATTERN\nSearch for PATTERN in standard input.\nPATTERN is a string. grep-lite will search standard input line by\nline, and (by default) print out those lines which\ncontain pattern as a substring.\n\n");
	printf("  -v, --invert-match     print non-matching lines\n");
	printf("  -n, --line-number      print line number with output\n");
	printf("  -q, --quiet            suppress all output\n\n");
	printf("Exit status is 0 if any line is selected, 1 otherwise;\nif any error occurs, then the exit status is 2.\n");
}

int main(int argc, char **argv)
{
	int i;
	int hFlag = FALSE;
	int vFlag = FALSE;
	int nFlag = FALSE;
	int qFlag = FALSE;

	const char *pattern = argv[argc - 1];
	for (i= 1; i < argc - 1; i++)
	{
		if(strcmp(argv[i], "--help") == 0)
		{
			hFlag = TRUE;
		}
		else if(strcmp(argv[i], "--invert-match") == 0) 
		{
			vFlag = TRUE;
		}
		else if(strcmp(argv[i], "--line-number") == 0) 
		{
			nFlag = TRUE;
		}
		else if(strcmp(argv[i], "--quiet") == 0)
		{	
			qFlag = TRUE;
		}
		else if(strcmp(argv[i], "-v") == 0) 
		{
			vFlag = TRUE;
		}
		else if(strcmp(argv[i], "-n") == 0) 
		{
			nFlag = TRUE;
		}
		else if(strcmp(argv[i], "-q") == 0) 
		{
			qFlag = TRUE;
		}
		else
		{
			fprintf(stderr,"Error\n");
			return ERROR_CODE;
		}
	}

	if(hFlag || strcmp(pattern, "--help") == 0)
	{
		printHelp();
		return EXIT_SUCCESS;
	}
	
	if(argc == 1)
	{
		fprintf(stderr, "Error\n");
		return ERROR_CODE;
	}

	char buf[BUFFER_SIZE];
	int fFlag = FALSE;
	int curL = 0;

	while(fgets(buf, BUFFER_SIZE, stdin) != NULL)
	{
		curL++;
		int match = strstr(buf, pattern) != NULL;
		if((match && !vFlag) || (!match && vFlag))
		{
			fFlag = TRUE;
			if(!qFlag)
			{
				if(nFlag) fprintf(stdout, "%d: ", curL);
				fprintf(stdout, "%s", buf);

			}
		}
	}
	
	return fFlag ? 0 : 1;
	
}
 
