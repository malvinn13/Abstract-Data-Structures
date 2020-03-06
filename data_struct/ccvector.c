#include "ccvector.h"
#include "common.h"

#define INITIAL_SIZE   100

int VecCreate(CC_VECTOR** Vector)
{
    if (NULL == Vector)
    {
        *Vector = NULL;
        return -1;
    }

    CC_VECTOR* vec = (CC_VECTOR*)malloc(sizeof(CC_VECTOR));
    if (NULL == vec)
    {
        *Vector = NULL;
        return -1;
    }

    memset(vec, 0, sizeof(*vec));

    vec->Count = 0;
    vec->Size = INITIAL_SIZE;
    vec->Array = (int*)malloc(sizeof(int) * INITIAL_SIZE);
    if (NULL == vec->Array)
    {
        free(vec);
        *Vector = NULL;
        return -1;
    }

    *Vector = vec;

    return 0;
}

int VecDestroy(CC_VECTOR** Vector)
{
    if (NULL == Vector || NULL == *Vector || NULL == (*Vector)->Array)
    {
        return -1;
    }
    CC_VECTOR* vec = *Vector;

    free(vec->Array);
    free(vec);

    *Vector = NULL;

    return 0;
}

int VecInsertTail(CC_VECTOR* Vector, int Value)
{
    if (NULL == Vector)
    {
        return -1;
    }

    if (Vector->Count >= Vector->Size)
    {
        int* backupVector = Vector->Array;
        Vector->Array = (int*)realloc(Vector->Array, sizeof(int) * Vector->Size * 2);
        if (NULL == Vector->Array)
        {
            Vector->Array = backupVector;
            return -1;
        }
        Vector->Size = Vector->Size * 2;
    }

    Vector->Array[Vector->Count] = Value;
    Vector->Count++;

    return 0;
}

int VecInsertHead(CC_VECTOR* Vector, int Value)
{
    if (NULL == Vector || NULL == Vector->Array)
    {
        return -1;
    }

    if (Vector->Count >= Vector->Size)
    {
        int* backupVector = Vector->Array;
        Vector->Array = (int*)realloc(Vector->Array, sizeof(int) * Vector->Size * 2);
        if (NULL == Vector->Array)
        {
            Vector->Array = backupVector;
            return -1;
        }
        Vector->Size = Vector->Size * 2;
    }

    for (int i = Vector->Count - 1; i >= 0; i--)
    {
        Vector->Array[i + 1] = Vector->Array[i];
    }
    Vector->Array[0] = Value;
    Vector->Count++;

    return 0;
}

int VecInsertAfterIndex(CC_VECTOR* Vector, int Index, int Value)
{
    if (NULL == Vector || NULL == Vector->Array || Index < -1 || Index >= Vector->Count || 0 == Vector->Count)
    {
        return -1;
    }

    if (Vector->Count >= Vector->Size)
    {
        int* backupVector = Vector->Array;
        Vector->Array = (int*)realloc(Vector->Array, sizeof(int) * Vector->Size * 2);
        if (NULL == Vector->Array)
        {
            Vector->Array = backupVector;
            return -1;
        }
        Vector->Size = Vector->Size * 2;
    }

    for (int i = Vector->Count - 1; i > Index; i--)
    {
        Vector->Array[i + 1] = Vector->Array[i];
    }
    Vector->Array[Index + 1] = Value;
    Vector->Count = Vector->Count + 1;

    return 0;
}

int VecRemoveByIndex(CC_VECTOR* Vector, int Index)
{
    if (NULL == Vector || NULL == Vector->Array || Index < 0 || Index >= Vector->Count)
    {
        return -1;
    }
    for (int i = Index; i < Vector->Count - 1; i++)
    {
        Vector->Array[i] = Vector->Array[i + 1];
    }
    Vector->Count = Vector->Count - 1;

    return 0;
}

int VecGetValueByIndex(CC_VECTOR* Vector, int Index, int* Value)
{
    if (NULL == Vector || NULL == Vector->Array || Index < 0 || Index >= Vector->Count)
    {
        return -1;
    }
    *Value = Vector->Array[Index];

    return 0;
}

int VecGetCount(CC_VECTOR* Vector)
{
    if (NULL == Vector || NULL == Vector->Array)
    {
        return -1;
    }

    return Vector->Count;
}

int VecClear(CC_VECTOR* Vector)
{
    if (NULL == Vector || NULL == Vector->Array)
    {
        return -1;
    }
    Vector->Count = 0;

    return 0;
}

int VecSort(CC_VECTOR* Vector)
{
    if (NULL == Vector)
    {
        return -1;
    }
    if (Vector->Count < 1)
    {
        return -1;
    }

    int swapped = 1, i = 0;
    while (i < Vector->Count && swapped)
    {
        swapped = 0;
        for (int j = 0; j < Vector->Count - i - 1; j++)
        {
            if (Vector->Array[j] < Vector->Array[j + 1])
            {
                const int temp = Vector->Array[j];
                Vector->Array[j] = Vector->Array[j + 1];
                Vector->Array[j + 1] = temp;
                swapped = 1;
            }
        }
        i = i + 1;
    }

    return 0;
}

int VecAppend(CC_VECTOR* DestVector, CC_VECTOR* SrcVector)
{
    if (NULL == SrcVector || NULL == DestVector || NULL == DestVector->Array || NULL == SrcVector->Array)
    {
        return -1;
    }
    const int srcVectorCount = SrcVector->Count;
    for (int i = 0; i < srcVectorCount; i++)
    {
        if (-1 == VecInsertTail(DestVector, SrcVector->Array[i]))
        {
            return -1;
        }
    }

    return 0;
}
