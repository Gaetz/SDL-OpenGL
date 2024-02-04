#include "game.h"
#include "../engine/resource_manager.h"
#include "../engine/gamestate.h"
#include "gamestate_main.h"

void Game::init(int screenWidth, int screenHeight) {
    windowWidth = screenWidth;
    windowHeight = screenHeight;
    gameIsRunning = true;

    inputManager = std::make_unique<InputManager>();
}

void Game::load() {
    // Load shaders
    ResourceManager::loadShader("assets/shaders/sprite.vert", "assets/shaders/sprite.frag", "", "sprite");
    ResourceManager::loadShader("assets/shaders/rect.vert", "assets/shaders/rect.frag", "", "rect");
    // Compute projection matrix
    auto fWindowWidth = static_cast<float>(windowWidth);
    auto fWindowHeight = static_cast<float>(windowHeight);
    Matrix4 projection = Matrix4::createOrtho(fWindowWidth, fWindowHeight, -1.0f, 1.0f);
    Matrix4 twoDimTranslation = Matrix4::createTranslation(Vector3(-fWindowWidth / 2.f, -fWindowHeight / 2.f, 0.0f));
    Matrix4 finalProjection = twoDimTranslation * projection;
    // Configure shaders
    ResourceManager::getShader("sprite").use();
    ResourceManager::getShader("sprite").setMatrix4("projection", finalProjection);
    ResourceManager::getShader("rect").use();
    ResourceManager::getShader("rect").setMatrix4("projection", finalProjection);
    // Set render-specific controls
    sRenderer = std::make_shared<SpriteRenderer>(ResourceManager::getShader("sprite"));
    gRenderer = std::make_shared<GeometryRenderer>(ResourceManager::getShader("rect"));

    // Game state
    changeState(std::make_unique<GameStateMain>(sRenderer, gRenderer));
}

void Game::handleInputs() {
    inputManager->prepareForUpdate();
    gameIsRunning = inputManager->pollInputs();
    const InputState& inputState = inputManager->getState();
    gameStates.back()->handleEvent(inputState);
}

void Game::update(unsigned int dt) {
    gameStates.back()->update(dt);
}

void Game::render() {
    gameStates.back()->draw();
}

void Game::clean() {
    ResourceManager::clear();
}

void Game::changeState(std::unique_ptr<GameState>&& state) {
    // Cleanup the current state
    if (!gameStates.empty()) {
        gameStates.back()->clean();
        gameStates.pop_back();
    }

    // Store and load the new state
    state->setGame(this);
    gameStates.push_back(std::move(state));
    gameStates.back()->load();
}

void Game::pushState(std::unique_ptr<GameState>&& state) {
    // Pause current state
    if (!gameStates.empty()) {
        gameStates.back()->pause();
    }

    // Store and init the new state
    gameStates.push_back(std::move(state));
    gameStates.back()->load();
}

void Game::popState() {
    // Cleanup the current state
    if (!gameStates.empty()) {
        gameStates.back()->clean();
        gameStates.pop_back();
    }

    // Resume previous state
    if (!gameStates.empty()) {
        gameStates.back()->resume();
    }
}