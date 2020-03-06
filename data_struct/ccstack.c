#include "ccstack.h"
#include "common.h"

#define INITIAL_SIZE 100

int StCreate(CC_STACK** Stack)
{
    if (NULL == Stack)
    {
        *Stack = NULL;
        return -1;
    }
    CC_STACK* stk = (CC_STACK*)malloc(sizeof(CC_STACK) * INITIAL_SIZE);
    if (NULL == stk)
    {
        *Stack = NULL;
        return -1;
    }

    memset(stk, 0, sizeof(CC_STACK));

    stk->Size = INITIAL_SIZE;
    stk->Top = -1;
    stk->Array = (int*)malloc(sizeof(int) * INITIAL_SIZE);

    if (NULL == stk->Array)
    {
        free(stk);
        *Stack = NULL;
        return -1;
    }

    *Stack = stk;

    return 0;
}

int StDestroy(CC_STACK** Stack)
{
    if (NULL == *Stack || NULL == (*Stack)->Array)
    {
        return -1;
    }
    free((*Stack)->Array);
    free(*Stack);

    *Stack = NULL;

    return 0;
}

int StPush(CC_STACK* Stack, int Value)
{
    if (Stack == NULL || Stack->Array == NULL)
    {
        return -1;
    }
    if (Stack->Top == Stack->Size - 1)
    {
        int* backupArray = Stack->Array;
        Stack->Array = (int*)realloc(Stack->Array, sizeof(int) * Stack->Size * 2);
        if (NULL == Stack->Array)
        {
            Stack->Array = backupArray;
            return -1;
        }
        Stack->Size = Stack->Size * 2;
    }
    Stack->Top = Stack->Top + 1;
    Stack->Array[Stack->Top] = Value;

    return 0;
}

int StPop(CC_STACK* Stack, int* Value)
{
    if (NULL == Stack || NULL == Stack->Array || Stack->Top == -1)
    {
        return -1;
    }
    *Value = Stack->Array[Stack->Top--];

    return 0;
}

int StPeek(CC_STACK* Stack, int* Value)
{
    if (NULL == Stack || NULL == Stack->Array || -1 == Stack->Top)
    {
        return -1;
    }
    *Value = Stack->Array[Stack->Top];

    return 0;
}

int StIsEmpty(CC_STACK* Stack)
{
    if (NULL == Stack || NULL == Stack->Array)
    {
        return -1;
    }

    return (Stack->Top == -1);
}

int StGetCount(CC_STACK* Stack)
{
    if (NULL == Stack || NULL == Stack->Array)
    {
        return -1;
    }

    return Stack->Top + 1;
}

int StClear(CC_STACK* Stack)
{
    if (NULL == Stack || NULL == Stack->Array)
    {
        return -1;
    }
    Stack->Top = -1;

    return 0;
}

int StPushStack(CC_STACK* Stack, CC_STACK* StackToPush)
{
    if (Stack == StackToPush || NULL == Stack || NULL == StackToPush || NULL == Stack->Array || NULL == StackToPush->
        Array)
    {
        return -1;
    }
    for (int i = 0; i <= StackToPush->Top; i++)
    {
        StPush(Stack, StackToPush->Array[i]);
    }
    StClear(StackToPush);

    return 0;
}
