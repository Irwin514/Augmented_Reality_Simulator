
#include <cmath>
#include <iostream>
#include <fstream>
#include <regex>
#include <typeinfo>

#include <windows.h> // for keyboard input

// Dr. Gordon's Libraries
#include "timer.h"
#include "ran.h"
#include "rotation.h"
#include "3D_graphics.h"

#include "graphics.h" // graphics functions for various geometries
#include "iArray.h"
#include "robot.h"

//Serial Libraries
#include <cstdio>
#include <cstdlib>
#include "serial_com.h"
#include <iostream>
#include <strstream> // for string streams

const double PI = 4*atan(1.0);

using namespace std;

void simulate_my_project();

void simulate_my_project()
{
	int i;
	static double Px,Py,Pz,roll,pitch,yaw;
	string tempy, tempp, tempr;
	static double dth = 0.001;
	static int init = 0; // initialization flag

	static double t; // clock time from t0
	static double t_clock; // clock time
	static double t_clock_p; // previous clock time
	static double t0; // initial clock time

	//local coordinates variables
	static double fov = 3.14159 / 4; // 45 deg;
	static double eye_point[3 + 1] = { 0.0 };
	static double lookat_point[3 + 1] = { 0.0 };
	static double up_dir[3 + 1] = { 0.0 };

	//Global Coordinates variables
	static double eye_point_g[3 + 1] = { 0.0 };
	static double lookat_point_g[3 + 1] = { 0.0 };
	static double up_dir_g[3 + 1] = { 0.0 };

	double R1[3 + 1][3 + 1], T1[3 + 1]; //Used to translate from local to global coordinates

	//Parameters for Serial Commuication
	static HANDLE h1;
	static const int NMAX = 20000; //Arduino can only support  64 characters in its serial buffer by default
	static char buffer[NMAX];  //Char array for the serial communication
	static int n;
	static char ch;
	static char chars[50];
	static string line("");
	static ostrstream sout(buffer, NMAX);
	static bool loaded = false;

	//output file
	static ofstream file("sreads.txt");


	//Environment Mesh
	static mesh surface("track1.x");


	static double v=10;

	//int n = 1;

	// initalization section ///////////////////
	if(!init) {

		// initial position in global coordinates
		Px = 0; Py = 0; Pz = 30;
		//roll = 0; pitch = 0; yaw = 0;
		//Clock Time parameters
		t0 = high_resolution_time(); // initial clock time (s)
		t_clock = t_clock_p = 0.0;

		//Serial Comms Initialization
		open_serial("\\\\.\\COM7", h1); // COM9 for my 3D printer
		Sleep(1); // need to wait for data to come
		//show_serial(h1); //Get The Welcome message from printer

		file << "Here are all the outputs of this program!" << endl;

		init = 1;
	} // end of initialization section
	

	t = high_resolution_time() - t0;

	// the position of your eye in local coordinates
	eye_point[1] = 0; // x
	eye_point[2] = 0; // y
	eye_point[3] = 0; // z
	// the position you are looking at in global coord
	lookat_point[1] = 1; // x
	lookat_point[2] = 0; // y
	lookat_point[3] = 0; // z
	//up direction. Note: the rest of the array is set to zero on top
	up_dir[3] = 1;

	// convert local to global coord with Pg = T1 + R1*pl
	// note T1 = 0 for up_dir since it's just a direction vector not a point
	T1[1] = Px; T1[2] = Py; T1[3] = Pz;

	// convert euler angles to rotation matrix (from rotation.h/cpp)
	euler_to_rotation(yaw, pitch, roll, R1);

	// multiply a matrix times a vector, b = A*x (from rotation.h/cpp)
	// calculate b = R1*pl
	multiply_Ax(R1, eye_point, eye_point_g);
	multiply_Ax(R1, lookat_point, lookat_point_g);
	multiply_Ax(R1, up_dir, up_dir_g);

	// add T1 to R1*pl for eye_point_g and lookat_point_g
	// ie Pg = T1 + R1*pl
	for (i = 1; i <= 3; i++) eye_point_g[i] += T1[i];
	for (i = 1; i <= 3; i++) lookat_point_g[i] += T1[i];

	//Change the orientation of the view to simulate the FPV 
	set_view(eye_point_g,lookat_point_g,up_dir_g, fov);

	// draw the flat surface
	surface.draw(0.0,0.0,0.0,0.0,0.0,0.0);


	// adjust yaw and pitch with keyboard
	/*if (KEY('W')) pitch -= dth;
	if (KEY('S')) pitch += dth;
	if (KEY('A')) yaw += dth;
	if (KEY('D')) yaw -= dth;
	if (KEY('Q')) roll += dth;
	if (KEY('E')) roll -= dth;*/

	// adjust forward increment with keyboard
	// in the local x direction
	if (KEY(VK_NUMPAD8)) Px += 0.1;
	if (KEY(VK_NUMPAD2)) Px += -0.1;
	if (KEY(VK_NUMPAD4)) Py += 0.1;
	if (KEY(VK_NUMPAD6)) Py += -0.1;
	if (KEY(VK_NUMPAD1)) Pz += 0.1;
	if (KEY(VK_NUMPAD3)) Pz += -0.1;


	static int l = 0;
	if (serial_available(h1) > 0)
	{
		serial_recv_char(ch, h1);
		chars[l] = ch;
		l++; l %= 50;
		if (ch == '\n') 
		{
			for (int j = 0; j < l; j++)
			{
				line += chars[j];
				chars[j] = '\0';
			}
			
			//extracting data
			regex re("(-?[[:digit:]]+.[[:digit:]]+)	(-?[[:digit:]]+.[[:digit:]]+)	(-?[[:digit:]]+.[[:digit:]]+)", std::regex::ECMAScript);
			smatch m;
			regex_search(line, m, re, regex_constants::match_default);
			if (m.size()>2)
			{
				tempy = (string)m[1];
				tempp = (string)m[2];
				tempr = (string)m[3];
				yaw = PI*atof(tempy.c_str())/180;
				pitch = PI*atof(tempp.c_str())/180;
				roll = PI*atof(tempr.c_str())/180;
				file << yaw << '	' << pitch << '	' << roll<<endl;
			}

			line = "";
			l = 0;

			//file.seekp(0); //using that to verify what is line made of
			
		}
		
		/*serial_recv(buffer, serial_available(h1), h1);
		file << buffer;*/

		
		//Sleep(100); // wait for more characters
	}

	if (t > 12 && !loaded)
	{
		sout << 'G';
		n = strlen(buffer);
		serial_send(buffer, n, h1);
		Sleep(2);
		loaded = true;
	}



}

