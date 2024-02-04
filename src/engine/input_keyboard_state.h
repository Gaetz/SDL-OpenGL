#ifndef INPUT_KEYBOARD_STATE_H
#define INPUT_KEYBOARD_STATE_H

#ifdef __linux__
#include <SDL2/SDL.h>
#elif _WIN32

#include <SDL.h>

#endif

enum KeyStatus {
    None,
    JustPressed,
    Held,
    JustReleased
};

// Holds the keyboard state
class KeyboardState {
    friend class InputManager;

public:
    // True when key is up or just released
    [[nodiscard]] bool isUp(SDL_Scancode) const;

    // True when key is up and not just released
    [[nodiscard]] bool isFree(SDL_Scancode) const;

    // True when key is just pressed
    [[nodiscard]] bool isJustPressed(SDL_Scancode) const;

    // True when key is down or just pressed
    [[nodiscard]] bool isDown(SDL_Scancode) const;

    // True when key is down and not just pressed
    [[nodiscard]] bool isHeld(SDL_Scancode) const;

    // True when key is just released
    [[nodiscard]] bool isJustReleased(SDL_Scancode) const;

private:
    const Uint8* currentValue;
    Uint8 previousValue[SDL_NUM_SCANCODES];

    // Get the boolean value of key
    [[nodiscard]] bool getKeyValue(SDL_Scancode) const;

    // Get a state based on current and previous frame
    [[nodiscard]] KeyStatus getKeyState(SDL_Scancode) const;
};

#endif