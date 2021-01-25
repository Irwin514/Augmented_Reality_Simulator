
#include <cmath>
#include <iostream>
#include <fstream>

#include <windows.h> // for keyboard input

// user defined functions

#include "timer.h"
#include "ran.h"
#include "rotation.h"
#include "3D_graphics.h"

#include "graphics.h" // graphics functions for various geometries

#include "iArray.h"

#include "robot.h"

using namespace std;

ofstream dout("dout.txt");

void robot::keyboard_input()
{
	u[1] = 0;
	u[2] = 0;

	// you could also say += here
	if ( KEY(VK_UP) ) {
		u[1] = 1;
	}

	if ( KEY(VK_DOWN) ) {
		u[1] = -1;
	}
	
	if ( KEY(VK_LEFT) ) {
		u[2] = 0.25;
	}

	if ( KEY(VK_RIGHT) ) {
		u[2] = -0.25;
	}

}

// simulate equations for one time step with Euler's method
void robot::simulate_step(double dt)
{	
	int i, N = 3;
	double xd[3+1];

	// calculate the inputs
	// 1 -- constant
	// 2 -- controller / behavioral algorithm
	// 3 -- adjust from keyboard / joystick

//	u[1] = 5.0; // us - forward speed
//	u[2] = 5.0;	// uw - turning angular velocity
		
	// calculate the derivative vector at time t
	xd[1] = u[1]*cos(x[3]);
	xd[2] = u[1]*sin(x[3]);
	xd[3] = u[2];
		
	// Euler's equation
	for(i=1;i<=N;i++) x[i] = x[i] + xd[i]*dt;

	t = t + dt; // increment time
}


robot::robot(double x[], double u[], double radius, char file_name[])
{
	this->x[1] = x[1];
	this->x[2] = x[2];
	this->x[3] = x[3];

	this->u[1] = u[1];
	this->u[2] = u[2];

	t = 0.0;

	this->radius = radius;

	pmesh = new mesh(file_name);

	if(pmesh == NULL) {
		// need to use dout since cout doesn't work
		dout << "\nerror in robot::robot(...)"; 
		return;
	}
	
	pmesh->Scale = 0.15;

}

robot::~robot()
{
	if( pmesh != NULL ) {
		delete pmesh;
		pmesh = NULL;
	} else {
		dout << "\nerror in robot::~robot()";
		return;
	}
}


void robot::draw() 
{
	double Px,Py,Pz,yaw,pitch,roll;

	// x = [x y th]
	Px = x[1];
	Py = x[2];
	Pz = 0.0;

	yaw = x[3]; // yaw is rotation around the z-axis
	pitch = 0.0;
	roll = 0.0;

	pmesh->draw(Px,Py,Pz,yaw,pitch,roll);

}

void robot::move()
{
	double ds = 0.1; // how much to move forward with each input
	double dth = 0.1;

	// read the keyboard

	// x = [x y th]
	// move forward in the direction th from the point x,y
	if ( KEY(VK_UP) ) {
		x[1] += ds*cos(x[3]); // move in theta direction
		x[2] += ds*sin(x[3]);
	}

	if ( KEY(VK_DOWN) ) {
		x[1] -= ds*cos(x[3]); // move in theta direction
		x[2] -= ds*sin(x[3]);
	}
	
	if ( KEY(VK_LEFT) ) {
		x[3] += dth;
	}

	if ( KEY(VK_RIGHT) ) {
		x[3] -= dth;
	}
}


Maze::Maze(char file_name[])
{
	int i;
	ifstream fin;

	fin.open(file_name);

	if(!fin) {
		// note can't use cout in a graphics program
		// --> could use a file output stream such as dout here 
		return;
	}

	fin >> N_wall;
	fin >> width;
	fin >> height;

	for(i=1;i<=N_wall;i++) {
		fin >> xc[i];
		fin >> yc[i];
		fin >> zc[i];
		fin >> theta[i];
		fin >> length[i];
		fin >> Rw[i];
		fin >> Gw[i];
		fin >> Bw[i];
	}

	fin.close();
}


void Maze::draw()
{
	int i;
	double Px,Py,Pz,yaw,pitch,roll,Lx,Ly,Lz,R,G,B;

	for(i=1;i<=N_wall;i++) {
		Px = xc[i];
		Py = yc[i];
		Pz = zc[i];

		yaw = theta[i];
		pitch = 0.0;
		roll = 0.0;

		Lx = length[i];
		Ly = width;
		Lz = height;

		R = Rw[i];
		G = Gw[i];
		B = Bw[i];

		draw_box(Px,Py,Pz,yaw,pitch,roll,Lx,Ly,Lz,R,G,B,1);
	}
}
