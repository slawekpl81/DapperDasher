//
// Created by sj on 27.10.2025.
//

#ifndef DAPPERDASHER_TILE_HPP
#define DAPPERDASHER_TILE_HPP

#include "Constans.hpp"

class Tile {
private:
    int _x;
    int _y;
    TileType _type;
    bool _collidable;

public:
    Tile(int x, int y, int type);

    void Draw() const;
};


#endif //DAPPERDASHER_TILE_HPP
