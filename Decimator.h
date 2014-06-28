#pragma once
#include <iostream>
#include <string>
#include "SmfModel.h"

class Decimator : public SmfModel
{
public:
	// output stream for testing
	friend std::ostream& operator<< (std::ostream& os, const Decimator& de);
	Decimator(const std::string &file = NULL) : SmfModel(file) {}
	virtual ~Decimator(void) {}
	// decimate it
	int decimate(int num);
private:
	// edge quadric error
	double getEdgeQuadricError(size_t edge);
	// vertex quadric error
	double getQuadricError(size_t vertex);
	// get vertex quadrics
	std::vector<std::vector<double> > getQuadrics(size_t vertex);
	// get new location for vertex
	std::vector<GLfloat> getNewLocation(size_t edge);
	// get matrix inverse
	std::vector<std::vector<double> > invertMatrix(const std::vector<std::vector<double> > &mat);
};
