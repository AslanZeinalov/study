#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int intComparatorAsc(int a, int b) {
    return a - b;
}

int intComparatorDesc(int a, int b) {
    return b - a;
}

void printInsertResult(InsertResult result, int item, t_btree parent) {
    switch (result) {
        case INSERTED_LEFT:
            printf("Вставка %d слева от %d\n", item, parent->data);
            break;
        case INSERTED_RIGHT:
            printf("Вставка %d справа от %d\n", item, parent->data);
            break;
        case INSERTED_ROOT:
            printf("Вставка %d как корень\n", item);
            break;
        case DUPLICATE:
            printf("Значение %d уже существует в дереве\n", item);
            break;
    }
}

int main() {
    t_btree root1 = NULL;
    InsertResult result;

    printf("--- Test Set 1 (Ascending) ---\n");
    result = bstree_insert(&root1, 50, intComparatorAsc);
    printInsertResult(result, 50, (root1 == NULL) ? NULL : root1);

    result = bstree_insert(&root1, 30, intComparatorAsc);
    printInsertResult(result, 30, (root1->left == NULL) ? NULL : root1);

    result = bstree_insert(&root1, 20, intComparatorAsc);
    printInsertResult(result, 20, (root1->left->left == NULL) ? NULL : root1->left);

    result = bstree_insert(&root1, 40, intComparatorAsc);
    printInsertResult(result, 40, (root1->left->right == NULL) ? NULL : root1->left);

    result = bstree_insert(&root1, 70, intComparatorAsc);
    printInsertResult(result, 70, (root1->right == NULL) ? NULL : root1);

    result = bstree_insert(&root1, 60, intComparatorAsc);
    printInsertResult(result, 60, (root1->right->left == NULL) ? NULL : root1->right);

    result = bstree_insert(&root1, 80, intComparatorAsc);
    printInsertResult(result, 80, (root1->right->right == NULL) ? NULL : root1->right);

    printf("\n--- Test Set 2 (Descending) ---\n");
    t_btree root2 = NULL;

    result = bstree_insert(&root2, 10, intComparatorDesc);
    printInsertResult(result, 10, (root2 == NULL) ? NULL : root2);

    result = bstree_insert(&root2, 5, intComparatorDesc);
    printInsertResult(result, 5, (root2->right == NULL) ? NULL : root2);

    result = bstree_insert(&root2, 15, intComparatorDesc);
    printInsertResult(result, 15, (root2->left == NULL) ? NULL : root2);

   result = bstree_insert(&root2, 3, intComparatorDesc);
    printInsertResult(result, 3, (root2->right->right == NULL) ? NULL : root2->right);

    result = bstree_insert(&root2, 7, intComparatorDesc);
    printInsertResult(result, 7, (root2->right->left == NULL) ? NULL : root2->right);

    result = bstree_insert(&root2, 12, intComparatorDesc);
    printInsertResult(result, 12, (root2->left->right == NULL) ? NULL : root2->left);

    result = bstree_insert(&root2, 18, intComparatorDesc);
    printInsertResult(result, 18, (root2->left->left == NULL) ? NULL : root2->left);

    freeTree(root1);
    freeTree(root2);

    return 0;
}
