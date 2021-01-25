
const int NMAX = 1000;

// hold all the variables that describe your object you want to simulate
class robot {
public:
	double x[3+1]; // state variable x = [x y th]
	double u[2+1]; // inputs u = [v w]
	double t;

	double radius; // assuming the robot has an approximate spherical region
	// might be useful for collisons and surface interactions -> ground

	// for drawing
	// - a variable that stores the x-file -- ie a mesh varible
	// an object member variable situation
	mesh *pmesh; // for a member variable with non-default
	// constructor then you need to have a pointe to that
	// object and init to a dynamic object

	// in this case it might be more useful to pass the name of the 
	// mesh x-file to the robot constructor rather than
	// send a mesh pointer to the constructor

	robot(double x[], double u[], double radius, char file_name[]);

//	robot(double x[], double u[], double radius, mesh *pmesh);

//	robot(char file_name[]); // the file contains information to initialize
	// all the members -- can't use a mesh pointer in this case
	// -- why can't we put a pointer in a file ?
	// -- a pointer is a relative memory address that could
	// change each time the program runs -- each time the pointer could be
	// different

//	robot(); // default good for arrays etc.

	// alternative -- perhaps more useful parameter
	// -- let's say we want just one parameter that allows
	// us to change everything
	// -> use an initialization file -> inside this file
	// would be the parameters above (x,u,radius,file_name)
	// one line at a time
	// -> make an initialization file

	~robot();

	void draw();

	// read the keyboard and move around
	void move();

	void keyboard_input();

	// simulate equations for one time step with Euler's method
	void simulate_step(double dt);

};

class Maze {
public:

	int N_wall; // the number of walls (max value of NMAX = 1000
	double xc[NMAX]; // the x center coordinate of wall i (size = NMAX)
	double yc[NMAX]; // the x center coordinate of wall i (size = NMAX)
	double zc[NMAX]; // the z center coordinate of wall i (size = NMAX)
	double theta[NMAX]; // the angle of walls from the x-axis (size = NMAX)
	double length[NMAX]; // the length of wall i (size = NMAX)
	double Rw[NMAX], Gw[NMAX], Bw[NMAX]; // the colour wall i (size = NMAX)
	double width; // the width of the walls
	double height; // the height of the walls

	Maze(char file_name[]);

	void draw();

};

