#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "input_state.h"

class InputManager {
public:
    InputManager();

    // Set input state before polling
    void prepareForUpdate();

    // Poll inputs and return quit status
    static bool pollInputs();

    // Access general state of inputs
    [[nodiscard]] const InputState& getState() const;

private:
    // Setup initial input state
    void init();

    // General state of inputs
    InputState inputState {};
};

#endif