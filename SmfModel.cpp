#include <fstream>
#include <sstream>
#include <iomanip>
#include "SmfModel.h"

std::ostream& operator<<(std::ostream& os, const SmfModel& model)
{
	for (std::vector<std::vector<GLfloat> >::const_iterator it = model.vertex_list.begin(); it != model.vertex_list.end(); ++ it)
	{
		os << "v ";
		for (std::vector<GLfloat>::const_iterator it1 = it->begin(); it1 != it->end(); ++ it1)
		{
			os << std::fixed << *it1 << " ";
		}
		os << std::endl;
	}
	for (std::vector<std::vector<size_t> >::const_iterator it = model.face_list.begin(); it != model.face_list.end(); ++ it)
	{
		os << "f ";
		for (std::vector<size_t>::const_iterator it1 = it->begin(); it1 != it->end(); ++ it1)
		{
			os << std::fixed << *it1 << " ";
		}
		os << std::endl;
	}
    return os;
}
SmfModel::SmfModel(const std::string &file)
{
	this->loadFile(file);
}
bool SmfModel::loadFile(const std::string &file)
{
	std::ifstream infile(file.c_str());
	if (infile.good())
	{
		vertex_list.clear();
		face_list.clear();
	}
	std::string line;
	while (std::getline(infile, line))
	{
		if (line.size() < 1)
		{
			continue;
		}
		std::istringstream iss(line.substr(1));
		std::vector<GLfloat> vertex(3, 0.0);
		std::vector<size_t> face(3, 0);
		switch (line[0])
		{
		case 'v':
			iss >> vertex[0] >> vertex[1] >> vertex[2];
			vertex_list.push_back(vertex);
			break;
		case 'f':
			iss >> face[0] >> face[1] >> face[2];
			face_list.push_back(face);
			break;
		case '#':
		default:
			break;
		}
	}
	infile.close();
	return true;
}
bool SmfModel::save(const std::string &filename)
{
	std::fstream file;
	file.open(filename.c_str(), std::ios_base::out | std::ios_base::in);  // will not create file
	if (file.is_open())
	{
		std::cerr << "file exists" << std::endl;
		file.close();
	}
	else
	{
		file.clear();
		file.open(filename.c_str(), std::ios_base::out);  // will create if necessary
		for (std::vector<std::vector<GLfloat> >::iterator it = vertex_list.begin(); it != vertex_list.end(); ++ it)
		{
			file << "v";
			for (std::vector<GLfloat>::iterator it1 = it->begin(); it1 != it->end(); ++ it1)
			{
				file << " " << *it1;
			}
			file << std::endl;
		}
		for (std::vector<std::vector<size_t> >::iterator it = face_list.begin(); it != face_list.end(); ++ it)
		{
			file << "f";
			for (std::vector<size_t>::iterator it1 = it->begin(); it1 != it->end(); ++ it1)
			{
				file << " " << *it1;
			}
			file << std::endl;
		}
	}
	file.close();
}
bool SmfModel::display(void)
{
	if (0 == face_list.size())
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
	glDrawArrays(GL_TRIANGLES, 0, vertex_num);
	glDisableClientState(GL_VERTEX_ARRAY);
}
