#ifndef COORDINATE_H
#define COORDINATE_H

#include <stdlib.h>

typedef struct _coordinate {
    int x, y;
} Coordinate;

double distance(Coordinate *from, Coordinate *to);
Coordinate* new_coordinate(int x, int y);

#endif