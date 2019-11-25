//
// Created by Reneil Pascua on 2019-11-22.
//

#include "Tour.hpp"


Tour::Tour(int id, vector<City> visits) : id(id), visits(visits) {
    calculateFitness();
}

double Tour::getDistance(City a, City b) const {
    return sqrt((pow(a.x - b.x, 2)) + (pow(a.y - b.y,2)));
}

double Tour::getTourDistance() const {
    double totaldistance = 0;
    for (int i=0; i<visits.size()-1; i++) {
        totaldistance += getDistance(visits[i],visits[i+1]);
    }
    return totaldistance;
}

ostream &operator<<(ostream &output, const Tour &tour) {
    output<<"tour #"<<tour.id<<" ";
    for (City city:tour.visits) {
        output << city.name <<"|";
    }
    output<<" fitness: " <<tour.fitness;

    return output;
}

void Tour::setTour(vector<City> visits) {
    this->visits = visits;
}

void Tour::calculateFitness() {
    fitness = FITNESS_SCALAR/getTourDistance();
}

bool Tour::operator==(const Tour &rhs) const {
    return(this->id == rhs.id);
}

bool Tour::operator<(const Tour &rhs) const {
    return (this->fitness == rhs.fitness)? (this->id>rhs.id) : (this->fitness<rhs.fitness);
}


