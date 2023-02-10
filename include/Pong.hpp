#ifndef PONG_HPP
#define PONG_HPP

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#else
#include <SDL.h>
#include <SDL_ttf.h>
#endif

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <time.h> /* time */

#include "Vector2.hpp"
#include "Dimension.hpp"
#include "Player.hpp"
#include "Configuration.hpp"

class Pong
{
public:
    //
    ~Pong();

    //
    void Init(SDL_Window *window,
              SDL_Renderer *renderer,
              TTF_Font *font,
              int width,
              int height,
              Configuration *config);
    void Update();
    void Render();
    void Loop();

    // Getters
    SDL_Window *GetSDLWindow();
    SDL_Renderer *GetSDLRenderer();

private:
    void _frameCap(time_t &previous);
    void _updateFilledRect(SDL_Rect &rect, Dimension dim);
    void _renderFilledRect(SDL_Rect &rect, int rgba[4]);
    void _playerMovementHandler(SDL_Event e);
    Dimension _calculateNextBallPosition();

    // Objects
    SDL_Rect _centerLine;
    SDL_Rect _ball; // in another parallelled world. a ball is a rectangle.
    SDL_Rect _leftScoreBoard;
    SDL_Rect _rightScoreBoard;
    Player _playerL;
    Player _playerR;

    // Colors
    int _white[4] = {255, 255, 255, 255};

    // Other Variables
    bool _quit = false;
    int _screen_h;
    int _screen_w;
    int _ballRadius = 8;
    int _leftScore = 0;
    int _rightScore = 0;

    bool _playerLeftDir[2] = {false, false};
    bool _playerRightDir[2] = {false, false};

    Vector2 _ballDirection;

    // Window
    SDL_Window *_window;

    // Renderer
    SDL_Renderer *_renderer = NULL;

    // Font
    TTF_Font *_font;

    // Surface
    SDL_Surface *_leftSurfaceText;
    SDL_Surface *_rightSurfaceText;

    // Texture
    SDL_Texture *_leftScoreTexture;
    SDL_Texture *_rightScoreTexture;

    // Configuration
    Configuration *_config;
};

#endif