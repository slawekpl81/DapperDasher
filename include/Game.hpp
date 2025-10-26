//
// Created by sj on 26.10.2025.
//

#ifndef DAPPERDASHER_GAME_HPP
#define DAPPERDASHER_GAME_HPP
#include <string>


class Game {
private:
    std::string _title;
    int _screen_width;
    int _screen_height;
    int _fps;
    int _current_fps;

    bool _debug_mode;
    std::string _debug_text;

public:
    Game();

    void Run();

    void Update();

    void Draw() const;

    void CloseGame();

    static void DrawDebugText(const std::string &text, int x, int y, int fontSize, Color color);
};


#endif //DAPPERDASHER_GAME_HPP
