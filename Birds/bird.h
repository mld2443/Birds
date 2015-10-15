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

#define R1 20
#define R2 50

#define T1 15
#define T2 170

using namespace std;

class bird {
private:
    v3<double> pos, vel, accel;
    double mass;
    
    v3<double> get_wind(const v3<double> wind){
        return v3<double>(wind.x,
                          wind.y * sin((pos.x+pos.z)*PI/90),
                          wind.z);
    }
    
    double d_coef(const double d) {
        if (d < R1)
            return 1.0;
        else if (d <= R2)
            return (R2 - d)/(R2 - R1);
        else
            return 0.0;
    }
    
    double t_coef(const double angle) {
        if (-T1 <= angle && angle <= T1)
            return 1.0;
        else if (-T2 <= angle && angle <= T2)
            return (T2 - angle)/(T2 - T1);
        else
            return 0.0;
    }
    
public:
    bird(v3<double> p = v3<double>(), v3<double> v = v3<double>(), double m = 1.0): pos(p), vel(v), mass(m) { }
    
    v3<double> get_pos() const { return pos; }
    
    v3<double> get_vel() const { return vel; }
    
    void calc_velocity(const list<bird*> &nearby,
                       const float ka, const float kv, const float kc,
                       const v3<double> wind, const float windc,
                       const v3<double> f_p, const v3<double> f_v, const double s_tan,
                       v3<double> goal,
                       const double t) {
        v3<double> v_tan = (pos - f_p).cross(f_v).normalize() * s_tan;
        auto w = get_wind(wind);
        accel = ((w - vel) * (windc/mass));
        
        list<v3<double>> accels;
        for (auto &neighbor : nearby) {
            if (neighbor != this) {
                auto x = neighbor->pos - pos;
                auto u_x = x.normalize();
                auto d = x.abs();
                
                double k_dt = d_coef(d) * t_coef(vel.angle(x));
                
                auto Aa = (u_x * - (ka / d)) * k_dt;
                auto Av = ((neighbor->vel - vel) * kv) * k_dt;
                auto Ac = (x * kc) * k_dt;
                
                accels.push_back((Aa + Av + Ac)/mass);
            }
        }
        
        for (auto &a : accels) accel += a;
        
        if (pos.y < 20) accel += v3<double>(0,20 / pos.y,0);
        if (pos.y > 180) accel -= v3<double>(0,20 / (200 - pos.y),0);
        
        //goal.y = pos.y;
        //accel += (goal - pos).normalize() * 10;
        vel += v_tan + accel * t;
    }
    
    void integrate(const double t) {
        pos += vel * t;
    }
    
    void draw() const {
        glPushMatrix(); {
            glTranslatef(pos.x, pos.y, pos.z);
            v3<double> nose(vel.normalize() * 5);
            v3<double> left(vel.cross(v3<double>(0,-1,0)).normalize());
            v3<double> right(vel.cross(v3<double>(0,1,0)).normalize());
            v3<double> norm = right.cross(nose).normalize() * 0.5;
            v3<double> left1 = left * 0.2 + norm;
            v3<double> right1 = right * 0.2 + norm;
            v3<double> left2 = left + norm;
            v3<double> right2 = right + norm;
            
            glBegin(GL_TRIANGLE_STRIP); {
                glNormal3f(norm.x, norm.y, norm.z);
                glVertex3f(left1.x, left1.y, left1.z);
                glVertex3f(nose.x, nose.y, nose.z);
                glVertex3f(left2.x, left2.y, left2.z);
            } glEnd();
            glBegin(GL_TRIANGLE_STRIP); {
                glNormal3f(right.x, right.y, right.z);
                glVertex3f(0.0, 0.0, 0.0);
                glVertex3f(nose.x, nose.y, nose.z);
                glVertex3f(left1.x, left1.y, left1.z);
            } glEnd();
            glBegin(GL_TRIANGLE_STRIP); {
                glNormal3f(left.x, left.y, left.z);
                glVertex3f(right1.x, right1.y, right1.z);
                glVertex3f(nose.x, nose.y, nose.z);
                glVertex3f(0.0, 0.0, 0.0);
            } glEnd();
            glBegin(GL_TRIANGLE_STRIP); {
                glNormal3f(norm.x, norm.y, norm.z);
                glVertex3f(right2.x, right2.y, right2.z);
                glVertex3f(nose.x, nose.y, nose.z);
                glVertex3f(right1.x, right1.y, right1.z);
            } glEnd();
            
            glBegin(GL_TRIANGLE_STRIP); {
                glNormal3f(-norm.x, -norm.y, -norm.z);
                glVertex3f(left2.x, left2.y, left2.z);
                glVertex3f(nose.x, nose.y, nose.z);
                glVertex3f(left1.x, left1.y, left1.z);
            } glEnd();
            glBegin(GL_TRIANGLE_STRIP); {
                glNormal3f(-right.x, -right.y, -right.z);
                glVertex3f(left1.x, left1.y, left1.z);
                glVertex3f(nose.x, nose.y, nose.z);
                glVertex3f(0.0, 0.0, 0.0);
            } glEnd();
            glBegin(GL_TRIANGLE_STRIP); {
                glNormal3f(-left.x, -left.y, -left.z);
                glVertex3f(0.0, 0.0, 0.0);
                glVertex3f(nose.x, nose.y, nose.z);
                glVertex3f(right1.x, right1.y, right1.z);
            } glEnd();
            glBegin(GL_TRIANGLE_STRIP); {
                glNormal3f(-norm.x, -norm.y, -norm.z);
                glVertex3f(right1.x, right1.y, right1.z);
                glVertex3f(nose.x, nose.y, nose.z);
                glVertex3f(right2.x, right2.y, right2.z);
            } glEnd();
        } glPopMatrix();
    }
};

#endif /* bird_h */
