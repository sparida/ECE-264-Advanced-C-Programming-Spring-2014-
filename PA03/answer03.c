#ifndef PA03_H
#define PA03_H 

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int compare (const void *, const void *);
int compareStr(const void *, const void *);

char * strcat_ex(char * * dest, int * n, const char * src)
{
	size_t src_len = strlen(src);
	size_t dest_len = *dest == NULL ? 0 : strlen(*dest);

	if((*dest == NULL) || ((src_len + dest_len + 1) >= *n) )
			{
				*n = 1 + 2 * (src_len + dest_len);
				char *buf =  malloc( *n * sizeof(char) );
				*buf = '\0'; 
				if(*dest != NULL)
				{
					strcpy(buf,  *dest);
				}
	
				free(*dest);
				*dest = buf;
			}

	strcat(*dest, src);
	return(*dest);
}

char * * explode(const char * str, const char * delims, int * arrLen)
{
	*arrLen = 1;
	int count = 0;

	while(str[count] != '\0')
	{
		if(strchr(delims, str[count]))
		{
			(*arrLen)++;
		}
		count++;
	}

	char **string_list = malloc( sizeof(char*) * *arrLen);

	count = 0;
	const char* start = str;
	const char* pos = str;

	while(*pos != '\0')
	{
		if(strchr(delims, *pos))
		{
			int len = pos - start;
			string_list[count] = malloc(sizeof(char) * (len +1));
			memcpy(string_list[count], start, sizeof(char) * len);
			string_list[count][len] = '\0';
			count++;
			start = pos + 1;
		}
		pos++;
	}
	int len = pos - start;
	string_list[count] = malloc(sizeof(char) * (len + 1));
	memcpy(string_list[count], start, sizeof(char) * len);
	string_list[count][len] = '\0';

	return string_list;

}

char * implode(char * * strArr, int len, const char * glue)
{
	int n = 0;
	int counter = 0;
	char *buf = NULL;
	strcat_ex(&buf, &n, (const char*) strArr[0]);
	for(counter = 1; counter < len; counter++)
	{
		strcat_ex(&buf, &n, glue);
		strcat_ex(&buf, &n, (const char*) strArr[counter]);
	}
	return(buf);
}

void sortStringArray(char * * arrString, int len)
{
	if(len != 0 && arrString != NULL)
	{
		qsort(&arrString[0], len, sizeof(char *), compareStr);
		
	}
	return;
}

void sortStringCharacters(char * str)
{
	if(str != NULL)
	{
		qsort (&str[0], strlen(str), sizeof(char), compare);
	}
	return;

}

int compare (const void * a, const void * b)
{
	  return ( *(char*)a - *(char*)b );
}

int compareStr(const void * a, const void * b)
{
	char *const *ca = a;
	char *const *cb = b;
	return strcmp(*ca, *cb);
}

void destroyStringArray(char * * strArr, int len)
{
	int counter = 0;
	if(len != 0)
	{
		for(counter = 0;counter < len; counter++)
		{
			free(strArr[counter]);
		}
		free(strArr);
	}
}

#endif
