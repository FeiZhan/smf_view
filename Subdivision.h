#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include "SmfModel.h"

class Subdivision
{
public:
	enum Type
	{
		Butterfly,
		Loop
	};
	// output stream for testing
	friend std::ostream& operator<< (std::ostream& os, const Subdivision& sd);
	Subdivision(const std::string &file = NULL);
	bool load(const std::string &file);
	bool display(void);
	bool subdivide(enum Type type = Butterfly, unsigned level = 1);
private:
	bool butterfly(void);
	bool loop(void);
	SmfModel model;
	std::map<size_t, std::set<size_t> > adjacent_vertices;
	std::vector<std::vector<GLfloat> > new_vertices;
	std::vector<std::vector<size_t> > new_faces;
};
