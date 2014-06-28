#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */
#include <climits>
#include <cfloat>
#include "Decimator.h"

// output stream for testing
std::ostream& operator<< (std::ostream& os, const Decimator& de)
{
	// output as SmfModel
	const SmfModel &model = de;
	os << model;
	return os;
}
int Decimator::decimate(int num)
{
	size_t original_size = edge_list.size();
	srand (time(NULL));
	// reduce edge number to half
	while (edge_list.size() * 2 > original_size)
	{
		std::set<size_t> candidates;
		// choose num candidate edges randomly
		for (size_t i = 0; i < num; ++ i)
		{
			candidates.insert( std::rand() % edge_list.size() );
		}
		double least_quadric_error = DBL_MAX;
		std::set<size_t>::iterator least;
		// find the candidate edge with least error
		for (std::set<size_t>::iterator it = candidates.begin(); it != candidates.end(); ++ it)
		{
			double quadric = this->getEdgeQuadricError(*it);
			if (quadric < least_quadric_error)
			{
				least_quadric_error = quadric;
				least = it;
			}
		}
		// find the edge with least error
		std::set<std::pair<size_t, size_t> >::iterator least_edge = edge_list.begin();
		std::advance(least_edge, *least);
		// remove the edge in the face list
		for (std::vector<std::vector<size_t> >::iterator it = face_list.begin(); it != face_list.end(); ++ it)
		{
			std::vector<size_t>::iterator first_it = it->end();
			// find first vertex
			for (std::vector<size_t>::iterator it1 = it->begin(); it1 != it->end(); ++ it1)
			{
				if (*it1 == least_edge->first)
				{
					first_it = it1;
					break;
				}
			}
			std::vector<size_t>::iterator second_it = it->end();
			// find second vertex
			for (std::vector<size_t>::iterator it1 = it->begin(); it1 != it->end(); ++ it1)
			{
				if (*it1 == least_edge->second)
				{
					second_it = it1;
					break;
				}
			}
			// if find both
			if (it->end() != first_it && it->end() != second_it)
			{
				-- it;
				// remove the face
				face_list.erase(it + 1);
			}
			// if only find the second
			else if (it->end() != second_it)
			{
				// change to the first vertex
				*second_it = least_edge->first;
			}
		}
		// remove the edge
		edge_list.erase(least_edge);
	}
	return EXIT_SUCCESS;
}
double Decimator::getEdgeQuadricError(size_t edge)
{
	std::set<std::pair<size_t, size_t> >::iterator edge_it = edge_list.begin();
	// find the edge
	std::advance(edge_it, edge);
	// sum up vertex errors
	return this->getQuadricError(edge_it->first) + this->getQuadricError(edge_it->second);
}
double Decimator::getQuadricError(size_t vertex)
{
	std::vector<std::vector<double> > Kp( this->getQuadrics(vertex) );
	std::vector<GLfloat> v( vertex_list[vertex] );
	v.push_back(1.0);
	double error = 0;
	for (size_t i = 0; i < 4; ++ i)
	{
		double e = 0;
		for (size_t j = 0; j < 4; ++ j)
		{
			e += Kp[j][i] * v[j];
		}
		error += e * v[i];
	}
	return error;
}
std::vector<std::vector<double> > Decimator::getQuadrics(size_t vertex)
{
	std::vector<std::vector<double> > Kp(4, std::vector<double> (4, 0.0));
	for (std::vector<std::vector<size_t> >::iterator it = face_list.begin(); it != face_list.end(); ++ it)
	{
		bool flag = false;
		for (std::vector<size_t>::iterator it1 = it->begin(); it1 != it->end(); ++ it1)
		{
			if (*it1 == vertex)
			{
				flag = true;
				break;
			}
		}
		if (flag)
		{
			std::vector<GLfloat> &A( vertex_list[(*it)[0] - 1] ), &B( vertex_list[(*it)[1] - 1] ), &C( vertex_list[(*it)[2] - 1] );
			double plane[4] = {0.0, 0.0, 0.0, 0.0};
			plane[0] = (B[1] - A[1]) * (C[2] - A[2]) - (C[1] - A[1]) * (B[2] - A[2]);
			plane[1] = (B[2] - A[2]) * (C[0] - A[0]) - (C[2] - A[2]) * (B[0] - A[0]);
			plane[2] = (B[0] - A[0]) * (C[1] - A[1]) - (C[0] - A[0]) * (B[1] - A[1]);
			plane[3] = - (plane[0] * A[0] + plane[1] * A[1] + plane[2] * A[2]);
			for (size_t i = 0; i < 4; ++ i)
			{
				for (size_t j = 0; j < 4; ++ j)
				{
					Kp[i][j] += plane[i] * plane[j];
				}
			}
		}
	}
	return Kp;
}
std::vector<GLfloat> Decimator::getNewLocation(size_t edge)
{
	std::set<std::pair<size_t, size_t> >::iterator edge_it = edge_list.begin();
	std::advance(edge_it, edge);
	std::vector<std::vector<double> > quadrics( this->getQuadrics(edge_it->first) ), q( this->getQuadrics(edge_it->second) );
	for (size_t i = 0; i < quadrics.size() && i < q.size(); ++ i)
	{
		for (size_t j = 0; j < quadrics[i].size() && j < q[i].size(); ++ i)
		{
			quadrics[i][j] += q[i][j];
		}
	}
	quadrics[3][0] = quadrics[3][1] = quadrics[3][2] = 0.0;
	quadrics[3][3] = 1;
	std::vector<std::vector<double> > inv( this->invertMatrix(quadrics) );
	std::vector<GLfloat> new_vertex(4, 0.0);
	for (size_t i = 0; i < 4; ++ i)
	{
		new_vertex[i] = inv[i][3];
	}
	return new_vertex;
}
std::vector<std::vector<double> > Decimator::invertMatrix(const std::vector<std::vector<double> > &mat)
{
	std::vector<std::vector<double> > inv(mat.size(), std::vector<double> (mat.size(), 0.0));
	inv[0][0] =	mat[1][0]  * mat[2][2] * mat[3][3] - 
				mat[1][0]  * mat[2][3] * mat[3][2] - 
				mat[2][1]  * mat[1][2]  * mat[3][3] + 
				mat[2][1]  * mat[1][3]  * mat[3][2] +
				mat[3][1] * mat[1][2]  * mat[2][3] - 
				mat[3][1] * mat[1][3]  * mat[2][2];

	inv[1][0] =	-mat[1][0]  * mat[2][2] * mat[3][3] + 
				mat[1][0]  * mat[2][3] * mat[3][2] + 
				mat[2][0]  * mat[1][2]  * mat[3][3] - 
				mat[2][0]  * mat[1][3]  * mat[3][2] - 
				mat[3][0] * mat[1][2]  * mat[2][3] + 
				mat[3][0] * mat[1][3]  * mat[2][2];

	inv[2][0] =	mat[1][0]  * mat[2][1] * mat[3][3] - 
				mat[1][0]  * mat[2][3] * mat[3][1] - 
				mat[2][0]  * mat[1][0] * mat[3][3] + 
				mat[2][0]  * mat[1][3] * mat[3][1] + 
				mat[3][0] * mat[1][0] * mat[2][3] - 
				mat[3][0] * mat[1][3] * mat[2][1];

	inv[3][0] = -mat[1][0]  * mat[2][1] * mat[3][2] + 
			   mat[1][0]  * mat[2][2] * mat[3][1] +
			   mat[2][0]  * mat[1][0] * mat[3][2] - 
			   mat[2][0]  * mat[1][2] * mat[3][1] - 
			   mat[3][0] * mat[1][0] * mat[2][2] + 
			   mat[3][0] * mat[1][2] * mat[2][1];

	inv[0][1] = -mat[0][1]  * mat[2][2] * mat[3][3] + 
				mat[0][1]  * mat[2][3] * mat[3][2] + 
				mat[2][1]  * mat[0][2] * mat[3][3] - 
				mat[2][1]  * mat[0][3] * mat[3][2] - 
				mat[3][1] * mat[0][2] * mat[2][3] + 
				mat[3][1] * mat[0][3] * mat[2][2];

	inv[1][0] = mat[0][0]  * mat[2][2] * mat[3][3] - 
				mat[0][0]  * mat[2][3] * mat[3][2] - 
				mat[2][0]  * mat[0][2] * mat[3][3] + 
				mat[2][0]  * mat[0][3] * mat[3][2] + 
				mat[3][0] * mat[0][2] * mat[2][3] - 
				mat[3][0] * mat[0][3] * mat[2][2];

	inv[2][1] = -mat[0][0]  * mat[2][1] * mat[3][3] + 
				mat[0][0]  * mat[2][3] * mat[3][1] + 
				mat[2][0]  * mat[0][1] * mat[3][3] - 
				mat[2][0]  * mat[0][3] * mat[3][1] - 
				mat[3][0] * mat[0][1] * mat[2][3] + 
				mat[3][0] * mat[0][3] * mat[2][1];

	inv[3][1] = mat[0][0]  * mat[2][1] * mat[3][2] - 
				mat[0][0]  * mat[2][2] * mat[3][1] - 
				mat[2][0]  * mat[0][1] * mat[3][2] + 
				mat[2][0]  * mat[0][2] * mat[3][1] + 
				mat[3][0] * mat[0][1] * mat[2][2] - 
				mat[3][0] * mat[0][2] * mat[2][1];

	inv[0][2] = mat[0][1]  * mat[1][2] * mat[3][3] - 
				mat[0][1]  * mat[1][3] * mat[3][2] - 
				mat[1][0]  * mat[0][2] * mat[3][3] + 
				mat[1][0]  * mat[0][3] * mat[3][2] + 
				mat[3][1] * mat[0][2] * mat[1][3] - 
				mat[3][1] * mat[0][3] * mat[1][2];

	inv[1][2] = -mat[0][0]  * mat[1][2] * mat[3][3] + 
				mat[0][0]  * mat[1][3] * mat[3][2] + 
				mat[1][0]  * mat[0][2] * mat[3][3] - 
				mat[1][0]  * mat[0][3] * mat[3][2] - 
				mat[3][0] * mat[0][2] * mat[1][3] + 
				mat[3][0] * mat[0][3] * mat[1][2];

	inv[2][2] = mat[0][0]  * mat[1][0] * mat[3][3] - 
				mat[0][0]  * mat[1][3] * mat[3][1] - 
				mat[1][0]  * mat[0][1] * mat[3][3] + 
				mat[1][0]  * mat[0][3] * mat[3][1] + 
				mat[3][0] * mat[0][1] * mat[1][3] - 
				mat[3][0] * mat[0][3] * mat[1][0];

	inv[3][2] = -mat[0][0]  * mat[1][0] * mat[3][2] + 
				mat[0][0]  * mat[1][2] * mat[3][1] + 
				mat[1][0]  * mat[0][1] * mat[3][2] - 
				mat[1][0]  * mat[0][2] * mat[3][1] - 
				mat[3][0] * mat[0][1] * mat[1][2] + 
				mat[3][0] * mat[0][2] * mat[1][0];

	inv[0][3] = -mat[0][1] * mat[1][2] * mat[2][3] + 
				mat[0][1] * mat[1][3] * mat[2][2] + 
				mat[1][0] * mat[0][2] * mat[2][3] - 
				mat[1][0] * mat[0][3] * mat[2][2] - 
				mat[2][1] * mat[0][2] * mat[1][3] + 
				mat[2][1] * mat[0][3] * mat[1][2];

	inv[1][3] = mat[0][0] * mat[1][2] * mat[2][3] - 
				mat[0][0] * mat[1][3] * mat[2][2] - 
				mat[1][0] * mat[0][2] * mat[2][3] + 
				mat[1][0] * mat[0][3] * mat[2][2] + 
				mat[2][0] * mat[0][2] * mat[1][3] - 
				mat[2][0] * mat[0][3] * mat[1][2];

	inv[2][3] = -mat[0][0] * mat[1][0] * mat[2][3] + 
				mat[0][0] * mat[1][3] * mat[2][1] + 
				mat[1][0] * mat[0][1] * mat[2][3] - 
				mat[1][0] * mat[0][3] * mat[2][1] - 
				mat[2][0] * mat[0][1] * mat[1][3] + 
				mat[2][0] * mat[0][3] * mat[1][0];

	inv[3][3] = mat[0][0] * mat[1][0] * mat[2][2] - 
				mat[0][0] * mat[1][2] * mat[2][1] - 
				mat[1][0] * mat[0][1] * mat[2][2] + 
				mat[1][0] * mat[0][2] * mat[2][1] + 
				mat[2][0] * mat[0][1] * mat[1][2] - 
				mat[2][0] * mat[0][2] * mat[1][0];

	double det = mat[0][0] * inv[0][0] + mat[0][1] * inv[1][0] + mat[0][2] * inv[2][0] + mat[0][3] * inv[3][0];
	if (det == 0)
	{
		return inv;
	}
	det = 1.0 / det;
	for (size_t i = 0; i < inv.size(); i ++)
	{
		for (size_t j = 0; j < inv[i].size(); ++ j)
		{
			inv[i][j] *= det;
		}
	}
	return inv;
}































