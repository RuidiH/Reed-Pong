#ifndef PLAYER_HPP
#define PLAYER_HPP

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include "Vector2.hpp"
#include "Dimension.hpp"

class Player
{
public:
    Player();
    Player(int height);
    ~Player();

    void Initialize(Vector2 location);
    void Update(int screenH);
    void Render(SDL_Renderer *renderer);

    void Move(bool up);
    void Stop();
    int getXPos() { return _catcher.x; };
    int getYPos() { return _catcher.y; };
    int getWidth() { return _catcher.w; };
    int getHeight() { return _catcher.h; };
    SDL_Rect *getCatcher() { return &_catcher; };

private:
    SDL_Rect _catcher;
    int _speed = 10;
    bool _dir[2] = {false, false};
};

#endif