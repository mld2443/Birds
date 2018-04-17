///////////////////////////////////////////////
//  float3.h                                 //
//  Birds                                    //
//                                           //
//  Created by Matthew Dillard on 10/15/15.  //
///////////////////////////////////////////////

#ifndef float3_h
#define float3_h

//////////////
// Includes //
//////////////

#include <random>
#include <math.h>


///////////////
// Constants //
///////////////

#define PI 3.141592653589793


//////////////////////
// Class defenition //
//////////////////////

/// A vector of 3 floatting point values
class float3 {
private:
    // RNG for random unit vectors
    inline static auto urd = std::uniform_real_distribution<float>(-1.f,1.f);
    inline static auto eng = std::default_random_engine();

public:
    float x,y,z;
    
    // Constructor
    float3(const float xx = 0.f, const float yy = 0.f, const float zz = 0.f);
    
    // Random vectors
    float3 static random_in_unit_sphere();
    float3 static random_on_unit_sphere();

    // Operators
    float3& operator =(const float3& a);
    float3 operator +=(const float3& a);
    float3 operator -=(const float3& a);
    float3 operator +(const float3& a) const;
    float3 operator -(const float3& a) const;
    float3 operator *(const float3& a) const;
    float3 operator *(const float& a) const;
    float3 operator /(const float& a) const;
    bool operator ==(const float3& v) const;
    
    // Unary Vector operations
    float abs() const;
    float3 normalize() const;
    
    // Binary vector operations
    float dot(const float3& a) const;
    float3 cross(const float3& a) const;
    float angle(const float3& v_2) const;
    
    // Rotations
    float3 rotateX(const float theta) const;
    float3 rotateY(const float theta) const;
    float3 rotateZ(const float theta) const;
};

#endif /* float3_h */
