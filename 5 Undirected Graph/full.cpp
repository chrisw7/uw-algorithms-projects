#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Weighted_graph.h"

// Create the executable. Suppose the executable is a.out or a.exe
// Call this executable with a command-line argument:
//   E.g., ./a.out 5   
//         a.exe 5
// This will create a graph with 5 vertices and add all possible edges.
// It will then call distance between all vertices.

int main( int argc, char *argv[] ) {
	int const N = atoi( argv[1] );

	srand48( time(0) );   // Replace time(0) with any integer if you want consistent results

	std::cout.precision( 4 );

	Weighted_graph graph( N );

	for ( int m = 0; m < N; ++m ) {
		for ( int n = m + 1; n < N; ++n ) {
			double d = drand48();
			d = 1.01 - d;  // each distance is between 0.01 and 1.01
			graph.insert( m, n, d );
			std::cout << "(" << m << "," << n << ") = " << d << std::endl;
		}
	}

	for ( int m = 0; m < N; ++m ) {
		for ( int n = 0; n < N; ++n ) {
			std::cout << std::fixed << graph.distance( m, n ) << "\t";
		}

		std::cout << std::endl;
	}

	return 0;
}
