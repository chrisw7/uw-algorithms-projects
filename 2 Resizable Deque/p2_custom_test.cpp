
#include <iostream>
#include <cassert>
#include "Resizable_deque.h"

int main() {
    std::cout << "Testing min. initial_array_capacity is 16...";
    Resizable_deque<int> q( 4 );
    assert( q.capacity() == 16 );
    assert( q.empty() );
    std::cout << " Passed!" << std::endl;

    std::cout << "Testing initial capacities > 16...";
    Resizable_deque<int> q2( 19 );
    assert( q2.capacity() == 19 );
    assert( q2.empty() );
    for ( int i = 0; i < 19; ++i ) {
        q2.push_front(i);
    }

    assert( q2.capacity() == 19 );
    assert( q2.front() == 18 );
    assert( q2.back() == 0 );
    assert( q2.size() == 19 );

    q2.push_front( 19 );
    assert( q2.capacity() == 38 );
    assert( q2.front() == 19 );
    assert( q2.back() == 0 );
    assert( q2.size() == 20 );

    for ( int i = 0; i < 10; ++i ) {
        q2.pop_front();
    }

    assert( q2.capacity() == 38 );
    assert( q2.front() == 9 );
    assert( q2.back() == 0 );
    assert( q2.size() == 10 );

    q2.pop_front();
    assert( q2.capacity() == 19 );
    assert( q2.front() == 8 );
    assert( q2.back() == 0 );
    assert( q2.size() == 9 );
    std::cout << " Passed!" << std::endl;
}

