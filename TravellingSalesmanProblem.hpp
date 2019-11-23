//
// Created by Reneil Pascua on 2019-11-22.
//

#ifndef GENETICALGORITHM_TRAVELLINGSALESMANPROBLEM_HPP
#define GENETICALGORITHM_TRAVELLINGSALESMANPROBLEM_HPP

#include "Tour.hpp"

class TravellingSalesmanProblem {
public:
    list<City> citylist;
    list<Tour> tours;

    TravellingSalesmanProblem();


    //randomly generates a list of cities of given size
    static list<City> generateRandomCities(int size);
};


#endif //GENETICALGORITHM_TRAVELLINGSALESMANPROBLEM_HPP
