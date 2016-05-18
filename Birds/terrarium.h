//
//  terrarium.h
//  Birds
//
//  Created by Matthew Dillard on 10/12/15.
//  this class is really only to make my main file manageable
//

#ifndef terrarium_h
#define terrarium_h

#include <GLUT/GLUT.h>
#include <OpenGL/gl.h>
#include <vector>
#include "grid.h"
#include "flock.h"

using namespace std;

class terrarium{
private:
    float boxxl, boxxh, boxyl, boxyh, boxzl, boxzh;
    float ldepth, lwidth, rdepth, rwidth;
    //GLUquadricObj *quadric;
    
    v3<double> wind;
    double windc;
    grid airspace;
    vector<flock> flocks;
    
    void draw_lights();
    void draw_ground();
    //void draw_tree(const float x, const float y, const float z);
    void draw_rock(const int x, const int y, const int z, const float h, const int w, const int l, const int r);
    
public:
    terrarium();
    
    void step(const double t);
    
    void draw();
    
    v3<float> camera_pos(unsigned int f);

    v3<float> camera_dir(unsigned int f);
};

#endif /* terrarium_h */
