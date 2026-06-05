#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "interval.h"

using color = vec3;

inline double linear_to_gamma(double linear_component){
    if (linear_component > 0)
        return std::sqrt(linear_component);

    return 0;
}

void write_color (std::ostream& out, const color& pixel) {
    auto r = pixel.x();
    auto g = pixel.y();
    auto b = pixel.z();

    // Apply a linear to gamma transform for gamma 2
    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    // [0,1] -> byte range
    static interval intensity(0.000,0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));
    // pixel dimensions from 0 to 1

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';   
}

#endif
