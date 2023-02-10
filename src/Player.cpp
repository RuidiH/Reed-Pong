#include "Player.hpp"
#include "Dimension.hpp"

Player::Player()
{
    _catcher.w = 15;
    _catcher.h = 120;
}

Player::Player(int height) {
     _catcher.w = 15;
    _catcher.h = height;
}

Player::~Player()
{
}

void Player::Initialize(Vector2 location)
{
    _catcher.x = location.x;
    _catcher.y = location.y;
}

void Player::Update(int screenH)
{
    if (_dir[0] && (_catcher.y - _speed >= 0))
    {
        _catcher.y -= _speed;
    }
    else if (_dir[1] && (_catcher.y + _catcher.h + _speed) <= screenH)
    {
        _catcher.y += _speed;
    }


}

void Player::Render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &_catcher);
}

void Player::Move(bool up)
{
    if (up)
    {
        _dir[0] = true;
    }
    else
    {
        _dir[1] = true;
    }
}

void Player::Stop()
{
    // reset direction condition
    _dir[0] = false;
    _dir[1] = false;
}