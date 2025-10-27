//
// Created by sj on 27.10.2025.
//

#include "Tile.hpp"

void draw_grass(const int x, const int y) {
    DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE,GREEN);
}

void draw_stone(const int x, const int y) {
    DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE,LIGHTGRAY);
}

void draw_water(const int x, const int y) {
    DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE,SKYBLUE);
}

void draw_sand(const int x, const int y) {
    DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, YELLOW);
}


Tile::Tile(const int x, const int y, const int type) : _x{x}, _y{y} {
    switch (type) {
        case 0: _type = TileType::GRASS;
            _collidable = false;
            break;
        case 1: _type = TileType::STONE;
            _collidable = false;
            break;
        case 2: _type = TileType::WATER;
            _collidable = true;
            break;
        case 3: _type = TileType::SAND;
            _collidable = false;
            break;
        default: break;
    }
}

void Tile::Draw() const {
    switch (_type) {
        case TileType::GRASS: draw_grass(_x, _y);
            break;
        case TileType::STONE: draw_stone(_x, _y);
            break;
        case TileType::WATER: draw_water(_x, _y);
            break;
        case TileType::SAND: draw_sand(_x, _y);
            break;
        default: break;
    }
}

bool Tile::isCollidable() const {
    return _collidable;
}
