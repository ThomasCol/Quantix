#ifndef __INPUTMANAGER_H__
#define __INPUTMANAGER_H__

#include <Type.h>
#include <GLFW/glfw3.h>
#include <Vec2.h>

#include "Core/DLLHeader.h"

namespace Quantix::Core::UserEntry
{
	enum class QUANTIX_API EKey
	{
		QX_KEY_SPACE = GLFW_KEY_SPACE,
		QX_KEY_APOSTROPHE = GLFW_KEY_APOSTROPHE,
		QX_KEY_COMMA = GLFW_KEY_COMMA,
		QX_KEY_MINUS = GLFW_KEY_MINUS,
		QX_KEY_PERIOD = GLFW_KEY_PERIOD,
		QX_KEY_SLASH = GLFW_KEY_SLASH,
		QX_KEY_BACKSLASH = GLFW_KEY_BACKSLASH,
		QX_KEY_SEMICOLON = GLFW_KEY_SEMICOLON,
		QX_KEY_EQUAL = GLFW_KEY_EQUAL,
		QX_KEY_0 = GLFW_KEY_0,
		QX_KEY_1 = GLFW_KEY_1,
		QX_KEY_2 = GLFW_KEY_2,
		QX_KEY_3 = GLFW_KEY_3,
		QX_KEY_4 = GLFW_KEY_4,
		QX_KEY_5 = GLFW_KEY_5,
		QX_KEY_6 = GLFW_KEY_6,
		QX_KEY_7 = GLFW_KEY_7,
		QX_KEY_8 = GLFW_KEY_8,
		QX_KEY_9 = GLFW_KEY_9,
		QX_KEY_A = GLFW_KEY_A,
		QX_KEY_B = GLFW_KEY_B,
		QX_KEY_C = GLFW_KEY_C,
		QX_KEY_D = GLFW_KEY_D,
		QX_KEY_E = GLFW_KEY_E,
		QX_KEY_F = GLFW_KEY_F,
		QX_KEY_G = GLFW_KEY_G,
		QX_KEY_H = GLFW_KEY_H,
		QX_KEY_I = GLFW_KEY_I,
		QX_KEY_J = GLFW_KEY_J,
		QX_KEY_K = GLFW_KEY_K,
		QX_KEY_L = GLFW_KEY_L,
		QX_KEY_M = GLFW_KEY_M,
		QX_KEY_N = GLFW_KEY_N,
		QX_KEY_O = GLFW_KEY_O,
		QX_KEY_P = GLFW_KEY_P,
		QX_KEY_Q = GLFW_KEY_Q,
		QX_KEY_R = GLFW_KEY_R,
		QX_KEY_S = GLFW_KEY_S,
		QX_KEY_T = GLFW_KEY_T,
		QX_KEY_U = GLFW_KEY_U,
		QX_KEY_V = GLFW_KEY_V,
		QX_KEY_W = GLFW_KEY_W,
		QX_KEY_X = GLFW_KEY_X,
		QX_KEY_Y = GLFW_KEY_Y,
		QX_KEY_Z = GLFW_KEY_Z,
		QX_KEY_LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET,
		QX_KEY_RIGHT_BRACKET = GLFW_KEY_RIGHT_BRACKET,
		QX_KEY_GRAVE_ACCENT = GLFW_KEY_GRAVE_ACCENT,

		QX_KEY_ESCAPE = GLFW_KEY_ESCAPE,
		QX_KEY_ENTER = GLFW_KEY_ENTER,
		QX_KEY_TAB = GLFW_KEY_TAB,
		QX_KEY_BACKSPACE = GLFW_KEY_BACKSPACE,
		QX_KEY_INSERT = GLFW_KEY_INSERT,
		QX_KEY_DELETE = GLFW_KEY_DELETE,
		QX_KEY_RIGHT = GLFW_KEY_RIGHT,
		QX_KEY_LEFT = GLFW_KEY_LEFT,
		QX_KEY_DOWN = GLFW_KEY_DOWN,
		QX_KEY_UP = GLFW_KEY_UP,
		QX_KEY_PAGE_UP = GLFW_KEY_PAGE_UP,
		QX_KEY_PAGE_DOWN = GLFW_KEY_PAGE_DOWN,
		QX_KEY_HOME = GLFW_KEY_HOME,
		QX_KEY_END = GLFW_KEY_END,
		QX_KEY_CAPS_LOCK = GLFW_KEY_CAPS_LOCK,
		QX_KEY_SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK,
		QX_KEY_NUM_LOCK = GLFW_KEY_NUM_LOCK,
		QX_KEY_PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN,
		QX_KEY_PAUSE = GLFW_KEY_PAUSE,
		QX_KEY_F1 = GLFW_KEY_F1,
		QX_KEY_F2 = GLFW_KEY_F2,
		QX_KEY_F3 = GLFW_KEY_F3,
		QX_KEY_F4 = GLFW_KEY_F4,
		QX_KEY_F5 = GLFW_KEY_F5,
		QX_KEY_F6 = GLFW_KEY_F6,
		QX_KEY_F7 = GLFW_KEY_F7,
		QX_KEY_F8 = GLFW_KEY_F8,
		QX_KEY_F9 = GLFW_KEY_F9,
		QX_KEY_F10 = GLFW_KEY_F10,
		QX_KEY_F11 = GLFW_KEY_F11,
		QX_KEY_F12 = GLFW_KEY_F12,
		QX_KEY_F13 = GLFW_KEY_F13,
		QX_KEY_F14 = GLFW_KEY_F14,
		QX_KEY_F15 = GLFW_KEY_F15,
		QX_KEY_F16 = GLFW_KEY_F16,
		QX_KEY_F17 = GLFW_KEY_F17,
		QX_KEY_F18 = GLFW_KEY_F18,
		QX_KEY_F19 = GLFW_KEY_F19,
		QX_KEY_F20 = GLFW_KEY_F20,
		QX_KEY_F21 = GLFW_KEY_F21,
		QX_KEY_F22 = GLFW_KEY_F22,
		QX_KEY_F23 = GLFW_KEY_F23,
		QX_KEY_F24 = GLFW_KEY_F24,
		QX_KEY_F25 = GLFW_KEY_F25,
		QX_KEY_KP_0 = GLFW_KEY_KP_0,
		QX_KEY_KP_1 = GLFW_KEY_KP_1,
		QX_KEY_KP_2 = GLFW_KEY_KP_2,
		QX_KEY_KP_3 = GLFW_KEY_KP_3,
		QX_KEY_KP_4 = GLFW_KEY_KP_4,
		QX_KEY_KP_5 = GLFW_KEY_KP_5,
		QX_KEY_KP_6 = GLFW_KEY_KP_6,
		QX_KEY_KP_7 = GLFW_KEY_KP_7,
		QX_KEY_KP_8 = GLFW_KEY_KP_8,
		QX_KEY_KP_9 = GLFW_KEY_KP_9,
		QX_KEY_KP_DECIMAL = GLFW_KEY_KP_DECIMAL,
		QX_KEY_KP_DIVIDE = GLFW_KEY_KP_DIVIDE,
		QX_KEY_KP_MULTIPLY = GLFW_KEY_KP_MULTIPLY,
		QX_KEY_KP_SUBTRACT = GLFW_KEY_KP_SUBTRACT,
		QX_KEY_KP_ADD = GLFW_KEY_KP_ADD,
		QX_KEY_KP_ENTER = GLFW_KEY_KP_ENTER,
		QX_KEY_KP_EQUAL = GLFW_KEY_KP_EQUAL,
		QX_KEY_LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
		QX_KEY_LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL,
		QX_KEY_LEFT_ALT = GLFW_KEY_LEFT_ALT,
		QX_KEY_LEFT_SUPER = GLFW_KEY_LEFT_SUPER,
		QX_KEY_RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
		QX_KEY_RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL,
		QX_KEY_RIGHT_ALT = GLFW_KEY_RIGHT_ALT,
		QX_KEY_RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER,
		QX_KEY_MENU = GLFW_KEY_MENU,

		QX_MOUSE_BUTTON_LEFT = GLFW_MOUSE_BUTTON_LEFT,
		QX_MOUSE_BUTTON_RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
		QX_MOUSE_BUTTON_MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE,
	};

	enum class EKeyState
	{
		DOWN = GLFW_REPEAT,
		UP,
		PRESSED = GLFW_PRESS,
		RELEASED = GLFW_RELEASE
	};

	struct QUANTIX_API Input
	{
		EKey key;
		EKeyState state;
	};

	class QUANTIX_API InputManager
	{
	private:
		#pragma region Attributes
			
		Input	_inputs[121] = {
			{EKey::QX_KEY_SPACE, EKeyState::UP},
			{EKey::QX_KEY_APOSTROPHE, EKeyState::UP},
			{EKey::QX_KEY_COMMA, EKeyState::UP},
			{EKey::QX_KEY_MINUS, EKeyState::UP},
			{EKey::QX_KEY_PERIOD, EKeyState::UP},
			{EKey::QX_KEY_SLASH, EKeyState::UP},
			{EKey::QX_KEY_BACKSLASH, EKeyState::UP},
			{EKey::QX_KEY_SEMICOLON, EKeyState::UP},
			{EKey::QX_KEY_EQUAL, EKeyState::UP},
			{EKey::QX_KEY_0, EKeyState::UP},
			{EKey::QX_KEY_1,EKeyState::UP},
			{EKey::QX_KEY_2, EKeyState::UP},
			{EKey::QX_KEY_3, EKeyState::UP},
			{EKey::QX_KEY_4, EKeyState::UP},
			{EKey::QX_KEY_5, EKeyState::UP},
			{EKey::QX_KEY_6, EKeyState::UP},
			{EKey::QX_KEY_7, EKeyState::UP},
			{EKey::QX_KEY_8, EKeyState::UP},
			{EKey::QX_KEY_9, EKeyState::UP},
			{EKey::QX_KEY_A, EKeyState::UP},
			{EKey::QX_KEY_B, EKeyState::UP},
			{EKey::QX_KEY_C, EKeyState::UP},
			{EKey::QX_KEY_D, EKeyState::UP},
			{EKey::QX_KEY_E, EKeyState::UP},
			{EKey::QX_KEY_F, EKeyState::UP},
			{EKey::QX_KEY_G, EKeyState::UP},
			{EKey::QX_KEY_H, EKeyState::UP},
			{EKey::QX_KEY_I, EKeyState::UP},
			{EKey::QX_KEY_J, EKeyState::UP},
			{EKey::QX_KEY_K, EKeyState::UP},
			{EKey::QX_KEY_L, EKeyState::UP},
			{EKey::QX_KEY_M, EKeyState::UP},
			{EKey::QX_KEY_N, EKeyState::UP},
			{EKey::QX_KEY_O, EKeyState::UP},
			{EKey::QX_KEY_P, EKeyState::UP},
			{EKey::QX_KEY_Q, EKeyState::UP},
			{EKey::QX_KEY_R, EKeyState::UP},
			{EKey::QX_KEY_S, EKeyState::UP},
			{EKey::QX_KEY_T, EKeyState::UP},
			{EKey::QX_KEY_U, EKeyState::UP},
			{EKey::QX_KEY_V, EKeyState::UP},
			{EKey::QX_KEY_W, EKeyState::UP},
			{EKey::QX_KEY_X, EKeyState::UP},
			{EKey::QX_KEY_Y, EKeyState::UP},
			{EKey::QX_KEY_Z, EKeyState::UP},
			{EKey::QX_KEY_LEFT_BRACKET, EKeyState::UP},
			{EKey::QX_KEY_RIGHT_BRACKET, EKeyState::UP},
			{EKey::QX_KEY_GRAVE_ACCENT, EKeyState::UP},

			{EKey::QX_KEY_ESCAPE, EKeyState::UP},
			{EKey::QX_KEY_ENTER, EKeyState::UP},
			{EKey::QX_KEY_TAB, EKeyState::UP},
			{EKey::QX_KEY_BACKSPACE, EKeyState::UP},
			{EKey::QX_KEY_INSERT, EKeyState::UP},
			{EKey::QX_KEY_DELETE, EKeyState::UP},
			{EKey::QX_KEY_RIGHT, EKeyState::UP},
			{EKey::QX_KEY_LEFT, EKeyState::UP},
			{EKey::QX_KEY_DOWN, EKeyState::UP},
			{EKey::QX_KEY_UP, EKeyState::UP},
			{EKey::QX_KEY_PAGE_UP, EKeyState::UP},
			{EKey::QX_KEY_PAGE_DOWN, EKeyState::UP},
			{EKey::QX_KEY_HOME, EKeyState::UP},
			{EKey::QX_KEY_END, EKeyState::UP},
			{EKey::QX_KEY_CAPS_LOCK, EKeyState::UP},
			{EKey::QX_KEY_SCROLL_LOCK, EKeyState::UP},
			{EKey::QX_KEY_NUM_LOCK, EKeyState::UP},
			{EKey::QX_KEY_PRINT_SCREEN, EKeyState::UP},
			{EKey::QX_KEY_PAUSE, EKeyState::UP},
			{EKey::QX_KEY_F1, EKeyState::UP},
			{EKey::QX_KEY_F2, EKeyState::UP},
			{EKey::QX_KEY_F3, EKeyState::UP},
			{EKey::QX_KEY_F4, EKeyState::UP},
			{EKey::QX_KEY_F5, EKeyState::UP},
			{EKey::QX_KEY_F6, EKeyState::UP},
			{EKey::QX_KEY_F7, EKeyState::UP},
			{EKey::QX_KEY_F8, EKeyState::UP},
			{EKey::QX_KEY_F9, EKeyState::UP},
			{EKey::QX_KEY_F10, EKeyState::UP},
			{EKey::QX_KEY_F11, EKeyState::UP},
			{EKey::QX_KEY_F12, EKeyState::UP},
			{EKey::QX_KEY_F13, EKeyState::UP},
			{EKey::QX_KEY_F14, EKeyState::UP},
			{EKey::QX_KEY_F15, EKeyState::UP},
			{EKey::QX_KEY_F16, EKeyState::UP},
			{EKey::QX_KEY_F17, EKeyState::UP},
			{EKey::QX_KEY_F18, EKeyState::UP},
			{EKey::QX_KEY_F19, EKeyState::UP},
			{EKey::QX_KEY_F20, EKeyState::UP},
			{EKey::QX_KEY_F21, EKeyState::UP},
			{EKey::QX_KEY_F22, EKeyState::UP},
			{EKey::QX_KEY_F23, EKeyState::UP},
			{EKey::QX_KEY_F24, EKeyState::UP},
			{EKey::QX_KEY_F25, EKeyState::UP},
			{EKey::QX_KEY_KP_0, EKeyState::UP},
			{EKey::QX_KEY_KP_1, EKeyState::UP},
			{EKey::QX_KEY_KP_2, EKeyState::UP},
			{EKey::QX_KEY_KP_3, EKeyState::UP},
			{EKey::QX_KEY_KP_4, EKeyState::UP},
			{EKey::QX_KEY_KP_5, EKeyState::UP},
			{EKey::QX_KEY_KP_6, EKeyState::UP},
			{EKey::QX_KEY_KP_7, EKeyState::UP},
			{EKey::QX_KEY_KP_8, EKeyState::UP},
			{EKey::QX_KEY_KP_9, EKeyState::UP},
			{EKey::QX_KEY_KP_DECIMAL, EKeyState::UP},
			{EKey::QX_KEY_KP_DIVIDE, EKeyState::UP},
			{EKey::QX_KEY_KP_MULTIPLY, EKeyState::UP},
			{EKey::QX_KEY_KP_SUBTRACT, EKeyState::UP},
			{EKey::QX_KEY_KP_ADD, EKeyState::UP},
			{EKey::QX_KEY_KP_ENTER, EKeyState::UP},
			{EKey::QX_KEY_KP_EQUAL, EKeyState::UP},
			{EKey::QX_KEY_LEFT_SHIFT, EKeyState::UP},
			{EKey::QX_KEY_LEFT_CONTROL, EKeyState::UP},
			{EKey::QX_KEY_LEFT_ALT, EKeyState::UP},
			{EKey::QX_KEY_LEFT_SUPER, EKeyState::UP},
			{EKey::QX_KEY_RIGHT_SHIFT, EKeyState::UP},
			{EKey::QX_KEY_RIGHT_CONTROL, EKeyState::UP},
			{EKey::QX_KEY_RIGHT_ALT, EKeyState::UP},
			{EKey::QX_KEY_RIGHT_SUPER, EKeyState::UP},
			{EKey::QX_KEY_MENU, EKeyState::UP},

			{EKey::QX_MOUSE_BUTTON_LEFT,EKeyState::UP},
			{EKey::QX_MOUSE_BUTTON_RIGHT,EKeyState::UP},
			{EKey::QX_MOUSE_BUTTON_MIDDLE, EKeyState::UP}
		};

		Math::QXvec2 _cursorPos;

		#pragma endregion

		#pragma region Constructors

		/**
		 * @brief Construct a new Input Manager object
		 * 
		 */
		InputManager() = default;

		#pragma endregion
	public:
		#pragma region Constructors

		/**
		 * @brief Construct a new Input Manager object
		 * 
		 * @param manager Manager to copy
		 */
		InputManager(const InputManager& manager) = delete;

		/**
		 * @brief Construct a new Input Manager object
		 * 
		 * @param manager Manager to move
		 */
		InputManager(InputManager&& manager) = delete;

		/**
		 * @brief Destroy the Input Manager object
		 * 
		 */
		~InputManager() = default;

		#pragma endregion

		#pragma region Functions

		/**
		 * @brief Get the Instance object
		 * 
		 * @return InputManager* Instance of object
		 */
		inline static InputManager* GetInstance() noexcept
		{
			static InputManager instance;
			return &instance;
		}

		/**
		 * @brief Update Manager
		 * 
		 * @param window Widow for update
		 */
		void Update(GLFWwindow* window) noexcept;

		/**
		 * @brief Get the Key State
		 * 
		 * @param key Key to get the state
		 * @return EKeyState State of the key
		 */
		EKeyState GetKeyState(EKey key) noexcept;

		/**
		 * @brief Get the Cursor Pos object
		 * 
		 * @return Math::QXvec2 Pos of the cursor
		 */
		inline Math::QXvec2 GetCursorPos() noexcept { return _cursorPos; }

		#pragma endregion
	};
}

#define GetKey(key) Quantix::Core::UserEntry::InputManager::GetInstance()->GetKeyState(Quantix::Core::UserEntry::EKey::key)
#define GetMousePos() Quantix::Core::UserEntry::InputManager::GetInstance()->GetCursorPos()

#endif // __INPUTMANAGER_H__