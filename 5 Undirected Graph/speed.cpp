#include <iostream>
#include <cmath>
#include <iostream>
#include "Weighted_graph.h"

// Note some details may change.  For example, for ease of understanding, this uses %
// while the final version may use some version of a bitwise operation.

int main() {
	int const LIMIT = 12;  // This number is subject to change
	int N = 8;

	double sum = 0.0;

	for ( int i = 0; i < LIMIT; ++i ) {
		N *= 2;

		Weighted_graph graph( N );

		for ( int j = 0; j < 8; ++j ) {
			// Modify some edges
			for ( int k = 0; k < N*(N - 1)/20; ++k ) {
				int m = lrand48() % N;
				int n = lrand48() % N;

				if ( m != n ) {
					// each distance is between 0.01 and 1.01
					double d = drand48();
					d = 1.01 - d*d;
					graph.insert( m, n, d );
				}
			}


			int m = lrand48() % N;

			// Test distances
			for ( int k = 0; k < 20; ++k ) {
				int n = lrand48() % N;
				std::cout << m << ", " << n << std::endl;
				sum += graph.distance( m, n );
			}
		}
	}

	std::cout << sum << std::endl;

	return 0;
}
