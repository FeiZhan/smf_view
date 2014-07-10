#include <cstdlib>
#include <ctime>
#include <climits>
#include <cfloat>
#include <cmath>
#include "Decimator.h"

// output stream for testing
std::ostream& operator<< (std::ostream& os, const Decimator& de)
{
	// output as SmfModel
	const SmfModel &model = de;
	os << model;
	return os;
}
// decimate it
int Decimator::decimate(int num, int percentage)
{
	// get quadric error and matrix list for each vertex
	getQuadricList();
	size_t original_size = edge_list.size();
	srand( time(NULL) );
	// reduce edge number to the percentage
	while (edge_list.size() > original_size * (100 - percentage) / 100)
	{
		std::set<size_t> candidates;
		// choose num candidate edges randomly
		for (size_t i = 0; i < num; ++ i)
		{
			size_t r = std::rand() % edge_list.size();
			candidates.insert(r);
		}
		double least_quadric_error = DBL_MAX;
		std::set<size_t>::iterator least;
		// find the candidate edge with least error
		for (std::set<size_t>::iterator it = candidates.begin(); it != candidates.end(); ++ it)
		{
			std::set<std::pair<size_t, size_t> >::iterator edge_it = edge_list.begin();
			std::advance(edge_it, *it);
			double quadric = quadric_error_list[ edge_it->first ] + quadric_error_list[ edge_it->second ];
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
		// remove the vertex
		vertex_list[least_edge->second] = std::vector<GLfloat>();
		// set the new location
		//vertex_list[least_edge->first] = getNewLocation(*least);
		// re-compute edges
		getEdgeList();
	}
	// re-compute normals
	getNormalList();
	// re-compute face maps
	getFaceMap();
	std::cout << "percentage edge " << edge_list.size() << " / " << original_size << "; face " << face_list.size() << std::endl;
	return EXIT_SUCCESS;
}
// get quadric error and matrix list for each vertex
bool Decimator::getQuadricList(void)
{
	quadric_matrix_list.clear();
	quadric_error_list.clear();
	// for each vertex
	for (size_t i = 0; i < vertex_list.size(); ++ i)
	{
		quadric_matrix_list.insert( std::make_pair(i, getQuadricMatrix(i)) );
		quadric_error_list.insert( std::make_pair(i, getQuadricError(i)) );
	}
	return true;
}
// vertex quadric error
double Decimator::getQuadricError(size_t vertex)
{
	// removed vertex
	if (vertex_list[vertex].size() < 3)
	{
		return DBL_MAX;
	}
	// get error quadric matrix
	std::vector<std::vector<double> > Q( quadric_matrix_list[vertex] );
	// copy the position of the vertex
	std::vector<GLfloat> v( vertex_list[vertex] );
	// turn it into a vector of 4 values
	v.push_back(1.0);
	double error = 0.0;
	// error = v^{T} Q v
	for (size_t i = 0; i < 4; ++ i)
	{
		double e = 0.0;
		for (size_t j = 0; j < 4; ++ j)
		{
			e += v[j] * Q[j][i];
		}
		error += e * v[i];
	}
	return error;
}
// get vertex quadric matrix
std::vector<std::vector<double> > Decimator::getQuadricMatrix(size_t vertex)
{
	// removed vertex
	if (vertex_list[vertex].size() < 3)
	{
		return std::vector<std::vector<double> >();
	}
	// quadric matrix
	std::vector<std::vector<double> > Q(4, std::vector<double> (4, 0.0));
	double plane[4] = {0.0, 0.0, 0.0, 0.0};
	// for connected faces
	for (std::set<size_t>::iterator it = face_map[vertex].begin(); it != face_map[vertex].end(); ++ it)
	{
		// fundamental error quadric
		std::vector<std::vector<double> > Kp(4, std::vector<double> (4, 0.0));
		// copy the position of each vertex in the face
		std::vector<GLfloat> &A( vertex_list[face_list[*it][0]] ), &B( vertex_list[face_list[*it][1]] ), &C( vertex_list[face_list[*it][2]] );
		// the parameters of a plane (a, b, c, d)
		plane[0] = (B[1] - A[1]) * (C[2] - A[2]) - (C[1] - A[1]) * (B[2] - A[2]);
		plane[1] = (B[2] - A[2]) * (C[0] - A[0]) - (C[2] - A[2]) * (B[0] - A[0]);
		plane[2] = (B[0] - A[0]) * (C[1] - A[1]) - (C[0] - A[0]) * (B[1] - A[1]);
		// normalize it with a^2 + b^2 + c^2 = 1
		double normalizer = sqrt( plane[0] * plane[0] + plane[1] * plane[1] + plane[2] * plane[2] );
		plane[0] /= normalizer;
		plane[1] /= normalizer;
		plane[2] /= normalizer;
		plane[3] = - (plane[0] * A[0] + plane[1] * A[1] + plane[2] * A[2]);
		for (size_t i = 0; i < 4; ++ i)
		{
			for (size_t j = 0; j < 4; ++ j)
			{
				// compute Kp = p p^{T}
				Kp[i][j] = plane[i] * plane[j];
				// sum up to get quadric
				Q[i][j] += Kp[i][j];
			}
		}
	}
	return Q;
}
// get new location for vertex
std::vector<GLfloat> Decimator::getNewLocation(size_t edge)
{
	std::set<std::pair<size_t, size_t> >::iterator edge_it = edge_list.begin();
	// find the edge
	std::advance(edge_it, edge);
	// get vertex quadric matrices of the edge
	std::vector<std::vector<double> > quadrics( quadric_matrix_list[edge_it->first] ), q( quadric_matrix_list[edge_it->second] );
	// sum up to get edge quadric matrix
	for (size_t i = 0; i < quadrics.size() && i < q.size(); ++ i)
	{
		for (size_t j = 0; j < quadrics[i].size() && j < q[i].size(); ++ j)
		{
			quadrics[i][j] += q[i][j];
		}
	}
	quadrics[3][0] = quadrics[3][1] = quadrics[3][2] = 0.0;
	quadrics[3][3] = 1.0;
	// invert the matrix
	std::vector<std::vector<double> > inv( this->invertMatrix(quadrics) );
	std::vector<GLfloat> new_vertex(4, 0.0);
	// not invertible
	if (inv.size() < 4)
	{
		// compute the new vertex from the center of the edge
		for (size_t i = 0; i < 3; ++ i)
		{
			new_vertex[i] = (vertex_list[edge_it->first][i] + vertex_list[edge_it->second][i]) / 2.0;
		}
		new_vertex[3] = 1.0;
	}
	else
	{
		// compute the new vertex from the last column of the inverted matrix
		for (size_t i = 0; i < 4 && i < inv.size(); ++ i)
		{
			new_vertex[i] = inv[i][3];
		}
	}
	return new_vertex;
}
// get matrix inverse
std::vector<std::vector<double> > Decimator::invertMatrix(const std::vector<std::vector<double> > &mat)
{
	std::vector<std::vector<double> > inv(mat.size(), std::vector<double> (mat.size(), 0.0));
	// assuming 4 x 4 matrix
	inv[0][0] =	mat[1][1]  * mat[2][2] * mat[3][3] +
				mat[1][2]  * mat[2][3] * mat[3][1] +
				mat[1][3]  * mat[2][1]  * mat[3][2] -
				mat[1][1]  * mat[2][3]  * mat[3][2] -
				mat[1][2] * mat[2][1]  * mat[3][3] - 
				mat[1][3] * mat[2][2]  * mat[3][1];
	inv[0][1] =	mat[0][1]  * mat[2][3] * mat[3][2] +
				mat[0][2]  * mat[2][1] * mat[3][3] +
				mat[0][3]  * mat[2][2]  * mat[3][1] -
				mat[0][1]  * mat[2][2]  * mat[3][3] -
				mat[0][2] * mat[2][3]  * mat[3][1] -
				mat[0][3] * mat[2][1]  * mat[3][2];
	inv[0][2] =	mat[0][1]  * mat[1][2] * mat[3][3] +
				mat[0][2]  * mat[1][3] * mat[3][2] +
				mat[0][3]  * mat[1][1] * mat[3][2] -
				mat[0][1]  * mat[1][3] * mat[3][2] -
				mat[0][2] * mat[1][1] * mat[3][3] -
				mat[0][3] * mat[1][2] * mat[3][1];
	inv[0][3] = mat[0][1]  * mat[1][3] * mat[2][2] +
				mat[0][2]  * mat[1][1] * mat[2][3] +
				mat[0][3]  * mat[1][2] * mat[2][1] -
				mat[0][1]  * mat[1][2] * mat[2][3] -
				mat[0][2] * mat[1][3] * mat[2][1] -
				mat[0][3] * mat[1][1] * mat[2][2];
	inv[1][0] = mat[1][0]  * mat[2][3] * mat[3][2] +
				mat[1][2]  * mat[2][1] * mat[3][3] +
				mat[1][3]  * mat[2][2] * mat[3][0] -
				mat[1][0]  * mat[2][2] * mat[3][3] -
				mat[1][2] * mat[2][3] * mat[3][0] -
				mat[1][3] * mat[2][0] * mat[3][2];
	inv[1][1] = mat[0][0]  * mat[2][2] * mat[3][3] +
				mat[0][2]  * mat[2][3] * mat[3][0] +
				mat[0][3]  * mat[2][0] * mat[3][2] -
				mat[0][0]  * mat[2][3] * mat[3][2] -
				mat[0][3] * mat[2][0] * mat[3][3] -
				mat[0][3] * mat[2][2] * mat[3][0];
	inv[1][2] = mat[0][0]  * mat[1][3] * mat[3][2] +
				mat[0][2]  * mat[1][0] * mat[3][3] +
				mat[0][3]  * mat[1][2] * mat[3][0] -
				mat[0][0]  * mat[1][2] * mat[3][3] -
				mat[0][2] * mat[1][3] * mat[3][0] -
				mat[0][3] * mat[1][0] * mat[3][2];
	inv[1][3] = mat[0][0]  * mat[1][2] * mat[2][3] +
				mat[0][2]  * mat[1][3] * mat[2][0] +
				mat[0][3]  * mat[1][0] * mat[2][2] -
				mat[0][0]  * mat[1][3] * mat[2][2] -
				mat[0][2] * mat[1][0] * mat[2][3] - 
				mat[0][3] * mat[1][2] * mat[2][0];
	inv[2][0] = mat[1][0]  * mat[2][1] * mat[3][3] +
				mat[1][1]  * mat[2][3] * mat[3][0] +
				mat[1][3]  * mat[2][0] * mat[3][1] -
				mat[1][0]  * mat[2][3] * mat[3][1] -
				mat[1][1] * mat[2][0] * mat[3][3] - 
				mat[1][3] * mat[2][1] * mat[3][0];
	inv[2][1] = mat[0][0]  * mat[2][3] * mat[3][1] +
				mat[0][1]  * mat[2][0] * mat[3][3] +
				mat[0][3]  * mat[2][1] * mat[3][0] -
				mat[0][0]  * mat[2][1] * mat[3][3] -
				mat[0][2] * mat[2][3] * mat[3][0] -
				mat[0][3] * mat[2][0] * mat[3][1];
	inv[2][2] = mat[0][0]  * mat[1][1] * mat[3][3] +
				mat[0][1]  * mat[1][3] * mat[3][1] +
				mat[0][3]  * mat[1][0] * mat[3][1] -
				mat[0][0]  * mat[0][3] * mat[3][1] -
				mat[0][1] * mat[1][0] * mat[3][3] -
				mat[0][3] * mat[1][1] * mat[3][0];
	inv[3][2] = mat[0][0]  * mat[1][3] * mat[2][1] +
				mat[0][1]  * mat[1][0] * mat[2][3] +
				mat[0][3]  * mat[1][1] * mat[2][0] -
				mat[0][0]  * mat[1][1] * mat[2][3] -
				mat[0][1] * mat[1][3] * mat[2][0] -
				mat[0][3] * mat[1][0] * mat[2][1];
	inv[3][0] = mat[1][0] * mat[2][2] * mat[3][1] +
				mat[1][1] * mat[2][0] * mat[3][2] +
				mat[1][2] * mat[2][1] * mat[3][0] -
				mat[1][0] * mat[2][1] * mat[3][2] -
				mat[1][1] * mat[2][2] * mat[3][0] -
				mat[1][2] * mat[2][0] * mat[3][1];
	inv[3][1] = mat[0][0] * mat[2][1] * mat[3][2] +
				mat[0][1] * mat[2][2] * mat[3][0] +
				mat[0][2] * mat[2][0] * mat[3][1] -
				mat[0][0] * mat[2][2] * mat[3][1] -
				mat[0][1] * mat[2][0] * mat[3][2] - 
				mat[0][2] * mat[2][1] * mat[3][0];
	inv[3][2] = mat[0][0] * mat[1][2] * mat[3][1] +
				mat[0][1] * mat[1][0] * mat[3][2] +
				mat[0][2] * mat[1][1] * mat[3][0] -
				mat[0][0] * mat[1][1] * mat[3][2] -
				mat[0][1] * mat[1][2] * mat[3][0] -
				mat[0][2] * mat[1][0] * mat[3][1];
	inv[3][3] = mat[0][0] * mat[1][1] * mat[2][2] +
				mat[0][1] * mat[1][2] * mat[2][0] +
				mat[0][2] * mat[1][0] * mat[2][1] -
				mat[0][0] * mat[1][2] * mat[2][1] -
				mat[0][1] * mat[1][0] * mat[2][2] -
				mat[0][2] * mat[1][1] * mat[2][0];
	// get determinant
	double det =	mat[0][0] * mat[1][1] * mat[2][2] * mat[3][3] +
					mat[0][0] * mat[1][2] * mat[2][3] * mat[3][1] +
					mat[0][0] * mat[1][3] * mat[2][1] * mat[3][2] +

					mat[0][1] * mat[1][0] * mat[2][3] * mat[3][2] +
					mat[0][1] * mat[1][2] * mat[2][0] * mat[3][3] +
					mat[0][1] * mat[1][3] * mat[2][2] * mat[3][0] +

					mat[0][2] * mat[1][0] * mat[2][1] * mat[3][3] +
					mat[0][2] * mat[1][1] * mat[2][3] * mat[3][0] +
					mat[0][2] * mat[1][3] * mat[2][0] * mat[3][1] +

					mat[0][3] * mat[1][0] * mat[2][2] * mat[3][1] +
					mat[0][3] * mat[1][1] * mat[2][0] * mat[3][2] +
					mat[0][3] * mat[1][2] * mat[2][1] * mat[3][0] +

					mat[0][0] * mat[1][1] * mat[2][3] * mat[3][2] -
					mat[0][0] * mat[1][2] * mat[2][1] * mat[3][3] -
					mat[0][0] * mat[1][3] * mat[2][2] * mat[3][1] -

					mat[0][1] * mat[1][0] * mat[2][2] * mat[3][3] -
					mat[0][1] * mat[1][2] * mat[2][3] * mat[3][0] -
					mat[0][1] * mat[1][3] * mat[2][0] * mat[3][2] -

					mat[0][2] * mat[1][0] * mat[2][3] * mat[3][1] -
					mat[0][2] * mat[1][1] * mat[2][0] * mat[3][3] -
					mat[0][2] * mat[1][3] * mat[2][1] * mat[3][0] -

					mat[0][3] * mat[1][0] * mat[2][1] * mat[3][2] -
					mat[0][3] * mat[1][1] * mat[2][2] * mat[3][0] -
					mat[0][3] * mat[1][2] * mat[2][0] * mat[3][1];
	// not invertible
	if (0.0 == det)
	{
		return std::vector<std::vector<double> > ();
	}
	// inverse
	det = 1.0 / det;
	for (size_t i = 0; i < inv.size(); ++ i)
	{
		for (size_t j = 0; j < inv[i].size(); ++ j)
		{
			inv[i][j] *= det;
		}
	}
	return inv;
}































