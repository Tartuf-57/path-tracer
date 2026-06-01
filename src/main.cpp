#include <iostream>
#include "vec3.h"
#include "color.h"

int main () {
    int img_width = 256;
    int img_height = 256;
    
    std::cout << "P3\n" << img_width   << " " << img_height << "\n255\n";

    for (int i = 0; i < img_height ; i++) {
        std::clog << "\rScanlines remaining: " << (img_height - i) << ' ' << std::flush;
        for (int j = 0; j < img_width; j++) {
            auto pixel_color = color(double(i)/(img_width-1), double(j)/(img_height-1), 0);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone.                 \n";
    return 0;
}
