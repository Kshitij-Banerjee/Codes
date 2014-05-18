#include <vector>
#include "limits.h"
using namespace std;
int find_max(vector<int> &R, int X, int M, int start, int end, int boat_start)
{
	int max = 0;
	int j = start;
	int i = boat_start;

	for (; j <= end; j++, i += (2 * X))
	{
		if (abs(R[j] - i) > max){
			max = abs( R[j] - i );
		}
	}

	return max;
}

int refine_clustor(vector<int> &R, int X, int M, int start, int end, int boat_start)
{
	int max[2] = { 0, 0 };
	int j = start;
	int i = boat_start;

	int residual_force = 0 ;

	for (; j <= end; j++, i += (2 * X))
	{
		residual_force += ( R[j] - i );

		if (abs(R[j] - i) > abs(max[0])){
			max[1] = max[0];
			max[0] = R[j] - i;
		}
		else if (abs(R[j] - i) > abs(max[1])){
			max[1] = R[j] - i;
		}			
	}

	// Is there room to shift?
	if (abs(max[0]) - abs(max[1]) > 1)
	{
	//return residual_force /2;

		int offset = (abs(max[0]) - abs(max[1])) >> 1;
		if ( max[0] > 0 )
			return offset;
		else
			return -offset;
	}	
	else
		return 0;
}

int find_mid(vector<int>& R, int start, int end)
{
	int sum = 0;
	for (int i = start; i <= end; i++){
		sum += R[i];
	}
	return sum / (end - start + 1);
}
int solve(vector<int>&R, int X, int M, int start, int end, int wall[2] )
{
	if (end < start)
		return -1;

	int center = find_mid(R, start, end);
	int clustor_start = center - (X*(end - start + 1));
	int clustor_end = center + (X*(end - start + 1));

	int offset = refine_clustor( R, X, M, start, end, clustor_start + X);

	clustor_start += offset;
	clustor_end += offset;

	if (clustor_start < wall[0] )
	{
		clustor_end += abs( wall[0] - clustor_start);
		clustor_start = wall[0];
	}

	if (clustor_end > wall[1])
	{
		clustor_start -= (clustor_end - wall[1]);
		clustor_end = wall[1];
	}
	
	wall[0] = clustor_start;
	wall[1] = clustor_end;

	if (start == end){		
		return abs(R[start] - (clustor_start + X));
	}

	int i = start;
	int boat_center = clustor_start + X;
	while ((i <= end) && (R[i] - boat_center <= 0)){
		boat_center += (2 * X);
		i++;
	}

	if (i > end){
		return find_max(R, X, M, start, i - 1, clustor_start + X);
	}

	int j = end;
	boat_center = clustor_end - X;
	while ((j >= start) && (R[j] - boat_center >= 0)){
		j--;
		boat_center -= (2 * X);
	}

	if (j < start){
		return find_max(R, X, M, j + 1, end, clustor_start + X);
	}
		

	if ((i == start) && (j == end)){
		return find_max(R, X, M, start, end, clustor_start + X);
	}
	
	
	int s_ends[2] = {0,M};
	int s = solve(R, X, M, start, i - 1, s_ends);

	int e_ends[2] = {0, M};
	int e = solve(R, X, M, j + 1, end, e_ends );

	int m_ends[2] = {0,M}; 
	int m = solve(R, X, M, i, j, m_ends);
	if( s!= -1 && m != -1 ){
	// Resolve m and e;
	bool flip = true;
	while( s_ends[1] > m_ends[0] ){
		if( flip ){
			if( s_ends[0] != 0 ){
			s_ends[1]--;
			s_ends[0]--;
			s++;
			}
		}
		else{
			if( m_ends[1] != M ){ 
			m_ends[0]++;
			m_ends[1]++;
			m++;
			}
		}
		flip = !flip;
	}
	}

	wall[0] = s == -1 ? m_ends[0] : s_ends[0];
	wall[1] = e == -1 ? m_ends[1] : e_ends[1];

	return e > s ? (e > m ? e : m ) : ( s > m ? s: m );
}
int solution(vector<int> &R, int X, int M) {
	// write your code in C++98

	if ((int)R.size() * 2 * X > M)
		return -1;

	int wall[2] = {0,M};

	return solve(R, X, M, 0, (int)R.size()-1,wall );
}

int UT_1()
{
	int input[] = { 1, 3, 14 };
	vector<int> in(input, input + 3);

	return solution(in, 2, 16);
}

int UT_2()
{
	int input[] = { 4, 7, 9, 11, 14, 21, 21, 22, 22, 23 };
	vector<int> in(input, input + 10);
	return solution(in, 1, 37);

}

int UT_3()
{
	int input[] = { 9, 14, 14, 14, 15, 19, 24, 24, 27, 30 };
	vector<int> in(input, input + 10);
	return solution(in, 1, 32);
}

int UT_4()
{
	vector<int> in;
	for (int i = 0; i < 5000; i++)
		in.insert(in.begin(), 0);

	for (int i = 0; i < 5000; i++)
		in.insert(in.end(), 100000);

	return solution(in, 1, 100000);
}
#include <algorithm>
int UT_5()
{
	vector<int> in;
	do{
		in.clear();
		for (int i = 0; i < 5; i++)
		{
			in.push_back(rand() % 10);
		}
		sort(in.begin(), in.end());
	} while (solution(in, 1, 10) == find_max(in, 1, 10, 0, (int)in.size() - 1, 1));

	return solution(in, 1, 10) != find_max(in, 1, 10, 0, (int)in.size() - 1, 1);
}
void main()
{
	if (UT_1() != 3)
		printf(" 1: Failed\n");

	if (UT_2() != 3)
		printf(" 2: Failed\n");

	if (UT_3() != 3)
		printf(" 3: Failed\n");
	
	/*if (UT_4() > 9999)
		printf(" 4: Failed \n");*/

	UT_5();

}
//
//([4, 7, 9, 11, 14, 21, 21, 22, 22, 23], 1, 37)
//with WRONG ANSWER[got 4 expected 3]


//([9, 14, 14, 14, 15, 19, 24, 24, 27, 30], 1, 32)
//with WRONG ANSWER[got 1 expected 3]