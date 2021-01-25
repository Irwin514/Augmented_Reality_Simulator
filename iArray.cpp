
// class for multidimensional dynamic array (1D to 2D) of ints

#include <iostream>

#include "iArray.h"

using namespace std;

// constructors for 1D, 2D arrays
iArray::iArray(int m)
{
	int j;
	
	M = m;
	N = 0;

	type = 1; // 1D array
	
	Size = M; // size of 1D array
	
	p = new int [Size];

	if( p == NULL ) {
		cout << "\nallocation error in iArray::iArray(m)";
		return;
	}
	
	// initialize elements to zero
	for(j=0;j<M;j++) {
		e(j) = 0;
	}	
	
}

iArray::iArray(int n, int m)
{
	int i,j;
	
	M = m;
	N = n;

	type = 2; // 2D array	
	
	Size = N*M; // size of 1D array
	
	p = new int [Size];

	if( p == NULL ) {
		cout << "\nallocation error in iArray::iArray(n,m)";
		return;
	}
	
	// initialize elements to zero	
	for(i=0;i<N;i++) {
		for(j=0;j<M;j++) {
			e(i,j) = 0;
		}
	}	
		
}


// destructor
iArray::~iArray()
{
	// safe delete
	if(p != NULL) {
		delete p;
		p = NULL;
	} else {
		cout << "\nerror: NULL pointer in iArray::~iArray()";
	}
	
}

// access functions
int & iArray::e(int j)
{
	if( (j < 0) || (j >= M) ) {
		cout << "\nerror: out of range in iArray::e(j), j = " << j;

		return p[0]; // first element in Array
	}

	// return reference to array element
	return p[j];
}

int & iArray::e(int i, int j)
{
	if( (j < 0) || (j >= M) || (i < 0) || (i >= N) ) {
		cout << "\nerror: out of range in iArray::e(i,j)";
		cout << "\ni = " << i << " , j = " << j; 
		return p[0]; // first element in Array
	}

	// return reference to array element
	return p[ M*i + j ];	
}


// print array elements
void iArray::print()
{
	int i,j;
	
	if( type == 1 ) { // 1D array
	
		for(j=0;j<Size;j++) {
			cout << e(j) << "\t";
		}
	
	} else if ( type == 2 ) { // 2D array

		for(i=0;i<N;i++) {
			for(j=0;j<M;j++) {
				cout << e(i,j) << "\t";
			}
			cout << "\n";
		}
		
	} else { // error
		cout << "\nerror in Array::print() : unknown array type";
	} // end else

	cout << "\n";

}


// pointer to 1D array for row i (works for 2D arrays)
int * iArray::row(int i)
{
	if( (i < 0) || (i >= N) ) {
		cout << "\nerror in Array::row(i) : out of bounds, i = " << i;
		return p; // pointer to first row in Array
	}
	
	// return pointer to first element of row i (ie for j = 0)
	return ( p + M*i );
}

