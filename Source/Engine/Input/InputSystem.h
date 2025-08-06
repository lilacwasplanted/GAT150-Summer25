#pragma once
#include "../Math/Vector2.h"
#include <vector>
#include <array>


using namespace std;

namespace viper {
	class is {

	public:
	
		enum class MouseButton : uint8_t {
			Left,
			Middle,
			Right

		};
	

		void InputSystem() {}

		bool Initialize();
		void Shutdown();
		void Update();

		//Keyboard Input
		bool GetKeyDown(unsigned int key) const { return _kbState[key]; }
		bool GetPrevKeyDown(unsigned int key)const  { return _prevKbState[key]; }
		bool GetKeyPressed(unsigned int key) const { return !_prevKbState[key] && _kbState[key]; }
		bool GetKeyReleased(unsigned int key) const { return _prevKbState[key] && !_kbState[key]; }


		//mouse input
		bool GetMouseButtonDown(MouseButton button) { return _mouseButtonState[(uint8_t)button]; }
		bool GetPrevMouseButtonDown(MouseButton button) {return _prevMouseButtonState[(uint8_t)button]; }
		bool GetMouseButtonPressed(MouseButton button) const {return !_prevMouseButtonState[(uint8_t)button] && _mouseButtonState[(uint8_t)button]; }
		bool GetMouseButtonReleased(MouseButton button) const { return _prevMouseButtonState[(uint8_t)button] && !_mouseButtonState[(uint8_t)button]; }

		const vec2& GetMousePos() const { return _mousePos; }
		const vec2& GetPrevMousePos() const{ return _prevMousePos; }


	private:
		vector<bool> _kbState;
		vector<bool> _prevKbState;

		vec2 _mousePos;
		vec2 _prevMousePos;

		array<bool, 3> _mouseButtonState{ false, false, false };
		array<bool, 3> _prevMouseButtonState{ false, false, false };


	};
}