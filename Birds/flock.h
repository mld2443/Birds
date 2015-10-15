//
//  flock.h
//  Flocks
//
//  Created by Matthew Dillard on 10/14/15.
//

#ifndef flock_h
#define flock_h

#include <vector>
#include <stack>
#include <math.h>
#include <random>
#include "grid.h"

class flock {
private:
    vector<bird> birds;
    default_random_engine rand;
    
    v3f spawn_p(const float x, const float y, const float z, const float d) {
        uniform_real_distribution<float> U11(-1.0, 1.0);
        float Y = U11(rand);
        uniform_real_distribution<float> Upp(-PI,PI);
        float T = Upp(rand);
        
        float R = sqrt(1 - Y*Y);
        
        v3f pshpere(R * cos(T), Y, R * sin(T));
        
        return v3f(x, y, z) + (pshpere * d);
    }
    
public:
    flock(vector<vector<vector<grid>>> &a, const unsigned long s, const float x, const float y, const float z, const float d, v3f v = v3f()) {
        for (unsigned long i = 0; i < s; i++) {
            v3f p = spawn_p(x,y,z,d);
            birds.push_back(bird(p, v));
            a[p.x/25][p.y/25][p.z/25].add_bird(birds.back());
        }
    }
    
    unsigned long get_size() const { return birds.size(); }
    
    void calc_velocities(vector<vector<vector<grid>>> &a, const float t) {
        for (auto &b : birds)
            b.calc_velocity(list<bird*>(), t);
    }
    
    void draw(){
        for (auto &b : birds){
            b.draw();
        }
    }
};

#endif /* flock_h */
