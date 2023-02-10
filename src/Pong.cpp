#include "Pong.hpp"

Pong::~Pong()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);

    _renderer = NULL;
    _window = NULL;

    SDL_Quit();
    TTF_CloseFont(_font);
    TTF_Quit();
}

void Pong::Init(SDL_Window *window,
                SDL_Renderer *renderer,
                TTF_Font *font,
                int width,
                int height,
                Configuration *config)
{
    _screen_w = width;
    _screen_h = height;

    _window = window;
    _renderer = renderer;
    _font = font;

    _config = config;

    /** initialize necessary objects **/

    // Center line
    Dimension centerLineDim(int(_screen_w / 2) - 5,
                            10,
                            10,
                            _screen_h - 20);

    _updateFilledRect(_centerLine, centerLineDim);

    // Ball
    Dimension ballDim(int(_screen_w / 2) - _ballRadius,
                      int(_screen_h / 2) - _ballRadius,
                      _ballRadius * 2,
                      _ballRadius * 2);
    _updateFilledRect(_ball, ballDim);
    _ballDirection.Set(-3, 5);

    // Players
    if (_config->gameModes[3])
    {
        int random = std::rand() % 2;
        if (random == 1) {
            _playerL = Player(60);
            _playerR = Player();
        } else {
            _playerL = Player();
            _playerR = Player(60);
        }
    }
    else
    {
        _playerL = Player();
        _playerR = Player();
    }

    Vector2 pL = Vector2();
    Vector2 pR = Vector2();

    pL.Set(0, (_screen_h / 2) - (_playerL.getHeight() / 2));
    pR.Set(_screen_w - _playerR.getWidth(), (_screen_h / 2) - (_playerL.getHeight() / 2));

    _playerL.Initialize(pL);
    _playerR.Initialize(pR);

    // Score board
    _leftScoreBoard.x = _screen_w / 2 - 250;
    _leftScoreBoard.y = 50;
    _leftScoreBoard.w = 50;
    _leftScoreBoard.h = 50;

    _rightScoreBoard.x = _screen_w / 2 + 200;
    _rightScoreBoard.y = 50;
    _rightScoreBoard.w = 50;
    _rightScoreBoard.h = 50;

    // Others
    _leftScore = 0;
    _rightScore = 0;
    _quit = false;
}

void Pong::Update()
{
    // update ball position
    Dimension ballDimension = _calculateNextBallPosition();
    _updateFilledRect(_ball, ballDimension);

    // update player positions
    _playerL.Update(_screen_h);
    _playerR.Update(_screen_h);

    // update texture
    std::string leftString = std::to_string(_leftScore);
    std::string rightString = std::to_string(_rightScore);
    _leftSurfaceText = TTF_RenderText_Solid(_font, leftString.c_str(), {255, 255, 255});
    _rightSurfaceText = TTF_RenderText_Solid(_font, rightString.c_str(), {255, 255, 255});
    _leftScoreTexture = SDL_CreateTextureFromSurface(_renderer, _leftSurfaceText);
    _rightScoreTexture = SDL_CreateTextureFromSurface(_renderer, _rightSurfaceText);
    SDL_FreeSurface(_leftSurfaceText);
    SDL_FreeSurface(_rightSurfaceText);

    // std::cout << "x: " << _ballDirection.x << " y: " << _ballDirection.y << std::endl;

    SDL_SetRenderDrawColor(_renderer, 0x22, 0x22, 0x22, 0xFF);
    SDL_RenderClear(_renderer);
}

void Pong::Render()
{
    // Render line and ball
    _renderFilledRect(_centerLine, _white);
    int red[4] = {255, 0, 0, 255};
    _renderFilledRect(_ball, red);

    _playerL.Render(_renderer);
    _playerR.Render(_renderer);

    // render text surface

    SDL_RenderCopy(_renderer, _leftScoreTexture, NULL, &_leftScoreBoard);
    SDL_RenderCopy(_renderer, _rightScoreTexture, NULL, &_rightScoreBoard);

    // render all
    SDL_RenderPresent(_renderer);
}

void Pong::Loop()
{
    SDL_Event e;

    // do I need this?
    SDL_StartTextInput();

    time_t prev = SDL_GetTicks();
    while (!_quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            _playerMovementHandler(e);
        }

        Update();

        _frameCap(prev);

        Render();
    }

    SDL_StopTextInput();
}

SDL_Window *Pong::GetSDLWindow()
{
    return _window;
}

SDL_Renderer *Pong::GetSDLRenderer()
{
    return _renderer;
}

void Pong::_frameCap(time_t &previous)
{

    time_t current = SDL_GetTicks();

    float expectation = (float)(1.0 * 1000 / 60.0);
    if (current - previous < expectation)
    {
        SDL_Delay(expectation - (current - previous));
    }

    // std::cout << "FPS: " << (1000.0 / (SDL_GetTicks() - previous)) << std::endl;
    previous = current;
}

void Pong::_updateFilledRect(SDL_Rect &rect, Dimension dim)
{
    rect.x = dim.x;
    rect.y = dim.y;
    rect.w = dim.w;
    rect.h = dim.h;
}

void Pong::_renderFilledRect(SDL_Rect &rect, int rgba[4])
{
    SDL_SetRenderDrawColor(_renderer, rgba[0], rgba[1], rgba[2], rgba[3]);
    SDL_RenderFillRect(_renderer, &rect);
}

Dimension Pong::_calculateNextBallPosition()
{
    // force exit if the ball is too fast
    if (std::abs(_ballDirection.x) > 50 || std::abs(_ballDirection.y) > 50)
    {
        _quit = true;
        _config->page = 0;
        std::cout << "The ball has exceeded the speed of light" << std::endl;
    }

    bool collided = false;
    // Check x
    if (SDL_HasIntersection(&_ball, _playerL.getCatcher())) // Hitting left
    {
        collided = true;
        int playerLeftY = _playerL.getYPos();
        if (playerLeftY - _ball.y > _ballRadius ||
            _ball.y + _ballRadius * 2 - (playerLeftY + _playerL.getHeight()) > _ballRadius)
        {
            _ballDirection.y *= -1;
        }
        else
        {
            _ballDirection.x *= -1;
            _ball.x += 1;
        }
    }
    else if (SDL_HasIntersection(&_ball, _playerR.getCatcher()))
    { // Hitting right
        collided = true;
        int playerRightY = _playerR.getYPos();
        if (playerRightY - _ball.y > _ballRadius ||
            _ball.y + _ballRadius * 2 - (playerRightY + _playerR.getHeight()) > _ballRadius)
        {
            _ballDirection.y *= -1;
        }
        else
        {
            _ballDirection.x *= -1;
            _ball.x -= 1;
        }
    }

    // reposition the ball if it is out of bound.
    if (_ball.x + (_ballRadius * 2) >= _screen_w)
    {
        // Left player gets a point
        _leftScore += 1;
        // std::cout << "x: " << _ball.x << " y: " << _ball.y << std::endl;
        // std::cout << "left score: " << _leftScore << std::endl;
        if (!_config->gameModes[1])
        {
            _ballDirection.Set(-3, 5);
        }
        else
        {
            _ballDirection.Set((std::abs(_ballDirection.x) * -1) - 1, std::abs(_ballDirection.y) + 1);
        }

        Dimension ballDim(int(_screen_w / 2) - _ballRadius,
                          int(_screen_h / 2) - _ballRadius,
                          _ballRadius * 2,
                          _ballRadius * 2);
        return ballDim;
    }
    else if (
        _ball.x <= 0)
    {
        // Right player gets a point
        _rightScore += 1;
        // std::cout << "x: " << _ball.x << " y: " << _ball.y << std::endl;
        // std::cout << "right score: " << _rightScore << std::endl;
        if (!_config->gameModes[1])
        {
            _ballDirection.Set(3, -5);
        }
        else
        {
            _ballDirection.Set(std::abs(_ballDirection.x) + 1, std::abs(_ballDirection.y) * -1 - 1);
        }

        Dimension ballDim(int(_screen_w / 2) - _ballRadius,
                          int(_screen_h / 2) - _ballRadius,
                          _ballRadius * 2,
                          _ballRadius * 2);
        return ballDim;
    }

    if (_config->gameModes[0])
    {
        // do nothing here.
    }
    else if (_config->gameModes[2])
    {
        if (_leftScore >= 1)
        {
            _quit = true;
            _config->page = 0;
            std::cout << "Left Player wins." << std::endl;
        }
        else if (_rightScore >= 1)
        {
            _quit = true;
            _config->page = 0;
            std::cout << "Right Player wins." << std::endl;
        }
    }
    else
    {
        if (_leftScore >= 3)
        {
            _quit = true;
            _config->page = 0;
            std::cout << "Left Player wins." << std::endl;
        }
        else if (_rightScore >= 3)
        {
            _quit = true;
            _config->page = 0;
            std::cout << "Right Player wins." << std::endl;
        }
    }

    // Check Y

    if (_ball.y + _ballRadius * 2 >= _screen_h ||
        _ball.y <= 0)
    {
        _ballDirection.y *= -1;
    }

    if (collided && _config->gameModes[1])
    {
        if (_ballDirection.x < 0)
        {
            _ballDirection.x -= 1;
        }
        else
        {
            _ballDirection.x += 1;
        }
        if (_ballDirection.y < 0)
        {
            _ballDirection.y -= 1;
        }
        else
        {
            _ballDirection.y += 1;
        }
        // _ballDirection.Set(std::abs(_ballDirection.x) + 1, std::abs(_ballDirection.y) * -1 - 1);
    }

    int nextX = _ball.x + _ballDirection.x;
    int nextY = _ball.y + _ballDirection.y;
    _ball.y = nextY;
    _ball.x = nextX;

    Dimension ballDim(_ball.x,
                      _ball.y,
                      _ballRadius * 2,
                      _ballRadius * 2);
    return ballDim;
}

void Pong::_playerMovementHandler(SDL_Event e)
{
    switch (e.type)
    {
    case SDL_QUIT:
        _config->quitGame = true;
        _quit = true;
        break;

    case SDL_KEYDOWN:
        if (e.key.keysym.sym == SDLK_w)
        {
            _playerL.Move(true);
        }
        else if (e.key.keysym.sym == SDLK_s)
        {
            _playerL.Move(false);
        }

        if (e.key.keysym.sym == SDLK_UP)
        {
            _playerR.Move(true);
        }
        else if (e.key.keysym.sym == SDLK_DOWN)
        {
            _playerR.Move(false);
        }
        break;

    case SDL_KEYUP:
        if (e.key.keysym.sym == SDLK_w || e.key.keysym.sym == SDLK_s)
        {
            _playerL.Stop();
        }

        if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_DOWN)
        {
            _playerR.Stop();
        }

        if (e.key.keysym.sym == SDLK_ESCAPE)
        {
            _config->page = 0;
            _quit = true;
        }

        break;
    }
}