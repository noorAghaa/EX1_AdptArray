#include "AdptArray.h"
#include <stdlib.h>
#include <string.h>

typedef struct AdptArray_
{
	int size;
	PElement* array;
	PRINT_FUNC printFunction;
	DEL_FUNC deleteFunction;
	COPY_FUNC copyFunction;
}AdptArray;

/**
* Function to create an Adpy Array.
* Inputs are the copy, delete and print functions
* returns pointer to our current array
*/
PAdptArray CreateAdptArray(COPY_FUNC copyFunction, DEL_FUNC deleteFunction, PRINT_FUNC printFunction)
{
	PAdptArray arrPointer = (PAdptArray)malloc(sizeof(AdptArray));
	if (!arrPointer)
	{
		return NULL;
	}
	arrPointer->array = NULL;
	arrPointer->copyFunction = copyFunction;
	arrPointer->deleteFunction = deleteFunction;
	arrPointer->printFunction = printFunction;
	arrPointer->size = 0;
	return arrPointer;
}

/**
* Input - pointer to AdptArray, index to change and new element.
* The function will set the array at our given index to be the new element.
* Output - Success or Fail.
*/
Result SetAdptArrayAt(PAdptArray arr, int index, PElement newElement)
{
	if (arr == NULL)
	{
		return FAIL;
	}

	if (index >= arr->size)
	{
		PElement* newArrPointer;
		if ((newArrPointer = (PElement*)calloc((index + 1), sizeof(PElement))) == NULL)
		{
			return FAIL;
		}
		memcpy(newArrPointer, arr->array, (arr->size) * sizeof(PElement));
		free(arr->array);
		arr->array = newArrPointer;
		arr->size = index + 1;
	}
	if (arr->array[index] != NULL)
	{
		arr->deleteFunction(arr->array[index]);
	}
	arr->array[index] = arr->copyFunction(newElement);
	return SUCCESS;
}


/**
* Return AdptArr size
*/
int GetAdptArraySize(PAdptArray pArr) {
	if (pArr == NULL) {
		return -1;
	}
	return pArr->size;
}

/**
*Input is pointer to Adpt Array.
* The function will itirate the array, free each element, and then free the pointer.
*/
void DeleteAdptArray(PAdptArray pArr)
{
	if (!pArr)
	{
		return;
	}
	for (int i = 0; i < pArr->size; i++)
	{
		if (pArr->array[i] != NULL)
		{
			pArr->deleteFunction((pArr->array)[i]);
		}
	}
	free(pArr->array);
	free(pArr);
}



/**
* Return the PElements of the given index
*/
PElement GetAdptArrayAt(PAdptArray pArr, int index) {
	if (!pArr->array[index])
	{
		return NULL;
	}
	else
	{
		return pArr->copyFunction(pArr->array[index]);
	}
}



/**
* Prints all the array elements
*/
void PrintDB(PAdptArray pArr)
{
	if (!pArr)
	{
		return;
	}
	for (int i = 0; i < pArr->size; i++)
	{
		if (pArr->array[i] != NULL)
		{
			pArr->printFunction(pArr->array[i]);
		}
	}
}
