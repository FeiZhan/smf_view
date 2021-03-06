#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <GL/glut.h>

// a model for mesh display from SMF file
class SmfModel
{
public:
	// output stream for testing
	friend std::ostream& operator<< (std::ostream& os, const SmfModel& dt);
	// constructor
	SmfModel(const std::string &file = std::string());
	virtual ~SmfModel(void) {}
	// load from a file
	bool loadFile(const std::string &file);
	// save to file
	bool save(const std::string &filename);
	// display in OpenGL
	bool display(void);
	// values for the mesh
	std::vector<std::vector<GLfloat> > vertex_list;
	std::vector<std::vector<size_t> > face_list;
	std::set<std::pair<size_t, size_t> > edge_list;
protected:
	// get edge list based on vertex list and face list
	bool getEdgeList(void);
	// get normals for each face and each vertex
	bool getNormalList(void);
	std::map<size_t, std::vector<GLfloat> > face_normals;
	std::map<size_t, std::vector<GLfloat> > vertex_normals;
	// get map of vertex - faces
	bool getFaceMap(void);
	std::map<size_t, std::set<size_t> > face_map;
};
// id of the selected radio button
static int radiogroup_item_id = 0;
