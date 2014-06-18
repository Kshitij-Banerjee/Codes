// QuickSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
using namespace std;

void printarray(int arr[],int s, int e)
{
	for(int i =s;i!=(e+1);i++)
	{
		cout<<arr[i];
	}
	cout<<endl;
}

int split(int arr[], int s , int e)
{
	int p = e;
	int a =0;
	int b =0;
	for(int i = 0;i!=e;i++)
	{
		if(arr[i] < arr[e])
		{
			int temp = arr[b];
			arr[b] = arr[a];
			arr[a] = temp;
			a++;b++;
				
		}
		else
		{
			b++;
		}

		cout<<"  i= "<<i<<"    :   ";
		printarray(arr,s,e);
		

	}

			int temp = arr[e];
			arr[e] = arr[a];
			arr[a] = temp;


			

			return a;

}

void quicksort(int arr[], int s, int e)
{
	if(s==e)
	return;

	int p = split(arr,s,e);

	
	cout<<"   at split of:"<<p<<"  " ;
	printarray(arr,s,e);

	if(p==0)
	{
		quicksort(arr,p+1,e);
	}
	else if(p==e)
	{
		quicksort(arr,0,p-1);
	}
	else{
	quicksort(arr,0,p-1);
	quicksort(arr,p+1,e);}

}
int _tmain(int argc, _TCHAR* argv[])
{
	int arr[15] = {2,4,3,6,5,9,1,8,0,7,21,17,13,35,11};
	cout<<" original arr :"<<endl;
	printarray(arr,0,14);
	quicksort(arr,0,14);
	cout<<"modified arr :";
	printarray(arr,0,14);

	return 0;
}

