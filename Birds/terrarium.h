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


///////////////
// Constants //
///////////////

// Light colors and positions
const GLfloat light0color[] = { 0.9f, 0.9f, 0.8f };
const GLfloat light0pos[] = { 5000.f, 10000.f, 5000.f };
const GLfloat light1color[] = { 0.4f, 0.4f, 0.2f };
const GLfloat light1pos[] = { 300.f, 300.f, 300.f };

// Grass colors
const GLfloat gnd_ambient[] = { 0.2f, 0.4f, 0.2f };
const GLfloat gnd_diffuse[] = { 0.f, 0.2f, 0.f };
const GLfloat gnd_specular[] = { 0.f, 0.f, 0.f };
const GLfloat gnd_shininess[] = { 0.f };

// Water colors
const GLfloat water_ambient[] = { 0.2f, 0.2f, 0.3f };
const GLfloat water_diffuse[] = { 0.1f, 0.1f, 0.3f };
const GLfloat water_specular[] = { 0.5f, 0.5f, 1.f };
const GLfloat water_shininess[] = { 10.f };

// Rock colors
const GLfloat rock_ambient[] = { 0.2f, 0.2f, 0.2f };
const GLfloat rock_diffuse[] = { 0.9f, 0.9f, 0.9f };
const GLfloat rock_specular[] = { 0.5f, 0.5f, 0.5f };
const GLfloat rock_shininess[] = { 1.f };


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
