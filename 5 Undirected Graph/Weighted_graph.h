/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  cm3willi@edu.uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Spring 2018
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -sbregu
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -sbregu
 *****************************************/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "Exception.h"

// include whatever classes you want

class Weighted_graph {
	private:

	double **matrix;
	static const double INF;
	int num_edges;
	int num_nodes;

	public:
		Weighted_graph( int = 50 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		double adjacent( int, int ) const;
		double distance( int, int );

		void insert( int, int, double );

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

Weighted_graph::Weighted_graph(int N) {
	matrix = new double * [(N <= 0) ? 1 : N];
	for (int i = 0; i < N; i++){
		matrix[i] = new double[N];
	}

	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			matrix[i][j] = INF;
		}
		matrix[i][i] = 0;
	}

    num_edges = 0;
	num_nodes = (N <= 0) ? 1 : N;

}

Weighted_graph::~Weighted_graph() {
    for (int i = 0; i < num_nodes; i++){
        delete [] matrix[i];
    }

    delete [] matrix;
}

int Weighted_graph::degree(int n) const {
    if (n > num_nodes){
        throw illegal_argument();
    }
	int deg_count = 0;
	for (int i = 0; i < num_nodes; i++){
		if (matrix[n][i] != INF && matrix[n][i] != 0){
			deg_count++;
		}
	}
    return deg_count;
}

int Weighted_graph::edge_count() const {
	return num_edges;
}

double Weighted_graph::adjacent(int r, int c) const {
    if (r > num_nodes || c > num_nodes){
        throw illegal_argument();
    }
	return matrix[r][c];
}

double Weighted_graph::distance(int start_node, int end_node) {

    //Declare tracking arrays
    double visits [num_nodes];
    double distances [num_nodes];

    //Initialize vertex
    for (int i = 0; i < num_nodes; i++){
        visits[i] = i;
    }

    //Set starting vertex and distance
    visits[start_node] = INF;

    //Update initial distances from the perspective of starting node
    for (int i = 0; i < num_nodes; i++){
        distances[i] = matrix[start_node][i]; //Pull values from adjacency matrix
    }

    //Update starting node's distance to itself
    distances[start_node] = 0;

    //Run Dijkstra's algorithm N-1 times
    for (int iteration = 1; iteration < num_nodes; iteration++){

        double minDistance = INF;
        int closestNeighbour = 0;

        //Identify the nearest adjacent node distance & node
        for (int i = 0; i < num_nodes; i++){
            if (visits[i] != INF && distances[i] < minDistance && distances[i] > 0){//skip nodes with weight (0,inf)
                closestNeighbour = i;
                minDistance = distances[i];
            }
        }
        visits[closestNeighbour] = INF; //Indicate node has been visited with INF

        for (int i = 0; i < num_nodes; i++){
            if (matrix[closestNeighbour][i] != INF){ //Check that probed node is connected
                if (distances[i] == INF){            //If connected but not yet updated, update
                    distances[i] = minDistance + matrix[closestNeighbour][i]; //reflects distance travelled so far
                }else if (distances[closestNeighbour] + matrix[closestNeighbour][i] < distances[i]){
                    //If new route to probed node is shorter than existing route, use the shorter route
                    distances[i] = minDistance + matrix[closestNeighbour][i];
                }
            }
        }

    }
    return distances[end_node];
}

void Weighted_graph::insert(int r, int c, double w) {
    if (r > num_nodes || c > num_nodes){
        throw illegal_argument();
    }
	matrix[r][c] = w;
	matrix[c][r] = w;
	num_edges++;
}

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
    out << std::endl;
    for (int i = 0; i < graph.num_nodes;i++){
        for (int j = 0; j < graph.num_nodes; j++){
            out << graph.matrix[i][j] << '\t';
        }
        out << std::endl;
    }
    return out << std::endl;
}

#endif
