#ifndef INTERVAL_H
#define INTERVAL_H

#include "common.h"

class interval {
public:
    double max, min;

    interval() : min(inf), max(-inf) {} // starts as empty interval
    
    interval (double x, double y) : min(x), max(y) {}

    double size(){
        return max - min;
    }

    bool contains(double x) {
        return (x>=min && x<=max);
    }
    bool surrounds(double x) {
        return (x>min && x < max);
    }

    double clamp (double x) {
        if (x < min) {return min;}
        if (x > max) {return max;}
        return x;
    }

    static const interval empty, universe;
};

const interval interval::empty = interval(inf,-inf);
const interval interval::universe = interval(-inf,inf);

#endif
