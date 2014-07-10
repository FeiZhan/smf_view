#pragma once
#include <iostream>
#include <string>
#include "SmfModel.h"

class Decimator : public SmfModel
{
public:
	// output stream for testing
	friend std::ostream& operator<< (std::ostream& os, const Decimator& de);
	// constructor which calls the contructor of SmfModel
	Decimator(const std::string &file = NULL) : SmfModel(file) {}
	virtual ~Decimator(void) {}
	// decimate it
	int decimate(int num, int percentage = 50);
public:
	// get quadric error and matrix list for each vertex
	bool getQuadricList(void);
	std::map<size_t, double > quadric_error_list;
	std::map<size_t, std::vector<std::vector<double> > > quadric_matrix_list;
	// vertex quadric error
	double getQuadricError(size_t vertex);
	// get vertex quadric matrix
	std::vector<std::vector<double> > getQuadricMatrix(size_t vertex);
	// get new location for vertex
	std::vector<GLfloat> getNewLocation(const std::set<std::pair<size_t, size_t> >::iterator &edge_it);
	// get matrix inverse
	std::vector<std::vector<double> > invertMatrix(const std::vector<std::vector<double> > &mat);
};
