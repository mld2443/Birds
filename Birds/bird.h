//
//  bird.h
//  Flocks
//
//  Created by Matthew Dillard on 10/14/15.
//

#ifndef bird_h
#define bird_h

#include <list>
#include "v3f.h"

const GLfloat black[] = { 0.0, 0.0, 0.0 };
const GLfloat white[] = { 1.0, 1.0, 1.0 };

using namespace std;

class bird {
private:
    v3f pos, vel, accel;
    
public:
    bird(v3f p = v3f(), v3f v = v3f()): pos(p), vel(v) { }
    
    void calc_velocity(const list<bird*> &nearby, const float f) {
        
    }
    
    void draw() {
        glBegin(GL_LINE_STRIP); {
            glMaterialfv(GL_FRONT, GL_AMBIENT, black);
            glVertex3f(pos.x, pos.y, pos.z);
            glMaterialfv(GL_FRONT, GL_AMBIENT, white);
            glVertex3f(pos.x + vel.x, pos.y + vel.y, pos.z + vel.z);
        } glEnd();
    }
};

#endif /* bird_h */
