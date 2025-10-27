//
// Created by sj on 26.10.2025.
//

#include <print>
#include <format>
#include <sstream>
#include "raylib.h"
#include "raymath.h"
#include "Game.hpp"
#include "Constans.hpp"

Game::Game() {
    _title = TITLE;
    _screen_width = SCREEN_WIDTH;
    _screen_height = SCREEN_HEIGHT;
    _fps = FPS;

    Camera2D _camera;
    _camera.offset = {
        static_cast<float>(SCREEN_WIDTH) / 2.0f, static_cast<float>(SCREEN_HEIGHT) / 2.0f
    }; // Środek ekranu
    _camera.zoom = 1.0f;
    _camera.rotation = 0.0f;
    _camera.target = {static_cast<float>(SCREEN_WIDTH) / 2.0f, static_cast<float>(SCREEN_HEIGHT) / 2.0f};
    //{ (float)(GRID_WIDTH * TILE_SIZE) / 2.0f, (float)(GRID_HEIGHT * TILE_SIZE) / 2.0f };  // Środek mapy na start

    _debug_mode = false;
    _debug_text = {""};

    InitWindow(_screen_width, _screen_height, _title.c_str());
    SetTargetFPS(_fps);

    _grid = std::make_unique<Grid>();
}

void Game::Run() {
    while (!WindowShouldClose()) {
        Update();
        Draw();
    }
    CloseWindow();
}

void Game::Update() {
    // FPS
    _current_fps = GetFPS();
    _debug_text = std::format("FPS: {};", _current_fps);
    // debug mode
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_D)) {
        _debug_mode = !_debug_mode;
        // std::println("DEBUG MODE: {}", _debug_mode ? "ON" : "OFF");
    }
    // CAMERA
    // Przesuwanie kamery WASD
    Vector2 cameraVelocity = {0.0f, 0.0f};
    if (IsKeyDown(KEY_W)) cameraVelocity.y -= 1.0f;
    if (IsKeyDown(KEY_S)) cameraVelocity.y += 1.0f;
    if (IsKeyDown(KEY_A)) cameraVelocity.x -= 1.0f;
    if (IsKeyDown(KEY_D)) cameraVelocity.x += 1.0f;

    if (Vector2Length(cameraVelocity) > 0.0f) {
        _camera.target.x += cameraVelocity.x * CAMERA_SPEED; // * deltaTime;
        _camera.target.y += cameraVelocity.y * CAMERA_SPEED; // * deltaTime;
    }

    // Opcjonalnie: follow gracza z lerp (smooth)
    // if (CAMERA_FOLLOW_PLAYER) {
    //     Vector2 playerScreenPos = GetScreenToWorld2D(player->position, camera);  // Pozycja gracza na ekranie
    //     Vector2 desiredTarget = player->position;
    //     camera.target = Vector2Lerp(camera.target, desiredTarget, CAMERA_LERP_SPEED);  // Smooth lerp
    // }

    // Ogranicz kamerę do granic mapy
    float halfMapW = (GRID_WIDTH * TILE_SIZE) / 2.0f;
    float halfMapH = (GRID_HEIGHT * TILE_SIZE) / 2.0f;
    _camera.target.x = Clamp(_camera.target.x, halfMapW, GRID_WIDTH * TILE_SIZE - halfMapW);
    _camera.target.y = Clamp(_camera.target.y, halfMapH, GRID_HEIGHT * TILE_SIZE - halfMapH);
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode2D(_camera);
    _grid->Draw(_camera);
    EndMode2D();
    //=======================================
    if (_debug_mode) {
        // std::string fps_text = std::format("FPS: {}", _current_fps);
        // DrawText(fps_text.c_str(), 5, _screen_height - 20, 15, RED);
        DrawDebugText(_debug_text, 5, 5, 15,RED);
    }
    DrawText("Hello, Raylib from CMake!", 190, 200, 20, LIGHTGRAY);

    EndDrawing();
}

void Game::CloseGame() {
    CloseWindow();
}

void Game::DrawDebugText(const std::string &text, int x, int y, int fontSize, Color color) {
    std::istringstream iss(text);
    std::string line;
    const int lineHeight = fontSize + 5;
    int currentY = y;

    while (std::getline(iss, line, ';')) {
        // Split po ';'
        DrawText(line.c_str(), x, currentY, fontSize, color);
        currentY += lineHeight;
    }
}
