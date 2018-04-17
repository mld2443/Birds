//////////////////////////////////////////////
//  float3.cpp                              //
//  Birds                                   //
//                                          //
//  Created by Matthew Dillard on 4/17/18.  //
//////////////////////////////////////////////

#include "float3.h"


/// Constructor
float3::float3(const float xx, const float yy, const float zz) : x(xx), y(yy), z(zz) {}

/// Returns a point with a uniform random distribution centered at the origin.
/// Can be outside the unit sphere.
float3 float3::random_in_unit_sphere() {
    return float3(urd(eng), urd(eng), urd(eng));
}

/// Returns a random point on the unit sphere.
float3 float3::random_on_unit_sphere() {
    return random_in_unit_sphere().normalize();
}

/// Copy assignment operator
float3& float3::operator =(const float3& a) {
    x = a.x;
    y = a.y;
    z = a.z;
    return *this;
}

/// Increment operator
float3 float3::operator +=(const float3& a) {
    x += a.x;
    y += a.y;
    z += a.z;
    return *this;
}

/// Decrement operator
float3 float3::operator -=(const float3& a) {
    x -= a.x;
    y -= a.y;
    z -= a.z;
    return *this;
}

/// Addition operator
float3 float3::operator +(const float3& a) const {
    return {x+a.x, y+a.y, z+a.z};
}

/// Subtraction operator
float3 float3::operator -(const float3& a) const {
    return {x-a.x, y-a.y, z-a.z};
}

/// In-line Multiplication operator
float3 float3::operator *(const float3& a) const {
    return {x*a.x, y*a.y, z*a.z};
}

/// Scaling operator
float3 float3::operator *(const float& a) const {
    return {x*a, y*a, z*a};
}

/// Scaling operator
float3 float3::operator /(const float& a) const {
    return {x/a, y/a, z/a};
}

/// Equality operator
bool float3::operator ==(const float3& v) const {
    return (x == v.x && y == v.y && z == v.z);
}

/// Magnitude, returns distance of given vector
float float3::abs() const {
    return sqrtf(x*x + y*y + z*z);
}

/// Normalization, returns direction of given vector
float3 float3::normalize() const {
    float len = abs();
    return float3(x/len, y/len, z/len);
}

/// Returns dot product of two vectors
float float3::dot(const float3& a) const {
    return x*a.x + y*a.y + z*a.z;
}

/// Returns cross product of two vectors
float3 float3::cross(const float3& a) const {
    return {y*a.z - z*a.y, z*a.x - x*a.z, x*a.y - y*a.x};
}

/// Returns degree angle between two vectors
float float3::angle(const float3& v_2) const {
    float a = abs();
    float b = v_2.abs();
    return (180.0f/PI) * acosf(dot(v_2)/(a * b));
}

/// 3D rotation in the YZ-plane
float3 float3::rotateX(const float theta) const {
    float cosT = cosf(theta * PI/180.0f);
    float sinT = sinf(theta * PI/180.0f);
    return float3(x, y * cosT - z * sinT, y * sinT + z * cosT);
}

/// 3D rotation in the XZ-plane
float3 float3::rotateY(const float theta) const {
    float cosT = cosf(theta * PI/180.0f);
    float sinT = sinf(theta * PI/180.0f);
    return float3(x * cosT + z * sinT, y, z * cosT - x * sinT);
}

/// 3D rotation in the XY-plane
float3 float3::rotateZ(const float theta) const {
    float cosT = cosf(theta * PI/180.0f);
    float sinT = sinf(theta * PI/180.0f);
    return float3(x * cosT - y * sinT, x * sinT + y * cosT, z);
}
