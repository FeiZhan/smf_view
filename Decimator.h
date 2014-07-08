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
private:
	// edge quadric error
	double getEdgeQuadricError(size_t edge);
	// vertex quadric error
	double getQuadricError(size_t vertex);
	// get vertex quadric matrix
	std::vector<std::vector<double> > getQuadricMatrix(size_t vertex);
	// get new location for vertex
	std::vector<GLfloat> getNewLocation(size_t edge);
	// get matrix inverse
	std::vector<std::vector<double> > invertMatrix(const std::vector<std::vector<double> > &mat);
};
