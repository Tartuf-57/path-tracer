#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

using color = vec3;

void write_color (std::ostream& out, const color& pixel) {
    auto r = pixel.x();
    auto g = pixel.y();
    auto b = pixel.z();

    // [0,1] -> byte range
    static interval intensity(0.000,0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));
    // pixel dimensions from 0 to 1

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';   
}

#endif
