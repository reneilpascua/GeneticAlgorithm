#include <iostream>
#include "TravellingSalesmanProblem.hpp"

int main() {

    // define this run's TSP
    const int POPULATION_SIZE = 32;
    const int CITIES_IN_TOUR = 32;
    const int SHUFFLE = 64;
    const int ITERATIONS = 100;
    const int MAP_BOUNDARY = 1000;
    const int PARENT_POOL_SIZE = 5;
    const double MUTATION_RATE = 0.20;
    const int NUMBER_OF_PARENTS = 2;
    const double IMPROVEMENT_THRESHOLD = 1.25; // 20% improvement

    TravellingSalesmanProblem myproblem(POPULATION_SIZE,CITIES_IN_TOUR,SHUFFLE,ITERATIONS,MAP_BOUNDARY,
            PARENT_POOL_SIZE,MUTATION_RATE,NUMBER_OF_PARENTS,IMPROVEMENT_THRESHOLD);

    myproblem.printTours();

    myproblem.solve();

    return 0;
}