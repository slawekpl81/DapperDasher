//
// Created by sj on 26.10.2025.
//
#include "raylib.h"
#include <string>

#ifndef DAPPERDASHER_CONSTANS_HPP
#define DAPPERDASHER_CONSTANS_HPP

constexpr std::string TITLE = "GAME 1.0";
// Stałe dla okna i renderingu
constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;
constexpr int FPS = 45;

// Dla kamery
constexpr float CAMERA_SPEED = 10.0f; // Prędkość przesuwania (px/s)
constexpr bool CAMERA_FOLLOW_PLAYER = true; // Opcja: follow z lerp (0.1f smooth)
constexpr float CAMERA_LERP_SPEED = 0.1f; // Smooth follow (0.0-1.0)

// Stałe dla gridu/mapy (z poprzednich dyskusji)
constexpr int GRID_WIDTH = 200;
constexpr int GRID_HEIGHT = 200;
constexpr float TILE_SIZE = 16.0f;
constexpr std::string GRID_FILE_DATA = "grid_data.txt";

// Stałe dla gracza i ruchu
constexpr float PLAYER_SPEED = 100.0f;
constexpr float INTERACTION_RANGE = 50.0f;

// Stałe dla zasobów (drzewa, kamienie)
constexpr int MAX_RESOURCES_SPAWN = 20;
constexpr int BASE_RESOURCE_AMOUNT = 3;

// Enumy (też tu, dla spójności)
enum class TileType { GRASS = 0, STONE = 1, WATER = 2, SAND = 3 };

enum ResourceType { TREE = 0, STONE = 1, BERRY_BUSH = 2 };

// Opcjonalnie: namespace dla grupowania (unikaj kolizji nazw)
namespace GameConfig {
    constexpr Color BACKGROUND_COLOR = BLACK;
    constexpr Color PLAYER_COLOR = RED;
}

#endif //DAPPERDASHER_CONSTANS_HPP
