#ifndef IGAME_H
#define IGAME_H

#include <memory>

class GameState;

// Interface for the game class, defined in the game module
class IGame {
public:
    virtual void init(int screenWidth, int screenHeight) = 0;

    virtual void load() = 0;

    virtual void handleInputs() = 0;

    virtual void update(unsigned int dt) = 0;

    virtual void render() = 0;

    virtual void clean() = 0;

    virtual void changeState(std::unique_ptr<GameState>&& state) = 0;

    virtual void pushState(std::unique_ptr<GameState>&& state) = 0;

    virtual void popState() = 0;

    virtual bool isRunning() = 0;
};

#endif //IGAME_H
