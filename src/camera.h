#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"

class camera {
private:
    int img_height;
    point3 center;
    point3 pixel00_loc;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;
    double pixel_sample_scale;

    vec3 sample_square () const {
        return vec3(random_double() - 0.5, random_double() + 0.5, 0);
    }

    ray get_ray(int i, int j) const {
        auto offset = sample_square();
        auto pixel_sample = pixel00_loc + (i + offset.x())*pixel_delta_u  + (j + offset.y())*pixel_delta_v;
        auto ray_origin = center;
        auto ray_direction = pixel_sample - ray_origin;
        return ray(ray_origin, ray_direction);
    }

    void initialize() {
        img_height = img_width/aspect_ratio;
        img_height = (img_height < 1) ? 1 : img_height;

        pixel_sample_scale = 1.0/samples_per_pixel;

        center = point3(0,0,0);

        //viewport dimensions
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (double(img_width)/img_height);

        // camera set up
        auto focal_length = 1.0;

        // vectors along viewport
        auto viewport_u = vec3(viewport_width,0,0);
        auto viewport_v = vec3(0,-viewport_height,0);

        // delta vectors
        pixel_delta_u = viewport_u/img_width;
        pixel_delta_v = viewport_v/img_height;

        //upper left data
        auto viewport_upper_left = center - vec3(0,0,focal_length) - (viewport_u + viewport_v)/2;
        auto pixel00_loc = viewport_upper_left + 0.5*(pixel_delta_u + pixel_delta_v); 
    }

    color ray_color(const ray& r, const hittable& world) const {
        hit_record rec;
        if (world.hit(r, interval(0,inf), rec)) {
            return 0.5 * (rec.normal + color(1,1,1)); // 0.5 for max limits and smooth gradients
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = (unit_direction.y() + 1.0)*0.5;
        return (1.0-a) * color(1.0,1.0,1.0) + a * color(0.5,0.7,1.0);
    }

public:
    double aspect_ratio = 16.0/10.0;
    int img_width = 400;
    int samples_per_pixel;

    void render(const hittable& world) {
        initialize();
        std::cout << "P3\n" << img_width   << " " << img_height << "\n255\n";

        for (int i = 0; i < img_height ; i++) {
            std::clog << "\rScanlines remaining: " << (img_height - i) << ' ' << std::flush;
            for (int j = 0; j < img_width; j++) {
                color pixel_color(0,0,0);
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    ray r = get_ray(i,j);
                    pixel_color += ray_color(r,world);
                }
                write_color(std::cout, pixel_sample_scale * pixel_color); // average of all pixels in .5 radius
            }
        }
        std::clog << "\rDone.                 \n";
    }
};

#endif