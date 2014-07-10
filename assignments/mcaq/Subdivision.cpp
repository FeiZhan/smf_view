#include "Subdivision.h"

std::ostream& operator<< (std::ostream& os, const Subdivision& sd)
{
	os << "new vertices " << sd.new_vertices.size() << " new faces " << sd.new_faces.size() << std::endl;
	for (std::vector<std::vector<GLfloat> >::const_iterator it = sd.new_vertices.begin(); it != sd.new_vertices.end(); ++ it)
	{
		//os << it << ":";
		for (std::vector<GLfloat>::const_iterator it1 = it->begin(); it1 != it->end(); ++ it1)
		{
			os << " " << *it1;
		}
		os << std::endl;
	}
	return os;
}
Subdivision::Subdivision(const std::string &file)
{
	this->load(file);
}

bool Subdivision::load(const std::string &file)
{
	return this->model.loadFile(file);
}
bool Subdivision::display(void)
{
	return this->model.display();
}
bool Subdivision::subdivide(enum Subdivision::Type type, unsigned level)
{
	if (0 == level)
	{
		return false;
	}
	else if (level > 1)
	{
		this->subdivide(type, level - 1);
	}
	switch (type)
	{
	case Butterfly:
		return this->butterfly();
		break;
	case Loop:
		return this->loop();
		break;
	default:
		return false;
		break;
	}
	return true;
}
bool Subdivision::butterfly(void)
{
	adjacent_vertices.clear();
	for (std::vector<std::vector<size_t> >::iterator it = this->model.face_list.begin(); it != this->model.face_list.end(); ++ it)
	{
		for (std::vector<size_t>::iterator it1 = it->begin(); it1 != it->end(); ++ it1)
		{
			std::map<size_t, std::set<size_t> >::iterator it2 = adjacent_vertices.find(*it1);
			if(adjacent_vertices.end() == it2)
			{
				adjacent_vertices.insert(std::make_pair(*it1, std::set<size_t> ()));
			}
			for (std::vector<size_t>::iterator it3 = it->begin(); it3 != it->end(); ++ it3)
			{
				//if (*it3 != *it1)
				//{
					adjacent_vertices[*it1].insert(*it3);
				//}
			}
		}
	}
	new_vertices.clear();
	new_faces.clear();
	// for each vertex v0
	for (std::map<size_t, std::set<size_t> >::iterator it = adjacent_vertices.begin(); it != adjacent_vertices.end(); ++ it)
	{
		// if extraordinary
		if (it->second.size() < 6 + 1)
		{
			continue;
		}
		std::set<size_t>::iterator it1 = it->second.find(it->first);
		// for each adjacent greater vertex v1
		for (++ it1; it1 != it->second.end(); ++ it1)
		{
			std::map<size_t, std::set<size_t> >::iterator it2 = adjacent_vertices.find(*it1);
			// if extraordinary
			if (it2->second.size() < 6 + 1)
			{
				continue;
			}
			// new point
			std::vector<GLfloat> new_pt(3, 0.0);
			for (size_t i = 0; i < new_pt.size(); ++ i)
			{
				new_pt[i] += 1.0 / 2.0 * (model.vertex_list[it->first - 1][i] + model.vertex_list[*it1 - 1][i]);
			}
			unsigned count(0);
			std::vector<size_t> butterfly_list;
			// for each adjacent vertex of v0
			for (std::set<size_t>::iterator it3 = it->second.begin(); it3 != it->second.end(); ++ it3)
			{
				// duplicate
				if (*it3 == it->first || *it3 == *it1)
				{
					continue;
				}
				// find if shared vertex
				std::set<size_t>::iterator it4 = it2->second.find(*it3);
				if (it2->second.end() != it4)
				{
					// first shared vertex v2 and second shared vertex v3
					if (count < 2)
					{
						butterfly_list.push_back(*it4);
						++ count;
					}
					else
					{
						break;
					}
				}
			}
			//std::cout << "test " << it->first << " " << *it1 << " " << butterfly_list[0] << " " << butterfly_list[1];
			for (size_t i = 0; i < new_pt.size(); ++ i)
			{
				new_pt[i] += 1.0 / 8.0 * (model.vertex_list[butterfly_list[0] - 1][i] + model.vertex_list[butterfly_list[1] - 1][i]);
			}
			for (std::set<size_t>::iterator it3 = it->second.begin(); it3 != it->second.end(); ++ it3)
			{
				if (*it3 != it->first && *it3 != *it1 && *it3 != butterfly_list[0] && *it3 != butterfly_list[1])
				{
					std::map<size_t, std::set<size_t> >::iterator it4 = adjacent_vertices.find(butterfly_list[0]);
					if (it4->second.end() != it4->second.find(*it3))
					{
						std::cout << " " << *it3;
						for (size_t i = 0; i < new_pt.size(); ++ i)
						{
							new_pt[i] -= 1.0 / 16.0 * model.vertex_list[*it3 - 1][i];
						}
						break;
					}
				}
			}
			for (std::set<size_t>::iterator it3 = it->second.begin(); it3 != it->second.end(); ++ it3)
			{
				if (*it3 != it->first && *it3 != *it1 && *it3 != butterfly_list[0] && *it3 != butterfly_list[1] && *it3 != butterfly_list[2])
				{
					std::map<size_t, std::set<size_t> >::iterator it4 = adjacent_vertices.find(butterfly_list[1]);
					if (it4->second.end() != it4->second.find(*it3))
					{
						std::cout << " " << *it3;
						for (size_t i = 0; i < new_pt.size(); ++ i)
						{
							new_pt[i] -= 1.0 / 16.0 * model.vertex_list[*it3 - 1][i];
						}
						break;
					}
				}
			}
			for (std::set<size_t>::iterator it3 = it2->second.begin(); it3 != it2->second.end(); ++ it3)
			{
				if (*it3 != it->first && *it3 != *it1 && *it3 != butterfly_list[0] && *it3 != butterfly_list[1])
				{
					std::map<size_t, std::set<size_t> >::iterator it4 = adjacent_vertices.find(butterfly_list[0]);
					if (it4->second.end() != it4->second.find(*it3))
					{
						std::cout << " " << *it3;
						for (size_t i = 0; i < new_pt.size(); ++ i)
						{
							new_pt[i] -= 1.0 / 16.0 * model.vertex_list[*it3 - 1][i];
						}
					}
				}
			}
			for (std::set<size_t>::iterator it3 = it2->second.begin(); it3 != it2->second.end(); ++ it3)
			{
				if (*it3 != it->first && *it3 != *it1 && *it3 != butterfly_list[0] && *it3 != butterfly_list[1])
				{
					std::map<size_t, std::set<size_t> >::iterator it4 = adjacent_vertices.find(butterfly_list[1]);
					if (it4->second.end() != it4->second.find(*it3))
					{
						std::cout << " " << *it3;
						for (size_t i = 0; i < new_pt.size(); ++ i)
						{
							new_pt[i] -= 1.0 / 16.0 * model.vertex_list[*it3 - 1][i];
						}
					}
				}
			}
			new_vertices.push_back(new_pt);
			size_t old_vertice_num = model.vertex_list.size();
			// new face
			std::vector<size_t> face(3, 0);
			face[0] = butterfly_list[0];
			face[1] = it->first;
			face[2] = old_vertice_num + new_vertices.size();
			new_faces.push_back(face);
			face[0] = butterfly_list[0];
			face[1] = old_vertice_num + new_vertices.size();
			face[2] = *it1;
			new_faces.push_back(face);
			face[0] = butterfly_list[1];
			face[1] = old_vertice_num + new_vertices.size();
			face[2] = it->first;
			new_faces.push_back(face);
			face[0] = butterfly_list[1];
			face[1] = *it1;
			face[2] = old_vertice_num + new_vertices.size();
			new_faces.push_back(face);
			//std::cin.get(); 
		}
		model.vertex_list.insert(model.vertex_list.end(), new_vertices.begin(), new_vertices.end());
		model.face_list.insert(model.face_list.end(), new_faces.begin(), new_faces.end());
	}
	return true;
}
bool Subdivision::loop(void)
{
	return true;
}
