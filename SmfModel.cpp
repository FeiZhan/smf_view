#include <cmath>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <GL/glui.h>
#include "SmfModel.h"

// output stream for testing
std::ostream& operator<< (std::ostream& os, const SmfModel& model)
{
	// output vertices
	for (std::vector<std::vector<GLfloat> >::const_iterator it = model.vertex_list.begin(); it != model.vertex_list.end(); ++ it)
	{
		os << "v ";
		for (std::vector<GLfloat>::const_iterator it1 = it->begin(); it1 != it->end(); ++ it1)
		{
			os << std::fixed << *it1 << " ";
		}
		os << std::endl;
	}
	// output faces
	for (std::vector<std::vector<size_t> >::const_iterator it = model.face_list.begin(); it != model.face_list.end(); ++ it)
	{
		os << "f ";
		for (std::vector<size_t>::const_iterator it1 = it->begin(); it1 != it->end(); ++ it1)
		{
			os << std::fixed << *it1 << " ";
		}
		os << std::endl;
	}
	// output edges
	for (std::set<std::pair<size_t, size_t> >::const_iterator it = model.edge_list.begin(); it != model.edge_list.end(); ++ it)
	{
		os << "e " << it->first << " " << it->second << std::endl;
	}
	return os;
}
// constructor
SmfModel::SmfModel(const std::string &file)
{
	// if no file specified
	if (file.length() == 0)
	{
		return;
	}
	// load from file
	this->loadFile(file);
}
// load from a file
bool SmfModel::loadFile(const std::string &file)
{
	std::ifstream infile(file.c_str());
	if (infile.good())
	{
		vertex_list.clear();
		face_list.clear();
	}
	else
	{
		// fail to load
		return false;
	}
	std::string line;
	// load line by line
	while (std::getline(infile, line))
	{
		if (line.size() < 1)
		{
			continue;
		}
		std::istringstream iss(line.substr(1));
		std::vector<GLfloat> vertex(3, 0.0);
		std::vector<size_t> face(3, 0);
		// switch by the leading character
		switch (line[0])
		{
		case 'v': // load vertices
			iss >> vertex[0] >> vertex[1] >> vertex[2];
			vertex_list.push_back(vertex);
			break;
		case 'f': // load faces
			iss >> face[0] >> face[1] >> face[2];
			for (size_t i = 0; i < 3; ++ i)
			{
				-- face[i];
			}
			face_list.push_back(face);
			break;
		case '#':
		default:
			break;
		}
	}
	infile.close();
	std::cout << "loadFile " << file << std::endl;
	// parse edge list and face map
	return getEdgeList() && getNormalList() && getFaceMap();
}
// save to file
bool SmfModel::save(const std::string &filename)
{
	std::fstream file;
	// will not create file
	file.open(filename.c_str(), std::ios_base::out | std::ios_base::in);
	// test if file exists
	if (file.is_open())
	{
		std::cerr << "file exists" << std::endl;
		file.close();
	}
	else
	{
		file.clear();
		// will create if necessary
		file.open(filename.c_str(), std::ios_base::out);
		// save vertices
		for (std::vector<std::vector<GLfloat> >::iterator it = vertex_list.begin(); it != vertex_list.end(); ++ it)
		{
			file << "v";
			for (std::vector<GLfloat>::iterator it1 = it->begin(); it1 != it->end(); ++ it1)
			{
				file << " " << *it1;
			}
			file << std::endl;
		}
		// save faces
		for (std::vector<std::vector<size_t> >::iterator it = face_list.begin(); it != face_list.end(); ++ it)
		{
			file << "f";
			for (std::vector<size_t>::iterator it1 = it->begin(); it1 != it->end(); ++ it1)
			{
				// offset by one
				file << " " << (*it1) + 1;
			}
			file << std::endl;
		}
	}
	file.close();
	std::cout << "save file " << filename << std::endl;
	return true;
}
// display the model
bool SmfModel::display(void)
{
	/*if (0 == face_list.size())
	{
		return false;
	}
	size_t vertex_num = face_list.size() * face_list[0].size() * 3;
	GLfloat *vertex_array = new GLfloat[vertex_num];
	for (size_t i = 0; i < face_list.size(); ++ i)
	{
		for (size_t j = 0; j < face_list[0].size(); ++ j)
		{
			vertex_array[(i * face_list[0].size() + j) * 3 + 0] = vertex_list[ face_list[i][j] - 1 ][0];
			vertex_array[(i * face_list[0].size() + j) * 3 + 1] = vertex_list[ face_list[i][j] - 1 ][1];
			vertex_array[(i * face_list[0].size() + j) * 3 + 2] = vertex_list[ face_list[i][j] - 1 ][2];
		}
	}
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertex_array);
	// draw triangles from array
	glDrawArrays(GL_TRIANGLES, 0, vertex_num);
	glDisableClientState(GL_VERTEX_ARRAY);*/

	// draw triangles
	glBegin(GL_TRIANGLES);
	for (size_t i = 0; i < face_list.size(); ++ i)
	{
		// face removed
		if (face_list[i].size() < 3 || vertex_list[ face_list[i][0] ].size() < 3 || vertex_list[ face_list[i][1] ].size() < 3 || vertex_list[ face_list[i][2] ].size() < 3)
		{
			continue;
		}
		for (size_t j = 0; j < face_list[i].size(); ++ j)
		{
			// vertex removed
			if (vertex_list[ face_list[i][j] ].size() < 3)
			{
				continue;
			}
			std::vector<GLfloat> normal;
			switch (radiogroup_item_id)
			{
			case 1: // smooth shaded - use face normal
				normal = face_normals[i];
				break;
			default: // flat shaded or other - use vertex normal
				normal = vertex_normals[face_list[i][j]];
				break;
			}
			glNormal3f(normal[0], normal[1], normal[2]);
			// draw triangles based on faces and vertices
			glVertex3f(vertex_list[ face_list[i][j] ][0], vertex_list[ face_list[i][j] ][1], vertex_list[ face_list[i][j] ][2]);
		}
	}
	glEnd();
	return true;
}
// get edge list based on vertex list and face list
bool SmfModel::getEdgeList(void)
{
	edge_list.clear();
	// for each face
	for (std::vector<std::vector<size_t> >::iterator it = face_list.begin(); it != face_list.end(); ++ it)
	{
		std::vector<size_t>::iterator it1 = it->begin();
		// start from the second item
		for (++ it1; it1 != it->end(); ++ it1)
		{
			// remove duplicate edges
			if (*(it1 - 1) < *it1)
			{
				// find edge with the previous item
				edge_list.insert(std::make_pair(*(it1 - 1), *it1));
			}
		}
		if (it->back() < it->front())
		{
			// find edge with the last and the first items
			edge_list.insert(std::make_pair(it->back(), it->front()));
		}
	}
	return true;
}
// get normals for each face and each vertex
bool SmfModel::getNormalList(void)
{
	face_normals.clear();
	vertex_normals.clear();
	// for each face
	for (std::vector<std::vector<size_t> >::iterator it = face_list.begin(); it != face_list.end(); ++ it)
	{
		std::vector<GLfloat> temp0(3), temp1(3);
		std::vector<GLfloat> normal(3);
		// compute the face normal
		for (size_t j = 0; j < 3; ++ j)
		{
			temp0[j] = vertex_list[ (*it)[1] ][j] - vertex_list[ (*it)[0] ][j];
			temp1[j] = vertex_list[ (*it)[2] ][j] - vertex_list[ (*it)[1] ][j];
		}
		normal[0] = temp0[1] * temp1[2] - temp0[2] * temp1[1];
		normal[1] = temp1[0] * temp0[2] - temp1[2] * temp0[0];
		normal[2] = temp0[0] * temp1[1] - temp0[1] * temp1[0];
		// normalize it to one
		GLfloat length = std::sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
		for (size_t j = 0; j < 3; ++ j)
		{
			normal[j] /= length;
		}
		face_normals.insert(std::make_pair(it - face_list.begin(), normal));
		// compute the vertex normal
		for (size_t j = 0; j < 3; ++ j)
		{
			if ( vertex_normals.find((*it)[j]) == vertex_normals.end() )
			{
				// not found
				vertex_normals[(*it)[j]] = normal;
			}
			else
			{
				// sum up all face normals with the same vertex
				for (size_t k = 0; k < 3; ++ k)
				{
					vertex_normals[(*it)[j]][k] += normal[k];
				}
			}
		}
	}
	// for vertex normals
	for (std::map<size_t, std::vector<GLfloat> >::iterator it = vertex_normals.begin(); it != vertex_normals.end(); ++ it)
	{
		// normalize it to one
		GLfloat length = std::sqrt((it->second)[0] * (it->second)[0] + (it->second)[1] * (it->second)[1] + (it->second)[2] * (it->second)[2]);
		for (size_t k = 0; k < 3; ++ k)
		{
			(it->second)[k] /= length;
		}
	}
	return true;
}
// get map of vertex - faces
bool SmfModel::getFaceMap(void)
{
	face_map.clear();
	for (size_t i = 0; i < face_list.size(); ++ i)
	{
		for (size_t j = 0; j < face_list[i].size(); ++ j)
		{
			face_map[j].insert(i);
		}
	}
	return true;
}



























