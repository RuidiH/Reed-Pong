#ifndef MENU_HPP
#define MENU_HPP

#if defined(LINUX) || defined(MINGW)
	#include <SDL2/SDL.h>
    #include <SDL2/SDL_ttf.h>
#else
	#include <SDL.h>
    #include <SDL_ttf.h>
#endif

#include <iostream>

#include "Dimension.hpp"
#include "Configuration.hpp"
#include "Checkbox.hpp"

class Menu
{
public:
    ~Menu();

    void Init(SDL_Window *window,
              SDL_Renderer *renderer,
              TTF_Font *font,
              int width,
              int height,
              Configuration *config);

    void Update();
    void Render();
    void Loop();

private:

    // Helper functions
    void _frameCap(time_t &previous);
    void _updateFilledRect(SDL_Rect &rect, Dimension dim);
    void _renderFilledRect(SDL_Rect &rect, int rgba[4]);

    int _width;
    int _height;

    // Window
    SDL_Window *_window;

    // Renderer
    SDL_Renderer *_renderer = NULL;

    // Font
    TTF_Font *_font;

    // Surface
    SDL_Surface* _titleSurface;
    SDL_Surface* _option1TextSurface;
    SDL_Surface* _copyrightSurface;

    // Texture
    SDL_Texture* _titleTexture;
    SDL_Texture* _option1Texture;
    SDL_Texture* _copyrightTexture;

    // Shape
    SDL_Rect _titleContainer;
    SDL_Rect _option1Container;
    SDL_Rect _option1Box;
    SDL_Rect _copyrightBox;

    // Checkbox
    Checkbox _checkbox[4];

    // Config
    Configuration *_config;

};

#endif