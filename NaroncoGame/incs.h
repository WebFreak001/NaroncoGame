#ifndef incs_h
#define incs_h
#define WIN32_LEAN_AND_MEAN

enum Keys {
	VK_0 = 48,
	VK_1,
	VK_2,
	VK_3,
	VK_4,
	VK_5,
	VK_6,
	VK_7,
	VK_8,
	VK_9,
	VK_A = 65,
	VK_B,
	VK_C,
	VK_D,
	VK_E,
	VK_F,
	VK_G,
	VK_H,
	VK_I,
	VK_J,
	VK_K,
	VK_L,
	VK_M,
	VK_N,
	VK_O,
	VK_P,
	VK_Q,
	VK_R,
	VK_S,
	VK_T,
	VK_U,
	VK_V,
	VK_W,
	VK_X,
	VK_Y,
	VK_Z
};

#pragma comment(lib, "SOIL.lib")

#include <windows.h>
#include <stdlib.h>
#include <fstream>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glut.h>
#include <SOIL.h>
#include <mmsystem.h>

using namespace std;
#endif