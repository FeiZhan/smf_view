#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <GL/glut.h>
#include <GL/glui.h>

class SmfModel
{
public:
    friend std::ostream& operator<<(std::ostream& os, const SmfModel& dt);
	SmfModel(const std::string &file = NULL);
	bool loadFile(const std::string &file);
	bool load(void);
	bool save(const std::string &filename);
	bool display(void);
private:
	std::vector<std::vector<GLfloat> > vertex_list;
	std::vector<std::vector<size_t> > face_list;
};
