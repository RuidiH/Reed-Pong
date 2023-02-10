#include "Menu.hpp"

Menu::~Menu()
{
}

void Menu::Init(SDL_Window *window,
                SDL_Renderer *renderer,
                TTF_Font *font,
                int width,
                int height,
                Configuration *config)
{

    _width = width;
    _height = height;

    _window = window;
    _renderer = renderer;
    _font = font;

    _config = config;

    /** initialize necessary objects **/

    // Title
    _titleContainer.x = (_width / 2) - (_width / 4);
    _titleContainer.y = 200;
    _titleContainer.w = _width / 2;
    _titleContainer.h = 200;

    _titleSurface = TTF_RenderText_Solid(_font, "Reed's Pong", {255, 255, 255});
    _titleTexture = SDL_CreateTextureFromSurface(_renderer, _titleSurface);
    SDL_FreeSurface(_titleSurface);

    // Box
    _option1Box.x = (_width / 2) - (_width / 8);
    _option1Box.y = _titleContainer.y + 275;
    _option1Box.w = _width / 4;
    _option1Box.h = 150;
    
    // copyright box
    _copyrightBox.x = 0;
    _copyrightBox.y = _height - 30;
    _copyrightBox.w = 300;
    _copyrightBox.h = 30;

    _copyrightSurface = TTF_RenderText_Solid(_font, "Copyright © Reeeeeed Build Game Engine Inc.", {255, 255, 255});
    _copyrightTexture = SDL_CreateTextureFromSurface(_renderer, _copyrightSurface);
    SDL_FreeSurface(_copyrightSurface);

    // Button1
    _option1Container.x = (_width / 2) - (_width / 10);
    _option1Container.y = _titleContainer.y + 300;
    _option1Container.w = _width / 5;
    _option1Container.h = 100;

    _option1TextSurface = TTF_RenderText_Solid(_font, "Play Pong!", {255, 255, 255});
    _option1Texture = SDL_CreateTextureFromSurface(_renderer, _option1TextSurface);
    SDL_FreeSurface(_option1TextSurface);

    // Checkbox
    for (int i = 0; i < sizeof(_checkbox); i++)
    {
        switch (i)
        {
        case 0:
            _checkbox[i].Init(font, _option1Box.x,
                              _option1Container.y + _option1Container.h + 100,
                              config, 0);
            break;
        case 1:
            _checkbox[i].Init(font, _option1Box.x + 160,
                              _option1Container.y + _option1Container.h + 100,
                              config, 1);
            break;

        case 2:
            _checkbox[i].Init(font, _option1Box.x,
                              _option1Container.y + _option1Container.h + 210,
                              config, 2);
            break;

        case 3:
            _checkbox[i].Init(font, _option1Box.x + 160,
                              _option1Container.y + _option1Container.h + 210,
                              config, 3);
            break;
        }
    }
}

    void Menu::Loop()
    {
        bool quit = false;

        SDL_Event e;

        SDL_StartTextInput();

        time_t prev = SDL_GetTicks();
        while (!quit)
        {
            SDL_Point mousePosition;

            while (SDL_PollEvent(&e) != 0)
            {
                mousePosition.x = e.motion.x;
                mousePosition.y = e.motion.y;
                // std::cout << mousePosition.x << " " << mousePosition.y << std::endl;
                switch (e.type)
                {
                case SDL_QUIT:
                    _config->quitGame = true;
                    quit = true;
                    break;
                case SDL_MOUSEBUTTONUP:
                    // TODO: Currently quit when option1Box is clicked. Implement code.
                    if (SDL_PointInRect(&mousePosition, &_option1Box))
                    {
                        quit = true;
                        _config->page = 1;
                    }
                    for (Checkbox cbx: _checkbox) {
                        cbx.CheckClick(mousePosition);
                    }
                    break;
                case SDL_KEYUP:
                    if (e.key.keysym.sym == SDLK_ESCAPE)
                    {
                        _config->quitGame = true;
                        quit = true;
                    }
                    break;
                }
            }

            Update();

            _frameCap(prev);

            Render();
        }

        SDL_StopTextInput();
    }

    void Menu::Update()
    {
        // TODO:

        SDL_SetRenderDrawColor(_renderer, 0x22, 0x22, 0x22, 0xFF);
        SDL_RenderClear(_renderer);
    }

    void Menu::Render()
    {
        // Render title
        SDL_RenderCopy(_renderer, _titleTexture, NULL, &_titleContainer);

        // Render option box
        SDL_SetRenderDrawColor(_renderer, 220, 220, 220, 255);
        SDL_RenderFillRect(_renderer, &_option1Box);

        // Render option
        SDL_RenderCopy(_renderer, _option1Texture, NULL, &_option1Container);

        // Render checkboxs
        for (Checkbox cbx : _checkbox) {
            cbx.Render(_renderer);
        }

        // Render copyright text
        SDL_RenderCopy(_renderer, _copyrightTexture, NULL, &_copyrightBox);

        SDL_RenderPresent(_renderer);
    }

    /** Private functions **/

    void Menu::_frameCap(time_t & previous)
    {

        time_t current = SDL_GetTicks();

        float expectation = (float)(1.0 * 1000 / 60.0);
        if (current - previous < expectation)
        {
            SDL_Delay(expectation - (current - previous));
        }

        previous = current;
    }

    void Menu::_updateFilledRect(SDL_Rect & rect, Dimension dim)
    {
        rect.x = dim.x;
        rect.y = dim.y;
        rect.w = dim.w;
        rect.h = dim.h;
    }

    void Menu::_renderFilledRect(SDL_Rect & rect, int rgba[4])
    {
        SDL_SetRenderDrawColor(_renderer, rgba[0], rgba[1], rgba[2], rgba[3]);
        SDL_RenderFillRect(_renderer, &rect);
    }