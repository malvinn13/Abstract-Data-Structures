#include "cchashtable.h"
#include "common.h"
#include <string.h>
#define SIZE 5
#define CONTAINING_RECORD(address, type, field) (\
    (type *)((char*)(address) -(unsigned long long)(&((type *)0)->field)))
CC_LIST_ENTRY* HtCreateListEntry()
{
    CC_LIST_ENTRY* ListEntry = (CC_LIST_ENTRY*)malloc(sizeof(CC_LIST_ENTRY));
    if(ListEntry == NULL)
    {
        return 0;
    }
    ListEntry->Blink = ListEntry;
    ListEntry->Flink = ListEntry;
    return ListEntry;
}
CC_LIST_ENTRY** HtCreateListOfEntries()
{
    CC_LIST_ENTRY** ListOfListEntries = (CC_LIST_ENTRY**)malloc(sizeof(CC_LIST_ENTRY*) * SIZE);
    if(NULL == ListOfListEntries)
    {
        return 0;
    }
    for(int i = 0; i < SIZE; i++)
    {
        ListOfListEntries[i] = HtCreateListEntry();
        if(ListOfListEntries[i] == NULL)
        {
            return 0;
        }
    }
    return ListOfListEntries;
}
int HtStrCmp(char *a, char *b)
{
    while (*a && *b && *a == *b) { ++a; ++b; }
    return (unsigned char)(*a) - (unsigned char)(*b);
}
int HtCreate(CC_HASH_TABLE **HashTable)
{
    if(NULL == HashTable)
    {
        return -1;
    }
    CC_HASH_TABLE* newHashTable = (CC_HASH_TABLE*)malloc(sizeof(CC_HASH_TABLE));
    if(NULL == newHashTable)
    {
        return -1;
    }
    memset(newHashTable, 0, sizeof(CC_HASH_TABLE));

    newHashTable->Size = SIZE;
    newHashTable->Count = 0;
    newHashTable->Entries = HtCreateListOfEntries();

    if(newHashTable->Entries == NULL)
    {
        return -1;
    }
    *HashTable = newHashTable;
    return 0;
}

int HtDestroy(CC_HASH_TABLE **HashTable)
{
    if(*HashTable == NULL)
    {
        return -1;
    }
    for(int index = 0; index < SIZE; index++)
    {
        CC_LIST_ENTRY* el = (*HashTable)->Entries[index]->Flink;
        CC_LIST_ENTRY* head = (*HashTable)->Entries[index];
        while (el != head)
        {
            CC_NODE* toDelete = CONTAINING_RECORD(el, CC_NODE, ListEntry);
            if(toDelete == NULL)
            {
                return -1;
            }
            el = el->Flink;
            free(toDelete);
        }
        if(head == NULL)
        {
            return -1;
        }
        free(head);
    }
    *HashTable = NULL;
    return 0;
}
int HtHash(char *Key)
{
    if (Key == NULL || Key[0] == 0)
    {
        return -1;
    }
    int hash = 0;
    int i = 0;
    while(*Key != 0)
    {
        hash += *Key ^ i;
        i++;
        Key++;
    }
    return hash % SIZE;
}
int HtSetKeyValue(CC_HASH_TABLE *HashTable, char *Key, int Value)
{
    if(HashTable == NULL || Key == NULL || Key[0] == 0 || HashTable->Entries == NULL)
    {
        return -1;
    }
    const int index = HtHash(Key);
    if(index == -1)
    {
        return -1;
    }
    CC_LIST_ENTRY* el = HashTable->Entries[index]->Flink;
    CC_LIST_ENTRY* head = HashTable->Entries[index];
    while(el != head)
    {
        char* nodeKey = CONTAINING_RECORD(el, CC_NODE, ListEntry)->Key;
        if(HtStrCmp(Key, nodeKey) == 0)
        {
            return -1;
        }
        el = el->Flink;
    }

    CC_NODE* newNode = (CC_NODE*)malloc(sizeof(CC_NODE));
    if(newNode == NULL)
    {
        return -1;
    }
    newNode->Key = Key;
    newNode->Value = Value;

    newNode->ListEntry.Blink = head->Blink;
    newNode->ListEntry.Flink = head;
    head->Blink->Flink = &newNode->ListEntry;
    head->Blink = &newNode->ListEntry;
    
    return 0;
}

int HtGetKeyValue(CC_HASH_TABLE *HashTable, char *Key, int *Value)
{
    if(HashTable == NULL || Key == NULL || Value == NULL || Key[0] == 0)
    {
        return -1;
    }
    const int index = HtHash(Key);

    CC_LIST_ENTRY* el = HashTable->Entries[index]->Flink;
    CC_LIST_ENTRY* head = HashTable->Entries[index];

    while(el != head)
    {
        CC_NODE* curNode = CONTAINING_RECORD(el, CC_NODE, ListEntry);
        if (HtStrCmp(Key, curNode->Key) == 0)
        {
            *Value = curNode->Value;
            return 0;
        }
        el = el->Flink;
    }
    return -1;
}

int HtRemoveKey(CC_HASH_TABLE *HashTable, char *Key)
{
    if(HashTable == NULL || Key == NULL || Key[0] == 0)
    {
        return -1;
    }
    const int index = HtHash(Key);
    if(index == -1)
    {
        return -1;
    }

    CC_LIST_ENTRY* el = HashTable->Entries[index]->Flink;
    CC_LIST_ENTRY* head = HashTable->Entries[index];

    while(el != head)
    {
        CC_NODE* curNode = CONTAINING_RECORD(el, CC_NODE, ListEntry);
        if(HtStrCmp(Key, curNode->Key) == 0)
        {
            CC_LIST_ENTRY* backupListEntry = &curNode->ListEntry;
            curNode->ListEntry.Blink->Flink = backupListEntry->Flink;
            curNode->ListEntry.Flink->Blink = backupListEntry->Blink;

            free(curNode);
            return 0;
        }
        el = el->Flink;
    }
    return -1;
}

int HtHasKey(CC_HASH_TABLE *HashTable, char *Key)
{
    if(HashTable == NULL || Key == NULL || Key[0] == 0)
    {
        return -1;
    }
    for(int index = 0; index < SIZE; index++)
    {
        CC_LIST_ENTRY* el = HashTable->Entries[index]->Flink;
        CC_LIST_ENTRY* head = HashTable->Entries[index];

        while (el != head)
        {
            CC_NODE* curNode = CONTAINING_RECORD(el, CC_NODE, ListEntry);
            if (HtStrCmp(Key, curNode->Key) == 0)
            {
                return 1;
            }
        }
    }
    return 0;
}

int HtGetFirstKey(CC_HASH_TABLE* HashTable, CC_HASH_TABLE_ITERATOR **Iterator, char **Key)
{
    CC_HASH_TABLE_ITERATOR *iterator = (CC_HASH_TABLE_ITERATOR*)malloc(sizeof(CC_HASH_TABLE_ITERATOR));

    if (NULL == HashTable || NULL == Iterator || NULL == Key || NULL == iterator)
    {
        return -1;
    }

    memset(iterator, 0, sizeof(*iterator));

    iterator->HashTable = HashTable;

    for(int index = 0; index < SIZE; index++)
    {
        CC_LIST_ENTRY* el = HashTable->Entries[index]->Flink;
        CC_LIST_ENTRY* head = HashTable->Entries[index];

        if(el != head)
        {
            iterator->Index = index;
            iterator->Element = el;
            break;
        }
    }

    *Iterator = iterator;

    *Key = CONTAINING_RECORD(iterator->Element, CC_NODE, ListEntry)->Key;
    return 0;
}

int HtGetNextKey(CC_HASH_TABLE_ITERATOR *Iterator, char **Key)
{
    if(Iterator == NULL || Key == NULL)
    {
        return -1;
    }
    if(Iterator->Element->Flink == Iterator->HashTable->Entries[Iterator->Index])
    {
        int sf = 0;
        for(int index = Iterator->Index + 1; index < SIZE; index++)
        {
            CC_LIST_ENTRY* el = Iterator->HashTable->Entries[index]->Flink;
            CC_LIST_ENTRY* head = Iterator->HashTable->Entries[index];

            if (el != head)
            {
                Iterator->Index = index;
                Iterator->Element = el;
                sf = 1;
                break;
            }
        }
        if(!sf)
        {
            return -2;
        }
    }else
    {
        Iterator->Element = Iterator->Element->Flink;
    }
    *Key = CONTAINING_RECORD(Iterator->Element, CC_NODE, ListEntry)->Key;
    return 0;
}

int HtReleaseIterator(CC_HASH_TABLE_ITERATOR **Iterator)
{
    if(*Iterator == NULL)
    {
        return -1;
    }
    free(*Iterator);

    return 0;
}

int HtClear(CC_HASH_TABLE *HashTable)
{
    if (HashTable == NULL)
    {
        return -1;
    }
    for (int index = 0; index < SIZE; index++)
    {
        CC_LIST_ENTRY* el = (HashTable)->Entries[index]->Flink;
        CC_LIST_ENTRY* head = (HashTable)->Entries[index];
        while (el != head)
        {
            CC_NODE* toDelete = CONTAINING_RECORD(el, CC_NODE, ListEntry);
            if (toDelete == NULL)
            {
                return -1;
            }
            el = el->Flink;
            free(toDelete);
        }
        if (head == NULL)
        {
            return -1;
        }
        head->Flink = head;
        head->Blink = head;
    }
    return 0;
}

int HtGetKeyCount(CC_HASH_TABLE *HashTable)
{
    if(HashTable == NULL)
    {
        return -1;
    }
    int count = 0;
    for (int index = 0; index < SIZE; index++)
    {
        CC_LIST_ENTRY* el = (HashTable)->Entries[index]->Flink;
        CC_LIST_ENTRY* head = (HashTable)->Entries[index];
        while (el != head)
        {
            count++;
            el = el->Flink;
        }
    }
    return count;
}
