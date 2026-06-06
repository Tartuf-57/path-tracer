#ifndef SPHERE_H
#define SPHERE_H

class sphere : virtual public hittable {
private:
    point3 center;
    double radius;
    std::shared_ptr<material> mat;
public:
    sphere(const point3& center, const double radius, shared_ptr<material> mat) : center(center), radius(std::fmax(0.0,radius)), mat(mat) {}
    bool hit (const ray& r, interval ray_t, hit_record& rec) const override {
        vec3 oc = r.origin() - center;
        double a = r.direction().length_squared();
        double h = dot(r.direction(), oc);
        double c = oc.length_squared() - radius*radius;
        double discriminant = h*h - a*c;
        if (discriminant < 0) {return false;}

        auto sqrtd = std::sqrt(discriminant);

        // we have to find that nearest root (camera facing) that lies in range [tmin,tmax]
        auto root = (-h - sqrtd)/a;
        if (!ray_t.surrounds(root)) {
            root = (-h+sqrtd)/a;
            if (!ray_t.surrounds(root)) {
                return false;
            }
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        auto outward_normal = (rec.p - center)/radius;
        rec.set_face_normal(r, outward_normal);
        rec.mat = mat;
        return true;
    } 
    
};

#endif
