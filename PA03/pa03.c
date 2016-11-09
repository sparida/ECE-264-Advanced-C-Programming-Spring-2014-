#include <stdio.h>
#include <stdlib.h>
#include "answer03.h"
#include <string.h>

int main(int argc, char * * argv )
{
	int n;
	char *str = (char *) malloc(9 * sizeof(char));
	strcpy(str, "heythere");
	printf("%s\n", str);
	n = sizeof(str);
	printf("n:%d\n", n);

	const char *st = "helloa";
	strcat_ex(&str,&n,st);	
	printf("%s\n", str);
	sortStringCharacters(str);
	printf("%s\n", str);
	return EXIT_SUCCESS;
}

