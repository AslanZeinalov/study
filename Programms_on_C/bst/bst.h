#ifndef BST_H
#define BST_H

typedef struct Node {
	int data;
	struct Node* left;
	struct Node* right;
} Node;

Node* bstree_create_node(int data);

#endif // BST_H
