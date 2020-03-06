#include <stdio.h>
#include "ccvector.h"
#include "ccstack.h"
#include "cchashtable.h"
#include "ccheap.h"
#include "cctree.h"
#include <stdlib.h>
#include <string.h>

#define ADVANCED_TESTS
#define DEBUG_INFO

int TestVector();
int TestStack();
int TestHashTable();
int TestHeap();
int TestTree();
int AdvancedTests_HashTable();
int AdvancedTests_Vector();
void RunTests();
void RunAdvancedTests();

int main(void)
{
    RunTests();
#ifdef ADVANCED_TESTS
    RunAdvancedTests();
#endif

    return 0;
}

char* randstring(int length)
{
    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
    char* randomString = NULL;

    if (length)
    {
        randomString = malloc(sizeof(char) * (length + 1));

        if (randomString)
        {
            for (int n = 0; n < length; n++)
            {
                int key = rand() % (int)(sizeof(charset) - 1);
                randomString[n] = charset[key];
            }

            randomString[length] = '\0';
        }
    }

    return randomString;
}

void RunTests()
{
    /// NOTE: The tests provided here are by no means exhaustive and are only
    /// provided as a starting point (not all functions are tested, not all use cases
    /// and failure scenarios are covered). You are encouraged to expand these tests
    /// to include missing scenarios.
    if (0 == TestVector())
    {
        printf("Vector test passed\n\n");
    }
    else
    {
        printf("Vector test failed\n\n");
    }

    if (0 == TestStack())
    {
        printf("Stack test passed\n\n");
    }
    else
    {
        printf("Stack test failed\n\n");
    }

    if (0 == TestHashTable())
    {
        printf("HashTable test passed\n\n");
    }
    else
    {
        printf("HashTable test failed\n\n");
    }

    if (0 == TestHeap())
    {
        printf("Heap test passed\n\n");
    }
    else
    {
        printf("Heap test failed\n\n");
    }

    if (0 == TestTree())
    {
        printf("Tree test passed\n\n");
    }
    else
    {
        printf("Tree test failed\n\n");
    }
}

void RunAdvancedTests()
{
    if(AdvancedTests_HashTable() == 0)
    {
        printf("HashTable - Advanced Tests: Passed\n");
    }
    else
    {
        printf("HashTable - Advanced Tests: Failed\n");
    }
    if (AdvancedTests_Vector() == 0)
    {
        printf("Vector - Advanced Tests: Passed\n");
    }
    else
    {
        printf("Vector - Advanced Tests: Failed\n");
    }
}
int AdvancedTests_HashTable()
{
    if (TestHashTable() == -1)
    {
        printf("Advanced Tests(HashTable) can't start if normal tests failed.\n");
        return 1;
    }

    int failedFlag = 0;
    CC_HASH_TABLE* MyHashTable = NULL;
    if (0 != HtCreate(&MyHashTable))
    {
#ifdef DEBUG_INFO
        printf("Hash Table Create - FAILED.\n");
#endif
        failedFlag = 1;
        return failedFlag;
    }

    if (0 != HtGetKeyCount(MyHashTable))
    {
#ifdef DEBUG_INFO
        printf("GetKeyCount - FAILED\n");
#endif
        failedFlag = 1;
        return failedFlag;
    }

    char* key;
    char keys[121][21];
    int keys_count = 0;
    for (int i = 1; i <= 20; i++)
    {
        key = randstring(i);
        strncpy_s(keys[keys_count++], 21, key, 21);
        if (HtSetKeyValue(MyHashTable, key, i) != 0)
        {
            failedFlag = 1;
#ifdef DEBUG_INFO
            printf("HtSetKeyValue(MyHashTable, %s, %d) - FAILED\n", key, i);
#endif
        }
#ifdef DEBUG_INFO
        printf("HtSetKeyValue(MyHashTable, %s, %d) - SUCCES\n", key, i);
#endif
    }
    for (int i = 1; i <= 20; i++)
    {
        key = randstring(i);
        strncpy_s(keys[keys_count++], 21, key, 21);
        if (HtSetKeyValue(MyHashTable, key, i) != 0)
        {
            failedFlag = 1;
#ifdef DEBUG_INFO
            printf("HtSetKeyValue(MyHashTable, %s, %d) - FAILED\n", key, i);
#endif
        }
#ifdef DEBUG_INFO
        printf("HtSetKeyValue(MyHashTable, %s, %d) - SUCCES\n", key, i);
#endif
    }
    for (int i = 1; i <= 20; i++)
    {
        key = randstring(i);
        strncpy_s(keys[keys_count++], 21, key, 21);
        if (HtSetKeyValue(MyHashTable, key, i) != 0)
        {
            failedFlag = 1;
#ifdef DEBUG_INFO
            printf("HtSetKeyValue(MyHashTable, %s, %d) - FAILED\n", key, i);
#endif
        }
#ifdef DEBUG_INFO
        printf("HtSetKeyValue(MyHashTable, %s, %d) - SUCCES\n", key, i);
#endif
    }
    if (HtGetKeyCount(MyHashTable) != 60)
    {
        failedFlag = 1;
        printf("HtGeyKeyCount - FAILED");
        return failedFlag;
    }
    for (int i = 1; i <= 20; i++)
    {
        key = randstring(i);
        strncpy_s(keys[keys_count++], 21, key, 21);
        if (HtSetKeyValue(MyHashTable, key, i) != 0)
        {
            failedFlag = 1;
#ifdef DEBUG_INFO
            printf("HtSetKeyValue(MyHashTable, %s, %d) - FAILED\n", key, i);
#endif
        }
#ifdef DEBUG_INFO
        printf("HtSetKeyValue(MyHashTable, %s, %d) - SUCCES\n", key, i);
#endif
    }
    for (int i = 1; i <= 20; i++)
    {
        key = randstring(i);
        strncpy_s(keys[keys_count++], 21, key, 21);
        if (HtSetKeyValue(MyHashTable, key, i) != 0)
        {
            failedFlag = 1;
#ifdef DEBUG_INFO
            printf("HtSetKeyValue(MyHashTable, %s, %d) - FAILED\n", key, i);
#endif
        }
#ifdef DEBUG_INFO
        printf("HtSetKeyValue(MyHashTable, %s, %d) - SUCCES\n", key, i);
#endif
    }
    for (int i = 1; i <= 20; i++)
    {
        key = randstring(i);
        strncpy_s(keys[keys_count++], 21, key, 21);
        if (HtSetKeyValue(MyHashTable, key, i) != 0)
        {
            failedFlag = 1;
#ifdef DEBUG_INFO
            printf("HtSetKeyValue(MyHashTable, %s, %d) - FAILED\n", key, i);
#endif
        }
#ifdef DEBUG_INFO
        printf("HtSetKeyValue(MyHashTable, %s, %d) - SUCCES\n", key, i);
#endif
    }
    if (HtGetKeyCount(MyHashTable) != 120)
    {
        failedFlag = 1;
        printf("HtGeyKeyCount - FAILED");
        return failedFlag;
    }
    int value, expectedValue = 1;
    for (int i = 0; i < keys_count; i++)
    {
        key = keys[i];
        if (expectedValue == 21) expectedValue = 1;
        if (HtGetKeyValue(MyHashTable, key, &value) != 0)
        {
            failedFlag = 1;
#ifdef DEBUG_INFO
            printf("HtGetKeyValue(MyHashTable, %s) - FAILED\n", key);
#endif
        }
        if (value != expectedValue)
        {
            failedFlag = 1;
#ifdef DEBUG_INFO
            printf("HtGetKeyValue(MyHashTable, %s) - FAILED (Value: %d; Expected: %d)\n", key, value, expectedValue);
#endif
        }
        else
        {
#ifdef DEBUG_INFO
            printf("HtGetKeyValue(MyHashTable, %s) - SUCCESS (Value: %d; Expected: %d)\n", key, value, expectedValue);
#endif
        }
        expectedValue++;
    }
    for (int i = 0; i < 100; i++)
    {
        key = randstring(i + 1);
        if (HtGetKeyValue(MyHashTable, key, &value) == 0)
        {
            failedFlag = 1;
            printf("HtGetKeyValue - Found value for non-existent key\n");
        }
    }

    CC_HASH_TABLE_ITERATOR* MyIterator = NULL;
    char *toCompare;
    if(HtGetFirstKey(MyHashTable, &MyIterator, &toCompare) != 0)
    {
        failedFlag = 1;
#ifdef DEBUG_INFO
        printf("HtGetFirstKey - FAILED\n");
#endif
    }

    for (int i = 0; i < keys_count; i++)
    {
        for (int j = 0; j < keys_count; j++)
        {
            if (strcmp(keys[j], toCompare) == 0)
            {
#ifdef DEBUG_INFO
                printf("%d. HtGetNextKey - Success(Key exists (%s))\n", i, toCompare);
#endif
                break;
            }
        }
        HtGetNextKey(MyIterator, &toCompare);
    }
    if(HtGetNextKey(MyIterator, &toCompare) != -2)
    {
#ifdef DEBUG_INFO
        printf("HtGetNextKey - Failed (No more keys but i found one(%s))\n", toCompare);
#endif
        failedFlag = 1;
    }
    if(HtDestroy(&MyHashTable) != 0)
    {
        failedFlag = 1;
#ifdef DEBUG_INFO
        printf("HtDestroy - FAILED \n");
#endif
    }
    HtDestroy(&MyHashTable);
    return failedFlag;

}
int AdvancedTests_Vector()
{
    if(TestVector() == -1)
    {
        printf("Advanced Tests(Vector) can't start if normal tests failed.\n");
        return 1;
    }
    int failedFlag = 0;
    CC_VECTOR* MyVector = NULL;
    if(VecCreate(&MyVector) != 0)
    {
#ifdef DEBUG_INFO
        printf("VecCreate - FAILED\n");
#endif
        return 1;
    }
    for(int i = 0; i < 100; i++)
    {
        if(VecInsertTail(MyVector, i) != 0)
        {
#ifdef DEBUG_INFO
            printf("VecInsertTail(MyVector, %d) - FAILED\n", i);        
#endif
            failedFlag = 1;
        }else
        {
#ifdef DEBUG_INFO
            printf("VecInsertHead(MyVector, %d) - SUCCESS\n", i);
#endif  
        }
    }
    for (int i = 0; i < 100; i++)
    {
        if (VecInsertHead(MyVector, i) != 0)
        {
#ifdef DEBUG_INFO
            printf("VecInsertHead(MyVector, %d) - FAILED\n", i);   
#endif
            failedFlag = 1;
        }else
        {
#ifdef DEBUG_INFO
            printf("VecInsertHead(MyVector, %d) - SUCCESS\n", i);
#endif 
        }
    }
    if(VecGetCount(MyVector) != 200)
    {
#ifdef DEBUG_INFO
        printf("VecGetCount(MyVector) - FAILED (Got: %d, Expected: 200)\n", VecGetCount(MyVector));
#endif
        failedFlag = 1;
    }else
    {
#ifdef DEBUG_INFO
        printf("VecGetCount(MyVector) - SUCCESS\n");
#endif
    }
    for(int i = 0; i < 200; i++)
    {
        if(VecRemoveByIndex(MyVector, 200-i-1) != 0)
        {
#ifdef DEBUG_INFO
            printf("VecRemoveByIndex(MyVector, %d) - FAILED\n", i);
#endif
            failedFlag = 1;
        }
    }
    if (VecGetCount(MyVector) != 0)
    {
#ifdef DEBUG_INFO
        printf("VecGetCount(MyVector) - FAILED (Got: %d, Expected: 200)\n", VecGetCount(MyVector));
#endif
        failedFlag = 1;
    }
    CC_VECTOR* MySecondVector = NULL;
    VecCreate(&MySecondVector);
    for(int i = 0; i < 100; i++)
    {
        VecInsertTail(MyVector, i);
        VecInsertTail(MySecondVector, i);
    }
    if(VecAppend(MyVector, MySecondVector) != 0)
    {
#ifdef DEBUG_INFO
        printf("VecAppend(MyVector - FAILED\n");
#endif
        failedFlag = 1;
    }else
    {
#ifdef DEBUG_INFO
        printf("VecAppend(MyVector) - SUCCESS\n");
#endif
    }
    if(VecGetCount(MyVector) != 200)
    {
#ifdef DEBUG_INFO
        printf("VecGetCount(MyVector) - FAILED (Got: %d, Expected: 200)\n", VecGetCount(MyVector));
#endif
        failedFlag = 1;
    }
    else
    {
#ifdef DEBUG_INFO
        printf("VecGetCount(MyVector) - SUCCESS\n");
#endif
    }
    return failedFlag;
}

int TestTree()
{
    int retVal;
    CC_TREE* usedTree = NULL;

    retVal = TreeCreate(&usedTree);
    if (0 != retVal)
    {
        printf("%d!\n", retVal);
        goto cleanup;
    }
    retVal = TreeInsert(usedTree, 20);
    if (0 != retVal)
    {
        printf("%d!\n", retVal);
        goto cleanup;
    }
    if (1 != TreeContains(usedTree, 20))
    {
        printf("TreeContains invalid return value!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = TreeRemove(usedTree, 20);
    if (0 != retVal)
    {
        printf("TreeRemove failed!\n");
        goto cleanup;
    }
    if (0 != TreeContains(usedTree, 20))
    {
        printf("TreeContains invalid return value after remove!\n");
        retVal = -1;
        goto cleanup;
    }

    if (0 != TreeGetCount(usedTree))
    {
        printf("TreeGetCount invalid return value %d! \n", TreeGetCount(usedTree));
        retVal = -1;
    }
cleanup:
    if (NULL != usedTree)
    {
        if (0 != TreeDestroy(&usedTree))
        {
            printf("TreeDestroy failed!\n");
            retVal = -1;
        }
    }
    return retVal;
}

int TestHeap()
{
    int retVal;
    int foundVal = -1;
    CC_HEAP* usedHeap = NULL;
    retVal = HpCreateMinHeap(&usedHeap, NULL);
    if (0 != retVal)
    {
        printf("HpCreateMinHeap failed!\n");
        goto cleanup;
    }

    retVal = HpInsert(usedHeap, 20);
    if (0 != retVal)
    {
        printf("HpInsert failed!\n");
        goto cleanup;
    }

    retVal = HpInsert(usedHeap, 10);
    if (0 != retVal)
    {
        printf("HpInsert failed!\n");
        goto cleanup;
    }

    if (2 != HpGetElementCount(usedHeap))
    {
        printf("Invalid element count!\n");
        retVal = -1;
        goto cleanup;
    }
    retVal = HpGetExtreme(usedHeap, &foundVal);
    if (0 != retVal)
    {
        printf("HpGetExtreme failed!\n");
        goto cleanup;
    }
    if (10 != foundVal)
    {
        printf("Invalid minimum value returned!\n");
        retVal = -1;
        goto cleanup;
    }
    retVal = HpPopExtreme(usedHeap, &foundVal);
    if (-1 == retVal)
    {
        printf("HpPopExtreme failed\n");
        goto cleanup;
    }
    if (10 != foundVal)
    {
        printf("Invalid extreme value returned !\n");
        goto cleanup;
    }

    CC_VECTOR* usedVector = NULL;
    retVal = VecCreate(&usedVector);
    HpInsert(usedHeap, 10);

    if (-1 == retVal)
    {
        printf("Vector create failed\n");
        goto cleanup;
    }
    retVal = HpSortToVector(usedHeap, usedVector);
    if (-1 == retVal)
    {
        printf("HpSortToVector failed! \n");
    }
    retVal = VecGetCount(usedVector);
    if (2 != retVal)
    {
        printf("Invalid vector count value returned!\n");
        goto cleanup;
    }
    retVal = VecGetValueByIndex(usedVector, 1, &foundVal);
    if (-1 == retVal)
    {
        printf("VecGetValueByIndex failed!\n");
        goto cleanup;
    }
    if (foundVal != 20)
    {
        printf("Invalid value returned for VecGetValueByIndex!\n");
    }
cleanup:
    if (NULL != usedHeap)
    {
        if (0 != HpDestroy(&usedHeap))
        {
            printf("HpDestroy failed!\n");
            retVal = -1;
        }
    }
    return retVal;
}

int TestHashTable()
{
    int retVal;
    int foundVal = -1;
    CC_HASH_TABLE* usedTable = NULL;

    retVal = HtCreate(&usedTable);
    if (0 != retVal)
    {
        printf("HtCreate failed!\n");
        goto cleanup;
    }

    retVal = HtSetKeyValue(usedTable, "mere", 20);

    if (0 != retVal)
    {
        printf("HtSetKeyValue failed!\n");
        goto cleanup;
    }

    retVal = HtGetKeyValue(usedTable, "mere", &foundVal);
    if (0 != retVal)
    {
        printf("HtGetKeyValue failed!\n");
        goto cleanup;
    }

    if (foundVal != 20)
    {
        printf("Invalid value after get!\n");
        retVal = -1;
    }
cleanup:
    if (NULL != usedTable)
    {
        if (0 != HtDestroy(&usedTable))
        {
            printf("HtDestroy failed!\n");
            retVal = -1;
        }
    }
    return retVal;
}

int TestStack()
{
    int retVal;
    int foundVal = -1;
    CC_STACK* usedStack = NULL;

    retVal = StCreate(&usedStack);
    if (0 != retVal)
    {
        printf("StCreate failed!\n");
        goto cleanup;
    }

    retVal = StPush(usedStack, 10);
    if (0 != retVal)
    {
        printf("StPush failed!\n");
        goto cleanup;
    }

    if (0 != StIsEmpty(usedStack))
    {
        printf("Invalid answer to StIsEmpty!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = StPop(usedStack, &foundVal);
    if (0 != retVal)
    {
        printf("StPop failed!\n");
        goto cleanup;
    }

    if (foundVal != 10)
    {
        printf("Invalid value after pop!\n");
        retVal = -1;
        goto cleanup;
    }

    if (-1 != StPeek(usedStack, &foundVal))
    {
        printf("StPeek failed!\n");
        retVal = -1;
        goto cleanup;
    }
    StPush(usedStack, 10);
    if (-1 == StPeek(usedStack, &foundVal))
    {
        printf("StPeek failed!\n");
        retVal = -1;
        goto cleanup;
    }
    if (foundVal != 10)
    {
        printf("Invalid value returned for StPeek!\n");
        retVal = -1;
        goto cleanup;
    }
    if (1 != StGetCount(usedStack))
    {
        printf("Invalid answer for StGetCount!\n");
        retVal = -1;
        goto cleanup;
    }
    if (-1 == StClear(usedStack))
    {
        printf("StClear failed!\n");
        retVal = -1;
        goto cleanup;
    }

    CC_STACK* newStack = NULL;

    retVal = StCreate(&newStack);
    if (0 != retVal)
    {
        printf("StCreate failed!\n");
        goto cleanup;
    }

    StPush(newStack, 10);
    StPush(newStack, 20);
    StPush(newStack, 30);
    retVal = StPush(newStack, 40);
    if (0 != retVal)
    {
        printf("StPush failed!\n");
        goto cleanup;
    }
    retVal = StPushStack(usedStack, newStack);
    if (retVal == -1)
    {
        printf("StPushStack failed !\n");
        goto cleanup;
    }
    if (4 != StGetCount(usedStack))
    {
        printf("StPushStack returned invalid stack !\n");
        retVal = -1;
    }
cleanup:
    if (NULL != usedStack)
    {
        if (0 != StDestroy(&usedStack))
        {
            printf("StDestroy failed!\n");
            retVal = -1;
        }
    }
    return retVal;
}

int TestVector()
{
    int retVal;
    int foundVal = 0;
    CC_VECTOR* usedVector = NULL;
    CC_VECTOR* testVector = NULL;
    VecCreate(&testVector);
    retVal = VecCreate(&usedVector);

    if (0 != retVal)
    {
        printf("VecCreate failed!\n");
        goto cleanup;
    }
    retVal = VecInsertTail(usedVector, 10);

    if (0 != retVal)
    {
        printf("VecInsertTail failed!\n");
        goto cleanup;
    }

    retVal = VecInsertHead(usedVector, 16);
    if (0 != retVal)
    {
        printf("VecInsertHead failed!\n");
        goto cleanup;
    }

    if (VecGetCount(usedVector) != 2)
    {
        printf("Invalid count returned!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = VecInsertAfterIndex(usedVector, 0, 20);
    if (0 != retVal)
    {
        printf("VecInsertAfterIndex failed!\n");
        goto cleanup;
    }
    retVal = VecRemoveByIndex(usedVector, 0);
    if (0 != retVal)
    {
        printf("VecRemoveByIndex failed!\n");
        goto cleanup;
    }

    retVal = VecGetValueByIndex(usedVector, 0, &foundVal);
    if (0 != retVal)
    {
        printf("VecGetValueByIndex failed!\n");
        goto cleanup;
    }

    if (foundVal != 20)
    {
        printf("Invalid value found at position 0\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = VecClear(usedVector);
    if (0 != retVal)
    {
        printf("VecClear failed!\n");
        goto cleanup;
    }

    if (0 != VecGetCount(usedVector))
    {
        printf("Invalid count after clear\n");
        retVal = -1;
    }


cleanup:
    if (NULL != usedVector)
    {
        if (0 != VecDestroy(&usedVector))
        {
            printf("VecDestroy failed!\n");
            retVal = -1;
        }
    }
    return retVal;
}
