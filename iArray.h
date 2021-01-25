
// class for multidimensional dynamic array (1D to 2D) of ints

class iArray {

	int *p; // dynamic 1D array storing array elements
	
	int Size; // size of dynamic 1D array p
	
public:

	int type; // 1 - 1D, 2 - 2D
	
	int M; // number of columns
	int N; // number of rows
	
	// constructors for 1D, 2D, and 3D arrays
	iArray(int m);
	iArray(int n, int m);
	
	// destructor
	~iArray();

	// access functions
	int & e(int j);
	int & e(int i, int j);

	// pointer to 1D array for row i (works for 2D arrays)
	int * row(int i);
	
	// print array elements
	void print();
	
};

