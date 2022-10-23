#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int key;
    struct node *parent, *left, *right; //부모 노드,자식 노드
} node;

typedef node *node_ptr;

//뿌리 노드
node_ptr tree;

node_ptr treeSearch(int k);
int findElement(int k);
void insertItem(int k);
node_ptr inOrderSucc(node_ptr w);
int removeElement(int k);
void preOrder(node_ptr root);
void output(int k);
void freeTree(node_ptr root);

int main()
{
    tree = (node_ptr)calloc(1, sizeof(node));
    tree->key = -1;
    tree->parent = NULL;
    tree->left = NULL;
    tree->right = NULL;

    int s = 1; //반복문 종료용 변수

    while (s)
    {
        int mode, key;
        scanf("%c", &mode);

        switch (mode)
        {
        case 'i':
            scanf("%d", &key);
            insertItem(key);
            break;

        case 'd':
            scanf("%d", &key);
            output(removeElement(key));
            break;

        case 's':
            scanf("%d", &key);
            output(findElement(key));
            break;

        case 'p':
            preOrder(tree);
            printf("\n");
            break;

        case 'q':
            s = 0;
            break;
        }
        // preOrder(tree);
        // printf("\n");

        getchar();
    }

    freeTree(tree);

    return 0;
}

node_ptr treeSearch(int k)
{
    node_ptr root = tree;

    while (root->key != -1)
    {
        if (root->key == k)
        {
            break;
        }
        else if (root->key > k)
        {
            root = root->left;
        }
        else if (root->key < k)
        {
            root = root->right;
        }
    }

    return root;
}

int findElement(int k)
{
    return treeSearch(k)->key;
}

void insertItem(int k)
{
    node_ptr tmp = treeSearch(k);

    tmp->key = k;

    tmp->left = (node_ptr)calloc(1, sizeof(node));
    tmp->left->key = -1;
    tmp->left->parent = tmp;

    tmp->right = (node_ptr)calloc(1, sizeof(node));
    tmp->right->key = -1;
    tmp->right->parent = tmp;
}

node_ptr inOrderSucc(node_ptr w)
{
    node_ptr root = w->right;

    while (root->left->key != -1)
    {
        root = root->left;
    }

    return root;
}

int removeElement(int k)
{
    node_ptr root = treeSearch(k);
    if (root->key == -1)
    {
        return -1;
    }

    //제거해야 할 노드가 뿌리노드 뿐일 경우
    if (root == tree && root->left->key == -1 && root->right->key == -1)
    {
        free(root->left);
        free(root->right);
        root->key = -1;
        return k;
    }

    if (root->left->key != -1 && root->right->key != -1)
    { //자식 노드 둘 다 내부 노드일 경우
        node_ptr y = inOrderSucc(root);
        root->key = y->key;
        root = y;
        // root를 root의 중위순회 후계자로 설정하고 아래 코드를 실행하면 자연스럽게 마무리 가능
    }

    //자식 노드 둘 중 하나만 내부 노드거나 둘다 외부 노드일 때
    node_ptr child = NULL, par = root->parent;

    if (root->left->key != -1)
    {
        child = root->left;
        free(root->right);
    }
    else
    {
        child = root->right;
        free(root->left);
    }

    //삭제된 노드가 뿌리 노드가 아닐 경우
    if (par)
    {
        if (par->left == root)
        {
            par->left = child;
        }
        else
        {
            par->right = child;
        }
    }
    //삭제된 노드가 뿌리 노드일 겅우
    else
    {
        tree = child;
    }
    child->parent = par;

    free(root);
    root = NULL;

    return k;
}

void preOrder(node_ptr root)
{
    if (root->key != -1)
    {
        printf(" %d", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void output(int k)
{
    if (k == -1)
    {
        printf("X\n");
    }
    else
    {
        printf("%d\n", k);
    }
}

void freeTree(node_ptr root)
{
    if (root->left)
    {
        freeTree(root->left);
    }
    if (root->right)
    {
        freeTree(root->right);
    }
    free(root);
    root = NULL;
}