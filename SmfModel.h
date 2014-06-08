#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <GL/glut.h>

// a model for mesh display from SMF file
class SmfModel
{
public:
	// output stream for testing
	friend std::ostream& operator<< (std::ostream& os, const SmfModel& dt);
	// constructor
	SmfModel(const std::string &file = std::string());
	// load from a file
	bool loadFile(const std::string &file);
	// save to file
	bool save(const std::string &filename);
	// display in OpenGL
	bool display(void);

	std::vector<std::vector<GLfloat> > vertex_list;
	std::vector<std::vector<size_t> > face_list;
	std::set<std::pair<size_t, size_t> > edge_list;
private:
	// get edge list based on vertex list and face list
	bool getEdgeList(void);
};
