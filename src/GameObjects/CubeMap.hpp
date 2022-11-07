//
// Created by Tom Arlt on 02.11.22.
//

#pragma once

#include "GameObject.hpp"
#include "CubeField.hpp"
#include "../data/MoveDirections.hpp"
#include "../data/DiceData.hpp"

class WorldMap;

class Player;

class CubeMapSide;

class CubeMap final : public GameObject {
public:
    CubeMap(Game &game, SDL_Renderer *render, const Vector<CubeMapSide>& sides, int startSide = 1,
            Point playerPos = {0, 0});

    void SetWorldMap(WorldMap *worldMap) { this->worldMap = worldMap; }

    void HandleEvent(const u32 frame, const u32 totalMSec, const float deltaT, Event event) override;

    void Update(const u32 frame, const u32 totalMSec, const float deltaT) override;

    void Render(const u32 frame, const u32 totalMSec, const float deltaT) override;

    void RenderUI(const u32 frame, const u32 totalMSec, const float deltaT) override;

    void Init() override;

public:
    bool movePlayer(PlayerMoveDirection dir);

    Point cubePositionToScreenPosition(Point cubePos);

    Point screenPositionToCubePosition(Point screenPos);

private:
    void moveCubeInWorld(DiceRollDirection rollDirection);

    void drawMinimap(const u32 frame, const u32 totalMSec, const float deltaT);

    void drawMap(const u32 frame, const u32 totalMSec, const float deltaT);

    /// get side of dice (1-6)
    CubeMapSide *getSide(int i);

    CubeField* getField(int side, int x, int y);
    CubeField* getField(int side, Point p);

private:
    WorldMap *worldMap = nullptr;
    Vector<CubeMapSide *> sides;
    int currentSideId = 1;
    Point playerPos;
    DiceData diceData;

    friend class WorldMap;
};

class CubeMapSide {
public:
    CubeMapSide(Vector<CubeField *> side, int width, int height) : width(width), height(height) { this->side = side; }
    CubeMapSide(Vector<CubeField *> side, Point size) : width(size.x), height(size.y) { this->side = side; }

    Vector<CubeField *> side;
    int width, height;

    CubeField *getField(int x, int y) { return side[getIndex(x, y)]; }

    [[nodiscard]] int getIndex(int x, int y) const { return x * width + y; }

    Point getFieldSize(Point windowSize);
    Point getStartingOffset(Point windowSize, Point fieldSize);

    void HandleEvent(CubeGame& game, const u32 frame, const u32 totalMSec, const float deltaT, Event event);

    void Update(CubeGame& game, const u32 frame, const u32 totalMSec, const float deltaT);

    void Render(CubeGame& game, Renderer* render, DiceData diceData, const u32 frame, const u32 totalMSec, const float deltaT);

    [[nodiscard]] Point cubePositionToScreenPosition(DiceData diceData, Point cubePos) const;

};