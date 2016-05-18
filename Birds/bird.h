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

// this is the ultimate influence radius, although the only boids it checks against are also properly limited
#define R1 20
#define R2 50

// this is the angles of theta for the birds vision
#define T1 15
#define T2 170

#define THR 0.01

using namespace std;

class bird {
private:
    v3<double> pos, vel, accel;
    double mass;
    
    v3<double> get_wind(const v3<double> wind){
        // this is the custom wind function, it can be any vector field, and wind is the weightof the functions
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
    
    void aggregate(v3<double> final_a, v3<double> final_v, v3<double> final_c, double a_res) {
        double f_a_len = final_a.abs(), f_v_len = final_v.abs(), f_c_len = final_c.abs();
        if (f_a_len > THR) {
            final_a = final_a.normalize() * min(a_res, f_a_len);
            a_res -= f_a_len;
        }
        if (f_v_len > THR) {
            final_v = final_v.normalize() * min(a_res, f_v_len);
            a_res -= f_v_len;
        }
        if (f_c_len > THR) {
            final_c = final_c.normalize() * min(a_res, f_c_len);
        }
        
        accel += final_a + final_v + final_c;
    }
    
public:
    bird(v3<double> p = v3<double>(), v3<double> v = v3<double>(), double m = 1.0): pos(p), vel(v), mass(m) { }
    
    v3<double> get_pos() const { return pos; }
    
    v3<double> get_vel() const { return vel; }
    
    void calc_velocity(const list<bird*> &nearby,
                       const float ka, const float kv, const float kc, const double a_res,
                       const v3<double> wind, const float windc,
                       const v3<double> f_p, const v3<double> f_v, const double s_tan,
                       v3<double> goal,
                       const double t) {
        //vortex force
        v3<double> v_tan = (pos - f_p).cross(f_v).normalize() * s_tan;
        
        //dynamic wind
        auto w = get_wind(wind);
        accel = ((w - vel) * (windc/mass));
        
        //calculate affect of nearby boids
        list<v3<double>> accel_a, accel_v, accel_c;
        for (auto &neighbor : nearby) {
            if (neighbor != this) {
                auto x = neighbor->pos - pos;
                auto u_x = x.normalize();
                auto d = x.abs();
                
                double k_dt = d_coef(d) * t_coef(vel.angle(x));
                
                accel_a.push_back((u_x * - (ka / d)) * k_dt);
                accel_v.push_back(((neighbor->vel - vel) * kv) * k_dt);
                accel_c.push_back((x * kc) * k_dt);
            }
        }
        
        //for acceleration prioritization
        v3<double> final_a, final_v, final_c;
        for (auto &a : accel_a) final_a += a;
        for (auto &a : accel_v) final_v += a;
        for (auto &a : accel_c) final_c += a;
        
        //prioritize
        aggregate(final_a, final_v, final_c, a_res);
        
        //push away from ceiling and floor
        if (pos.y < 20) accel += v3<double>(0,20 / pos.y,0);
        if (pos.y > 180) accel -= v3<double>(0,20 / (200 - pos.y),0);
        
        //steer toward a goal
        goal.y = pos.y;
        accel += (goal - pos).normalize() * 5;
        
        //finally update the velocity
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
