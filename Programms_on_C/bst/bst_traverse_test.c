#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

void printNodeData(int data) {
    printf("%d ", data);
}

int main() {
    t_btree root1 = NULL;
    t_btree root2 = NULL;

    // --- Test Set 1 (Ascending) ---
    printf("--- Test Set 1 (Ascending) ---\n");
    bstree_insert(&root1, 50, intComparatorAsc);
    bstree_insert(&root1, 30, intComparatorAsc);
    bstree_insert(&root1, 20, intComparatorAsc);
    bstree_insert(&root1, 40, intComparatorAsc);
    bstree_insert(&root1, 70, intComparatorAsc);
    bstree_insert(&root1, 60, intComparatorAsc);
    bstree_insert(&root1, 80, intComparatorAsc);

    printf("Infix: ");
    bstree_apply_infix(root1, printNodeData);
    printf("\n");

    printf("Prefix: ");
    bstree_apply_prefix(root1, printNodeData);
    printf("\n");

    printf("Postfix: ");
    bstree_apply_postfix(root1, printNodeData);
    printf("\n");

    // --- Test Set 2 (Descending) ---
    printf("\n--- Test Set 2 (Descending) ---\n");
    bstree_insert(&root2, 10, intComparatorDesc);
    bstree_insert(&root2, 5, intComparatorDesc);
    bstree_insert(&root2, 15, intComparatorDesc);
    bstree_insert(&root2, 3, intComparatorDesc);
    bstree_insert(&root2, 7, intComparatorDesc);
    bstree_insert(&root2, 12, intComparatorDesc);
    bstree_insert(&root2, 18, intComparatorDesc);

    printf("Infix: ");
    bstree_apply_infix(root2, printNodeData);
    printf("\n");

    printf("Prefix: ");
    bstree_apply_prefix(root2, printNodeData);
    printf("\n");

    printf("Postfix: ");
    bstree_apply_postfix(root2, printNodeData);
    printf("\n");

    freeTree(root1);
    freeTree(root2);

    return 0;
}
