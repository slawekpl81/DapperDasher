//
// Created by sj on 26.10.2025.
//

#include <sstream>
#include <iostream>
#include <fstream>
#include <print>
#include <cmath>
#include "Grid.hpp"


Grid::Grid() {
    if (!load_from_file(GRID_FILE_DATA)) {
        for (auto y{0}; y < GRID_HEIGHT; ++y) {
            for (auto x{0}; x < GRID_WIDTH; ++x) {
                _tiles.emplace_back(x, y, x % 45 ? 0 : 2);
            }
        }
    }
    std::cout << "GRID SIZE: " << _tiles.size() << std::endl;
    // std::cout << _tiles[0]._x << " " << _tiles[0]._y << " " << static_cast<int>(_tiles[0]._type) << std::endl;
}


void Grid::Draw(Camera2D &camera) {
    // int drawing_n{0};

    // 1. POPRAWNE Obliczanie obszaru widzenia kamery w World Space
    Vector2 topLeftWorld = GetScreenToWorld2D({0, 0}, camera);
    Vector2 bottomRightWorld = GetScreenToWorld2D({static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT)},
                                                  camera);

    // 2. Konwertuj na grid coords (tile indices) z użyciem zaokrąglenia
    int startX = std::max(0, static_cast<int>(std::floor(topLeftWorld.x / TILE_SIZE)));
    int startY = std::max(0, static_cast<int>(std::floor(topLeftWorld.y / TILE_SIZE)));

    // Używamy ceil i nie dodajemy +1, bo ceil już zapewnia objęcie ostatniego kafelka
    int endX = std::min(GRID_WIDTH, static_cast<int>(std::ceil(bottomRightWorld.x / TILE_SIZE)));
    int endY = std::min(GRID_HEIGHT, static_cast<int>(std::ceil(bottomRightWorld.y / TILE_SIZE)));
    // Upewnij się, że rysujesz tylko W KAMERZE
    // BeginMode2D(camera);

    // 3. Rysuj tylko te tile'e (zoptymalizowana kolejność pętli)
    for (int y = startY; y < endY; ++y) {
        for (int x = startX; x < endX; ++x) {
            // Konwersja 2D -> 1D (wiersz * szerokość + kolumna)
            _tiles[y * GRID_WIDTH + x].Draw();
            // drawing_n++;
        }
    }

    // EndMode2D();

    // Debug: Użyj raylib do wypisywania tekstu na ekranie, a nie std::println
    // DrawText(TextFormat("Drawing tiles: %d", drawing_n), 10, 10, 20, BLACK);
    // lub zostaw std::println dla konsoli
    // std::println("Drawing grid elements: {}", drawing_n);
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
