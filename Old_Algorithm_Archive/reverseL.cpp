// reverseL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
using namespace std;

struct node
{
	int data;
	node* next;
	
};

void printnodes(node* curr)
{
	while(curr != NULL)
	{
		cout<<curr->data;
		curr=curr->next;
	}
	cout<<endl;
}

node* reverse(node*& prev, node*& curr)
{
	

	if(curr->next==NULL)
		{
	node* temp = curr->next;
	curr->next = prev;
	return curr;
	}

	else	
		{
	node* temp = curr->next;
	curr->next = prev;
	return reverse(curr,temp);
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	
	struct node six = {6,NULL};
	struct node two = {2,NULL};
	struct node nine = {9,NULL};
	struct node eight = {8,NULL};

	struct node* head = &six;
	six.next = &two;
	two.next = &nine;
	nine.next = &eight;
	eight.next = NULL;

    printnodes(head);

	struct node* nul = NULL;
	head = reverse(nul,head);

	printnodes(head);

	return 0;
}


