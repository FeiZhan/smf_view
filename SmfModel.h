#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <GL/glut.h>

class SmfModel
{
public:
	// output stream for testing
    friend std::ostream& operator<< (std::ostream& os, const SmfModel& dt);
	SmfModel(const std::string &file = std::string());
	// load from a file
	bool loadFile(const std::string &file);
	bool load(void);
	// save to file
	bool save(const std::string &filename);
	// display in OpenGL
	bool display(void);

	std::vector<std::vector<GLfloat> > vertex_list;
	std::vector<std::vector<size_t> > face_list;
};
