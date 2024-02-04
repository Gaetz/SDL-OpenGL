#include "engine.h"
#include "engine.h"

Engine::Engine(std::unique_ptr<IGame>&& _game, std::string _title, int _screenWidth, int _screenHeight) :
        game(std::move(_game)),
        title(std::move(_title)),
        screenWidth(_screenWidth),
        screenHeight(_screenHeight) {

    window = IWindow::create(title);
    if (!window->init(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, false)) {
        return;
    }
    window->logGlParams();
}


void Engine::start() {
    // Main game elements loading
    game->init(screenWidth, screenHeight);
    game->load();
}

void Engine::run() {
    // Game loop
    while (game->isRunning()) {
        dt = timer.computeDeltaTime();
        window->updateFpsCounter(dt);

        game->handleInputs();
        game->update(dt);

        window->clear();
        game->render();
        window->swapBuffer();

        // Delay frame if game runs too fast
        timer.delayTime();
    }
}

void Engine::shutdown() {
    // Exit game
    game->clean();
    window->clean();
}