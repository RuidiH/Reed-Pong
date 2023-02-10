#include "GameModel.hpp"

GameModel::GameModel(int w, int h) : _window_width(w), _window_height(h)
{
    bool success = true;

    std::stringstream errorStream;
    _window = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        // Window creation
        _window = SDL_CreateWindow("Pong",
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   _window_width,
                                   _window_height,
                                   SDL_WINDOW_SHOWN);

        // Check window creation
        if (_window == NULL)
        {
            errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        }

        // Create renderer
        _renderer = SDL_CreateRenderer(_window,
                                       -1,
                                       SDL_RENDERER_ACCELERATED);

        if (_renderer == NULL)
        {
            errorStream << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        }

        // Initialize TTF
        if (TTF_Init() == -1)
        {
            std::cout << "Could not initialize SDL2_tff, error: " << TTF_GetError() << std::endl;
            success = false;
        }

        _font = TTF_OpenFont("fonts/arial.ttf", 25);
        if (_font == nullptr)
        {
            std::cout << "Could not load font" << std::endl;
            exit(1);
        }
    }

    if (!success)
    {
        errorStream << "Failed to initialize!\n";
        std::string errors = errorStream.str();
        std::cout << errors << std::endl;
    }
    else
    {
        std::cout << "No SDL or OpenGL errors detected.\n\n";
    }

    // Initialize _config
    _config.page = 0;
}

GameModel::~GameModel()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);

    _renderer = NULL;
    _window = NULL;


    TTF_CloseFont(_font);
    TTF_Quit();
    SDL_Quit();
}

void GameModel::Run()
{

    while (!_config.quitGame)
    {
        switch (_config.page)
        {
        case 0:
            _menu.Init(_window, _renderer, _font, _window_width, _window_height, &_config);
            _menu.Loop();
            break;

        case 1:
            _pong.Init(_window, _renderer, _font, _window_width, _window_height, &_config);
            _pong.Loop();
            break;
        }

        // clear render
        SDL_RenderClear(_renderer);
    }

    // _menu.Init(_window, _renderer, _font, _window_width, _window_height, _config);
    // _menu.Loop();

    // // clear render
    // SDL_RenderClear(_renderer);

    // _pong.Init(_window, _renderer, _font, _window_width, _window_height, _config);
    // _pong.Loop();
}