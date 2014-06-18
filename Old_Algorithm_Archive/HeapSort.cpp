// HeapSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
using namespace std;


int left(int arr[], int i,int n)
{
	if((2*i+1) >(n-1))
		return -1;
	else
	return 2*i+1;
}
int right(int arr[], int i, int n )
{
	if((2*i+2) > (n-1))
	return -1;
	else
		return (2*i + 2);
}
int parent(int arr[], int i)
{
	return i/2-1;
}
void swap(int arr[],int i,int j)
{
	arr[i] += arr[j];
	arr[j] = arr[i] - arr[j];
	arr[i] = arr[i] - arr[j];
}

void heapify(int arr[], int i,int n)
{
	int l =left(arr,i,n);
	int r = right(arr,i,n);
	
	while(l!=-1 && r!=-1)
	{
		if(arr[l]<arr[r])
		{
			if(arr[i]>arr[l])
			{	
				swap(arr,i,l);
				i=l;
				l= left(arr,i,n);
				r = right(arr,i,n);
			}
			else return;
			
		}
		else if(arr[i]>arr[r])
		{
			swap(arr,i,r);
				i=r;
				l= left(arr,i,n);
				r = right(arr,i,n);

		}
			
		else
			return;
		
	}
	
}
void print(int arr[] , int n )
{
	for(int i =0;i<n;i++)
	{
		cout<<arr[i]<< " ";
	}
	cout<<endl;
}

void buildheap(int arr[],int n )
{
	for(int i = n/2-1; i>=0 ; i--)
	{
		cout<<"calling heapify at "<<arr[i]<<" "<<endl;
		heapify(arr,i,n);
		print(arr,n);
	}
	

}

void heapsort(int arr[], int i, int j)
{
	for(;j>0;)
	{
	swap(arr,i,j);
	cout<<"calling swap at "<<arr[i]<<" & "<<arr[j]<<endl;
	print(arr,15);
	j--;
	cout<<"calling heapify at "<<arr[i]<<" "<<endl;
	heapify(arr,i,j);
	print(arr,15);
	}
	
}

int _tmain(int argc, _TCHAR* argv[])
{
	int arr[15] = {9,1,8,2,7,3,6,4,5,16,0,12,15,14,10};
	print(arr,15);
	buildheap(arr,15);
	print(arr,15);
	cout<<endl<<endl;


	heapsort(arr,0,14);
	print(arr,15);

	return 0;
}

