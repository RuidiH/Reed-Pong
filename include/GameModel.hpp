#ifndef GAMEMODEL_HPP
#define GAMEMODEL_HPP

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#else
#include <SDL.h>
#include <SDL_ttf.h>
#endif

#include <string>
#include <iostream>
#include <sstream>

#include "Pong.hpp"
#include "Menu.hpp"
#include "Configuration.hpp"

class GameModel
{
public:
    GameModel(int w, int h);
    ~GameModel();

    void Run();

private:
    // Window
    int _window_width;
    int _window_height;
    SDL_Window *_window;

    // Renderer
    SDL_Renderer *_renderer = NULL;

    // Font
    TTF_Font *_font;

    // Content
    Menu _menu;
    Pong _pong;

    // Configuration
    Configuration _config;
};

#endif