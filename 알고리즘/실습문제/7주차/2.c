#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int key, height;
    struct node *parent, *left, *right; //부모 노드,자식 노드
} node;

typedef node *node_ptr;

//뿌리 노드
node_ptr tree;

//자식 노드의 높이 중 가장 큰 높이값을 반환
int maxHeight(node_ptr root);
//오른쪽으로 회전
node_ptr rightRotate(node_ptr nodeA);
//왼쪽으로 회전
node_ptr leftRotate(node_ptr nodeA);
//불균형 정도 조사
int getBalanceFactor(node_ptr root);
node_ptr rebalance(node_ptr root);
node_ptr treeSearch(int k);
void searchAndFix(node_ptr w);
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
    tree->height = 1;

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

int maxHeight(node_ptr root)
{
    if (root->left->height > root->right->height)
    {
        return root->left->height;
    }
    else
    {
        return root->right->height;
    }
}

node_ptr rightRotate(node_ptr nodeA)
{
    node_ptr nodeB = nodeA->left;
    node_ptr nodeBchild = nodeB->right;
    node_ptr par = nodeA->parent;

    //회전
    nodeB->right = nodeA;
    nodeA->left = nodeBchild;

    //부모 갱신
    nodeB->parent = nodeA->parent;
    nodeA->parent = nodeB;
    nodeBchild->parent = nodeA;

    //자식 갱신
    if (par)
    {
        if (par->left == nodeA)
        {
            par->left = nodeB;
        }
        else
        {
            par->right = nodeB;
        }
    }

    //높이 갱신
    nodeA->height = 1 + maxHeight(nodeA);
    nodeB->height = 1 + maxHeight(nodeB);

    return nodeB;
}

node_ptr leftRotate(node_ptr nodeA)
{
    node_ptr nodeB = nodeA->right;
    node_ptr nodeBchild = nodeB->left;
    node_ptr par = nodeA->parent;

    //회전
    nodeB->left = nodeA;
    nodeA->right = nodeBchild;

    //부모 갱신
    nodeB->parent = nodeA->parent;
    nodeA->parent = nodeB;
    nodeBchild->parent = nodeA;

    //자식 갱신
    if (par)
    {
        if (par->left == nodeA)
        {
            par->left = nodeB;
        }
        else
        {
            par->right = nodeB;
        }
    }

    //높이 갱신
    nodeA->height = 1 + maxHeight(nodeA);
    nodeB->height = 1 + maxHeight(nodeB);

    return nodeB;
}

int getBalanceFactor(node_ptr root)
{
    int heightLeft, heightRight;

    heightLeft = root->left->height;
    heightRight = root->right->height;

    int balanceFactor = heightLeft - heightRight;

    return balanceFactor;
}

node_ptr rebalance(node_ptr root)
{
    if (root->key == -1)
    {
        return root;
    }

    int balanceFactor = getBalanceFactor(root);
    if (balanceFactor > 1) // right rotation
    {
       //자식 노드의 균형이 0인 경우도 고려해야 제대로 작동한다. 
        if (getBalanceFactor(root->left) >= 0)
        { // LL case
            return rightRotate(root);
        }
        else
        { // LR case
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    else if (balanceFactor < -1) // left rotation
    {
        if (getBalanceFactor(root->right) <= 0)
        { // RR case
            return leftRotate(root);
        }
        else
        { // RL case
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }

    return root;
}

void searchAndFix(node_ptr w)
{
    if (!w)
    {
        return;
    }

    while (1)
    {
        w = rebalance(w);
        w->height = 1 + maxHeight(w);
        if (!w->parent)
        {
            tree = w;
            return;
        }
        w = w->parent;
    }
}

int findElement(int k)
{
    return treeSearch(k)->key;
}

void insertItem(int k)
{
    node_ptr tmp = treeSearch(k);

    tmp->key = k;
    tmp->height = 1;

    tmp->left = (node_ptr)calloc(1, sizeof(node));
    tmp->left->key = -1;
    tmp->left->parent = tmp;
    tmp->left->height = 0;

    tmp->right = (node_ptr)calloc(1, sizeof(node));
    tmp->right->key = -1;
    tmp->right->parent = tmp;
    tmp->right->height = 0;

    searchAndFix(tmp);
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
    node_ptr root = treeSearch(k);//삭제할 노드 찾기
    if (root->key == -1)
    {
        return -1;
    }

    //트리에 존재하는 노드가 뿌리노드 뿐이고, 해당 노드를 삭제해야 할 경우
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

    searchAndFix(par);

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