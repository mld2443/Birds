////////////////////////////////////////////////////////////////
//  bird.h                                                    //
//  Birds                                                     //
//                                                            //
//  Created by Matthew Dillard on 10/14/15.                   //
////////////////////////////////////////////////////////////////

#ifndef bird_h
#define bird_h

//////////////
// Includes //
//////////////

#include <GLUT/GLUT.h>
#include <OpenGL/gl.h>
#include <list>
#include "float3.h"

///////////////
// Constants //
///////////////

// The ultimate influence radii, boids further apart than this do not interact
#define R1 20.f
#define R2 50.f

// The angles of theta for the birds vision, foveal and peripheral
#define T1 15.f
#define T2 170.f

// Threshold
#define THR 0.01f

//////////////////////
// Class defenition //
//////////////////////

/// The boids of this simulation, represented by little paper airplanes
class bird {
private:
    float3 m_pos, m_vel, m_accel;
    float m_mass;
    
    float3 get_wind(const float3 wind);
    
    float d_coef(const float d) const;
    float t_coef(const float angle) const;
    
    void aggregate(float3 final_a, float3 final_v, float3 final_c, float a_res);
    
public:
    bird(float3 p = float3(), float3 v = float3(), float m = 1.f);
    
    float3 get_pos() const;
    float3 get_vel() const;
    
    void calc_velocity(const std::list<bird*> &nearby,
                       const float ka, const float kv, const float kc, const float a_res,
                       const float3 wind, const float windc,
                       const float3 f_p, const float3 f_v, const float s_tan,
                       float3 goal,
                       const float t);
    
    void integrate(const double t);
    
    void draw() const;
};

#endif /* bird_h */
