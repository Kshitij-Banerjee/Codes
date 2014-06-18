// Quicksort on LinkedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
using namespace std;

struct node 
{
	int data;
	node* next ;
};
void swapnodes(node* one, node* second);
class LinkedList
{
private:
	node* head;
public:
	LinkedList()
	{
		head = NULL;
	}
	node* operator[](int data);
	void push_front(int data);
	void print_list();
	void quicksort();
	void quicksort(node* start, node* last);
	node* end();
	node* middle();
	node* part(node*& start, node*& end);

};
void LinkedList::quicksort()
{
	quicksort(head, end());
}
void LinkedList::quicksort(node* start, node* last)
{
	cout<<endl<<"quick sort :"<<start->data<<" and "<<last->data<<endl;
	if(start==NULL || last==NULL)
	{
		cout<<"NULL arguments";
	}
	if(start==last)
		return;
	node* partition = part(start,last);
	print_list();	
	node* ptr = start;
	if(partition==start)
		quicksort(start->next,last);
	else if(partition==last)
	{
		while(ptr->next!=partition)
		{
			ptr = ptr ->next;
		}
		quicksort(start,ptr);
	}
		
	else
	{
		while(ptr->next!=partition)
		{
			ptr = ptr ->next;
		}
		quicksort(start,ptr);
		quicksort(partition->next, last);
	}
	

}
node* LinkedList::part(node*& start, node*& end)
{
	node* low=start;
	node* high=start;
	node* ptr = start;
	while(ptr!= end)
	{
		//cout<<"currentnode is "<<ptr->data<<endl;

		if(ptr->data < end->data)
		{
			swapnodes(low,ptr);
		//	print_list();	
			low=low->next;
			
		}
		if(ptr->data > end->data)
		{
			high = high ->next;
			//cout<<"high is now : " <<high->data<<endl;
		}
		ptr=ptr->next;
	}
	if(low!=end)
	swapnodes(end,low);
	else
		return(end);
	//print_list();	

	return(low);

}

void swapnodes(node* one, node* second)
{
	if(one==second)
		return;
	//cout<<"swapping "<<one->data;
	//cout<<" with "<<second->data<<endl;
	one->data += second->data;
	second->data = one->data - second->data;
	one->data = one->data - second->data;
	
	
}
node* LinkedList::middle()
{
	node* slow = head ; 
	node* fast = head ; 
	while(fast!=NULL)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}
node* LinkedList::end()
{
	node* ptr = head ; 
	while(ptr->next !=NULL)
	{
		ptr = ptr->next;
	}
	return ptr;
}

void LinkedList::print_list()
{
	node* ptr = head ; 
	while(ptr!=NULL)
	{
		cout<<ptr->data<<" ";
		ptr = ptr->next;
	}
	cout<<endl;
	
}
node* LinkedList::operator[](int index)
	{
		node* ptr = head;
		if(ptr == NULL)
			return NULL;
		int i = 0;
		while(i!=index && ptr!=NULL)
		{
			i++;
			ptr = ptr->next;
		}
		return ptr;
	}
void LinkedList::push_front(int data)
{
	node* newnode= new node();
	newnode->data = data;
	newnode->next = head; 
	head = newnode;

}

int _tmain(int argc, _TCHAR* argv[])
{
	LinkedList* LL = new LinkedList();
	LinkedList &objLL = (*LL);

	objLL.push_front(0);
	objLL.push_front(10);
	objLL.push_front(3);
	objLL.push_front(2);
	objLL.push_front(23);
	objLL.push_front(1);
	objLL.push_front(45);
	objLL.push_front(0);
	objLL.push_front(90);

	cout<<"list end"<<objLL.end()->data<<endl;


	objLL.print_list();
	objLL.quicksort();
	objLL.print_list();


	
	
		
	return 0;
}

