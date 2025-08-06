#include "InputSystem.h"
#include <SDL3/SDL.h>
using namespace std;

namespace viper {

	bool is::Initialize() {
		int numbKeys;
		const bool* keyboardState = SDL_GetKeyboardState(&numbKeys);

		_kbState.resize(numbKeys);
		copy(keyboardState, keyboardState + numbKeys, _kbState.begin());
		_prevKbState = _kbState;


		return true;
	}
	void is::Shutdown() {

	}
	void is::Update() {
		//keyboard input
		_prevKbState = _kbState;
		const bool* keyboardState = SDL_GetKeyboardState(nullptr);
		copy(keyboardState, keyboardState + _kbState.size(), _kbState.begin());

		//mouse input
		_prevMousePos = _mousePos;
		uint32_t mouseBtnState = SDL_GetMouseState(&_mousePos.x, &_mousePos.y);
		_mouseButtonState[(uint8_t)MouseButton::Left] = mouseBtnState & SDL_BUTTON_LMASK;
		_mouseButtonState[(uint8_t)MouseButton::Middle] = mouseBtnState & SDL_BUTTON_MMASK;
		_mouseButtonState[(uint8_t)MouseButton::Right] = mouseBtnState & SDL_BUTTON_RMASK;
	}
}