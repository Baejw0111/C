#define FALSE 0
#define TRUE 1

typedef struct node
{
    char data;
    struct node *left_child, *right_child;
    int left_thread, right_thread;
} node;

typedef node *list_ptr;

list_ptr data_init(int n)
{ // list ptr 자료형 배열 생성
    list_ptr a = NULL;
    a = (list_ptr)calloc(n + 1, sizeof(node)); //배열의 첫번째 자리는 트리 생성 시 헤드 노드를 위한 자리다.

    char s='A';
    for (list_ptr i = a + 1; i < a + n + 1; i++)
    {
        i->data=s;
        s++;
    }

    return a;
}

void append_child(list_ptr parent, list_ptr child, int n)
{ //자식 삽입,n은 왼쪽 자식인지 오른쪽 자식인지 구분하기 위한 인자.
    parent->left_thread = FALSE;
    parent->right_thread = FALSE;
    child->left_thread = TRUE;
    child->right_thread = TRUE;

    if (n == 1)
    {
        child->left_child = parent->left_child;
        child->right_child = parent;
        parent->left_child = child;
    }

    if (n == 2)
    {
        child->right_child = parent->right_child;
        child->left_child = parent;
        parent->right_child = child;
    }
}

void array_to_tree(list_ptr a, int n)
{ //배열로 된 트리의 정보를 이진 트리 형태로 만들기
    /*
    a는 이진 트리의 정보가 저장된 list_ptr 자료형 배열,
    n은 배열의 크기
    */
    a->left_child = a + 1;
    a->right_child = a + 1;
    a->left_thread = FALSE;
    a->right_thread = FALSE;

    list_ptr root = a + 1;
    root->left_child = a;
    root->right_child = a;
    root->left_thread = TRUE;
    root->right_thread = TRUE;

    for (int i = 0; 2 * i + 1 < n; i++)
    {
        list_ptr parent = root + i;
        for (int j = 2 * i + 1; j < n && j <= 2 * i + 2; j++)
        {
            list_ptr child = root + j;
            if (child->data != '-')
            {
                append_child(parent, child, j - 2 * i);
            }
        }
    }
}

//순환 알고리즘으로 탐색 시 트리의 헤드 노드가 아니라 루트 노드의 포인터를 인자로 넣어야 한다.
void inorder(list_ptr branch)
{ //순환 알고리즘으로 중위 탐색
    if (!branch->left_thread)
    {
        inorder(branch->left_child);
    }

    printf("%c", branch->data);

    if (!branch->right_thread)
    {
        inorder(branch->right_child);
    }
}

void preorder(list_ptr branch)
{ //순환 알고리즘으로 전위 탐색
    printf("%c", branch->data);

    if (!branch->left_thread)
    {
        preorder(branch->left_child);
    }

    if (!branch->right_thread)
    {
        preorder(branch->right_child);
    }
}

void postorder(list_ptr branch)
{ //순환 알고리즘으로 후위 탐색
    if (!branch->left_thread)
    {
        postorder(branch->left_child);
    }

    if (!branch->right_thread)
    {
        postorder(branch->right_child);
    }

    printf("%c", branch->data);
}

//스레드 탐색 알고리즘

list_ptr find_insucc(list_ptr branch)
{ //중위후속자 반환 함수
    list_ptr succ;
    succ = branch->right_child;

    if (!branch->right_thread)
    { //해당 노드가 말단이면 오른쪽 자식 반환
        while (!succ->left_thread)
        {                            //아닐 경우 succ이 말단 노드가 될때까지
            succ = succ->left_child; //완쪽으로 타고 내려간다.
        }
    }
    return succ;
}

void thread_inorder(list_ptr tree)
{ //스레드를 이용해 중위탐색
    list_ptr cur = tree;

    printf("중위 탐색: ");

    while ((cur = find_insucc(cur)) != tree)
    {
        printf("%c", cur->data);
    }
    printf("\n");
}