#include <iostream>
#include <GL/glut.h>
#include "MeshGui.h"
#include "SmfModel.h"
using namespace std;

int main(int argc, char *argv[])
{
	// Initialize GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(800, 600);
	main_window = glutCreateWindow("MeshGUI");
	glutDisplayFunc(myGlutDisplay);
	GLUI_Master.set_glutReshapeFunc(myGlutReshape);  
	GLUI_Master.set_glutKeyboardFunc(myGlutKeyboard);
	GLUI_Master.set_glutSpecialFunc(NULL);
	GLUI_Master.set_glutMouseFunc(myGlutMouse);
	glutMotionFunc(myGlutMotion);

	MeshGui mg;
	mg.run();

	// Regular GLUT main loop
	glutMainLoop();

	return EXIT_SUCCESS;
}
