//
// Created by Reneil Pascua on 2019-11-22.
//

#include "City.hpp"

City::City(string name, int x, int y):name(name),x(x),y(y) {}

ostream &operator<<( ostream &output, const City& city ) {
    output << city.name << " at (" << city.x << ", " << city.y << ")" << endl;
    return output;
}

bool City::operator==(const City &rhs) const {
    return (this->name == rhs.name);
}
