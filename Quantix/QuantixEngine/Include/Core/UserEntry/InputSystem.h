#ifndef __INPUTSYSTEM_H__
#define __INPUTSYSTEM_H__

#include <vector>
#include <unordered_map>

#include "GLFW/glfw3.h"

namespace Quantix::Core::UserEntry
{
	enum class EButtonType
	{
		KEYBOARD,
		GAMEPAD
	};

	enum class ETriggerType
	{
		DOWN,
		UP,
		PRESSED,
		RELEASED
	};

#pragma region TypeOfKeys

	enum EKey
	{
		QTX_KEY_SPACE = GLFW_KEY_SPACE,
		QTX_KEY_APOSTROPHE = GLFW_KEY_APOSTROPHE,
		QTX_KEY_COMMA = GLFW_KEY_COMMA,
		QTX_KEY_MINUS = GLFW_KEY_MINUS,
		QTX_KEY_PERIOD = GLFW_KEY_PERIOD,
		QTX_KEY_SLASH = GLFW_KEY_SLASH,
		QTX_KEY_BACKSLASH = GLFW_KEY_BACKSLASH,
		QTX_KEY_SEMICOLON = GLFW_KEY_SEMICOLON,
		QTX_KEY_EQUAL = GLFW_KEY_EQUAL,
		QTX_KEY_0 = GLFW_KEY_0,
		QTX_KEY_1 = GLFW_KEY_1,
		QTX_KEY_2 = GLFW_KEY_2,
		QTX_KEY_3 = GLFW_KEY_3,
		QTX_KEY_4 = GLFW_KEY_4,
		QTX_KEY_5 = GLFW_KEY_5,
		QTX_KEY_6 = GLFW_KEY_6,
		QTX_KEY_7 = GLFW_KEY_7,
		QTX_KEY_8 = GLFW_KEY_8,
		QTX_KEY_9 = GLFW_KEY_9,
		QTX_KEY_A = GLFW_KEY_A,
		QTX_KEY_B = GLFW_KEY_B,
		QTX_KEY_C = GLFW_KEY_C,
		QTX_KEY_D = GLFW_KEY_D,
		QTX_KEY_E = GLFW_KEY_E,
		QTX_KEY_F = GLFW_KEY_F,
		QTX_KEY_G = GLFW_KEY_G,
		QTX_KEY_H = GLFW_KEY_H,
		QTX_KEY_I = GLFW_KEY_I,
		QTX_KEY_J = GLFW_KEY_J,
		QTX_KEY_K = GLFW_KEY_K,
		QTX_KEY_L = GLFW_KEY_L,
		QTX_KEY_M = GLFW_KEY_M,
		QTX_KEY_N = GLFW_KEY_N,
		QTX_KEY_O = GLFW_KEY_O,
		QTX_KEY_P = GLFW_KEY_P,
		QTX_KEY_Q = GLFW_KEY_Q,
		QTX_KEY_R = GLFW_KEY_R,
		QTX_KEY_S = GLFW_KEY_S,
		QTX_KEY_T = GLFW_KEY_T,
		QTX_KEY_U = GLFW_KEY_U,
		QTX_KEY_V = GLFW_KEY_V,
		QTX_KEY_W = GLFW_KEY_W,
		QTX_KEY_X = GLFW_KEY_X,
		QTX_KEY_Y = GLFW_KEY_Y,
		QTX_KEY_Z = GLFW_KEY_Z,
		QTX_KEY_LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET,
		QTX_KEY_RIGHT_BRACKET = GLFW_KEY_RIGHT_BRACKET,
		QTX_KEY_GRAVE_ACCENT = GLFW_KEY_GRAVE_ACCENT,

		QTX_KEY_ESCAPE = GLFW_KEY_ESCAPE,
		QTX_KEY_ENTER = GLFW_KEY_ENTER,
		QTX_KEY_TAB = GLFW_KEY_TAB,
		QTX_KEY_BACKSPACE = GLFW_KEY_BACKSPACE,
		QTX_KEY_INSERT = GLFW_KEY_INSERT,
		QTX_KEY_DELETE = GLFW_KEY_DELETE,
		QTX_KEY_RIGHT = GLFW_KEY_RIGHT,
		QTX_KEY_LEFT = GLFW_KEY_LEFT,
		QTX_KEY_DOWN = GLFW_KEY_DOWN,
		QTX_KEY_UP = GLFW_KEY_UP,
		QTX_KEY_PAGE_UP = GLFW_KEY_PAGE_UP,
		QTX_KEY_PAGE_DOWN = GLFW_KEY_PAGE_DOWN,
		QTX_KEY_HOME = GLFW_KEY_HOME,
		QTX_KEY_END = GLFW_KEY_END,
		QTX_KEY_CAPS_LOCK = GLFW_KEY_CAPS_LOCK,
		QTX_KEY_SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK,
		QTX_KEY_NUM_LOCK = GLFW_KEY_NUM_LOCK,
		QTX_KEY_PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN,
		QTX_KEY_PAUSE = GLFW_KEY_PAUSE,
		QTX_KEY_F1 = GLFW_KEY_F1,
		QTX_KEY_F2 = GLFW_KEY_F2,
		QTX_KEY_F3 = GLFW_KEY_F3,
		QTX_KEY_F4 = GLFW_KEY_F4,
		QTX_KEY_F5 = GLFW_KEY_F5,
		QTX_KEY_F6 = GLFW_KEY_F6,
		QTX_KEY_F7 = GLFW_KEY_F7,
		QTX_KEY_F8 = GLFW_KEY_F8,
		QTX_KEY_F9 = GLFW_KEY_F9,
		QTX_KEY_F10 = GLFW_KEY_F10,
		QTX_KEY_F11 = GLFW_KEY_F11,
		QTX_KEY_F12 = GLFW_KEY_F12,
		QTX_KEY_F13 = GLFW_KEY_F13,
		QTX_KEY_F14 = GLFW_KEY_F14,
		QTX_KEY_F15 = GLFW_KEY_F15,
		QTX_KEY_F16 = GLFW_KEY_F16,
		QTX_KEY_F17 = GLFW_KEY_F17,
		QTX_KEY_F18 = GLFW_KEY_F18,
		QTX_KEY_F19 = GLFW_KEY_F19,
		QTX_KEY_F20 = GLFW_KEY_F20,
		QTX_KEY_F21 = GLFW_KEY_F21,
		QTX_KEY_F22 = GLFW_KEY_F22,
		QTX_KEY_F23 = GLFW_KEY_F23,
		QTX_KEY_F24 = GLFW_KEY_F24,
		QTX_KEY_F25 = GLFW_KEY_F25,
		QTX_KEY_KP_0 = GLFW_KEY_KP_0,
		QTX_KEY_KP_1 = GLFW_KEY_KP_1,
		QTX_KEY_KP_2 = GLFW_KEY_KP_2,
		QTX_KEY_KP_3 = GLFW_KEY_KP_3,
		QTX_KEY_KP_4 = GLFW_KEY_KP_4,
		QTX_KEY_KP_5 = GLFW_KEY_KP_5,
		QTX_KEY_KP_6 = GLFW_KEY_KP_6,
		QTX_KEY_KP_7 = GLFW_KEY_KP_7,
		QTX_KEY_KP_8 = GLFW_KEY_KP_8,
		QTX_KEY_KP_9 = GLFW_KEY_KP_9,
		QTX_KEY_KP_DECIMAL = GLFW_KEY_KP_DECIMAL,
		QTX_KEY_KP_DIVIDE = GLFW_KEY_KP_DIVIDE,
		QTX_KEY_KP_MULTIPLY = GLFW_KEY_KP_MULTIPLY,
		QTX_KEY_KP_SUBTRACT = GLFW_KEY_KP_SUBTRACT,
		QTX_KEY_KP_ADD = GLFW_KEY_KP_ADD,
		QTX_KEY_KP_ENTER = GLFW_KEY_KP_ENTER,
		QTX_KEY_KP_EQUAL = GLFW_KEY_KP_EQUAL,
		QTX_KEY_LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
		QTX_KEY_LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL,
		QTX_KEY_LEFT_ALT = GLFW_KEY_LEFT_ALT,
		QTX_KEY_LEFT_SUPER = GLFW_KEY_LEFT_SUPER,
		QTX_KEY_RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
		QTX_KEY_RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL,
		QTX_KEY_RIGHT_ALT = GLFW_KEY_RIGHT_ALT,
		QTX_KEY_RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER,
		QTX_KEY_MENU = GLFW_KEY_MENU
	};

	enum EMouseButton
	{
		QTX_MOUSE_BUTTON_1 = GLFW_MOUSE_BUTTON_1,
		QTX_MOUSE_BUTTON_2 = GLFW_MOUSE_BUTTON_2,
		QTX_MOUSE_BUTTON_3 = GLFW_MOUSE_BUTTON_3,
		QTX_MOUSE_BUTTON_4 = GLFW_MOUSE_BUTTON_4,
		QTX_MOUSE_BUTTON_5 = GLFW_MOUSE_BUTTON_5,
		QTX_MOUSE_BUTTON_6 = GLFW_MOUSE_BUTTON_6,
		QTX_MOUSE_BUTTON_7 = GLFW_MOUSE_BUTTON_7,
		QTX_MOUSE_BUTTON_8 = GLFW_MOUSE_BUTTON_8
	};

	enum EGamepadButton
	{
		QTX_GAMEPAD_BUTTON_A = GLFW_GAMEPAD_BUTTON_A,
		QTX_GAMEPAD_BUTTON_B = GLFW_GAMEPAD_BUTTON_B,
		QTX_GAMEPAD_BUTTON_X = GLFW_GAMEPAD_BUTTON_X,
		QTX_GAMEPAD_BUTTON_Y = GLFW_GAMEPAD_BUTTON_Y,
		QTX_GAMEPAD_BUTTON_LEFT_BUMPER = GLFW_GAMEPAD_BUTTON_LEFT_BUMPER,
		QTX_GAMEPAD_BUTTON_RIGHT_BUMPER = GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER,
		QTX_GAMEPAD_BUTTON_BACK = GLFW_GAMEPAD_BUTTON_BACK,
		QTX_GAMEPAD_BUTTON_START = GLFW_GAMEPAD_BUTTON_START,
		QTX_GAMEPAD_BUTTON_GUIDE = GLFW_GAMEPAD_BUTTON_GUIDE,
		QTX_GAMEPAD_BUTTON_LEFT_THUMB = GLFW_GAMEPAD_BUTTON_LEFT_THUMB,
		QTX_GAMEPAD_BUTTON_RIGHT_THUMB = GLFW_GAMEPAD_BUTTON_RIGHT_THUMB,
		QTX_GAMEPAD_BUTTON_DPAD_UP = GLFW_GAMEPAD_BUTTON_DPAD_UP,
		QTX_GAMEPAD_BUTTON_DPAD_RIGHT = GLFW_GAMEPAD_BUTTON_DPAD_RIGHT,
		QTX_GAMEPAD_BUTTON_DPAD_DOWN = GLFW_GAMEPAD_BUTTON_DPAD_DOWN,
		QTX_GAMEPAD_BUTTON_DPAD_LEFT = GLFW_GAMEPAD_BUTTON_DPAD_LEFT
	};

	enum EGamepadAxis
	{
		QTX_GAMEPAD_AXIS_LEFT_X = GLFW_GAMEPAD_AXIS_LEFT_X,
		QTX_GAMEPAD_AXIS_LEFT_Y = GLFW_GAMEPAD_AXIS_LEFT_Y,
		QTX_GAMEPAD_AXIS_RIGHT_X = GLFW_GAMEPAD_AXIS_RIGHT_X,
		QTX_GAMEPAD_AXIS_RIGHT_Y = GLFW_GAMEPAD_AXIS_RIGHT_Y,
		QTX_GAMEPAD_AXIS_LEFT_TRIGGER = GLFW_GAMEPAD_AXIS_LEFT_TRIGGER,
		QTX_GAMEPAD_AXIS_RIGHT_TRIGGER = GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER
	};
#pragma endregion

	typedef int Joystick;

	struct Input
	{
	public:

		bool			_isValid = false;
		unsigned int	_index = -1;

		//Methods
		virtual void React(int action) = 0;
	};

	struct MouseMvmt : public Input
	{
	public:

		double	_x = 0.f;
		double	_y = 0.f;

		//Callback
		//TODO: Add definitions
		void Update(double xPos, double yPos);
		void React(int action) override;
	};

	struct Button : public Input
	{
	public:
		//Attributes
		EKey			_scancode;
		EButtonType		_buttonType;
		ETriggerType	_triggerType;
		unsigned int	_index;

		//Callback
		void Update(int key, int action);
		void React(int action) override;

		//Constructor & Destructor
		Button(EKey scancode, ETriggerType triggerType);
		//Button(EGamepadButton scancode, ETriggerType triggerType);

		//Operators
		bool operator==(const Button& k) const;
		bool operator!=(const Button& k) const;
	};

	struct KeyPack
	{
		//Attribute
		std::vector<Button>	_buttons;
		unsigned int		_index;

		//Getter
		bool IsValid() const;
	};

	class InputMgr
	{
	private:
		//Attribute
		std::vector<KeyPack>	_packs;
		MouseMvmt				_mouseMvmt;
		std::vector<Joystick>	_joysticks;

		static InputMgr* instance;

		//Methods
		bool	IsKeyAlreadyInPack(unsigned int indexOfPack, const Button& key);

	public:
		//Constructor & Destructor
		InputMgr() = default;
		~InputMgr() = default;

		//Methods
		int		AddPack(const KeyPack& pack);
		void	SuppPack(unsigned int indexOfPack);
		int		AddKeyToPack(unsigned int indexOfPack, const Button& key);
		void	SuppKeyFromPack(unsigned int indexOfPack, unsigned int indexOfKey);
		void	CheckKeys(int key, int action);

		//TODO: Add GetMousePos Method

		//GAMEPAD
		/*void	AddJoystick(const Joystick& joystick);
		void	SuppJoystick(const Joystick& joystick);

		void	ManageJoystick(const Joystick& joystick, int event);

		bool	GetJoysticksButtonState(const Joystick& joystick, EGamepadButton button);
		float	GetJoysticksAxis(const Joystick& joystick, EGamepadAxis axis);*/

		//Getter
		static InputMgr* GetInstance();
		const KeyPack& GetPack(unsigned int index);
	};
}

#endif //__INPUTSYSTEM_H__