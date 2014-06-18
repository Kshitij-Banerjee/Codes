// BinarySearchTreeImplementation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
using namespace std;

struct node{
int data;
node* left;
node* right;
};

class BST
{

	
public:
	struct node root;
	BST()
	{
		root.data = 0;
		root.left =  NULL;
		root.right = NULL;
	}
	void add(node* root,int data);
	void inorder(node* root);
};

void BST::add(node* root, int data)
{
	
	if(root->data==0 || root->data == data)
	{
		root->data = data;
		return;
	}

	if(data<  (root->data) && root->left==NULL)
	{
		root->left = (node*)malloc(sizeof(node));
		return;
	}

	if(data>  (root->data) && root->right==NULL)
	{
		root->right = (node*)malloc(sizeof(node));
		return;
	}
	
	if(data<  (root->data) && root->left!=NULL)
		add((root->left),data);

	else if(data>  (root->data) && root->right!=NULL)
		add((root->right),data);
	


}

void BST::inorder(node* root)
{
	if(root==NULL)
	return;

	inorder(root->left);
	cout<<root->data;
	inorder(root->right);

	
}
int _tmain(int argc, _TCHAR* argv[])
{
	int data =1;
	BST *bst = new BST();
	while(data!=-1)
	{
		cin>>data;
		bst->add(&(bst->root), data);
	
	}

	bst->inorder(&(bst->root));
	
	return 0;
}

