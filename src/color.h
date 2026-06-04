#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

using color = vec3;

void write_color (std::ostream& out, const color& pixel) {
    auto r = pixel.x();
    auto g = pixel.y();
    auto b = pixel.z();

    int rb = int(255.999 * r);
    int gb = int(255.999 * g);
    int bb = int(255.999 * b);

    // pixel dimensions from 0 to 1

    out << rb << ' ' << gb << ' ' << bb << '\n';   
}

#endif
