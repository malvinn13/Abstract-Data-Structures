#include "ccheap.h"
#include "common.h"

#define INITIAL_SIZE 10

void SwapValues(int* Value1, int* Value2)
{
    const int temp = *Value1;
    *Value1 = *Value2;
    *Value2 = temp;
}

int HpCompareElements(const int CurrentValue, const int ValueToCompare, const int IsMinHeap)
{
    return (IsMinHeap == 0) ? CurrentValue > ValueToCompare : CurrentValue < ValueToCompare;
}

int HpFilterUp(CC_HEAP* Heap, int Index)
{
    if (NULL == Heap || NULL == Heap->Array || Index < 0 || Index >= Heap->Count)
    {
        return -1;
    }
    while (Index != 1)
    {
        if (HpCompareElements(Heap->Array[Index], Heap->Array[(Index - 1) / 2], Heap->IsMinHeap))
        {
            SwapValues(&Heap->Array[Index], &Heap->Array[(Index - 1) / 2]);

            Index = (Index - 1) / 2;
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

int HpFilterDown(CC_HEAP* Heap, int Index)
{
    if (NULL == Heap || NULL == Heap->Array || Index < 0 || Index >= Heap->Count)
    {
        return -1;
    }
    while (2 * Index + 1 < Heap->Count)
    {
        if (2 * Index + 2 < Heap->Count)
        {
            if (HpCompareElements(Heap->Array[Index], Heap->Array[2 * Index + 1], Heap->IsMinHeap) && HpCompareElements(
                Heap->Array[Index], Heap->Array[2 * Index + 2], Heap->IsMinHeap))
            {
                return 0;
            }
            if (HpCompareElements(Heap->Array[2 * Index + 1], Heap->Array[2 * Index + 2], Heap->IsMinHeap))
            {
                SwapValues(&Heap->Array[Index], &Heap->Array[2 * Index + 1]);

                Index = 2 * Index + 1;
            }
            else
            {
                SwapValues(&Heap->Array[Index], &Heap->Array[2 * Index + 2]);
                Index = 2 * Index + 2;
            }
        }
        else
        {
            if (HpCompareElements(Heap->Array[Index], Heap->Array[2 * Index + 1], Heap->IsMinHeap))
            {
                return 0;
            }
            SwapValues(&Heap->Array[Index], &Heap->Array[2 * Index + 1]);

            Index = 2 * Index + 1;
        }
    }
    return 0;
}

int HpCreateMaxHeap(CC_HEAP** MaxHeap, CC_VECTOR* InitialElements)
{
    if (NULL == MaxHeap || (NULL != InitialElements && NULL == InitialElements->Array))
    {
        *MaxHeap = NULL;
        return -1;
    }

    CC_HEAP* heap = (CC_HEAP*)malloc(sizeof(CC_HEAP));

    if (NULL == heap)
    {
        *MaxHeap = NULL;
        return -1;
    }

    memset(heap, 0, sizeof(CC_HEAP));

    heap->IsMinHeap = 0;
    heap->Size = INITIAL_SIZE;
    heap->Array = (int*)malloc(sizeof(int) * INITIAL_SIZE);

    if (NULL == heap->Array)
    {
        *MaxHeap = NULL;
        return -1;
    }

    heap->Count = 0;

    if (NULL != InitialElements)
    {
        int foundVal;
        for (int i = 0; i < VecGetCount(InitialElements); i++)
        {
            const int retVal = VecGetValueByIndex(InitialElements, i, &foundVal);
            if (-1 == retVal)
            {
                *MaxHeap = NULL;
                return -1;
            }
            if (-1 == HpInsert(heap, foundVal))
            {
                *MaxHeap = NULL;
                return -1;
            }
        }
    }


    *MaxHeap = heap;
    return 0;
}

int HpCreateMinHeap(CC_HEAP** MinHeap, CC_VECTOR* InitialElements)
{
    if (NULL == MinHeap || (NULL != InitialElements && NULL == InitialElements->Array))
    {
        *MinHeap = NULL;
        return -1;
    }

    CC_HEAP* heap = (CC_HEAP*)malloc(sizeof(CC_HEAP));

    if (NULL == heap)
    {
        *MinHeap = NULL;
        return -1;
    }

    memset(heap, 0, sizeof(CC_HEAP));

    heap->IsMinHeap = 1;
    heap->Size = INITIAL_SIZE;
    heap->Array = (int*)malloc(sizeof(int) * INITIAL_SIZE);

    if (NULL == heap->Array)
    {
        *MinHeap = NULL;
        return -1;
    }

    heap->Count = 0;

    if (NULL != InitialElements)
    {
        int foundVal;
        for (int i = 0; i < VecGetCount(InitialElements); i++)
        {
            const int retVal = VecGetValueByIndex(InitialElements, i, &foundVal);
            if (-1 == retVal)
            {
                *MinHeap = NULL;
                return -1;
            }
            if (-1 == HpInsert(heap, foundVal))
            {
                *MinHeap = NULL;
                return -1;
            }
        }
    }


    *MinHeap = heap;
    return 0;
}

int HpDestroy(CC_HEAP** Heap)
{
    if (NULL == Heap || NULL == (*Heap)->Array)
    {
        return -1;
    }

    free((*Heap)->Array);
    free(*Heap);

    *Heap = NULL;

    return 0;
}

int HpInsert(CC_HEAP* Heap, int Value)
{
    if (NULL == Heap || NULL == Heap->Array)
    {
        return -1;
    }

    if (Heap->Count == 0)
    {
        Heap->Array[0] = Value;
        Heap->Count++;
        return 0;
    }

    if (Heap->Size <= Heap->Count * 2 + 2)
    {
        int* backupArray = Heap->Array;
        Heap->Array = (int*)realloc(Heap->Array, sizeof(int) * Heap->Size * 2 + 2);
        if (NULL == Heap->Array)
        {
            Heap->Array = backupArray;
            return -1;
        }
        Heap->Size = Heap->Size * 2 + 2;
    }
    Heap->Array[Heap->Count] = Value;
    Heap->Count++;

    int i = Heap->Count - 1;
    while (i > 0 && HpCompareElements(Value, Heap->Array[(i - 1) / 2], Heap->IsMinHeap))
    {
        const int temp = Heap->Array[i];
        Heap->Array[i] = Heap->Array[(i - 1) / 2];
        Heap->Array[(i - 1) / 2] = temp;
        i = (i - 1) / 2;    
    }
    Heap->Array[i] = Value;
    return 0;
}

int HpRemove(CC_HEAP* Heap, int Value)
{
    if (NULL == Heap || NULL == Heap->Array)
    {
        return -1;
    }
    int i = 0;
    while(i < Heap -> Count)
    {
        if (Heap->Array[i] == Value)
        {
            Heap->Array[i] = Heap->Array[--Heap->Count];
            if (i == 0 || Heap->Array[(i - 1) / 2] < Heap->Array[i])
            {
                HpFilterDown(Heap, i);
            }
            else
            {
                HpFilterUp(Heap, i);
            }
        } else
        {
            i = i + 1;
        }
    }
    return 0;
}

int HpGetExtreme(CC_HEAP* Heap, int* ExtremeValue)
{
    if (NULL == Heap || NULL == Heap->Array)
    {
        return -1;
    }
    *ExtremeValue = Heap->Array[0];
    return 0;
}

int HpPopExtreme(CC_HEAP* Heap, int* ExtremeValue)
{
    if (NULL == Heap || NULL == Heap->Array)
    {
        return -1;
    }
    if (-1 != HpGetExtreme(Heap, ExtremeValue) && -1 != HpRemove(Heap, *ExtremeValue))
    {
        return 0;
    }
    return -1;
}

int HpGetElementCount(CC_HEAP* Heap)
{
    if (NULL == Heap || NULL == Heap->Array)
    {
        return -1;
    }
    return Heap->Count;
}

int HpSortToVector(CC_HEAP* Heap, CC_VECTOR* SortedVector)
{
    if(NULL == Heap || NULL == Heap->Array || NULL == SortedVector || NULL == SortedVector->Array)
    {
        return -1;
    }
    int heapCount = Heap->Count;
    while (heapCount)
    {
        if (Heap->IsMinHeap == 1)
        {
            int extremeValue = 0;
            if(-1 == HpPopExtreme(Heap, &extremeValue))
            {
                return -1;
            }
            VecInsertTail(SortedVector, extremeValue);
        }
        else
        {
            int minVal = Heap->Array[0];
            int count = 1;
            for (int i = 1; i < Heap->Count; i++)
            {
                if (minVal == Heap->Array[i])
                {
                    count = count + 1;
                }
                if (minVal > Heap->Array[i])
                {
                    minVal = Heap->Array[i];
                    count = 1;
                }
            }
            for (int i = 0; i < count; i++)
            {
                VecInsertTail(SortedVector, minVal);
            }
            HpRemove(Heap, minVal);  
        }
        heapCount = Heap->Count;
    }
    
    for(int i = 0; i < SortedVector->Count; i++)
    {
        HpInsert(Heap, SortedVector->Array[i]);
        
    }
    return 0;
}
