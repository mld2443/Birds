///////////////////////////////////////////////
//  terrarium.h                              //
//  Birds                                    //
//                                           //
//  Created by Matthew Dillard on 10/12/15.  //
///////////////////////////////////////////////

#ifndef terrarium_h
#define terrarium_h

//////////////
// Includes //
//////////////

#include <GLUT/GLUT.h>
#include <OpenGL/gl.h>
#include <vector>

#include "grid.h"
#include "flock.h"


//////////////////////
// Class Defenition //
//////////////////////

/// Creates the environment for the boids to fly around in and spawns the flocks themselves
class terrarium {
private:
    float boxxl, boxxh, boxyl, boxyh, boxzl, boxzh;
    float ldepth, lwidth, rdepth, rwidth;
    //GLUquadricObj *quadric;
    
    float3 wind;
    float windc;
    grid airspace;
    std::vector<flock> flocks;
    
    void draw_lights() const;
    void draw_ground() const;
    //void draw_tree(const float x, const float y, const float z);
    void draw_rock(const int x, const int y, const int z, const float h, const int w, const int l, const int r) const;
    
public:
    terrarium();
    
    void step(const float t);
    
    void draw() const;
    
    float3 camera_pos(unsigned int f) const;
    float3 camera_dir(unsigned int f) const;
};

#endif /* terrarium_h */
