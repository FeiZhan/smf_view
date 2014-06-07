#pragma once

#include <iostream>
#include <string>
#include "SmfModel.h"
#include "Subdivision.h"

class MeshGui
{
public:
	MeshGui(void);
	virtual ~MeshGui(void) {};
	// main entrance
	int run(int argc, char *argv[]);
private:
	// initialize GLUT
	int initGlut(int argc, char *argv[]);
	// initialize GLUI
	int initGlui(void);
	// initialize GL
	int initGl(void);
	// callbacks to GLUT
	static void display(void);
	static void reshape(int x, int y);
	static void keyboard(unsigned char Key, int x, int y);
	static void mouse(int button, int button_state, int x, int y);
	static void motion(int x, int y);
	static void myGlutMenu(int value);
	static void idle(void);
	// GLUI control callback
	static void control_cb( int control );
	
	static SmfModel smf_model;
	static Subdivision subd;

	// shared variables
	static float xy_aspect;
	static int segments;
	static float scale;
	static int light0_enabled;
	static int light1_enabled ;
	static float light0_intensity;
	static float light1_intensity;
	static int radiogroup_item_id;
	static char filename[];
	static char filetext[sizeof(GLUI_String)];
	static int show_text;
	static const char *string_list[];
	static int curr_string;
	static GLUI_Spinner *light0_spinner, *light1_spinner;

	static int main_window;
	static float sphere_rotate[16];
	static float torus_rotate[16];
	static float view_rotate[16];
	static float obj_pos[];

	static GLfloat light0_ambient[];
	static GLfloat light0_diffuse[];
	static GLfloat light0_position[];
	static GLfloat light1_ambient[];
	static GLfloat light1_diffuse[];
	static GLfloat light1_position[];
	static GLfloat lights_rotation[16];
};
