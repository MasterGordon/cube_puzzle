#include "Player.hpp"
#include "../States/Level.hpp"
#include "CubeMap.hpp"

Player::Player(CubeGame &game, SDL_Renderer *render) : GameObject(game, render) {}

void Player::HandleEvent(const u32 frame, const u32 totalMSec, const float deltaT, Event event) {
    if (event.type != SDL_KEYDOWN) return;
    const Keysym &what_key = event.key.keysym;
    if (what_key.scancode == SDL_SCANCODE_UP) {
        move(PlayerMoveDirection::UP);
    } else if (what_key.scancode == SDL_SCANCODE_DOWN) {
        move(PlayerMoveDirection::DOWN);
    } else if (what_key.scancode == SDL_SCANCODE_RIGHT) {
        move(PlayerMoveDirection::RIGHT);
    } else if (what_key.scancode == SDL_SCANCODE_LEFT) {
        move(PlayerMoveDirection::LEFT);
    }
}

void Player::Update(const u32 frame, const u32 totalMSec, const float deltaT) {
    if (cubeMap == nullptr) return;
    nextDraw = cubeMap->playerDrawPosition();
}

void Player::Render(const u32 frame, const u32 totalMSec, const float deltaT) {
    if (cubeMap == nullptr) return;
    Rect r = nextDraw;
    r.y += (int)(sin(frame/20.0)*2);
    drawSprite(game.getSpriteStorage()->playerSpriteSheet, render, {0, 0}, r);
}

void Player::setCubeMap(CubeMap *cubeMap) {
    this->cubeMap = cubeMap;
}

bool Player::move(PlayerMoveDirection direction) {
    return cubeMap->movePlayer(direction);
}