///////////////////////////////////////////////////////////////////////////
//  grid.h                                                               //
//  Birds                                                                //
//                                                                       //
//  Created by Matthew Dillard on 10/14/15.                              //
///////////////////////////////////////////////////////////////////////////

#ifndef grid_h
#define grid_h

//////////////
// Includes //
//////////////

#include <vector>
#include <list>

#include "cell.h"


//////////////////////
// Class Defenition //
//////////////////////

/// A grid is a 3-dimensional array of containers that keep track of
/// locally near boids. There is only one grid system for all boids.
class grid {
private:
    /// Regular spaced interval cells
    std::vector<std::vector<std::vector<cell>>> m_cells;
    
    /// List of all boids in the grid
    std::list<std::tuple<int,int,int>> m_record;
    
public:
    grid(const unsigned int w, const unsigned int h, const unsigned int l);
    
    void add_bird(const int x, const int y, const int z, bird* b);
    void move_birds();
    
    cell& get_cell(int x, int y, int z);
};

#endif /* grid_h */
