#include <math.h>
#include "coordinate.h"

double distance(Coordinate *from, Coordinate *to){
    int x_diff, y_diff;
    x_diff = from->x - to->x;
    y_diff = from->y - to->y;
    return sqrt(pow(x_diff, 2) + pow(y_diff, 2));
}

Coordinate* new_coordinate(int x, int y){
    Coordinate *c = (Coordinate*) malloc(sizeof(Coordinate));
    c->x = x;
    c->y = y;
    return c;
}