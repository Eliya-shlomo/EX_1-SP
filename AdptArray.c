//
// Created by eliya on 13/03/2023.
//
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"

typedef struct AdptArray_
{
    int ArrSize;
    PElement* pElemArr;
    DEL_FUNC delFunc;
    COPY_FUNC copyFunc;
    PRINT_FUNC PRINT_FUNC;
}pAdptArray;




PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC delFunc,PRINT_FUNC printFunc){

PAdptArray pArr = (PAdptArray)malloc(sizeof(pAdptArray));
if (pArr == NULL)   return NULL;
pArr->ArrSize = 0;
pArr->pElemArr = NULL;
pArr->delFunc = delFunc;
pArr->copyFunc = copyFunc;
pArr->PRINT_FUNC =printFunc;
return pArr;
}




Result SetAdptArrayAt(PAdptArray pArr, int index, PElement pNewElem)
{
    PElement* newpElemArr;
    if (pArr == NULL)
        return FAIL;

    if (index >= pArr->ArrSize)
    {

        if ((newpElemArr = (PElement*)calloc((index + 1), sizeof(PElement))) == NULL)
            return FAIL;
        memcpy(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement));
        free(pArr->pElemArr);
        pArr->pElemArr = newpElemArr;
    }

    if((pArr->pElemArr)[index]!=NULL) {
        pArr->delFunc((pArr->pElemArr)[index]);
    }
    (pArr->pElemArr)[index] = pArr->copyFunc(pNewElem);


    pArr->ArrSize = (index >= pArr->ArrSize) ? (index + 1) : pArr->ArrSize;
    return SUCCESS;
}


void DeleteAdptArray(PAdptArray pArr)
{
    int i;
    if (pArr == NULL)
        return;
    for(i = 0; i < pArr->ArrSize; ++i) {
        if ((pArr->pElemArr)[i] != NULL) {
            pArr->delFunc((pArr->pElemArr)[i]);
        }
    }
    free(pArr->pElemArr);
    free(pArr);
}

PElement GetAdptArrayAt(PAdptArray pArr, int index){
    if((pArr->pElemArr)[index]==NULL) return FAIL;
    if((pArr->pElemArr)[index]!=NULL) {
        return pArr->copyFunc((pArr->pElemArr)[index]);
    }
    return FAIL;
}

int GetAdptArraySize(PAdptArray pArr){
    if(pArr->pElemArr==NULL)return -1;
    else{
        return pArr->ArrSize;
    }
}
void PrintDB(PAdptArray pArr){
    for(int i=0;i<pArr->ArrSize;i++) {
        if ((pArr->pElemArr)[i] != NULL) {
            pArr->PRINT_FUNC((pArr->pElemArr)[i]);
        }
    }
}
