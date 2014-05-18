#include <iostream>
#include <vector>
#include <math.h>
#include <limits.h>
using namespace std;
typedef vector<int>::iterator vit;

enum monotonicity
{
	MONOTONIC_NONE,
	MONOTONIC_INCREASING,
	MONOTONIC_DECREASING
};

monotonicity is_monotonic( vector<int>& A )
{
	vit it1 = A.begin();
	vit it2 = it1+1;

	bool is_increasing = (*it2 >= *it1);
	while( is_increasing && it2 != A.end() )
	{
		is_increasing &= (*it2 >= *it1 );
		it1++;
		it2++;
	}
	if( is_increasing ) return MONOTONIC_INCREASING;

	it1 = A.begin();
	it2 = it1+1;
	bool is_decreasing = (*it2 <= *it1);
	while( is_decreasing && it2 != A.end() )
	{
		is_decreasing &= (*it2 <= *it1 );
		it1++;
		it2++;
	}
	if( is_decreasing ) return MONOTONIC_DECREASING;

	return MONOTONIC_NONE;
}

class Segment
{
private:
	vector<int>::iterator max;
	vector<int>::iterator min;
	Segment* next_seg;
	monotonicity _mon;
	bool _is_complete;
	int _overlap;
	int K;
	
public:
	vector<int>::iterator _start;
	vector<int>::iterator _end;

	Segment( vit it, vit it2, int K, monotonicity mon );
	vit& operator++( int );
	bool is_complete();
	Segment* spit_new();
	int overlaps();
	int size();	
};
bool Segment::is_complete()
{
	return _is_complete;
}
int Segment::size()
{
	return ( _end - _start + 1 );
}
int Segment::overlaps()
{
	return _overlap;
}

Segment* Segment::spit_new()
{
	return next_seg;	
}
Segment::Segment( vit it, vit it2, int k, monotonicity mon)
{
	K = k;
	_start = it;
	_end = it2;
	max = *it > *it2 ? it : it2;
	min = *it < *it2 ? it : it2;
	_is_complete = false;
	_overlap = 0;
	next_seg = NULL;
	_mon = mon;
}

vit& Segment::operator++( int )
{
	vit it = _end + 1;

	if( *it == INT_MAX )
	{
		_is_complete = true;
		next_seg = NULL;
		return _end;
	}

	if( ((*it > *max) && ((*it - *min) > K)) )
	{		
		if( _mon == MONOTONIC_INCREASING ) 
			next_seg = new Segment( min+1, it, K, _mon );
		else
		   next_seg = new Segment( min+1, min+1, K, _mon );
        
		_is_complete = true;
		return _end;
	} 

	if(	((*it < *min) && ((*max - *it) > K)) )
	{
		if( _mon == MONOTONIC_DECREASING ) 
			next_seg = new Segment( max+1, it, K, _mon );
		else
			next_seg = new Segment( max+1, max+1, K, _mon );

		_is_complete = true;
		return _end;
	}

	// If none of the above but new max..
	if( *it > *max )
	{
		max = it;
	}
	if( *it < *min )
	{
		min = it;
	}
		
	return ++_end;
}


unsigned long combinations( unsigned long seg_length )
{	
	long result  = powl( seg_length, 2) - seg_length ;
	result = result >> 1 ;
	return std::min<unsigned long>( result + seg_length, 1000000000 );
}
int solution(int K, vector<int> &A)
{
	if( A.size() == (size_t) 0 ) return 0;
	if( A.size() == (size_t) 1 ) return 1;

	monotonicity mon = is_monotonic( A );

	A.insert( A.end() , INT_MAX);
	vector<Segment*> segments;
	Segment* seg = new Segment( A.begin(), A.begin(),  K, mon );
	while( seg )
	{
		while( !seg->is_complete() )
			(*seg)++;

		segments.push_back( seg );
		seg = seg->spit_new();		
	}	
	
	segments.push_back( seg );
	
	unsigned long result = 0;
	for( vector<Segment*>::iterator it = segments.begin(); it != segments.end(); it ++ )
	{
		Segment* segment = *it;
		Segment* next = *(it +1);
		result += combinations( segment->size() );

		if( !segment->spit_new() )
			break;
		
		if( (next->_start) <= (segment->_end) ) 
			result -= combinations( segment->_end - next->_start + 1 );
	}

	for( vector<Segment*>::iterator it = segments.begin(); it != segments.end(); it ++ )
	{
		delete *it;
	}

	return std::min<unsigned long>( result, 1000000000 );
}


int UT_1()
{
	vector<int> A;
	A.push_back( 3 );
	A.push_back( 5 );
	A.push_back( 7 );
	A.push_back( 6 );
	A.push_back( 3 );

	return solution( 2, A );
}

int UT_2()
{
	vector<int> A;
	A.push_back( 10 );

	return solution( 0, A );
}

int UT_3()
{
	vector<int> A;
	A.push_back( 10 );
	A.push_back( 8 );
	A.push_back( 6 );

	return solution( 0, A );
}
int UT_4()
{
	vector<int> A;
	A.push_back( 10 );
	A.push_back( 10 );
	A.push_back( 10 );

	return solution( 0, A );
}

//(6, [4, 5, 8, 5, 1, 4, 6, 8, 7, 2, 2, 5])

int UT_5()
{
	int arr[] = { 4, 5, 8, 5, 1, 4, 6, 8, 7, 2, 2, 5 };
	vector<int> A( arr, arr + 12 );

	return solution( 6, A );
}

int UT_6()
{
	vector<int> A( 100000, 1000000000);

	return solution( 0 , A );
}

int UT_7()
{
	int arr[12] = { 10, 7, 10, 4, 9, 3, 5, 8, 2, 7, 7, 3 };
	vector<int> A( arr, arr + 12 );
	return solution( 5, A );
}

//5 [2, 3, 2, 9, 8, 3, 10, 6, 7, 1, 10, 9
int UT_8()
{
	int arr[12] = { 2, 3, 2, 9, 8, 3, 10, 6, 7, 1, 10, 9 };
	vector<int> A( arr, arr + 12 );
	return solution( 5, A );
}

int UT_9()
{
	int arr[12] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	vector<int> A( arr, arr + 12 );
	return solution( 5, A );
}

void main()
{
	if( 9 !=UT_1() )
		cout<< "FAILED 1" <<endl;

	if( 1 != UT_2() )
		cout<< "FAILED 2" << endl;

	if( 3 != UT_3() )
		cout<< "FAILED 3" << endl;

	if( 6 != UT_4() )
		cout<< "FAILED 4" << endl;

	if( 44 != UT_5() )
		cout<< "FAILED 5: " << UT_5() << " != " << 44 <<  endl;

	if( 1000000000 != UT_6() )
		cout<< "FAILED 6: " << UT_6() << "!= " << 1000000000 << endl;

	if( 25 != UT_7() )
		cout << "FAILED 7: " << UT_7() << " != " << 25 << endl;

	if( 21 != UT_8() )
		cout<< "FAILED 8:" << endl;

	UT_9();
	int x ;
	cin >> x;
}
