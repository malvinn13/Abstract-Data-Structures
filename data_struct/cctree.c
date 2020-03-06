#include "cctree.h"
#include "common.h"

int maxim(int a, int b)
{
    return (a > b) ? a : b;
}
int NodeHeight(CC_TREE_NODE* Root)
{
    if (Root == NULL)
    {
        return -1;
    }
    return Root->Height;
}

int BalanceFactor(CC_TREE_NODE* Root)
{
    if (Root == NULL)
    {
        return 0;
    }
    return NodeHeight(Root->Left) - NodeHeight(Root->Right);
}
CC_TREE_NODE* newNode(int Value) 
{ 
    CC_TREE_NODE* node = (CC_TREE_NODE*) malloc(sizeof(CC_TREE_NODE));
    if(node == NULL)
    {
        return NULL;
    }
    node->Value   = Value;
    node->Left   = NULL;
    node->Right  = NULL;
    node->Height = 1;  
    return node; 
} 
CC_TREE_NODE* RightRotate(CC_TREE_NODE* Root)
{
    CC_TREE_NODE* x = Root->Left;
    CC_TREE_NODE* T2 = x->Right;

    x->Right = Root;
    Root->Left = T2;

    Root->Height = maxim(NodeHeight(Root->Left), NodeHeight(Root->Right)) + 1;
    x->Height = maxim(NodeHeight(x->Left), NodeHeight(x->Right)) + 1;

    return x;
}

CC_TREE_NODE* LeftRotate(CC_TREE_NODE* Root)
{
    CC_TREE_NODE* y = Root->Right;
    CC_TREE_NODE* T2 = y->Left;

    y->Left = Root;
    Root->Right = T2;

    Root->Height = maxim(NodeHeight(Root->Left), NodeHeight(Root->Right)) + 1;
    y->Height = maxim(NodeHeight(y->Left), NodeHeight(y->Right)) + 1;

    return y;
}
CC_TREE_NODE* NodeInsert(CC_TREE_NODE *Root, const int Value)
{
    if (Root == NULL)
        return newNode(Value);

    if (Value < Root->Value)
        Root->Left = NodeInsert(Root->Left, Value);
    else
        Root->Right = NodeInsert(Root->Right, Value);

    Root->Height = 1 + maxim(NodeHeight(Root->Left),NodeHeight(Root->Right));
    const int balance = BalanceFactor(Root);
    if (balance > 1 && Value < Root->Left->Value)
        return RightRotate(Root);
    if (balance < -1 && Value > Root->Right->Value)
        return LeftRotate(Root);
    if (balance > 1 && Value > Root->Left->Value)
    {
        Root->Left = LeftRotate(Root->Left);
        return RightRotate(Root);
    }
    if (balance < -1 && Value < Root->Right->Value)
    {
        Root->Right = RightRotate(Root->Right);
        return LeftRotate(Root);
    }
    return Root;

}

CC_TREE_NODE* LeftmostNode(CC_TREE_NODE* Root)
{
    while (Root && Root->Right != NULL)
        Root = Root->Right;

    return Root;
}

CC_TREE_NODE* RightmostNode(CC_TREE_NODE* Root)
{
    while (Root && Root->Left != NULL)
        Root = Root->Left;

    return Root;
}
CC_TREE_NODE* DeleteNode(CC_TREE* Tree, CC_TREE_NODE* Root, int Value)
{
    CC_TREE_NODE* q;

    if (Root == NULL)
        return NULL;
    if (Root->Left == NULL && Root->Right == NULL)
    {
        if (Root == Tree->Root)
            Tree->Root = NULL;
        free(Root);
        return NULL;
    }

    if (Value < Root->Value)
        Root->Left = DeleteNode(Tree, Root->Left, Value);
    else if (Value > Root->Value)
        Root->Right = DeleteNode(Tree, Root->Right, Value);
    else
    {
        if (NodeHeight(Root->Left) > NodeHeight(Root->Right))
        {
            q = LeftmostNode(Root->Left);
            Root->Value = q->Value;
            Root->Left = DeleteNode(Tree, Root->Left, q->Value);
        }
        else
        {
            q = RightmostNode(Root->Right);
            Root->Value = q->Value;
            Root->Right = DeleteNode(Tree, Root->Right, q->Value);
        }
    }
    return Root;
}

int TreeCreate(CC_TREE** Tree)
{
    if (NULL == Tree)
    {
        *Tree = NULL;
        return -1;
    }
    CC_TREE* tree = (CC_TREE*)malloc(sizeof(CC_TREE));
    if (NULL == tree)
    {
        *Tree = NULL;
        return -1;
    }

    memset(tree, 0, sizeof(CC_TREE));
    tree->Root = NULL;
    tree->Count = 0;
    *Tree = tree;
    return 0;
}

int TreeDestroy(CC_TREE** Tree)
{
    if (NULL == Tree || NULL == *Tree)
    {
        return -1;
    }
    TreeClear(*Tree);
    free(*Tree);
    *Tree = NULL;
    return 0;
}

int TreeInsert(CC_TREE* Tree, int Value)
{
    if (Tree == NULL)
    {
        return -1;
    }
    Tree->Root = NodeInsert(Tree->Root, Value);
    Tree->Count += 1;
    return 0;
}

int TreeRemove(CC_TREE* Tree, int Value)
{
    if (Tree == NULL)
    {
        return -1;
    }
    while (TreeContains(Tree, Value))
    {
        DeleteNode(Tree, Tree->Root, Value);
        Tree->Count -= 1;
    }
    return 0;
}

int TreeGetCount(CC_TREE* Tree)
{
    if (Tree == NULL)
    {
        return -1;
    }
    return Tree->Count;
}
int maxDepth(CC_TREE_NODE* Root)
{
    if (Root == NULL)
        return 0;
    else
    {

        int lDepth = maxDepth(Root->Left);
        int rDepth = maxDepth(Root->Right);

        if (lDepth > rDepth)
            return(lDepth + 1);
        else return(rDepth + 1);
    }
}
int TreeGetHeight(CC_TREE* Tree)
{
    if (Tree == NULL)
    {
        return -1;
    }
    return maxDepth(Tree->Root);
}

int TreeContains(CC_TREE* Tree, int Value)
{
    if (Tree == NULL)
    {
        return -1;
    }
    CC_TREE_NODE* t = Tree->Root;

    while (t != NULL)
    {
        if (Value == t->Value)
            return 1;
        if (Value < t->Value)
            t = t->Left;
        else
            t = t->Right;
    }
    return 0;
}
void FreeRoot(CC_TREE_NODE* Root)
{
    if(Root == NULL)
    {
        return;
    }
    FreeRoot(Root->Left);
    FreeRoot(Root->Right);
    free(Root);    
}
int TreeClear(CC_TREE* Tree)
{
    if(Tree == NULL || Tree->Root == NULL)
    {
        return -1;
    }
    FreeRoot(Tree->Root);
    return 0;
}
int GetValuePreOrder(CC_TREE_NODE *Root, int *Count, int *Value)
{
    if (NULL == Root)
    {
        return -1;
    }
    if (*Count == 0)
    {
        *Value = Root->Value;
        return 0;
    }
    *Count -= 1;
    if (GetValuePreOrder(Root->Left, Count, Value) == 0)
    {
        return 0;
    }
    if (GetValuePreOrder(Root->Right, Count, Value) == 0)
    {
        return 0;
    }

    return -1;
}
int GetValueInOrder(CC_TREE_NODE *Root, int *Count, int *Value)
{
    if (NULL == Root)
    {
        return -1;
    }

    if (GetValueInOrder(Root->Left, Count, Value) == 0)
    {
        return 0;
    }
    if (*Count == 0)
    {
        *Value = Root->Value;
        return 0;
    }
    *Count -= 1;
    if (GetValueInOrder(Root->Right, Count, Value) == 0)
    {
        return 0;
    }

    return -1;
}
int GetValuePostOrder(CC_TREE_NODE *Root, int *Count, int *Value)
{
    if (NULL == Root)
    {
        return -1;
    }

    if (GetValuePostOrder(Root->Left, Count, Value) == 0)
    {
        return 0;
    }

    if (GetValuePostOrder(Root->Right, Count, Value) == 0)
    {
        return 0;
    }
    if (*Count == 0)
    {
        *Value = Root->Value;
        return 0;
    }
    *Count -= 1;
    
    return -1;
}
int TreeGetNthPreorder(CC_TREE* Tree, int Index, int* Value)
{
    if(Tree == NULL || Tree->Root == NULL || Index < 0 || Index >= Tree->Count || Value == NULL)
    {
        return -1;
    }
    if(GetValuePreOrder(Tree->Root, &Index, Value) == -1)
    {
        return -1;
    }
    return 0;
}

int TreeGetNthInorder(CC_TREE* Tree, int Index, int* Value)
{
    if (Tree == NULL || Tree->Root == NULL || Index < 0 || Index >= Tree->Count || Value == NULL)
    {
        return -1;
    }
    if(GetValueInOrder(Tree->Root, &Index, Value) == -1)
    {
        return -1;
    }
    return 0;
}

int TreeGetNthPostorder(CC_TREE* Tree, int Index, int* Value)
{
    if (Tree == NULL || Tree->Root == NULL || Index < 0 || Index >= Tree->Count || Value == NULL)
        return -1;
    
    if(GetValuePostOrder(Tree->Root, &Index, Value) == -1)
    {
        return -1;
    }
    return 0;
}
