#include <stdlib.h>
#include "answer01.h"

int arraySum(int * array, int len)
{
	int sum = 0;  //Sum of elements of array
	int index;  //Array Index Counter
	
	for(index = 0; index < len; ++index)
	{
		sum += array[index];
	}

	return sum;
}

int arrayCountNegative(int * array, int len)
{	
	int index = 0;  //Array Index Counter
	int counter = 0;  //Number of elemenys less than 0
	
	for(index = 0; index < len; ++index)
		{
			if(array[index] < 0)
			{
				counter++;
			}

		}

	return counter;
}

int arrayIsIncreasing(int * array, int len)
{
	int index = 0;  //Array Index Counter
	
	for(index = 1; index < len; ++index)
		{
			if(array[index] < array[index - 1])
			{
				return 0;
			}
		}
	
	return 1;
}


int arrayIndexRFind(int needle, const int * haystack, int len)
{
	int index = 0;  //Array Index Counter
	int finalIndex = -1;  //Index of found needle
	
	for(index = 0; index < len; ++index)
		{
			if(haystack[index] == needle)
			{
				finalIndex = index;
			}
		}

	return finalIndex;
}

int arrayFindSmallest(int * array, int len)
{
	int index = 0;  //Array Index Counter
	int smallIndex = -1;  //Index of found needle
	int small;  //Smallest numnber temporarily

	
	if(len == 0)
	{
		return 0;
	}

	else
	{
		small = array[len - 1];

		for(index = (len - 1); index >= 0; index--)
		{
			if(array[index] <=  small)
			{
				smallIndex = index;
				small = array[index];
			}
		}
	}

	return smallIndex;
}
