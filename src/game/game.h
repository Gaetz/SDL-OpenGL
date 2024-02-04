#ifndef GAME_H
#define GAME_H

#ifdef __linux__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>
#endif

#include <GL/glew.h>
#include <vector>
#include <memory>

#include "../engine/input_manager.h"
#include "../engine/shader.h"
#include "../engine/renderer_sprite.h"
#include "../engine/renderer_geometry.h"
#include "../engine/gamestate.h"
#include "../engine/igame.h"

// This game class manages game states and triggers their logic.
// It supports gamestate stacking. It does not implement a 
// gameobject/entity/whatever logic to let you free to choose
// your architecture.
class Game : public IGame {
public:
    void init(int screenWidth, int screenHeight) override;

    void load() override;

    void handleInputs() override;

    void update(unsigned int dt) override;

    void render() override;

    void clean() override;

    void changeState(std::unique_ptr<GameState>&& state) override;

    void pushState(std::unique_ptr<GameState>&& state) override;

    void popState() override;

    inline bool isRunning() override { return gameIsRunning; }

    bool gameIsRunning { false };
    int windowWidth { 0 };
    int windowHeight { 0 };

private:
    std::unique_ptr<InputManager> inputManager;
    std::shared_ptr<SpriteRenderer> sRenderer;
    std::shared_ptr<GeometryRenderer> gRenderer;
    std::vector<std::unique_ptr<GameState>> gameStates;
};

#endif