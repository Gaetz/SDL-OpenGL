#include "input_manager.h"
#include <cstring>

InputManager::InputManager()
{
    init();
}

InputManager::~InputManager()
{

}

void InputManager::init()
{
	// Keyboard

	// Assign current state pointer
	inputState.keyboardState.currentValue = SDL_GetKeyboardState(nullptr);
	// Clear previous state memory
	memset(inputState.keyboardState.previousValue, 0, SDL_NUM_SCANCODES);
}


void InputManager::prepareForUpdate()
{
	// Keyboard: Copy current state to previous
	memcpy(inputState.keyboardState.previousValue, inputState.keyboardState.currentValue, SDL_NUM_SCANCODES);
}

bool InputManager::pollInputs()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	bool isRunning = true;
	switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
	}
	return isRunning;
}

const InputState& InputManager::getState() const
{
    return inputState;
}