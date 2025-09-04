#include "InputSystem.h"

namespace viper {
  bool InputSystem::Initialize() {
    int numKeys;
    const bool* keyboardState = SDL_GetKeyboardState(&numKeys);
    
    m_keyboardState.resize(numKeys);
     copy(keyboardState, keyboardState + numKeys, m_keyboardState.begin());
    m_prevKeyboardState = m_keyboardState;
  
    SDL_GetMouseState(&m_mousePosition.x, &m_mousePosition.y);
    m_prevMousePosition = m_mousePosition;

    return true;
  }

  void InputSystem::Shutdown() {
    //
  }

  void InputSystem::Update() {
    // keyboard input
    m_prevKeyboardState = m_keyboardState;
    const bool* keyboardState = SDL_GetKeyboardState(nullptr);
     copy(keyboardState, keyboardState + m_keyboardState.size(), m_keyboardState.begin());

    // mouse input
    m_prevMousePosition = m_mousePosition;

    m_prevMouseButtonState = m_mouseButtonState;
    uint32_t mouseButtonState = SDL_GetMouseState(&m_mousePosition.x, &m_mousePosition.y);

    m_mouseButtonState[(uint8_t)MouseButton::Left] = mouseButtonState & SDL_BUTTON_LMASK;
    m_mouseButtonState[(uint8_t)MouseButton::Middle] = mouseButtonState & SDL_BUTTON_MMASK;
    m_mouseButtonState[(uint8_t)MouseButton::Right] = mouseButtonState & SDL_BUTTON_RMASK;
  }

}