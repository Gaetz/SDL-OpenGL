#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "renderer_sprite.h"
#include "renderer_geometry.h"
#include "input_state.h"
#include "igame.h"

// Interface for scenes
class GameState {
public:
    virtual ~GameState() = default;

    virtual void load() = 0;

    virtual void clean() = 0;

    virtual void handleEvent(const InputState&) = 0;

    virtual void update(unsigned int dt) = 0;

    virtual void draw() = 0;

    virtual void pause() = 0;

    virtual void resume() = 0;

    virtual void setGame(IGame* _game) = 0;
};

#endif