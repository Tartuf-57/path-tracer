#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"

class material {
public:
    virtual ~material() = default;
    
    virtual bool scatter (const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
        return false;
    }
};

class lambertian : virtual public material {
private:
    color albedo;
public:
    lambertian(const color& alb) : albedo(alb){}

    bool scatter (const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        auto scatter_direction = rec.normal + random_unit_vector();
        if (scatter_direction.near_zero()) {
            scatter_direction = rec.normal;
        }
        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }
};

class metal : virtual public material {
private:
    color albedo;
    double fuzz;
public:
    metal (const color& alb, double f = 0.0) : albedo(alb), fuzz(f < 1 ? f : 1) {}

    bool scatter (const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        auto reflected = reflect(r_in.direction(), rec.normal);
        auto scattered_direction = unit_vector(reflected) + fuzz * random_unit_vector();
        scattered = ray(rec.p, scattered_direction);
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }
};

#endif