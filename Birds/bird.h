//
//  bird.h
//  Birds
//
//  Created by Matthew Dillard on 10/14/15.
//

#ifndef bird_h
#define bird_h

#include <list>
#include "v3.h"

const GLfloat black[] = { 0.0, 0.0, 0.0 };
const GLfloat white[] = { 1.0, 1.0, 1.0 };

using namespace std;

class bird {
private:
    v3<double> pos, vel, accel;
    
public:
    bird(v3<double> p = v3<double>(), v3<double> v = v3<double>()): pos(p), vel(v) { }
    
    v3<double> get_pos() const { return pos; }
    
    void calc_velocity(const list<bird*> &nearby, const float ka, const float kv, const float kc, const float t) {
        list<v3<double>> accels;
        for (auto &neighbor : nearby) {
            if (neighbor != this) {
                auto x = neighbor->pos - pos;
                auto u_x = x.normalize();
                auto d = x.abs();
                auto Aa = u_x * - (ka / d);
                auto Av = (neighbor->vel - vel) * kv;
                auto Ac = x * kc;
                
                accels.push_back(Aa + Av + Ac);
            }
        }
        for (auto &a : accels) {
            accel += a;
        }
        
        if (pos.y < 20)
            accel += v3<double>(0, 20 / pos.y, 0);
        
        if (pos.y > 180)
            accel -= v3<double>(0, 20 / (200 - pos.y), 0);
        
        vel += accel * t;
    }
    
    void integrate(const float t) {
        pos += vel;
    }
    
    void draw() const {
        glBegin(GL_LINE_STRIP); {
            glMaterialfv(GL_FRONT, GL_AMBIENT, black);
            glVertex3f(pos.x, pos.y, pos.z);
            glMaterialfv(GL_FRONT, GL_AMBIENT, white);
            glVertex3f(pos.x + vel.x, pos.y + vel.y, pos.z + vel.z);
        } glEnd();
    }
};

#endif /* bird_h */
