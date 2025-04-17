#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

Node* bstree_create_node (int data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) {
		perror("Ошибка выделения памяти для new node");
		return NULL;
	}
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}
