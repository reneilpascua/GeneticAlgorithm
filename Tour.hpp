//
// Created by Reneil Pascua on 2019-11-22.
//

#ifndef GENETICALGORITHM_TOUR_HPP
#define GENETICALGORITHM_TOUR_HPP

#include "City.hpp"
#include <list>
#include <set>

class Tour {
public:
    // list of cities visited in list order
    list<City> citylist;

    Tour();
    ~Tour();

    //populates citylist with random visit order, given a list of cities
    void populateRandomTour(list<City> citylist);

    //calculates the distance between 2 given cities
    double getDistance(City,City);

    //calculates the total distance of the tour
    double getTourDistance();
};


#endif //GENETICALGORITHM_TOUR_HPP
