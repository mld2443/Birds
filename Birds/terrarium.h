//
//  terrarium.h
//  Flocks
//
//  Created by Matthew Dillard on 10/12/15.
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
    GLUquadricObj *quadric;
    vector<vector<vector<grid>>> airspace;
    vector<flock> flocks;
    
    void draw_lights();
    void draw_bounds();
    void draw_ground();
    void draw_tree(const float x, const float y, const float z);
    void draw_rock(const int x, const int y, const int z, const float h, const int w, const int l, const int r);
    
public:
    terrarium();
    
    void step(const float t);
    
    void draw();
    
};

#endif /* terrarium_h */
