#include <iostream>
#include "TravellingSalesmanProblem.hpp"

#include <chrono>

int main() {

    auto start = chrono::high_resolution_clock::now();
    // define this run's TSP
    const int POPULATION_SIZE = 32;
    const int CITIES_IN_TOUR = 32;
    const int SHUFFLE = 64;
    const int ITERATIONS = 1000;
    const int MAP_BOUNDARY = 1000;
    const int PARENT_POOL_SIZE = 5;
    const double MUTATION_RATE = 0.20;
    const int NUMBER_OF_PARENTS = 2;
    const double IMPROVEMENT_THRESHOLD = 1.25; // 25% improvement

    // which runs to do?
    bool useRandomizedCities = true;
    bool useGreaterVancouver = false;

    if (useRandomizedCities) {


        cout<<"tsp of random cities and random tours: -------------"<<endl;
        TravellingSalesmanProblem myproblem1(POPULATION_SIZE,CITIES_IN_TOUR,SHUFFLE,ITERATIONS,MAP_BOUNDARY,
                                             PARENT_POOL_SIZE,MUTATION_RATE,NUMBER_OF_PARENTS,IMPROVEMENT_THRESHOLD);
        myproblem1.printTours();
        myproblem1.solve();
    }

    if (useGreaterVancouver) {
        cout <<"tsp of user-defined cities and random tours: -------------"<<endl;
        vector<City> userCities;
        userCities.push_back(City("vancouver",0.0,0.0));
        userCities.push_back(City("burnaby",25.0,0.0));
        userCities.push_back(City("new westminster",50.0,-10.0));
        userCities.push_back(City("west vancouver",0.0,30.0));
        userCities.push_back(City("north vancouver",25.0,25.0));
        userCities.push_back(City("richmond",10.0,-20.0));
        userCities.push_back(City("delta",15.0,-30.0));
        userCities.push_back(City("surrey",70.0,-30.0));
        userCities.push_back(City("tsawassen",25.0,-50.0));
        userCities.push_back(City("maple ridge",100.0,10.0));
        userCities.push_back(City("coquitlam",80.0,40.0));
        userCities.push_back(City("port coquitlam",80.0,25.0));

        TravellingSalesmanProblem myproblem2(POPULATION_SIZE,SHUFFLE,ITERATIONS,
                                             PARENT_POOL_SIZE,MUTATION_RATE,NUMBER_OF_PARENTS,2.0,
                                             userCities);
        myproblem2.printTours();
        myproblem2.solve();
    }

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop-start);
    cout << "this run took " << duration.count() << " microseconds"<<endl;
    return 0;
}