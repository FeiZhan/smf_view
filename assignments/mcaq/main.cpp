#include <iostream>
#include "MeshGui.h"
using namespace std;

int main(int argc, char *argv[])
{
	// run smf viewer
	MeshGui mg;
	mg.run(argc, argv);

	return EXIT_SUCCESS;
}
