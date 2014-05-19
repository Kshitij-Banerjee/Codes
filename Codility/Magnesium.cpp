#include <vector>
#include <assert.h>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include "limits.h"
using namespace std;

typedef vector< vector< pair<int, int> > > vvpi;
typedef vector < pair<int,int> > vpi;
typedef vpi::iterator vpit;
typedef vvpi::iterator vvpit;

typedef vector<int> vi;
typedef vi::iterator vit;


int highest_depth;

struct comparator
{
	bool operator()( const pair< int, pair<int, int> >& l,   const pair< int, pair<int, int> >& r )
	{
		return l.first < r.first ;
	}
} comparer;


bool is_ascending( int i , int weight, int memo_last[] )
{
	// current edge is greater than the last edge for the max path

	return (weight > memo_last[i]);
}

int solution_brute( int N, vector<int> &A, vector<int> &B, vector<int> &C );
int solution( int N, vector<int> &A, vector<int> &B, vector<int> &C )
{
	if( A.size() == 0 )
		return 0;

	vvpi adjacency(N, vector<pair<int, int> >());

	for (size_t i = 0; i < A.size(); i++)
	{
		adjacency[A[i]].push_back(make_pair(B[i], C[i]));
		adjacency[B[i]].push_back(make_pair(A[i], C[i]));
	}

	vector< pair< int, pair<int,int> > > edges;
	for( size_t i = 0 ; i < A.size(); i ++ )
	{
		edges.push_back( make_pair( C[i] , make_pair( A[i], B[i] ) ) );
	}

	// Sort on edge weights.
	std::sort( edges.begin(), edges.end(), comparer );
	   
	int* memo = new int[N+1];
	int* memo_last = new int[N+1];
	fill( memo, memo + N + 1, 1 ); // every node has atleast one edge to be traversed from.
	
	for( size_t i = 0 ; i < adjacency.size() ; i ++ )
	{
		int min = INT_MAX;
		for( size_t j = 0 ; j < adjacency[i].size() ; j ++ )
			min = std::min( adjacency[i][j].second, min );		

		memo_last[ i ] = min;
	}

	for( size_t i = 0; i < edges.size(); i++ )
	{
		int start = edges[i].second.first;
		int end = edges[i].second.second;

		int old_start = memo[start];
		int old_end = memo[end ];

		bool start_ascending =	is_ascending( start, edges[i].first, memo_last );
		bool end_ascending =	is_ascending( end, edges[i].first, memo_last );
		
		if( start_ascending )
		{
			if( (old_start + 1) > memo[end] ) 
			{
				memo[end] = old_start + 1;
				memo_last[ end ] = edges[i].first; // entered end from this edge.
			}
		}

		if( end_ascending )
		{
			if( (old_end + 1) > memo[ start ] ){
				memo[start] = old_end + 1;
				memo_last[ start ] = edges[i].first; // entered end from this edge.
			}
		}
	}

	int max = 0 ;
	for( int i = 0 ; i < (N +1) ; i ++ )
	{
		max = std::max( max, memo[i] );
	}

	delete [] memo;
	delete [] memo_last;
	return max;
}

#include < iostream >
void UT_1()
{
	vector< int > A(8, 0 );
	vector< int > B(8, 0 );
	vector< int > C(8,0);

	A[0] = 0;        
	A[1] = 1;        
	A[2] = 1;        
	A[3] = 2;        
	A[4] = 3;        
	A[5] = 4;        
	A[6] = 5;        
	A[7] = 3;        

	B[0] = 1 ;
	B[1] = 2 ;
	B[2] = 3 ;
	B[3] = 3 ;
	B[4] = 4 ;
	B[5] = 5 ;
	B[6] = 0 ;
	B[7] = 2 ;
			 
	C[0] = 4;
	C[1] = 3;
	C[2] = 2;
	C[3] = 5;
	C[4] = 6;
	C[5] = 6;
	C[6] = 8;
	C[7] = 7;
 
	if(  solution(6, A, B, C) != 4 )
		cout << "Failed 1" << endl ;
	
}

void UT_2()
{
	int inA[] = { 2, 1, 3, 0, 1, 3, 0 };
	int inB[] = { 1, 1, 4, 4, 0, 2, 1 };
	int inC[] = { 4, 15, 10, 7, 2, 5, 16};
	vector< int > A(inA, inA + 7 );
	vector< int > B(inB, inB + 7 );
	vector< int > C(inC, inC + 7 );

	if( solution( 5, A, B, C ) != 4 )
		cout << "Failed 2" << endl;
}

void UT_randomization()
{
	int nverts = 3;
	int nedges = 5;
	vector< int> A, B, C ;

	do{

		A.clear(); B.clear(); C.clear();

		for( int i =0 ;i < nedges; i ++ )
		{
			A.push_back( rand() % nverts );
			B.push_back( rand() % nverts );
			C.push_back( rand() % nverts );
		}
	}
	while( solution( nverts, A, B, C ) == solution_brute( nverts, A, B, C ) );
	
	cout << nverts;
}

int main()
{
	UT_1();
	UT_2();
	UT_randomization();
}