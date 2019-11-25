//
// Created by Reneil Pascua on 2019-11-22.
//

#ifndef GENETICALGORITHM_TOUR_HPP
#define GENETICALGORITHM_TOUR_HPP

#include "City.hpp"
#include <vector>
#include <cmath>

using namespace std;

class Tour {
public:

    // arbitrary scalar for fitness
    double FITNESS_SCALAR=10000.0;

    // tourID
    int id;
    // vector of cities in visit order
    vector<City> visits;
    // the tour's fitness
    double fitness;

    // constructor
    Tour(int id, vector<City> visits);
//    ~Tour();

    // sets given visit order
    void setTour(vector<City> visits);

    //calculates the distance between 2 given cities
    double getDistance(City,City) const;

    //calculates the total distance of the tour
    double getTourDistance() const;

    //calculates the fitness of the tour
    void calculateFitness();

    //overloaded insertion operator prints cities in visit order and fitness
    friend ostream &operator<<( ostream &output, const Tour& tour );

    //overloaded == operator compares tour id
    bool operator==(const Tour& rhs) const;

    //overloaded < operator compares fitness; in a set, tours with less fitness will be to the left of those with more fitness
    bool operator<(const Tour& rhs) const;
};


#endif //GENETICALGORITHM_TOUR_HPP
