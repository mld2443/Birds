//
//  grid.h
//  Birds
//
//  Created by Matthew Dillard on 10/14/15.
//  This is just to hold the 3D grid vector with a layer of obfuscation
//  I only have one grid which all flocks share
//

#ifndef grid_h
#define grid_h

#include <vector>
#include "cell.h"

class grid {
private:
    vector<vector<vector<cell>>> cells;
    vector<v3<int>> record;
    
public:
    grid(const unsigned int w, const unsigned int h, const unsigned int l) {
        cells = vector<vector<vector<cell>>>(w, vector<vector<cell>>(h, vector<cell>(l, 0.0)));
        
        for (int x = 0; x < w; x++)
            for (int z = 0; z < l; z++)
                cells[x][0][z].add_potential(25);
    }
    
    void add_bird(const int x, const int y, const int z, bird* b) {
        record.push_back(v3<int>(x,y,z));
        cells[x][y][z].add_bird(b);
    }
    
    void move_birds() {
        vector<bird*> phase;
        for (auto &b : record)
            phase.push_back(cells[b.x][b.y][b.z].pop_bird());
        
        record.clear();
        
        for (auto &b : phase){
            int x = b->get_pos().x/25, y = b->get_pos().y/25, z = b->get_pos().z/25;
            if (x < 0) { x = 0; }
            if (x > 399) { x = 399; }
            if (y < 0) { y = 0; }
            if (y > 7) { y = 7; }
            if (z < 0) { z = 0; }
            if (z > 399) { z = 399; }
            record.push_back(v3<int>(x,y,z));
            cells[x][y][z].add_bird(b);
        }
    }
    
    cell& get_cell(int x, int y, int z) {
        if (x < 0) { x = 0; }
        if (x > 399) { x = 399; }
        if (y < 0) { y = 0; }
        if (y > 7) { y = 7; }
        if (z < 0) { z = 0; }
        if (z > 399) { z = 399; }
        return cells[x][y][z];
    }
};

#endif /* grid_h */
