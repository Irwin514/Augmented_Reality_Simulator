
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

// 3D graphics window size
int WIDTH_MIN = 0;
int HEIGHT_MIN = 0;
int WIDTH_MAX = 800; // increase this to increase the window width
int HEIGHT_MAX = 600; // increase this to increase the window height

// background colour for the scene
float BACK_R = 0.0f; // red colour component (0 to 1)
float BACK_G = 0.0f; // green colour component (0 to 1)
float BACK_B = 0.5f; // blue colour component (0 to 1)

// default min and max viewing distances.
// objects closer than VMIN and farther than VMAX are not drawn (ie cannot be seen).
// note the ratio of VMAX/VMIN should be less than 60,000 for most graphics cards.
double VMIN = 0.1; // units of m (or whatever units you draw your object in)
double VMAX = 15000.0; // units of m

// directional light #0 (the default light) magnitude and direction
double LIGHT0_R = 0.8; // red (0 to 1)
double LIGHT0_G = 0.8; // green (0 to 1)
double LIGHT0_B = 0.8; // blue (0 to 1)
double LIGHT0_X = -1.0; // x direction
double LIGHT0_Y = -1.0; // y direction
double LIGHT0_Z = -1.0; // z direction
// (-1,-1,-1) -> towards the origin along the default viewing direction

int LIGHT0_SWITCH = 1; // 1 - on, 0 - off

// ambient light level
float AMBIENT_R = 0.7; // red (0 to 1)
float AMBIENT_G = 0.7; // green (0 to 1)
float AMBIENT_B = 0.7; // blue (0 to 1)

const double PI = 4*atan(1.0);

using namespace std;

void simulate_my_project();

void draw_3D_graphics()
{
	simulate_my_project();
}

