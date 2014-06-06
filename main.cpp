#include <iostream>
#include <GL/glut.h>
#include <GL/glui.h>
#include "MeshGui.h"
#include "SmfModel.h"
using namespace std;

int main(int argc, char *argv[])
{
	// run smf viewer
	MeshGui mg;
	mg.run(argc, argv);

	return EXIT_SUCCESS;
}
