// printspiral.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
using namespace std;

void printinspiral(int arr[],int m, int n,int count)
{
	int im = count;
	int in = count;

	for(int i =count; i<n-count-2 ;i++)
	{
		cout<<arr[n*(count-1) + i];
	}

	for(int j = 1; j<m-count-1;j++)
	{
		cout<<arr[m*j-1];
	}
	
	for(int j = n-2; j>0;j++)
	{
		cout<<arr[(m-count-1)*n +j];
	}

	for(int j = n-2; j>0;j++)
	{
		cout<<arr[(m-count)*j +1];
	}

}

int _tmain(int argc, _TCHAR* argv[])
{
	int m,n;
	cin>>m;
	cin>>n;
	int *arr = (int*)calloc(sizeof(int)*m,sizeof(int)*n);

	for(int i =0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			cin>>arr[i*n+j];
		}
	}

	printinspiral(arr);
	return 0;
}

