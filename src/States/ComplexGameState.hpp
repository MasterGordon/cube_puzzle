#pragma once

#include "../gamebase.hpp"

class CubeGame;

class ComplexGameState: public GameState{
public:
    ComplexGameState(CubeGame& cubeGame, Renderer* render);
protected:
    CubeGame& cubeGame;
};