#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main()
{
    int n=26;
    list_ptr tree = data_init(n);
    array_to_tree(tree, n);

    printf("\n==순환 알고리즘 이용==\n");
    printf("중위 탐색: ");
    inorder(tree + 1);
    printf("\n");
    printf("전위 탐색: ");
    preorder(tree + 1);
    printf("\n");
    printf("후위 탐색: ");
    postorder(tree + 1);
    printf("\n\n");

    printf("==스레드 이용==\n");
    thread_inorder(tree);

    free(tree);
    tree = NULL;
    return 0;
}