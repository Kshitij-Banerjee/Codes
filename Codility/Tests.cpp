#include <vector>
#include <iostream>
using namespace std;
// Frwrd Decl..
vector<int> solution( int K, vector<int> &T );
vector<int> solution_silver( int K, vector<int> &T );

void UT_1()
{
	int i[7] = {1,2,3,3,2,1,4};
	int a[5] = {2, 0, 6, 3, 5};
	vector<int> ans( a, a+5 );
	vector<int> input(i , i + 7 );
	if( ans != solution( 2, input ) )
		cout<< "UT1 Failed!" << endl;
}

void UT_2()
{
	int i[17] = {10, 8, 3, 12, 6, 9, 10, 11, 4, 1, 16, 6, 9, 14, 10, 1, 16};
	vector<int> input(i , i + 17 );
	solution( 16, input );
}

void UT_3()
{
	int i[10] = { 1,2,3,4,5,6,7,8,9,10 };
	vector<int> input(i, i +10 );
	solution( 0, input);
}



void UT_4()
{
	int i[17] = {10, 8, 5, 15, 11, 15, 9, 8, 12, 12, 13, 12, 2, 16, 10, 13, 16};
	vector<int> input(i, i +17);
	solution( 16, input);
}


void UT_5()
{
	int i[1] = {0};
	vector<int>input( i , i+1 );
	solution( 0, input );
}

//(16, [1, 11, 5, 13, 15, 13, 10, 16, 11, 15, 9, 6, 16, 9, 3, 12, 16])
//with WRONG ANSWER [ got [16, 0, 14, 2, 4, 7,.. expected [16, 0, 2, 14, 4, 7,.. ]
void UT_6()
{
	int i[17] = {1, 11, 5, 13, 15, 13, 10, 16, 11, 15, 9, 6, 16, 9, 3, 12, 16};
	int a[7] = {16, 0, 2, 14, 4, 7,8};
	vector<int> ans( a, a+7 );
	vector<int> input( i , i+17 );
	if( ans != solution( 16, input ) )
		cout<< "Failed 7!"<< endl;

}


//(16, [10, 2, 4, 11, 7, 10, 10, 14, 13, 14, 3, 16, 4, 6, 11, 4, 16])
//with WRONG ANSWER [ got [16, 8, 1, 0, 5, 9, .. expected [16, 1, 8, 0, 5, 9, .. 
void UT_7()
{
	int i[17] = {10, 2, 4, 11, 7, 10, 10, 14, 13, 14, 3, 16, 4, 6, 11, 4, 16};
	int a[8] = {16, 1, 8, 0, 5, 9, 12, 15};
	vector<int> ans( a, a+8 );
	vector<int> input( i , i+17 );
	if( ans != solution( 16, input ) )
		cout<< "Failed 7!"<< endl;
}
//void UT_8()
//{
//	int i[10] = {8,};
//	int a[8] = {16, 1, 8, 0, 5, 9, 12, 15};
//	vector<int> ans( a, a+8 );
//	vector<int> input( i , i+17 );
//	if( ans != solution( 16, input ) )
//}
bool is_valid_graph( vector<int> &T, int K);

#define max 10
void main()
{
	UT_1();
	UT_2();
	UT_3();
	UT_4();
	UT_5();
	UT_6();
	UT_7();
	//UT_8();
	/*vector<int> input;
	int K;
	do
	{
		input.clear();
		for( int i = 0; i < max; i ++ )
		{
			int random = rand()%max;
			while( random == i )
				random = rand()%max;

			input.push_back(random );
		}

		K = rand()%max;

		if( !is_valid_graph( input, K ) ) 
		{
			input.clear();
			input.push_back( 0 );
			K = 0;
			continue;
		}

		 
	}while( solution_silver( K, input ) == solution(K, input) );

	cout<< "DONE" ;		*/
}