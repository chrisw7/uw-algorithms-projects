#include <iostream>
#include <cstdlib>
#include <string>
#include "Weighted_graph.h"

// Note some details may change.  For example, for ease of understanding, this uses %
// while the final version may use some version of a bitwise operation.

int main( int argc, char *argv[] ) {
	int const LIMIT = atoi( argv[1] );
	int N = 2 << LIMIT;
	int MASK = N - 1;

	const double INF = std::numeric_limits<double>::infinity();
	double sum = 0.0;

	Weighted_graph graph( N );

	for ( int j = 0; j < 8; ++j ) {
		for ( int k = 0; k < N*(N - 1)/20; ++k ) {
			int m = lrand48() & MASK;
			int n = lrand48() & MASK;

			if ( m != n ) {
				double d = drand48();
				d = 1.01 - d*d;  // each distance is between 0.01 and 1.01
				graph.insert( m, n, d );
			}
		}

		int m = lrand48() & MASK;

		for ( int k = 0; k < 20; ++k ) {
			int n = lrand48() & MASK;
			double d = graph.distance( m, n );

			if ( d < INF ) {
				sum += graph.distance( m, n );
			}
		}
	}

	std::cout << sum << std::endl;

	return 0;
}
