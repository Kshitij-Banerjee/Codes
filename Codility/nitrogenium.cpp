#include <list>
#include <vector>
#include <algorithm>
//#include < iostream >
using namespace std;
void preprocess( vector<int>&, vector<int>&, int  );

vector<int> solution(vector<int> &A, vector<int> &B)
{		
	if( B.empty() ) return B;
	if( A.empty() ) return A;

	int max_b = *max_element( B.begin(), B.end() );
	
	vector<int> unique_list;
	preprocess( A, unique_list, max_b );

	vector<int> sea_level_to_island( max_b + 1, 0 ); // map that needs to be created

	vector<int>::iterator before,current,after;
	before = unique_list.begin();
	current = before + 1;
	after = current +1;

	while( after != unique_list.end() )
	{
		if( (*current > *after) && (*current > *before) ) 
		{
			sea_level_to_island[ *current -1 ] ++;
		}
		else if( (*current < *after) && (*current < *before ) )
		{
			if( *current > 0 ) sea_level_to_island[ *current -1 ] --; 
		}			

		before++;
		current++;
		after++;
	}

	for( int i = max_b; i > 0; i -- )
	{
		sea_level_to_island[ i - 1 ] += sea_level_to_island[ i ];
	}

	for( current = B.begin(); current != B.end() ; current ++ )
	{
		*current = sea_level_to_island[ *current ];
	}

	return B; // TODO!
}


void preprocess( vector<int>& A, vector<int>& unique_list, int max_b )
{
	// remove duplicate plots adjacent to each other.
	// also make any elements > max_b = (max_b + 1)
	// returns intial island count..

	//Append -1 to start and end to begin with.

	unique_list.push_back( 0 ); // start -1

	for( vector<int>::iterator it = A.begin(); it != A.end() ; it++ )
	{
		//cout << *it << ", ";
		if( *it  > max_b ) 
			*it = (max_b + 1 );
	}
	
	for( vector<int>::iterator it = A.begin(); it != A.end() ;  )
	{	
		// remove duplicates..
		unique_list.push_back( *it );

		vector<int>::iterator it2 = it+1;

		while( it2 != A.end() &&  (*it2 == *it ) )
			it2++;
		
		if( it2 == A.end() ) break;
		else it = it2; // move ahead...
	}

	unique_list.push_back( 0 ); //end -1

}
//
//
//
//
//
//void UT_1(){
//	int arr[5] = { 2, 1, 3, 2, 3 };
//	vector<int> A(arr, arr+5);
//	int arr2[5] = { 0, 1, 2, 3, 1 };
//	vector<int> B( arr2, arr2+5 );
//	solution( A, B );
//}
//
//void UT_2(){
//	int arr[3] = { 5, 0, 5 };
//	vector<int> A(arr, arr+3);
//	int arr2[3] = { 0, 3, 5 };
//	vector<int> B( arr2, arr2+3 );
//	solution( A, B );
//}
//
//void UT_3(){
//	int arr[6] = { 10,2,10,2,10,2 };
//	vector<int> A(arr, arr+6);
//	int arr2[5] = { 0,2,3,9,11 };
//	vector<int> B( arr2, arr2+5 );
//	solution( A, B );
//}
//
//#include < iostream >
//void assert( bool exp )
//{
//	if( !exp ) cout<< " ASSERT failed! ";
//}
//void main()
//{
//	UT_2();
//}
//
//
//
////void UT_3(){
////	int arr[6] = { 6, 56, 196, 342, 69, 56, 116, 379, 73, 371, 331, 68, 268, 224, 206, 499, 46, 10, 470, 201, 99, 165, 182, 478, 105, 108, 293, 274, 477, 420, 178, 102, 419, 495, 15, 368, 435, 326, 109, 399, 365, 97, 321, 109, 20, 168, 167, 198, 324, 418, 481, 489, 497, 395, 153, 88, 312, 273, 337, 46, 96, 461, 301, 348, 47, 199, 455, 325, 496, 98, 227, 401, 222, 395, 281, 59, 49, 492, 59, 97, 167, 357, 427, 238, 249, 395, 139, 186, 306, 318, 19, 56, 69, 363, 347, 487, 384, 127, 383, 493, 174, 5, 187, 141, 88, 22, 62, 433, 25, 307, 103, 96, 411, 149, 92, 227, 348, 262, 430, 201, 262, 359, 231, 359, 233, 66, 61, 392, 373, 472, 345, 290, 83, 427, 59, 212, 70, 190, 153, 213, 356, 271, 121, 390, 368, 414, 16, 307, 448, 129, 101, 407, 182, 201, 409, 192, 99, 107, 173, 349, 184, 386, 33, 124, 313, 240, 250, 468, 138, 90, 16, 241, 148, 237, 2, 0, 190, 379, 150, 457, 290, 202, 389, 116, 303, 424, 271, 160, 48, 287, 93, 186, 271, 471, 337, 260, 430, 154, 194, 339, 277, 111, 205, 412, 121, 353, 24, 478, 342, 162, 492, 399, 30, 124, 246, 500, 70, 23, 156, 22, 204, 269, 220, 70, 11, 402, 220, 240, 239, 343, 451, 414, 364, 169, 84, 44, 430, 28, 285, 455, 161, 194, 209, 473, 342, 420, 19, 365, 225, 201, 409, 368, 456, 370, 455, 214, 278, 393, 227, 68, 293, 436, 436, 62, 190, 114, 170, 480, 210, 156, 136, 220, 335, 171, 93, 113, 130, 454, 84, 377, 54, 393, 133, 390, 216, 39, 47, 400, 271, 243, 176, 346, 241, 31, 301, 157, 424, 275, 387, 60, 354, 305, 426, 442, 276, 296, 384, 132, 273, 394, 297, 271, 428, 488, 129, 37, 307, 74, 485, 237, 267, 409, 435, 71, 227, 90, 230, 66, 439, 178, 195, 449, 412, 168, 250, 332, 94, 68, 429, 81, 354, 369, 296, 173, 429, 394, 35, 449, 318, 144, 84, 49, 406, 424, 174, 90, 36, 207, 149, 26, 149, 411, 32, 202, 257, 81, 18, 37, 72, 488, 431, 353, 450, 163, 124, 435, 303, 462, 179, 206, 359, 442, 82, 131, 6, 280, 462, 284, 74, 346, 325, 52, 458, 330, 245, 172, 80, 234, 183, 116, 323, 331, 478, 485, 233, 358, 187, 217, 284, 491, 21, 231, 168, 403, 476, 236, 39, 297, 294, 341, 389, 232, 275, 384, 13, 120, 344, 489, 472 };
////	vector<int> A(arr, arr+6);
////	int arr2[5] = { 0,2,3,9,11 };
////	vector<int> B( arr2, arr2+5 );
////	solution( A, B );
////}