#ifndef CHECKBOX_HPP
#define CHECKBOX_HPP

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#else
#include <SDL.h>
#include <SDL_ttf.h>
#endif

#include <string>
#include "Configuration.hpp"

class Checkbox
{
public:
    Checkbox();
    void Init(
        TTF_Font *font,
        int x,
        int y,
        Configuration *config,
        int id);

    void CheckClick(SDL_Point mousePos);
    void Render(SDL_Renderer *renderer);
private:
    int _id;

    // Font
    TTF_Font *_font;

    // Surface
    SDL_Surface *_modeSurface;

    // Texture
    SDL_Texture *_modeTexture;

    // Shape
    SDL_Rect _modeContainer;
    SDL_Rect _checkBox;
    SDL_Rect _disableBox;
    SDL_Rect _enableBox;

    // Config
    Configuration *_config;
};

#endif