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
    PRINT_FUNC print;
}AdptArray, *PAdptArray;


PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_, PRINT_FUNC p)
{
    PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
    if (pArr == NULL)
        return NULL;
    pArr->ArrSize = 0;
    pArr->pElemArr = NULL;
    pArr->delFunc = delFunc_;
    pArr->copyFunc = copyFunc_;
    pArr->print= p;
    return pArr;
}


////////B.
Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem)
{
    PElement* newpElemArr;
    if (pArr == NULL)
        return FAIL;

    if (idx >= pArr->ArrSize)
    {
        
// Extend Array
        if ((newpElemArr = (PElement*)calloc((idx + 1), sizeof(PElement))) == NULL)
            return FAIL;
        for(int i=0; i<pArr->ArrSize; i++){
           newpElemArr[i]  =pArr->pElemArr[i];
        }


        free(pArr->pElemArr);
        pArr->pElemArr = newpElemArr;
    }

    // Delete Previous Elem
    if((pArr->pElemArr)[idx]!=NULL){
        pArr->delFunc((pArr->pElemArr)[idx]);
    }

    (pArr->pElemArr)[idx] = pArr->copyFunc(pNewElem);

    // Update Array Size
    pArr->ArrSize = (idx >= pArr->ArrSize) ? (idx + 1) : pArr->ArrSize;
    return SUCCESS;
}
//C.

void DeleteAdptArray(PAdptArray pArr)
{
    if (pArr == NULL)
        return;
    for(int i = 0; i < pArr->ArrSize; i++)
    {   
        if(pArr->pElemArr[i]!= NULL){
            pArr->delFunc((pArr->pElemArr)[i]);
        }
    }
    free(pArr->pElemArr);
    free(pArr);
}

//D
PElement GetAdptArrayAt(PAdptArray pAr, int i){

    if((pAr==NULL) || (i<0) || (i > pAr->ArrSize)){
        return NULL;
    }

    if(pAr->pElemArr[i]!= NULL){
        return pAr->copyFunc(pAr->pElemArr[i]);
    }
    return NULL;
}

//E
int GetAdptArraySize(PAdptArray p){
    if(p == NULL ){
        return -1;
    }
    return p->ArrSize;
}

//F
void PrintDB(PAdptArray p){

    if(p== NULL){
        return;
    }
    for(int i=0; i< p->ArrSize; i++){
        if(p->pElemArr[i]!= NULL){
              p->print(p->pElemArr[i]);
        }
    }
}

