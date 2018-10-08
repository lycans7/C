/*
 * binarySearchTree.c
 *
 *  Created on: 04-Oct-2018
 *      Author: Parth shah
 */

#include <stdio.h>
#include <stdlib.h>

struct BST {
	int data;
	struct BST* left;
	struct BST* right;
};
struct BST* space_create(int data) {
	struct BST* temp = (struct BST*) malloc(sizeof(struct BST));
	temp->left = NULL;
	temp->right = NULL;
	temp->data = data;
	return temp;
}
struct BST* insert(struct BST* root, int data) {
	if (root == NULL) {
		return space_create(data);
	}
	if (data < root->data) {
		root->left = insert(root->left, data);
	} else if (data > root->data) {
		root->right = insert(root->right, data);
	}

	return root;
}
void inorder(struct BST* root) {
	if (root != NULL) {
		inorder(root->left);
		printf("%d \n", root->data);
		inorder(root->right);
	}
}
int main() {
	struct BST* root = NULL;
	root = insert(root, 50);
	insert(root, 30);
	insert(root, 20);
	insert(root, 40);
	insert(root, 70);
	insert(root, 60);
	insert(root, 80);
	inorder(root);
	return 0;
}

