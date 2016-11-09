#include <stdio.h>
#include <stdlib.h>
#include "answer06.h"
int main(int argc, char **argv)
{
int value;
printf("Enter Value:");
scanf("%d", &value);
partitionOddAndEven(value);
return EXIT_SUCCESS;
}

