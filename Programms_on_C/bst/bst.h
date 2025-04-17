#ifndef BST_H
#define BST_H

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

typedef Node* t_btree;

typedef enum {
    INSERTED_LEFT,
    INSERTED_RIGHT,
    INSERTED_ROOT,
    DUPLICATE
} InsertResult;

Node* bstree_create_node(int data);
InsertResult bstree_insert(t_btree *root, int item, int (*cmpf) (int, int));
void freeTree(t_btree root);

void bstree_apply_infix(t_btree root, void (*applyf) (int));
void bstree_apply_prefix(t_btree root, void (*applyf) (int));
void bstree_apply_postfix(t_btree root, void (*applyf) (int));

int intComparatorAsc(int a, int b);
int intComparatorDesc(int a, int b);

#endif
