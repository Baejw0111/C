#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int elem;
    struct node *left, *right;
} node;

typedef node *node_ptr;

node_ptr Input(node_ptr root);
void Search(node_ptr root, int n);
void FreeTree(node_ptr root);

int main()
{
    node_ptr tree = NULL;

    int n, s; // n은  노드 개수,s는 탐색 횟수
    scanf("%d", &n);
    tree = Input(tree);

    scanf("%d", &s);
    for (int i = 0; i < s; ++i)
    {
        Search(tree, n);
    }

    FreeTree(tree);
}

node_ptr Input(node_ptr root)
{
    root = (node_ptr)calloc(1, sizeof(node));
    int parent, left, right;
    scanf("%d %d %d", &parent, &left, &right);
    root->elem = parent;

    if (left != 0)
    {
        root->left = Input(root->left);
    }
    else
    {
        root->left = NULL;
    }

    if (right != 0)
    {
        root->right = Input(root->right);
    }
    else
    {
        root->right = NULL;
    }
}

void Search(node_ptr root, int n)
{
    char *str = NULL;
    str = (char *)calloc(n, sizeof(char));

    scanf("%s", str);
    node_ptr cur = root;

    printf(" %d", cur->elem);
    for (char *i = str; i < str + strlen(str); ++i)
    {
        if (*i == 'L')
        {
            cur = cur->left;
        }
        else if (*i == 'R')
        {
            cur = cur->right;
        }

        if (cur->elem == 0)
        {
            return;
        }
        else
        {
            printf(" %d", cur->elem);
        }
    }
    printf("\n");
}

void FreeTree(node_ptr root)
{
    if (root->left)
    {
        FreeTree(root->left);
    }
    if (root->right)
    {
        FreeTree(root->right);
    }
    free(root);
}