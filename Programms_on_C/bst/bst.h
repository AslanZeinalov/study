#ifndef BST_H
#define BST_H

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

typedef Node* t_btree; // Определение t_btree как указателя на Node

// Enum для обозначения места вставки
typedef enum {
    INSERTED_LEFT,
    INSERTED_RIGHT,
    INSERTED_ROOT,
    DUPLICATE
} InsertResult;

Node* bstree_create_node(int data);
InsertResult bstree_insert(t_btree *root, int item, int (*cmpf) (int, int)); // ИСПРАВЛЕНО: Теперь возвращает InsertResult
void freeTree(t_btree root);
void printTree(t_btree root, int level);

#endif // BST_H
