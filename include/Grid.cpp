//
// Created by sj on 26.10.2025.
//

#include <sstream>
#include <iostream>
#include <fstream>
#include "Grid.hpp"


Grid::Grid() {
    if (!load_from_file(GRID_FILE_DATA)) {
        for (auto x{0}; x < GRID_WIDTH; ++x) {
            for (auto y{0}; y < GRID_HEIGHT; ++y) {
                _tiles.emplace_back(x, y, x % 71 ? 0 : 2);
            }
        }
    }
    std::cout << "GRID SIZE: " << _tiles.size() << std::endl;
    std::cout << _tiles[0]._x << " " << _tiles[0]._y << " " << static_cast<int>(_tiles[0]._type) << std::endl;
}


void Grid::Draw(Camera2D &camera) {
    // Oblicz widoczne bounds w world space
    Vector2 topLeftWorld = GetWorldToScreen2D({0, 0}, camera); // Lewy górny róg ekranu w world
    Vector2 bottomRightWorld = GetWorldToScreen2D({static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT)},
                                                  camera);
    // Prawy dolny

    // Konwertuj na grid coords (tile indices)
    int startX = std::max(0, static_cast<int>(topLeftWorld.x / TILE_SIZE));
    int startY = std::max(0, static_cast<int>(topLeftWorld.y / TILE_SIZE));
    int endX = std::min(GRID_WIDTH, static_cast<int>(bottomRightWorld.x / TILE_SIZE) + 1);
    int endY = std::min(GRID_HEIGHT, static_cast<int>(bottomRightWorld.y / TILE_SIZE) + 1);

    // Rysuj tylko te tile'e
    int drawing{0};
    for (int y = startY; y < endY; ++y) {
        for (int x = startX; x < endX; ++x) {
            // Vector2 gridPos = {static_cast<float>(x), static_cast<float>(y)};
            // tiles[y][x].Draw(gridPos, TILE_SIZE);
            _tiles[y * GRID_WIDTH + x].Draw();
            drawing++;
            std::cout << "tiles: " << drawing << std::endl;
        }
    }
    // for (const auto &tile: _tiles) {
    // tile.Draw();
    // }
}

bool Grid::save_to_file(const std::string &filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "GRID: Błąd: Nie można otworzyć pliku do zapisu." << std::endl;
        return false;
    }

    for (const auto &tile: _tiles) {
        file << tile._x << " " << tile._y << " " << static_cast<int>(tile._type) << "\n";
    }

    file.close();
    std::cout << "GRID: Dane zostały zapisane do pliku." << std::endl;
    return true;
}

bool Grid::load_from_file(const std::string &filename) {
    _tiles.clear();
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "GRID: Błąd: Nie można otworzyć pliku do odczytu." << std::endl;
        return false;
    }

    int a, b, c;
    while (file >> a >> b >> c) {
        _tiles.emplace_back(a, b, c);
    }

    file.close();
    std::cout << "GRID: Dane zostały odczytane z pliku. " << std::endl;
    return true;
}
