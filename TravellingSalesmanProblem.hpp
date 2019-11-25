//
// Created by Reneil Pascua on 2019-11-22.
//

#ifndef GENETICALGORITHM_TRAVELLINGSALESMANPROBLEM_HPP
#define GENETICALGORITHM_TRAVELLINGSALESMANPROBLEM_HPP


#include "Tour.hpp"
#include <set>
#include <unordered_set>
#include <iomanip>

class TravellingSalesmanProblem {
public:

// parameters to define the problem
    // number of tours in a generation
    int POPULATION_SIZE;
    // number of cities in a tour
    int CITIES_IN_TOUR;
    // number of swaps per shuffle
    int SHUFFLE;
    // minimum iterations
    int ITERATIONS;
    // map boundary
    int MAP_BOUNDARY;
    // (uniform) randomly pick this many tours -- the fittest of this pool becomes a parent
    int PARENT_POOL_SIZE;
    // proportion of tours to mutate
    const double MUTATION_RATE_TOURS = 0.3;
    // mutation rate
    double MUTATION_RATE;
    // number of parents to be crossed to make a child
    int NUMBER_OF_PARENTS;
    // improvement factor = new best_distance / base_distance (ie. old best_distance). below this threshold, stop algo
    double IMPROVEMENT_THRESHOLD;

    // vector of cities to be used in this problem
    vector<City> cities;
    // vector of tours
    vector<Tour> tours;
    // vector of fitness corresponding to each tour
    vector<double> fitnesses;
    // base fitness
    double base_fitness;
    double base_average_fitness;
    // number of tours that have existed
    int nTours;
    // indicates whether the improvement threshold was reached
    bool thresholdreached;



    //giant constructor which defines parameters, initializes citylist and tours
    TravellingSalesmanProblem(int populationSize, int citiesInTour, int shuffle, int iterations, int mapBoundary,
                              int parentPoolSize, double mutationRate, int numberOfParents,
                              double improvementThreshold);

    //solve the travelling salesman problem using a genetic algorithm
    void solve();

    //generates a vector of cities w random attributes and sets the cities vector
    void generateRandomCities();

    //generates a vector of tours w random visit orders
    void generateRandomTours();

    //shuffles cities vector with a seed to enhance randomization
    void shuffleCities(int seed);

    //populates the fitnesses vector by looking at each tour
    void populateFitnesses();

    //identifies the single most fit tour and moves it to the back, then returns its fitness
    double findElite();

    //births a new generation of tours by crossover, saving the single elite from the previous gen
    void crossoverPhase();

    //crosses a set of given parents to produce a new tour with a seed to enhance randomization
    Tour cross(const set<Tour>& parents, int seed);

    //copies N cities from one vector's beginning to another
    void copyCities(const vector<City>& src, vector<City>& dest, int N);

    //enacts mutation on the front N tours
    void mutationPhase();

    //mutates the given tour with a seed to enhance randomization
    void mutate(Tour& t,int seed);

    //report
    void report(double,double,double);

    //calculates the average fitness of the tours
    double getAverageFitness();

    //prints out all the cities
    void printCities();

    //prints out all the tours
    void printTours();

    //converts improvement factor to percent
    double convertToPercent(double);


};


#endif //GENETICALGORITHM_TRAVELLINGSALESMANPROBLEM_HPP
