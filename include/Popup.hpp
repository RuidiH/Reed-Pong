#ifndef POPUP_HPP
#define POPUP_HPP

#if defined(LINUX) || defined(MINGW)
	#include <SDL2/SDL.h>
    #include <SDL2/SDL_ttf.h>
#else
	#include <SDL.h>
    #include <SDL_ttf.h>
#endif

#include "Configuration.hpp"

class Popup
{
public:

private:
    int _width;
    int _height;

    // Window
    SDL_Window *_window;

    // Renderer
    SDL_Renderer *_renderer = NULL;

    // Font
    TTF_Font *_font;

    // Surface
    SDL_Surface* _messageSurface;

    // Texture
    SDL_Texture* _messageTexture;
};

#endif