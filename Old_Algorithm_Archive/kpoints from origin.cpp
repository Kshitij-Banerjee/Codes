// Given N pointsin a 2d space. Find the k points with minimum distance from origin.
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct point
{
	int x;
	int y;
};

int computedistance(point& pt)
{
	return(pt.x*pt.x + pt.y*pt.y);
}
bool compare(const int& x,const int& y)
{
	return(y<x?true:false);
}
void findkclosest(point arr[],int size,int k)
{
	vector<int> vecarr(size);

	for(int i =0;i<size;i++)
	{
		vecarr[i] = computedistance(arr[i]);
		cout<<vecarr[i]<<" ";
	}
	cout<<endl;

	vector<int> heapofk(vecarr.begin(),vecarr.begin()+k);
	make_heap(heapofk.begin(),heapofk.end());

	vector<int>::iterator it ;	
	cout<<endl<<heapofk.front()<<endl;

	for(it=vecarr.begin()+k;it<vecarr.end();it++)
	{
		if(*it < heapofk.front())
		{
			pop_heap(heapofk.begin(),heapofk.end());
			heapofk.pop_back();
			heapofk.push_back(*it);
			push_heap(heapofk.begin(),heapofk.end());
		}
	}
	
	for(it=heapofk.begin();it<heapofk.end();it++)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
	



}

int _tmain(int argc, _TCHAR* argv[])
{

	point arr[10] = {{1,0},{2,3},{3,4},{5,6},{-3,7},{3,9},{2,2},{6,7},{3,5},{3,3}};
	findkclosest(arr,10,5);
	return 0;
}

