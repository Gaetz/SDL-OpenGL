#ifndef ENGINE_H
#define ENGINE_H

#include <cstdint>
#include <string>
#include <memory>

#include "window.h"
#include "igame.h"
#include "timer.h"

class Engine {
public:
    Engine(std::unique_ptr<IGame>&& game, std::string title, int screenWidth, int screenHeight);
    void start();
    void run();
    void shutdown();

private:
    // Delta time
    uint32_t dt;

    std::string title;
    const int screenWidth = 450;
    const int screenHeight = 680;
    std::unique_ptr<IWindow> window { nullptr };
    std::unique_ptr<IGame> game;
    Timer timer;
};

#endif //ENGINE_H
