#pragma once

#include "../CubeGame.hpp"
#include "GameObject.hpp"

class CubeObject {
public:
    /// render only method
    // TODO Mina ich brauche irgendeine Möglichkeit um auf diceData und die Würfelseite (beispiel sideID in CubeMapSide)
    virtual void Render(CubeGame &game, Renderer *render, Point size, Point location, u32 frame, u32 totalMSec, float deltaT);
    /// Handle input events, probably unused
    virtual void HandleEvent(CubeGame &game, u32 frame, u32 totalMSec, float deltaT, Event event);
    /// physics, etc. update method
    // TODO mina hier wirst GARANTIERT auch die Dice Data und sideID benötigen.....
    virtual void Update(CubeGame &game, u32 frame, u32 totalMSec, float deltaT);

    void setDiceData(DiceData* dice_data);
    void setSideId(int sideID);
    
    void drawSpriteBorder(CubeGame &game, Renderer *render, Rect dst);
    virtual bool canPlayerEnter();
    virtual bool canEnterPressurePlate();
    virtual bool canActivatePressurePlate();
    virtual bool isLevelFinishedIfEntered();
    
protected:
    DiceData *diceData;
    int sideId;
};

class GravityObject : public CubeObject {
public:
    bool canEnterPressurePlate() override;
};

class Stone : public GravityObject {
private:
    bool isFalling = false;
public:
    Stone() = default;
    void Render(CubeGame &game, Renderer *render, Point size, Point location, u32 frame, u32 totalMSec, float deltaT) override;
    void HandleEvent(CubeGame &game, u32 frame, u32 totalMSec, float deltaT, Event event) override;
    void Update(CubeGame &game, u32 frame, u32 totalMSec, float deltaT) override;
    bool canActivatePressurePlate() override;
};

class Activatable : public CubeObject {
public:
    bool canActivatePressurePlate() override;
};

class Slider : public Activatable {
public:
    void Render(CubeGame &game, Renderer *render, Point size, Point location, u32 frame, u32 totalMSec, float deltaT) override;
};

class Moveable : public CubeObject {
};

class Magnet : public Moveable {
public:
    void Render(CubeGame &game, Renderer *render, Point size, Point location, u32 frame, u32 totalMSec, float deltaT) override;
};

class Collectible : public CubeObject {
public:
    bool canPlayerEnter() override;
};

class Flag : public Collectible {
public:
    // Level:: void returnToLevelSelector(ExitState exitState);
    // ExitState::FINISHED
    void Render(CubeGame &game, Renderer *render, Point size, Point location, u32 frame, u32 totalMSec, float deltaT) override;

    bool canEnterPressurePlate() override;
    bool canActivatePressurePlate() override;
    
    bool isLevelFinishedIfEntered() override;
};