// Adding_LinkLists.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include<iostream>
#include<stack>
#include<string>
#include<sstream>
#include<stdlib.h>
using namespace std;


struct node{

	int data;
	node *next;
};

 node *head3 = NULL;

void add(node*& head ,int data)
{
	struct node* temp ;
	temp = (struct node*)malloc(sizeof(struct node));
	temp->data = data;
	temp->next = head;
	head = temp;
	
}
void addnumbersaslinkedlist2(node* head1,node* head2)
{
    node* start1 = head1;
     node* start2 = head2;
	stack<int> s1 ;
	stack<int> s2 ;
	while(head1!=NULL)
	{
                      s1.push(head1->data);
                      head1 = head1->next;
                      
                      }
                      
    while(head2!=NULL)
	{
                      s2.push(head2->data);
                      head2 = head2->next;
                      
                      }
                      
 int carry=0;
 int first,second;
 
 while(!(s1.empty() || s2.empty()))
 {
 first = s1.top();
 second = s2.top();
 
 s1.pop();
 s2.pop();
 
 add(head3,((first+second)%10)+carry);
 carry = (first+second)/10;
 start1= start1->next;
 start2= start2->next;
                      }
 
if(s1.size()>s2.size())
{
                       add(head3,s1.top()+carry);
                       s1.pop();
                       while(!s1.empty()){
                               add(head3,s1.top());
                               s1.pop();           
                                          }
                       }
else
{
    add(head3,s2.top()+carry);
                       s2.pop();
    while(!s2.empty())
    {
           add(head3,s2.top());
           s2.pop();
                      }
}

 


}

void addnumbersaslinkedlist(node* head1,node* head2)
{
	string s1 = "";
	string s2 = "";
	std::stringstream convert;

	  while(head1!=NULL)
	  {
		  
		  convert << head1->data;
		  head1=head1->next;
			
	  }
	  s1.append(convert.str());
	  convert.str("");
	  while(head2!=NULL)
	  {
		 convert << head2->data;

		  head2=head2->next;
	  }
	  
		  s2 += convert.str();
		  convert.str("");
		 

	  int i1 = atoi(s1.c_str());
	  int i2 = atoi(s2.c_str());

	  cout<<i1+i2;

}

void print(node *head)
{
	
	while(head!= NULL)
	{
		printf("%d",head->data);
		head=head->next;
	}

	printf("\n");
}
int main()
{
	node *head1  = NULL;
	node *head2 = NULL;
	
	add(head1,9);
	add(head1,9);
	add(head1,9);

	add(head2,3);
	add(head2,3);
	add(head2,3);
	add(head2,3);
	add(head2,3);
	
	

	print(head2);
	print(head1);

//	addnumbersaslinkedlist(head1,head2);
	addnumbersaslinkedlist2(head1,head2);
	print(head3);
	
	getchar();



	return 0;
}

