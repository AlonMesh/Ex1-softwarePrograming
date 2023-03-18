#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"
#include <string.h>

// definition of the AdptArray struct
typedef struct AdptArray_
{
	int ArrSize;
	PElement* pElemArr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
	PRINT_FUNC printFunc;
}AdptArray;



// function for creating an adaptive array
PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_, PRINT_FUNC printFunc)
{
	PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
	if (pArr == NULL)
		return NULL;
	pArr->ArrSize = 0;
	pArr->pElemArr = NULL;
	pArr->delFunc = delFunc_;
	pArr->copyFunc = copyFunc_;
	pArr->printFunc = printFunc;
	return pArr;
}

// function for setting an element at a specific index in the adaptive array
Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem)
{
	PElement* newpElemArr;
	if (pArr == NULL || idx < 0)
		return FAIL;

	if (idx >= pArr->ArrSize)
	{
		
		// Extend Array
   		newpElemArr = (PElement*)calloc((idx + 1), sizeof(PElement));
		if (newpElemArr == NULL)
			return FAIL;
		memcpy(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement));
		free(pArr->pElemArr);
		pArr->pElemArr = newpElemArr;
		pArr->ArrSize = idx + 1;  // update array size
	}

	// Delete Previous Elem
	if (pArr->pElemArr[idx] != NULL)
	pArr->delFunc((pArr->pElemArr)[idx]);

	(pArr->pElemArr)[idx] = pArr->copyFunc(pNewElem);
	return SUCCESS;
}

// function for deleting an adaptive array
void DeleteAdptArray(PAdptArray pArr)
{
	if (pArr == NULL)
		return;

	for (int i = 0; i < pArr->ArrSize; ++i)
	{
		if (pArr->pElemArr[i] != NULL) // Check if element is not NULL before calling delFunc
			pArr->delFunc(pArr->pElemArr[i]);
	}
	
	free(pArr->pElemArr);
	free(pArr);
}

// returns a copy of an element from a given index
PElement GetAdptArrayAt(PAdptArray pArr, int idx)
{
	if (pArr == NULL || idx < 0 || idx >= pArr->ArrSize || pArr->pElemArr[idx] == NULL)
		return NULL;
	
	return pArr->copyFunc((pArr->pElemArr)[idx]);
}

// returns the corrent size of the array
int GetAdptArraySize(PAdptArray pArr)
{
	if (pArr == NULL)
		return -1;
	
	return pArr->ArrSize;
}

// print each elemnt in the array
void PrintDB(PAdptArray pArr)
{
	if (pArr == NULL)
		return;

	for (int i = 0; i < pArr->ArrSize; i++) {
		PElement element = pArr->pElemArr[i];
		
		if (element != NULL) {
			pArr->printFunc(element);
		}
	}
}
