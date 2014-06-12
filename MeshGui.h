#pragma once
#include <iostream>
#include <GL/glut.h>
#include <GL/glui.h>
#include "SmfModel.h"
#include "Subdivision.h"

// a GUI for mesh displaying
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
	
	// instance of SMF model
	static SmfModel smf_model;
	// instance of subdivision model
	static Subdivision subd;

	// shared variables between main programs and control callbacks
	static int light0_enabled;
	static int light1_enabled ;
	static float light0_intensity;
	static float light1_intensity;
	static float xy_aspect;
	static float scale;
	static char filename[];
	static char filetext[sizeof(GLUI_String)];
	static int show_text;
	static const char *string_list[];
	static int curr_string;
	static GLUI_Spinner *light0_spinner, *light1_spinner;

	static int main_window;
	static float mesh_rotate[16];
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
