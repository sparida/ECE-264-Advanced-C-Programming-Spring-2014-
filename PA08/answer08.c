#include <stdio.h>
#include <stdlib.h>
#include "answer08.h"


void fChange(SparseNode * mnode, SparseNode *array1, SparseNode *array2);

SparseNode * SparseNode_create(int index, int value)
{
	SparseNode *node = malloc(sizeof(SparseNode));
	node->index = index;
	node->value = value;
	node->left = NULL;
	node->right = NULL;
	return node;
}

SparseNode * SparseArray_insert(SparseNode * array, int index, int value)
{
	if(value == 0) return array;

	if(array == NULL) return SparseNode_create(index, value);

	if(array->index == index)
	{
		array->value = value;
	}
	else if(array->index > index)
	{
		array->left = SparseArray_insert(array->left, index, value);
	}
	else if(array->index < index)
	{
		array->right = SparseArray_insert(array->right, index, value);
	}

	return array;
}

SparseNode * SparseArray_build(int * indices, int * values, int length)
{
	if (length == 0) return NULL;
	int i = 0;

	SparseNode *node = SparseNode_create(indices[i], values[i]);

	for(i = 1; i < length; i++)
	{
		node = SparseArray_insert(node, indices[i], values[i]);
	}
	return node;
}

void SparseArray_destroy(SparseNode * array)
{
	if(array == NULL) return;
	SparseArray_destroy(array->left);
	SparseArray_destroy(array->right);
	free(array);
}

int SparseArray_getMin(SparseNode * array)
{
	if(array->left == NULL) return array->index;
	return SparseArray_getMin(array->left);
}

int SparseArray_getMax(SparseNode * array)
{
	if(array->right == NULL) return array->index;
	return SparseArray_getMax(array->right);
}

SparseNode * SparseArray_getNode(SparseNode * array, int index)
{
	if (array == NULL) return NULL;
	
	if(array->index == index) return array;
	
	if(array->index < index) return SparseArray_getNode(array->left, index);
	
	return SparseArray_getNode(array->right, index); 
}

SparseNode * SparseArray_remove(SparseNode * array, int index)
{
	if(array == NULL) return NULL;
	
	if(array->index < index)
	{	
		array->right = SparseArray_remove(array->right, index);
		return array;
	}
	if(array->index > index) 
	{
		array->left = SparseArray_remove(array->left, index);
		return array;
	}
	
	int left = (array->left == NULL);
	int right = (array->right == NULL);

	if(left && right) {free(array);return NULL;}

	if(left)
	{
		SparseNode *node = array->right;
		free(array);
		return node;
	}

	if(right)
	{
		SparseNode *node = array->left;
		free(array);
		return node;
	}

	SparseNode *p = array -> right;

	while((p->left) != NULL)
	{
		p = p -> left;
	}

	int t = p -> index;
	p->index = array->index;
	array -> index = t;

	array -> right =  SparseArray_remove(array -> right, p -> index);
	return array;
	
}


SparseNode * SparseArray_copy(SparseNode * array)
{
	SparseNode *cnode = NULL;

	if(array == NULL) return cnode;
	
	cnode = SparseNode_create(array->index, array->value);

	cnode->left = SparseArray_copy(array->left);
	cnode->right = SparseArray_copy(array->right);

	return cnode;

}

SparseNode * SparseArray_merge(SparseNode * array_1, SparseNode * array_2)
{
	SparseNode *mnode = SparseArray_copy(array_1);

	fChange(mnode, array_1, array_2);

	return mnode;

}


void fChange(SparseNode * mnode, SparseNode *array1, SparseNode *array2)
{
	if(array2 == NULL) return;

	SparseNode *node = SparseArray_getNode(array1, array2->index);
	if (node == NULL)  
	{
	mnode = SparseArray_insert(mnode, array2->index, array2->value);
	}
	
	else
	{
	int dec = node->value + array2->value;
	
	if(dec == 0)
	{
	SparseArray_remove(mnode, array2->index);
	}
	else
	{
	mnode = SparseArray_insert(mnode, node->index, dec); 
	}

	}

	fChange(mnode, array1, array2->left);
	fChange(mnode, array1, array2->right);

	return;
	
	

}

