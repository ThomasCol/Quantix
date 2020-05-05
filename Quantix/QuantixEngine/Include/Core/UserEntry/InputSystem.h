#ifndef __INPUTSYSTEM_H__
#define __INPUTSYSTEM_H__

#include <vector>
#include <unordered_map>

#include "Core/DLLHeader.h"

#include "GLFW/glfw3.h"

namespace Quantix::Core::UserEntry
{
	enum class /*QUANTIX_API*/ EButtonType
	{
		KEYBOARD,
		GAMEPAD,
		MOUSE
	};

	enum class /*QUANTIX_API*/ ETriggerType
	{
		DOWN,
		UP,
		PRESSED,
		RELEASED
	};

#pragma region TypeOfKeys

	enum /*QUANTIX_API*/ EKey
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
		QX_KEY_MENU = GLFW_KEY_MENU
	};

	enum /*QUANTIX_API*/ EMouseButton
	{
		QX_MOUSE_BUTTON_LEFT = GLFW_MOUSE_BUTTON_LEFT,
		QX_MOUSE_BUTTON_RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
		QX_MOUSE_BUTTON_MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE
	};

	enum /*QUANTIX_API*/ EGamepadButton
	{
		QX_GAMEPAD_BUTTON_A = GLFW_GAMEPAD_BUTTON_A,
		QX_GAMEPAD_BUTTON_B = GLFW_GAMEPAD_BUTTON_B,
		QX_GAMEPAD_BUTTON_X = GLFW_GAMEPAD_BUTTON_X,
		QX_GAMEPAD_BUTTON_Y = GLFW_GAMEPAD_BUTTON_Y,
		QX_GAMEPAD_BUTTON_LEFT_BUMPER = GLFW_GAMEPAD_BUTTON_LEFT_BUMPER,
		QX_GAMEPAD_BUTTON_RIGHT_BUMPER = GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER,
		QX_GAMEPAD_BUTTON_BACK = GLFW_GAMEPAD_BUTTON_BACK,
		QX_GAMEPAD_BUTTON_START = GLFW_GAMEPAD_BUTTON_START,
		QX_GAMEPAD_BUTTON_GUIDE = GLFW_GAMEPAD_BUTTON_GUIDE,
		QX_GAMEPAD_BUTTON_LEFT_THUMB = GLFW_GAMEPAD_BUTTON_LEFT_THUMB,
		QX_GAMEPAD_BUTTON_RIGHT_THUMB = GLFW_GAMEPAD_BUTTON_RIGHT_THUMB,
		QX_GAMEPAD_BUTTON_DPAD_UP = GLFW_GAMEPAD_BUTTON_DPAD_UP,
		QX_GAMEPAD_BUTTON_DPAD_RIGHT = GLFW_GAMEPAD_BUTTON_DPAD_RIGHT,
		QX_GAMEPAD_BUTTON_DPAD_DOWN = GLFW_GAMEPAD_BUTTON_DPAD_DOWN,
		QX_GAMEPAD_BUTTON_DPAD_LEFT = GLFW_GAMEPAD_BUTTON_DPAD_LEFT
	};

	enum /*QUANTIX_API*/ EGamepadAxis
	{
		QX_GAMEPAD_AXIS_LEFT_X = GLFW_GAMEPAD_AXIS_LEFT_X,
		QX_GAMEPAD_AXIS_LEFT_Y = GLFW_GAMEPAD_AXIS_LEFT_Y,
		QX_GAMEPAD_AXIS_RIGHT_X = GLFW_GAMEPAD_AXIS_RIGHT_X,
		QX_GAMEPAD_AXIS_RIGHT_Y = GLFW_GAMEPAD_AXIS_RIGHT_Y,
		QX_GAMEPAD_AXIS_LEFT_TRIGGER = GLFW_GAMEPAD_AXIS_LEFT_TRIGGER,
		QX_GAMEPAD_AXIS_RIGHT_TRIGGER = GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER
	};
#pragma endregion

	typedef int Joystick;

	struct /*QUANTIX_API*/ Input
	{
	public:

		bool			_isValid = false;
		unsigned int	_index = -1;

		//Methods
		virtual void		React(int action) = 0;
	};

	struct /*QUANTIX_API*/ MouseMouvement : public Input
	{
	public:

		double	_x = 0.f;
		double	_y = 0.f;

		//Callback
		//TODO: Add definitions
		void				Update(double xPos, double yPos);
		//void				React(int action) override;
	};

	struct /*QUANTIX_API*/ Button : public Input
	{
	public:
		//Attributes
		EKey			_scancode;
		EButtonType		_buttonType;
		ETriggerType	_triggerType;
		unsigned int	_index;

		//Callback
		void				Update(int key, int action);
		void				React(int action) override;

		//Constructor & Destructor
		Button(EKey scancode, ETriggerType triggerType);
		//Button(EGamepadButton scancode, ETriggerType triggerType);

		//Operators
		bool				operator==(const Button& k) const;
		bool				operator!=(const Button& k) const;
	};

	struct /*QUANTIX_API*/ KeyPack
	{
		//Attribute
		std::vector<Button>	_buttons;
		unsigned int		_index;

		//Getter
		bool IsValid() const;
	};

	class /*QUANTIX_API*/ InputManager
	{
	private:
		//Attribute
		std::vector<KeyPack>	_packs;
		//MouseMvmt				_mouseMvmt;
		std::vector<Joystick>	_joysticks;

		static InputManager*		instance;

		//Methods
		bool				IsKeyAlreadyInPack(unsigned int indexOfPack, const Button& key);

	public:
		//Constructor & Destructor
		InputManager() = default;
		~InputManager() = default;

		//Methods
		int					AddPack(const KeyPack& pack);
		void				SuppPack(unsigned int indexOfPack);
		int					AddKeyToPack(unsigned int indexOfPack, const Button& key);
		void				SuppKeyFromPack(unsigned int indexOfPack, unsigned int indexOfKey);
		void				CheckKeys(int key, int action);

		//TODO: Add GetMousePos Method

		//GAMEPAD
		/*void	AddJoystick(const Joystick& joystick);
		void	SuppJoystick(const Joystick& joystick);

		void	ManageJoystick(const Joystick& joystick, int event);

		bool	GetJoysticksButtonState(const Joystick& joystick, EGamepadButton button);
		float	GetJoysticksAxis(const Joystick& joystick, EGamepadAxis axis);*/

		//Getter
		//static InputManagers*	GetInstance();
		const KeyPack&		GetPack(unsigned int index);
	};
}

#endif //__INPUTSYSTEM_H__