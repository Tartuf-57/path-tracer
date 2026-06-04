#include <iostream>
#include "vec3.h"
#include "ray.h"
#include "color.h"
#include "hittable.h"
#include "sphere.h"
#include "hittable_list.h"

using std::make_shared;
using std::shared_ptr;

const double inf = std::numeric_limits<double>::infinity() - 1.0; //useful for platforms
const double pi = 3.1415926535897932385;
inline double degrees_to_radians (double degrees) {
    return degrees * pi / 180.0;
}

color ray_color (const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, 0, inf, rec)) {
        return 0.5 * (rec.normal + color(1,1,1)); // 0.5 for max limits and smooth gradients
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = (unit_direction.y() + 1.0)*0.5;
    return (1.0-a) * color(1.0,1.0,1.0) + a * color(0.5,0.7,1.0);
}

int main () {
    auto aspect_ratio = 16.0/10.0;
    int img_width = 400;
    
    //to calculate image height
    auto img_height = img_width/aspect_ratio;
    img_height = (img_height < 1) ? 1 : img_height;

    //viewport dimensions
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(img_width)/img_height);

    // camera set up
    auto focal_length = 1.0;
    auto camera_center = point3(0,0,0);

    // vectors along viewport
    auto viewport_u = vec3(viewport_width,0,0);
    auto viewport_v = vec3(0,-viewport_height,0);

    // delta vectors
    auto pixel_delta_u = viewport_u/img_width;
    auto pixel_delta_v = viewport_v/img_height;

    //upper left data
    auto viewport_upper_left = camera_center - vec3(0,0,focal_length) - (viewport_u + viewport_v)/2;
    auto pixel00_loc = viewport_upper_left + 0.5*(pixel_delta_u + pixel_delta_v); 

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.4));
    world.add(make_shared<sphere>(point3(0, -1000.0 -0.5, -1), 1000));

    // now we render


    std::cout << "P3\n" << img_width   << " " << img_height << "\n255\n";

    for (int i = 0; i < img_height ; i++) {
        std::clog << "\rScanlines remaining: " << (img_height - i) << ' ' << std::flush;
        for (int j = 0; j < img_width; j++) {
            auto pixel_center = pixel00_loc + (j*pixel_delta_u) + (i*pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);
            color pixel_color = ray_color(r,world);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone.                 \n";
    return 0;
}
