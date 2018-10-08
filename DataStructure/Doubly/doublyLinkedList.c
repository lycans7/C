/*
 * doublyLinkedList.c
 *
 *  Created on: 21-Aug-2018
 *      Author: Parth shah
 */

#include <stdio.h>
#include <stdlib.h>

struct Doubly {
	int data;
	struct Doubly* left;
	struct Doubly* right;
};

void insert(int val);
void display(struct Doubly* root);
int main() {
	struct Doubly* root;
	root = NULL;
	insert(root,4);
	insert(root,5);
	insert(root,6);
	insert(root,7);

	return 0;
}

struct Doubly* insert_BST(int val){
	struct Doubly* temp = (struct Doubly*)malloc(sizeof(struct Doubly));
	temp->data = val;
	temp->left = temp->right = NULL;
	return temp;
}

struct Doubly* insert(struct Doubly* root, int val) {
	if (root == NULL) {
		root = insert_BST(val);
	} else if (val <= root->data) {
		root->left = insert(root->left, val);
	} else {
		root->right = insert(root->right, val);
	}
	return root;
}

void display(struct Doubly* root){

}
