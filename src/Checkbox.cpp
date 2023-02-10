#include "Checkbox.hpp"

Checkbox::Checkbox()
{
}

void Checkbox::Init(
    TTF_Font *font,
    int x,
    int y,
    Configuration *config,
    int id)
{
    _font = font;
    _config = config;
    _id = id;

    // checkbox
    _checkBox.x = x;
    _checkBox.y = y;
    _checkBox.w = 150;
    _checkBox.h = 100;

    _disableBox.x = _checkBox.x + 10;
    _disableBox.y = _checkBox.y + 40;
    _disableBox.w = 20;
    _disableBox.h = 20;

    _enableBox.x = _disableBox.x + 5;
    _enableBox.y = _disableBox.y + 5;
    _enableBox.w = 10;
    _enableBox.h = 10;

    // text container
    _modeContainer.x = _disableBox.x + _disableBox.w + 5;
    _modeContainer.y = _checkBox.y + 20;
    _modeContainer.w = 110;
    _modeContainer.h = 60;
}

void Checkbox::CheckClick(SDL_Point mousePos)
{
    if (SDL_PointInRect(&mousePos, &_checkBox))
    {
        _config->gameModes[_id] = !_config->gameModes[_id];
        
        // special rules: game mode 0 and 2 are not compatible.
        if (_config->gameModes[0] == _config->gameModes[2] && (_config->gameModes[0] || _config->gameModes[2])) {
            if (_id == 0) {
                _config->gameModes[2] = !_config->gameModes[2];
            } else if (_id == 2) {
                _config->gameModes[0] = !_config->gameModes[0];
            }
        }
    }
}

void Checkbox::Render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderFillRect(renderer, &_checkBox);

    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(renderer, &_disableBox);

    if (_config->gameModes[_id])
    {
        SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
        SDL_RenderFillRect(renderer, &_enableBox);
    }

    // render text based on id
    std::string description = "";
    switch (_id)
    {
    case 0:
        description = "Eternity";
        break;
    case 1:
        description = "Accelerate";
        break;
    case 2:
        description = "One Punch";
        break;
    case 3:
        description = "Misfortune";
        break;
    }
    _modeSurface = TTF_RenderText_Solid(_font, description.c_str(), {255, 255, 255});
    _modeTexture = SDL_CreateTextureFromSurface(renderer, _modeSurface);
    SDL_FreeSurface(_modeSurface);
    SDL_RenderCopy(renderer, _modeTexture, NULL, &_modeContainer);
}