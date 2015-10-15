//
//  grid.h
//  Flocks
//
//  Created by Matthew Dillard on 10/14/15.
//  Copyright © 2015 Matthew Dillard. All rights reserved.
//

#ifndef grid_h
#define grid_h

#include <list>
#include "bird.h"

class grid {
private:
    list<bird*> birds;
    float potential;
    
public:
    grid(const float p = 0.0): potential(p) {}
    
    float get_potential() const { return potential; }
    list<bird*>::iterator bird_begin() { return birds.begin(); }
    list<bird*>::iterator bird_end() { return birds.end(); }
    
    void add_potential(const float p) { potential += p; }
    void add_bird(bird &b) { birds.push_back(&b); }
    void remove_bird(bird &b) { birds.remove(&b); }
};

#endif /* grid_h */
