#include <iostream>
#include <GL/glut.h>
#include "SmfModel.h"

enum SHADING
{
	FLAT_SHADING,
	SMOOTH_SHADING,
	WIREFRAME,
	EDGE_SHADING,
	POINT_SHADING
};
enum MATERIAL_TYPE
{
	BRASS,
	RED_PLASTIC,
	EMERALD,
	SLATE
} MaterialType;
enum MATERIAL_DISPLAY
{
	TORUS_MATERIAL = 1,
	TEAPOT_MATERIAL = 2,
	ICO_MATERIAL = 3
} MaterialDisplayList;
enum LIGHT_VALUE
{
	LIGHT_OFF,
	LIGHT_RED,
	LIGHT_WHITE,
	LIGHT_GREEN
} LightValues;
GLfloat red_light[] = {1.0, 0.0, 0.0, 1.0},
green_light[] = {0.0, 1.0, 0.0, 1.0},
white_light[] = {1.0, 1.0, 1.0, 1.0};
GLfloat left_light_position[] = {-1.0, 0.0, 1.0, 0.0},
right_light_position[] = {1.0, 0.0, 1.0, 0.0};
GLfloat brass_ambient[] = {0.33, 0.22, 0.03, 1.0},
brass_diffuse[] = {0.78, 0.57, 0.11, 1.0},
brass_specular[] = {0.99, 0.91, 0.81, 1.0},
brass_shininess = 27.8;
GLfloat red_plastic_ambient[] = {0.0, 0.0, 0.0},
red_plastic_diffuse[] = {0.5, 0.0, 0.0},
red_plastic_specular[] = {0.7, 0.6, 0.6},
red_plastic_shininess = 32.0;
GLfloat emerald_ambient[] = {0.0215, 0.1745, 0.0215},
emerald_diffuse[] = {0.07568, 0.61424, 0.07568},
emerald_specular[] = {0.633, 0.727811, 0.633},
emerald_shininess = 76.8;
GLfloat slate_ambient[] = {0.02, 0.02, 0.02},
slate_diffuse[] = {0.02, 0.01, 0.01},
slate_specular[] = {0.4, 0.4, 0.4},
slate_shininess = .78125;

int shade_model = GL_SMOOTH;
char *left_light, *right_light;
char *ico_material, *teapot_material, *torus_material;

void test(void)
{
	SmfModel m("smf/eight.smf");
	//std::cout << m << std::endl;
	m.display();
}

void displayTorus(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
	enum SHADING shading_mode = WIREFRAME;
	switch (shading_mode)
	{
	case FLAT_SHADING:
		glShadeModel(GL_FLAT);
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		break;
	case SMOOTH_SHADING:
		glShadeModel(GL_SMOOTH);
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		break;
	case EDGE_SHADING:
		glShadeModel(GL_FLAT);
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL | GL_LINE );
		break;
	case POINT_SHADING:
		glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );
		break;
	case WIREFRAME:
	default:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	}

    glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
    // clear the identity matrix.
    glLoadIdentity();
    // traslate the draw by z = -4.0
    // Note this when you decrease z like -8.0 the drawing will looks far , or smaller.
    glTranslatef(0.0,0.0,-4.5);
    // Red color used to draw.
    glColor3f(0.8, 0.2, 0.1); 
    
	GLfloat xRotated=33;
	GLfloat yRotated=40;
	GLfloat zRotated = 30.0;
    // changing in transformation matrix.
    // rotation about X axis
    /*glRotatef(xRotated,1.0,0.0,0.0);
    // rotation about Y axis
    glRotatef(yRotated,0.0,1.0,0.0);
    // rotation about Z axis
    glRotatef(zRotated,0.0,0.0,1.0);
    // scaling transfomation 
    glScalef(1.0,1.0,1.0);*/

	GLdouble innerRaidus=0.5;
	GLdouble outterRaidus=1;
	GLint sides = 50;
	GLint rings = 50;
    //glutSolidTorus(innerRaidus,outterRaidus,sides,rings);
	test();
	
    glFlush();        
    // sawp buffers called because we are using double buffering 
	glutSwapBuffers();
}

void initMesh(void)
{
	GLfloat light_ambient[] =
  {0.2, 0.2, 0.2, 1.0};
  GLfloat light_diffuse[] =
  {1.0, 1.0, 1.0, 1.0};
  GLfloat light_specular[] =
  {1.0, 1.0, 1.0, 1.0};
  GLfloat light_position[] =
  {1.0, 1.0, 2.0, 0.0};

  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
}
void displayMesh(void)
{
	displayTorus();
}
void reshapeMesh(int x, int y)
{
    if (y == 0 || x == 0) return;  //Nothing is visible then, so return
    //Set a new projection matrix
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    //Angle of view:40 degrees
    //Near clipping plane distance: 0.5
    //Far clipping plane distance: 20.0
     
    gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 20.0);
 
    glViewport(0, 0, x, y);  //Use the whole window for rendering
}
void idleMesh(void)
{
}

int main(int argc, char *argv[])
{
	glutInitWindowSize(800, 600);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("MeshGUI");
	initMesh();
	glutDisplayFunc(displayMesh);
	glutReshapeFunc(reshapeMesh);
	glutIdleFunc(idleMesh);

	glutMainLoop();

	return 0;
}
