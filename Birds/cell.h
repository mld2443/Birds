///////////////////////////////////////////////
//  cell.h                                   //
//  Birds                                    //
//                                           //
//  Created by Matthew Dillard on 10/15/15.  //
///////////////////////////////////////////////

#ifndef cell_h
#define cell_h

//////////////
// Includes //
//////////////

#include <list>

#include "bird.h"


//////////////////////
// Class Definition //
//////////////////////

/// The basic container to identify nearby boids
class cell {
private:
    /// List of all boids currently inside this cell
    std::list<bird*> m_birds;
    
    /// Potential is the measure of how much this cell is avoided
    float m_potential;
    
public:
    cell(const float p = 0.0);
    
    // List operations
    bool check() const;
    std::list<bird*>::iterator bird_begin();
    std::list<bird*>::iterator bird_end();
    
    // Get or modify potential
    float get_potential() const;
    void add_potential(const float p);
    
    // Add or remove boids
    void add_bird(bird* b);
    bird* pop_bird();
};

#endif /* cell_h */
