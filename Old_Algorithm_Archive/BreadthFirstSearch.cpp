// BreadthFirstSearch.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cstdlib>
#include <iostream>
#include <conio.h>
#include <queue>
#include <math.h>


using namespace std;

struct Node 
{
       int data ;
       Node *left;
       Node *right;

	   Node()
	   {
		   data = 0;
		   left = NULL;
		   right=NULL;
	   }

	   Node(int value)
	   {
		   data = value;
		   left = NULL;
		   right=NULL;
	   }
      
};

class BinaryTree
    {
    private:
    	 struct Node* o_root;

    public:

    BinaryTree()
    	{
            o_root = NULL;    
    	}

		void inorder();
    	void inorder(Node*root);
		void BFS();
		void insert(int key);
		void insert(Node*& root,int key);
		void flattentolinkedlist();
		Node* flattentolinkedlist(Node*& prev , Node* current);
		Node* findLCA(Node* root, int first, int second);
		Node* BinaryTree::findLCA(int first, int second);
    	
    };

    void BinaryTree::inorder()
	{
		inorder(o_root);
	}

    void BinaryTree::inorder(Node* root)
    	{
    		 if(root==NULL)
    		 {
    			 return;
    		 }
    		 inorder(root->left);
         
    		 cout<< root -> data;
         
    		 inorder(root->right);
         
    	}

	void BinaryTree::insert(int key)
	{
		insert(o_root,key);
	}

	void BinaryTree::insert(Node*& root,int key)
	{

		if(root==NULL)
		{
			root = new Node(key);
		}

		if(key < root->data)
		{
			if(root->left==NULL)
			{
				root->left = new Node(key);
				
			}
			else
			insert(root->left,key);
		}
		else if(key>root->data)
		{
			if(root->right==NULL)
			{
				root->right = new Node(key);
			}
			else
				insert(root->right,key);

		}
			
	}


queue<Node*> Q;
queue<int> first;

 
 void BinaryTree::BFS()
 {    
      int i(0);
	  Q.push(o_root);
 
      while(!Q.empty())
      {
      
      if(Q.size() == pow(2.0,i))
      {
      cout<<endl; 
      ++i;
      }         
      
      cout<<Q.front()->data;
      Q.push(Q.front()->left);
      Q.push(Q.front()->right);
	  
      Q.pop();
	   
      
      }
  }
  
 void reverse(Node* root)
  {
    
       if((root->left==NULL) && (root->right==NULL))
       {
                             cout<<"NULL reached";
         return; }
      
                         
       if(root->left)
       reverse(root->left);
       
       if(root->right)
       reverse(root->right);
       
       cout<<"about to reverse node " << root->data<<endl;
       
       if(root->left)
       {
       root->left->left = root;
        root->left->right  = NULL;
        }
    
   if(root->right){
     root->right->right = root;
    root->right->right = NULL;
    } 
   
   
       
   }

 void link(Node*& prev, Node*& curr)
 {
	 if(prev!=NULL)
	 {
	 cout<<"linked "<<prev->data<<" with "<<curr->data;
	 curr->left = prev;
	 prev->right = curr;
	 cout<<endl;

	 }
 }

 void BinaryTree::flattentolinkedlist()
 {
	 Node* prev = NULL;
	 flattentolinkedlist(prev,o_root);
 }
/*
		  4
	2		    7
1	   3  	5		8
  5

*/
 Node* BinaryTree::flattentolinkedlist(Node*& prev, Node* curr)
 {

	 if(curr->left ==NULL && curr->right == NULL)
     {
		 link(prev,curr);

		 return curr;
     }

	 if(curr->left !=NULL)
	 {
			  prev = flattentolinkedlist(prev,curr->left);
			  link(prev,curr);
	 }
			 
			 if(curr->right !=NULL)
			 {
			 Node* next = flattentolinkedlist(curr,curr->right);
			 link(curr,next);
			 return next;
			 }

			 
 };
       
 Node* BinaryTree::findLCA(Node* root, int first, int second)
 {
	  if(root==NULL)
		 return NULL;
	 if(root->data==first || root->data==second)
	 return root;

	 Node* l = findLCA(root->left,first,second);
	 Node* r = findLCA(root->right,first,second);

	 if(l&&r)
		 return root;
	 else if (l)
		 return l;
	 else if(r)
		 return r;
	 
 }

 Node* BinaryTree::findLCA(int first, int second)
 {
	return findLCA(o_root,first,second);
	 

 }

int _tmain(int argc, _TCHAR* argv[])
{

	BinaryTree *bt = new BinaryTree();

	/*Node *root, *one, *two, *three, *four, *five, *six, *seven,*eight  ;
    root = new Node();
    one = new Node();
        two = new Node();
            three = new Node();
                four = new Node();
                    five = new Node();
                        six= new Node();
                             seven= new Node();
                                 eight= new Node();
                           
    root->data = 0;
    one->data = 1;
    two->data = 2;
    three->data = 3;
    four->data =4;
    five->data = 5;
    six ->data = 6;
    seven->data = 7;
     eight->data = 8;
    

	 
  
    
     one->left = three;
    one->right = four;
    
    
     three->left = seven;
     three->right = NULL;
   
    two->left = five;
    two->right = six;
    
    four ->left = NULL;
        four ->right = NULL;
        
    five ->left = NULL;
        five ->right = NULL;
        
        
    six ->left = NULL;
        six ->right = eight;
        */
        
        
        
 //Q.push(root);
 //BFS();
 //reverse(root);

	bt->insert(5);
	bt->insert(3);
	bt->insert(2);
	bt->insert(1);
	bt->insert(8);
	bt->insert(4);
	bt->insert(6);
	bt->insert(8);
	
	//bt->BFS();
	//bt->flattentolinkedlist();

	cout<<bt->findLCA(4,2)->data;


    getch();
   
	return 0;
}

