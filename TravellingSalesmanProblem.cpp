//
// Created by Reneil Pascua on 2019-11-22.
//

#include "TravellingSalesmanProblem.hpp"

TravellingSalesmanProblem::TravellingSalesmanProblem(int populationSize, int citiesInTour, int shuffle, int iterations,
                                                     int mapBoundary, int parentPoolSize, double mutationRate,
                                                     int numberOfParents, double improvementThreshold)
        : POPULATION_SIZE(populationSize), CITIES_IN_TOUR(citiesInTour), SHUFFLE(shuffle), ITERATIONS(iterations),
          MAP_BOUNDARY(mapBoundary), PARENT_POOL_SIZE(parentPoolSize), MUTATION_RATE(mutationRate),
          NUMBER_OF_PARENTS(numberOfParents), IMPROVEMENT_THRESHOLD(improvementThreshold) {


    nTours=0;
    thresholdreached = false;
    generateRandomCities();
    generateRandomTours();
    populateFitnesses();
}

TravellingSalesmanProblem::TravellingSalesmanProblem(int populationSize, int shuffle, int iterations,
                                                     int parentPoolSize, double mutationRate,
                                                     int numberOfParents, double improvementThreshold, vector<City> userCities)
        : POPULATION_SIZE(populationSize), SHUFFLE(shuffle), ITERATIONS(iterations),
          PARENT_POOL_SIZE(parentPoolSize), MUTATION_RATE(mutationRate),
          NUMBER_OF_PARENTS(numberOfParents), IMPROVEMENT_THRESHOLD(improvementThreshold) {


    nTours=0;
    thresholdreached = false;

    cities = userCities;
    CITIES_IN_TOUR=userCities.size();
    MAP_BOUNDARY=0; // don't care about map boundary if user-defined cities/locations

    generateRandomTours();
    populateFitnesses();
}


void TravellingSalesmanProblem::solve() {
    cout << "\n===== solving... =============================" << endl;

// setup
    base_fitness = findElite();
    Tour basetour = *(tours.end()-1);
    base_average_fitness = getAverageFitness();
    double highestFitness = base_fitness;
    double prevHighest=0;
    double prevAverage=0;
    cout << "base fitness: "<<base_fitness<<endl<<endl;

// begin to iterate generation to generation
    int numIterations=0;
    while (numIterations<ITERATIONS) {
        if (highestFitness/base_fitness > IMPROVEMENT_THRESHOLD) {
            thresholdreached=true;
            break;
        }
        prevHighest = highestFitness;
        prevAverage = getAverageFitness();
        cout << "===== begin iteration "<<numIterations<<" with previous highest fitness = "<<fixed<<setprecision(7)<<prevHighest << endl;
        // crossover -- mix routes and overwrite the first POPULATION_SIZE-1 tours
//        cout << "crossover..." << endl;
        crossoverPhase();
        // mutation -- select subset of non-elite tours and mutate them
//        cout << "mutation..." << endl;
        mutationPhase();
        // evaluation -- after mutation, the TSP must re-poll fitnesses
//        cout << "evaluation..." << endl;
        populateFitnesses();
        // selection -- move elite to the back and do not touch until next generation
//        cout << "selection..."<<endl;
        highestFitness = findElite();
        // report -- output details of this iteration
        report(highestFitness, prevHighest,prevAverage);

        numIterations++;

//        // interim check:
//        if (numIterations%5==0)printTours();
    }


    // final print of the tours
    cout<<"\n\nFINAL REPORT:\n\n"<<endl;
    printTours();
    cout<<endl;
    report(highestFitness,prevHighest,prevAverage);

    cout<<"elite tour:"<<fixed<<setprecision(7)<<endl;
    cout<< *(tours.end()-1) <<endl;
    cout << "base tour:"<<endl;
    cout<<basetour<<endl;

    cout<<fixed<<setprecision(3);
    double impThr = convertToPercent(IMPROVEMENT_THRESHOLD);
    if (thresholdreached) {
        cout<<"\n-- improvement threshold of "<<impThr<<"% reached at iteration "<<--numIterations << " --"<<endl;
    } else {
        cout<<"\n-- improvement threshold of "<<impThr<<"% NOT reached by iteration "<<--numIterations << " --"<<endl;
    }

}

void TravellingSalesmanProblem::generateRandomCities() {
    srand(time(NULL));
    string name;
    int x;
    int y;

    for (int i=0; i<CITIES_IN_TOUR; i++) {
        name = to_string(i);
        x = rand()%MAP_BOUNDARY;
        y = rand()%MAP_BOUNDARY;
        cities.push_back(City(name,x,y));
    }
}



void TravellingSalesmanProblem::generateRandomTours() {
    srand(time(NULL));
    for (int i=0; i<POPULATION_SIZE; i++) {
        shuffleCities((rand()));
        tours.push_back(Tour(nTours++,cities));
    }
}

void TravellingSalesmanProblem::shuffleCities(int seed) {
    srand(seed+time(NULL));
    int a,b;
    for (int i=0; i<SHUFFLE; i++) {
        a = rand()%cities.size();
        b = rand()%cities.size();
        City temp = cities[a];
        cities[a] = cities[b];
        cities[b] = temp;
    }
}

void TravellingSalesmanProblem::populateFitnesses() {
    fitnesses.clear();
    for (Tour tour:tours) {
        fitnesses.push_back(tour.fitness);
    }
}

double TravellingSalesmanProblem::findElite() {
    auto it = tours.begin();
    auto highestPos = tours.begin();
    double highestFitness = it->fitness;
    for (; it!=tours.end(); it++) {
//        if (it->fitness > highestFitness) {
//            highestFitness = it->fitness;
//            highestPos = it;
//        }

        if (*highestPos < *it) {
            highestFitness = it->fitness;
            highestPos=it;
        }
    }

    Tour eliteTour = *highestPos;
    tours.erase(highestPos);
    tours.push_back(eliteTour);

    return highestFitness;
}

void TravellingSalesmanProblem::crossoverPhase() {
    srand(time(NULL));
    vector<Tour> newGeneration;
    set<Tour> parentPool;
    set<Tour> chosenParents;
    for (int i=0; i<POPULATION_SIZE-1; i++) { // -1 because saving the elite

        chosenParents.clear();
        //cout << "attempting to find "<<NUMBER_OF_PARENTS<<" parents..." <<endl;
        while (chosenParents.size()<NUMBER_OF_PARENTS) {
            parentPool.clear();
            //cout << "attempting to group "<<PARENT_POOL_SIZE<<" parents into a pool" <<endl;
            while (parentPool.size()<PARENT_POOL_SIZE) {
                parentPool.insert(tours[rand()%POPULATION_SIZE]);
            }
            // choose the most fit from this pool
            auto mostEliteItr = parentPool.end();
            mostEliteItr--;
            chosenParents.insert(*mostEliteItr);
        }

        newGeneration.push_back(cross(chosenParents, (rand())));
    }

    // copy the new generation into tours vector
    for (int i=0; i<newGeneration.size(); i++) {
        tours[i] = newGeneration[i];
    }
}

Tour TravellingSalesmanProblem::cross(const set<Tour>& parents, int seed) {
    srand(seed+time(NULL));
    int N = parents.size();
    vector<City> newVisits;

    auto parentsItr = parents.begin();
    auto lastParent = parents.end();
    lastParent--;
    // iterate until last parent
    for (; parentsItr!=lastParent; parentsItr++) {
        int citiesLeftToVisit = CITIES_IN_TOUR - newVisits.size();
        if (citiesLeftToVisit == 0) {
            break;
        } else {
            int numCitiesToCopy = rand()%citiesLeftToVisit + 1;
            copyCities(parentsItr->visits, newVisits, numCitiesToCopy);
        }
    }

    // fill the rest w last parent's stuff
    copyCities(lastParent->visits, newVisits, CITIES_IN_TOUR-newVisits.size());

    return Tour(nTours++,newVisits);
}

void TravellingSalesmanProblem::copyCities(const vector<City> &src, vector<City> &dest, int N) {

    if (N<=0) return;

    // create an unordered set of destination city names, to easily check if a city has already been visited
    unordered_set<string> citiesAlreadyVisited_Names;
    auto destItr = dest.begin();
    for (; destItr != dest.end(); destItr++) {
        citiesAlreadyVisited_Names.insert(destItr->name);
    }

    int numCopied=0;
    auto srcItr = src.begin();
    //cout << "attempting to copy "<<N<<" cities..." << endl;
    while (numCopied<N) {
        if (citiesAlreadyVisited_Names.find(srcItr->name) == citiesAlreadyVisited_Names.end()) { // if city isnt found
            dest.push_back(*srcItr);
            citiesAlreadyVisited_Names.insert(srcItr->name);
            numCopied++;
        }

        // set the next iteration to look at the next city, or loop back
        srcItr++;
        if (srcItr==src.end()) {
            srcItr=src.begin();
        }
    }
}

void TravellingSalesmanProblem::mutationPhase() {
    int nMutateTours = floor(POPULATION_SIZE * MUTATION_RATE_TOURS);
    // the front n tours will be mutated.
    // note: if MUTATION_RATE_TOURS==1, elite will also be mutated
    srand(time(NULL));
    for (int i=0; i<nMutateTours; i++) {
        int mutateIndex = rand()%(POPULATION_SIZE-1); //popsize -1 because not mutating elite
        mutate(tours[mutateIndex],(rand()));
    }
}

void TravellingSalesmanProblem::mutate(Tour &t, int seed) {
    srand(seed+time(NULL));
    double mutationRate;
    auto itr = t.visits.begin();
    for (; itr!=t.visits.end(); itr++) {
        mutationRate = rand()%1000 /1000.0;
        if (mutationRate<MUTATION_RATE) {
            City temp = *itr;
            int moveLeft = rand()%2;
            if (moveLeft) {
                if (itr!=t.visits.begin()) {
                    *itr = *(itr-1);
                    *(itr-1) = temp;
                } else {
                    *itr = *(itr+1);
                    *(itr+1) = temp;
                }
            } else {
                if (itr!=t.visits.end()-1) {
                    *itr = *(itr+1);
                    *(itr+1) = temp;
                } else {
                    *itr = *(itr-1);
                    *(itr-1) = temp;
                }
            }
        }
    }

    // once the tour is mutated, it should recalculate its fitness
    t.calculateFitness();
}


void TravellingSalesmanProblem::printCities() {
    cout << "cities: "<<endl;
    for (City city:cities) {
        cout << city;
    }
}

void TravellingSalesmanProblem::report(double highestFitness, double prevHighest,double prevAvg) {
    double avg = getAverageFitness();
    cout << fixed << setprecision(7) <<"new highest fitness:\t"<< highestFitness <<endl;
    cout << "new average fitness:\t" << avg << endl;
    cout << fixed << setprecision(3) << "improvement of highest / previous:\t" << convertToPercent(highestFitness/prevHighest) <<"%"<< endl;
    cout << "improvement of highest / base:\t\t" << convertToPercent(highestFitness/base_fitness) <<"%"<< endl;
    cout << "improvement of average / previous:\t" << convertToPercent(avg/prevAvg) <<"%"<< endl;
    cout << "improvement of average / base:\t\t" << convertToPercent(avg/base_average_fitness) <<"%"<< endl << endl;
}

void TravellingSalesmanProblem::printTours() {
    cout << fixed << setprecision(7) << "tours: "<<endl;
    for (Tour tour:tours) {
        cout << tour<<endl;
    }
}

double TravellingSalesmanProblem::getAverageFitness() {
    double sum=0;
    int count=0;
    for (double fitness:fitnesses) {
        sum+=fitness;
        count++;
    }
    return sum/count;
}

double TravellingSalesmanProblem::convertToPercent(double improvementfactor) {
    return (improvementfactor-1.0)*100;
}













