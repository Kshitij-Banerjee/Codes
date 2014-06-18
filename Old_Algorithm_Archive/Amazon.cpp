// Amazon.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;
int count;

void getFirstLetterWord(char text[],int N) {
/* Please print the final output.
N denotes the length of the array text*/
	int i =0;
	while(text[i]!='\o')
	{

	}

}



int getSingleDigitProduct(int N) {

	if(N/10==0)
		return count;
	int udigit=0;
	int product=1;
	while(N!=0)
	{
		udigit= N%10;
		product*=udigit;
		N/=10;
	}
	count++;
	return(getSingleDigitProduct(product));
}


/* Write your custom/own functions here */
int iterateSequence( int a[], int L, int N ){
/*L : Length of the array */

	while(N>0)
	{
		for(int i =0;i<L-1;i++)
		{
			a[i] = a[i+1]-a[i];
		}
		L--;
		N--;
	}
	int sum=0;
	
	for(int i =0;i<L;i++)
		{
			sum+=a[i];
		}
	return sum;


}


int _tmain(int argc, _TCHAR* argv[])	
{
	int arr[] = { 5,6,3,9,-1 } ;
	
	cout<<iterateSequence(arr,5,1);
	return 0;
}

