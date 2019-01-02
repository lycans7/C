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

struct node * minValueNode(struct node* node) {
	struct node* current = node;

	/* loop down to find the leftmost leaf */
	while (current->left != NULL)
		current = current->left;

	return current;
}

struct node* deleteNode(struct node* root, int key) {
	// base case
	if (root == NULL)
		return root;

	// If the key to be deleted is smaller than the root's key,
	// then it lies in left subtree
	printf("\t\n %d ",root->key);
	if (key < root->key)
		root->left = deleteNode(root->left, key);

	// If the key to be deleted is greater than the root's key,
	// then it lies in right subtree
	else if (key > root->key)
		root->right = deleteNode(root->right, key);

	// if key is same as root's key, then This is the node
	// to be deleted
	else {
		// node with only one child or no child
		if (root->left == NULL) {
			struct node *temp = root->right;
			free(root);
			return temp;
		} else if (root->right == NULL) {
			struct node *temp = root->left;
			free(root);
			return temp;
		}

		// node with two children: Get the inorder successor (smallest
		// in the right subtree)
		struct node* temp = minValueNode(root->right);

		// Copy the inorder successor's content to this node
		root->key = temp->key;

		// Delete the inorder successor
		root->right = deleteNode(root->right, temp->key);
	}
	return root;
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
	root = deleteNode(root, 20);
	printf("Inorder traversal of the modified tree \n");
	inorder(root);

	printf("\nDelete 30\n");
	root = deleteNode(root, 30);
	printf("Inorder traversal of the modified tree \n");
	inorder(root);

	printf("\nDelete 50\n");
	root = deleteNode(root, 50);
	printf("Inorder traversal of the modified tree \n");
	inorder(root);
	return 0;
}

