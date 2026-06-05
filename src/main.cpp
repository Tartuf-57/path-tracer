#include "common.h"
#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

int main () {    

    camera cam;
    cam.img_width = 400;
    cam.aspect_ratio = 16.0/10.0;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.4));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    cam.render(world);

    return 0;
}
