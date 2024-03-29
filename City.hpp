//
// Created by Reneil Pascua on 2019-11-22.
//

#ifndef GENETICALGORITHM_CITY_HPP
#define GENETICALGORITHM_CITY_HPP

#include <iostream>
#include <string>

using namespace std;

class City {
public:
    string name;
    //coordinates, limited to [0,MAP_BOUNDARY]
    int x;
    int y;

    City(string,int,int);
//    ~City();

    friend ostream &operator<<( ostream &output, const City& city );

    bool operator==(const City& rhs) const;
};


#endif //GENETICALGORITHM_CITY_HPP
