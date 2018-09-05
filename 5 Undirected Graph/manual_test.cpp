//
// Created by laptop on 4/4/18.
//

#include "Weighted_graph.h"

int main(){

    Weighted_graph *test = new Weighted_graph(4);
    std::cout << *test;

    test->insert(1,0,1);
    test->insert(1,2,2);
    test->insert(2,3,5);
    test->insert(1,3,6);

    std::cout << *test;

    std::cout << test->adjacent(3,2) << std::endl;
    std::cout << test->degree(3) << std::endl;
    std::cout << test->degree(2) << std::endl;
    std::cout << test->edge_count() << std::endl;

    std::cout << test->distance(0,3);

    return 0;

}