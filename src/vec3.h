#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class vec3 {
public:
    double e[3];

    vec3 () : e{0,0,0} {}
    vec3 (double e0, double e1, double e2) : e{e0,e1,e2} {}

    double x() const {return e[0];}
    double y() const {return e[1];}
    double z() const {return e[2];}

    vec3 operator-() const {
        return vec3(-e[0], -e[1], -e[2]);
    }
    double operator[] (int i) const {
        return e[i];
    }
    double& operator[] (int i) {
        return e[i];
    }
    vec3& operator+= (const vec3& v) {
        e[0] += v.x();
        e[1] += v.y();
        e[2] += v.z();
        return *this;
    }
    vec3& operator*= (const double k) {
        e[0] *= k;
        e[1] *= k;
        e[2] *= k;
        return *this;
    }
    vec3& operator/= (const double k) {
        return *this *= (1/k);
    }
    
    double length_squared () const {
        return (e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
    }
    double length () const {
        return std::sqrt(length_squared());
    }
    
};

// alias for position vector
using point3 = vec3;

inline std::ostream& operator<< (std::ostream &out, const vec3& v) {
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

inline vec3 operator+ (const vec3& v1, const vec3& v2) {
    return vec3(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
}

inline vec3 operator- (const vec3& v1, const vec3& v2) {
    return vec3(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
}

inline vec3 operator* (const vec3& v1, const vec3& v2) {
    return vec3(v1.x() * v2.x(), v1.y() * v2.y(), v1.z() * v2.z());
}

inline vec3 operator* (const vec3& v1, const double k) {
    return vec3(v1.x() * k, v1.y() * k, v1.z() * k);
}

inline vec3 operator* (const double k, const vec3& v1) {
    return v1 * k;
}

inline vec3 operator/ (const vec3& v1, const double k) {
    return v1 * (1/k);
}

inline double dot (const vec3& u, const vec3& v) {
    return (u.x()*v.x() + u.y()*v.y() + u.z()*v.z());
}

inline vec3 cross (const vec3&u, const vec3&v) {
    return vec3(u.y() * v.z() - u.z() * v.y(),
                u.z() * v.x() - u.x() * v.z(),
                u.x() * v.y() - u.y() * v.x());
}

inline vec3 unit_vector (const vec3& v) {
    return v/v.length();
}

#endif
