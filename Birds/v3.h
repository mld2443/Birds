//
//  v3.h
//  Birds
//
//  Created by Matthew Dillard on 10/15/15.
//  self explainatory
//

#ifndef v3_h
#define v3_h

#include <math.h>

#define PI 3.141592653589793

template <class T>
class v3 {
public:
    T x,y,z;
    
    v3(const T xx = 0.0, const T yy = 0.0, const T zz = 0.0) : x(xx), y(yy), z(zz) {}
    
    v3<T>& operator =(const v3<T>& a) {
        x = a.x;
        y = a.y;
        z = a.z;
        return *this;
    }
    
    v3<T> operator +=(const v3<T>& a) {
        x += a.x;
        y += a.y;
        z += a.z;
        return *this;
    }
    
    v3<T> operator -=(const v3<T>& a) {
        x -= a.x;
        y -= a.y;
        z -= a.z;
        return *this;
    }
    
    v3<T> operator +(const v3<T>& a) const {
        return {x+a.x, y+a.y, z+a.z};
    }
    
    v3<T> operator -(const v3<T>& a) const {
        return {x-a.x, y-a.y, z-a.z};
    }
    
    v3<T> operator *(const v3<T>& a) const {
        return {x*a.x, y*a.y, z*a.z};
    }
    
    v3<T> operator *(const T& a) const {
        return {x*a, y*a, z*a};
    }
    
    v3<T> operator /(const T& a) const {
        return {x/a, y/a, z/a};
    }
    
    double abs() const {
        return sqrt(x*x + y*y + z*z);
    }
    
    v3<T> normalize() const {
        double len = abs();
        return v3<T>(x/len, y/len, z/len);
    }
    
    double dot(const v3<T>& a) const {
        return x*a.x + y*a.y + z*a.z;
    }
    
    double angle(const v3<T>& v_2) const {
        double a = abs();
        double b = v_2.abs();
        return (180.0/PI) * acos(dot(v_2)/(a * b));
    }
    
    v3<T> cross(const v3<T>& a) const {
        return {y*a.z - z*a.y, z*a.x - x*a.z, x*a.y - y*a.x};
    }
    
    bool operator ==(const v3<T>& v) const {
        return (x == v.x && y == v.y && z == v.z);
    }
    
    v3<T> rotateX(const float theta) const {
        double cosT = cos(theta * PI/180);
        double sinT = sin(theta * PI/180);
        return v3<T>(x, y * cosT - z * sinT, y * sinT + z * cosT);
    }
    
    v3<T> rotateY(const float theta) const {
        double cosT = cos(theta * PI/180);
        double sinT = sin(theta * PI/180);
        return v3<T>(x * cosT + z * sinT, y, z * cosT - x * sinT);
    }
    
    v3<T> rotateZ(const float theta) const {
        double cosT = cos(theta * PI/180);
        double sinT = sin(theta * PI/180);
        return v3<T>(x * cosT - y * sinT, x * sinT + y * cosT, z);
    }
};

#endif /* v3_h */
