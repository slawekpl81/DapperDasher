//
// Created by sj on 26.10.2025.
//

#include <print>
#include <format>
#include <sstream>
#include "raylib.h"
#include "Game.hpp"
#include "Constans.hpp"

Game::Game() {
    _title = TITLE;
    _screen_width = SCREEN_WIDTH;
    _screen_height = SCREEN_HEIGHT;
    _fps = FPS;

    _debug_mode = false;
    _debug_text = {""};

    InitWindow(_screen_width, _screen_height, _title.c_str());
    SetTargetFPS(_fps);
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
}

void Game::Draw() const {
    BeginDrawing();
    ClearBackground(RAYWHITE);
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
