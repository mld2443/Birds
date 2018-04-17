///////////////////////////////////////////////
//  flock.h                                  //
//  Birds                                    //
//                                           //
//  Created by Matthew Dillard on 10/14/15.  //
///////////////////////////////////////////////

#ifndef flock_h
#define flock_h

//////////////
// Includes //
//////////////

#include <list>
#include <math.h>
#include <stdlib.h>

#include "grid.h"


///////////////
// Constants //
///////////////

const GLfloat darkgrey[] = { 0.2, 0.2, 0.2 };
const GLfloat grey[] = { 0.6, 0.6, 0.6 };
const GLfloat white[] = { 1.0, 1.0, 1.0 };


//////////////////////
// Class Defenition //
//////////////////////

/// Common group of boids, all spawned at once.
class flock {
private:
    /// Birds spawned by this flock
    std::list<bird> birds;
    
    float k_a, k_v, k_c;
    float3 wind, goal;
    float windc, s_tan;
    float a_res;
    
public:
    // Constructor
    flock(grid &g, const unsigned long size,
          const float x, const float y, const float z,
          const float d,
          const float ka, const float kv, const float kc, const float ar,
          float3 goal_,
          float3 w = float3(), float wc = 0.f,
          float3 v = float3(), float s_t = 0.f,
          const float is_t = 0.f);
    
    // Simulation
    void calc_velocities(grid &g, const int radius, const float t);
    void integrate(const float t);
    
    // Getters
    unsigned long get_size() const;
    float3 get_center() const;
    float3 get_vel() const;
    
    // OpenGL
    void draw() const;
};

#endif /* flock_h */
