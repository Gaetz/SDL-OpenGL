#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "input_state.h"

class InputManager
{
public:
	InputManager();
	virtual ~InputManager();

	// Set input state before polling
	void prepareForUpdate();

	// Poll inputs and return quit status
	bool pollInputs();

	// Acces general state of inputs
	const InputState& getState() const;

private:
	// Setup initial input state
	void init();

	// General state of inputs
	InputState inputState;
};

#endif