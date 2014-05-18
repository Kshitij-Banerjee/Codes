

#include <vector>
#include "limits.h"
using namespace std;

typedef vector<int> vec;
typedef vec::iterator vit;

typedef vector< vit > vec_it;
typedef vec_it::iterator vec_it_it;


vec_it_it find_next_max(vec_it &range, int query){
	int start = 0;
	int end = range.size() - 1;
	int mid = 0;
	while (end > start){
		mid = (start + end) >> 1;
		if (*range[mid] > query){
			end = mid;
		}
		else if (*range[mid] < query){
			start = mid;
		}
	}

	return range.begin() + mid;
}

int solution(vec &A)
{
	// Construct the sorted range vec_it for query.
	vec_it range;
	for (int i = A.size() -1 ; i > 0; i--)
	{
		if (A[i] > *range.back())
			range.push_back( A.begin() + i );
	}

	// Now find the max slice for each elements..

	int max = 0;
	for (vit it = A.begin(); it != A.end(); it++)
	{
		vec_it_it it2 = find_next_max(range, *it);
		if (it2 != range.end()){
			max = *it2 - it > max ? *it2 - it : max;
		}
	}

	return max;
}




//===============================================================

int solution_silver(vector<int> &A)
{
	int max = INT_MIN;
	for (vit i = A.begin(); i != A.end(); i++)
	{
		for (vit j = i + 1; j != A.end(); j++)
		{
			if ((*i <= *j))
				max = (j - i) > max ? (j - i) : max;
		}
	}
	return max;
}
int UT_1()
{
	int in[] = { 4, 5, 8, 5, 1, 4, 6, 8 };
	vector<int> ans(in, in + 8);

	return solution(ans); // 7

}

int UT_2()
{
	int in[] = { 7, 10, 3, 9, 4, 10, 3, 1 };
	vector<int> ans(in, in + 8);

	return solution(ans); // 5
}

int UT_3()
{
	vector<int> ans;
	int size = 5;
	for (int i = 0; i < size; i++)
	{
		ans.push_back(size + i);
	}

	for (int i = 0; i < size; i++)
	{
		ans.push_back(size - i);
	}

	return solution(ans);
}

int UT_4()
{
	int size = 10;
	vec ans;

	do{
		ans.clear();
		for (int i = 0; i < size; i++)
		{
			ans.push_back(rand() % size);
		}
	} while (solution(ans) == solution_silver(ans));

	return 0;
}

int main()
{
	UT_1();
	UT_2();
	UT_3();
	UT_4();
}
