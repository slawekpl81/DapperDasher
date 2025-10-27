//
// Created by sj on 26.10.2025.
//

#ifndef DAPPERDASHER_GRID_HPP
#define DAPPERDASHER_GRID_HPP
#include <vector>

#include "Tile.hpp"


class Grid {
private:
    std::vector<Tile> _tiles;

public:
    Grid();

    void Draw(Camera2D &camera);

    bool load_from_file(const std::string &filename);

    bool save_to_file(const std::string &filename) const;
};


#endif //DAPPERDASHER_GRID_HPP
