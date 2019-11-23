#include <iostream>

int main() {

    // number of tours in a generation
    const int POPULATION_SIZE = 32;
    // number of cities in a tour
    const int CITIES_IN_TOUR = 32;
    // number of swaps per shuffle
    const int SHUFFLE = 64;
    // minimum iterations
    const int ITERATIONS = 1000;
    // map boundary
    const int MAP_BOUNDARY = 1000;
    // (uniform) randomly pick this many tours -- the fittest of this pool becomes a parent
    const int PARENT_POOL_SIZE = 5;
    // mutation rate
    const double MUTATION_RATE = 0.15;
    // number of parents to be crossed to make a child
    const int NUMBER_OF_PARENTS = 2;
    // improvement factor = new best_distance / base_distance (ie. old best_distance). below this threshold, stop algo
    const double IMPROVEMENT_THRESHOLD = 1.0;



    return 0;
}