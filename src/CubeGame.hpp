#pragma once

#include "gamebase.hpp"
#include "data/SpriteStorage.hpp"
#include "audioHandler.hpp"

class LevelSelector;

/// Cube Game handler
class CubeGame final : public Game {
public:
    CubeGame();

    AudioPlayer  audio;

    bool HandleEvent(const Event event) override;

    SpriteStorage *getSpriteStorage() override;

    /// should display debug info
    bool isDebug();

private:
    SpriteStorage spriteStorage;

    /// load sprites into sprite storage
    void loadSprites();

    void setWindowIcon();

    /// this should be set to false in final version
    bool debugView = true;
protected:
    friend class LevelSelector;
};
