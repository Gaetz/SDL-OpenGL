#include "input_keyboard_state.h"

bool KeyboardState::getKeyValue(SDL_Scancode keyCode) const
{
	return currentValue[keyCode] == 1;
}

KeyStatus KeyboardState::getKeyState(SDL_Scancode keyCode) const
{
	if (previousValue[keyCode] == 0)
	{
		if (currentValue[keyCode] == 0)
		{
			return None;
		}
		else
		{
			return JustPressed;
		}
	}
	else // Prev state must be 1
	{
		if (currentValue[keyCode] == 0)
		{
			return JustReleased;
		}
		else
		{
			return Held;
		}
	}
}

bool KeyboardState::isUp(SDL_Scancode keyCode) const
{
	return !getKeyValue(keyCode);
}

bool KeyboardState::isFree(SDL_Scancode keyCode) const
{
	return getKeyState(keyCode) == None;
}

bool KeyboardState::isJustPressed(SDL_Scancode keyCode) const
{
	return getKeyState(keyCode) == JustPressed;
}

bool KeyboardState::isDown(SDL_Scancode keyCode) const
{
	return getKeyValue(keyCode);
}

bool KeyboardState::isHeld(SDL_Scancode keyCode) const
{
	return getKeyState(keyCode) == Held;
}

bool KeyboardState::isJustReleased(SDL_Scancode keyCode) const
{
	return getKeyState(keyCode) == JustReleased;
}