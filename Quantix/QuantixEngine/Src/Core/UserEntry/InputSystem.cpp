#include "Core/UserEntry/InputSystem.h"

#include <iostream>

namespace Quantix::Core::UserEntry
{
	InputMgr* InputMgr::instance{ nullptr };

	Button::Button(EKey scancode, ETriggerType triggerType)
	{
		_scancode = scancode;
		_triggerType = triggerType;
		_isValid = false;
		_buttonType = EButtonType::KEYBOARD;
		_index = -1;
	}
	
	/*Button::Button(EGamepadButton scancode, ETriggerType triggerType)
	{
		_scancode = scancode;
		_triggerType = triggerType;
		_isValid = false;
		_buttonType = GAMEPAD;
		_index = -1;
	}*/

	void Button::Update(int key, int action)
	{
		//Check if key is the one that has been triggered
		if (_scancode == key)
			React(action);
	}

	void Button::React(int action)
	{
		switch (_triggerType)
		{
		case ETriggerType::DOWN:
		{
			if (action == GLFW_PRESS)
			{
				std::cout << "Key/Button " << _scancode << " pressed" << std::endl;
				_isValid = true;
			}
			else if (action == GLFW_RELEASE)
				_isValid = false;
		}
		break;

		case ETriggerType::UP:
		{
			if (action == GLFW_PRESS)
			{
				std::cout << "Key/Button " << _scancode << " pressed" << std::endl;
				_isValid = false;
			}
			else 
				_isValid = true;
		}
		break;

		case ETriggerType::PRESSED:
		{
			if (action == GLFW_PRESS)
			{
				std::cout << "Key/Button " << _scancode << " pressed" << std::endl;
				_isValid = true;
			}
			else
				_isValid = false;
		}
		break;

		case ETriggerType::RELEASED:
		{
			if (action == GLFW_RELEASE)
			{
				std::cout << "Key/Button " << _scancode << " released" << std::endl;
				_isValid = true;
			}
			else
				_isValid = false;
		}
		break;
		}
	}

	bool Button::operator==(const Button& k) const
	{
		return (_scancode == k._scancode && _triggerType == k._triggerType);
	}

	bool Button::operator!=(const Button& k) const
	{
		return (_scancode != k._scancode || _triggerType != k._triggerType);
	}


	bool KeyPack::IsValid() const
	{
		//Check if all keys of pack are valid
		for (std::vector<Button>::const_iterator it = _buttons.cbegin(); it != _buttons.cend(); ++it)
			if (!(*it)._isValid)
				return false;

		return true;
	}

	const KeyPack& InputMgr::GetPack(unsigned int index)
	{
		return _packs[index];
	}

	InputMgr* InputMgr::GetInstance()
	{
		if (instance == nullptr)
			instance = new InputMgr;

		return instance;
	}


	bool InputMgr::IsKeyAlreadyInPack(unsigned int indexOfPack, const Button& key)
	{
		//for going through list of keys of packs
		for (std::vector<Button>::const_iterator itK = _packs[indexOfPack]._buttons.cbegin(); itK != _packs[indexOfPack]._buttons.cend(); ++itK)
			if ((*itK) == key)
				return true;

		return false;
	}

	int InputMgr::AddPack(const KeyPack& pack)
	{
		_packs.push_back(pack);
		return (int)_packs.size() - 1;
	}

	void InputMgr::SuppPack(unsigned int indexOfPack)
	{
		if (indexOfPack > _packs.size())
			return;

		std::vector<KeyPack>::const_iterator it = _packs.cbegin() + indexOfPack;
		_packs.erase(it);
	}

	int InputMgr::AddKeyToPack(unsigned int indexOfPack, const Button& button)
	{
		if (indexOfPack > _packs.size())
		{
			std::cout << "Couldn't add button in a non existing pack " << indexOfPack << std::endl;
			return -1;
		}

		if (!IsKeyAlreadyInPack(indexOfPack, button))
		{
			_packs[indexOfPack]._buttons.push_back(button);
			_packs[indexOfPack]._buttons.back()._index = (int)_packs[indexOfPack]._buttons.size() - 1;
			return _packs[indexOfPack]._buttons.back()._index;
		}

		return -1;
	}

	void InputMgr::SuppKeyFromPack(unsigned int indexOfPack, unsigned int indexOfKey)
	{
		if (indexOfPack > _packs.size())
			return;

		//for going through list of packs
		for (std::vector<KeyPack>::const_iterator itP = _packs.cbegin(); itP != _packs.cend(); ++itP)
		{
			if (indexOfKey > (*itP)._buttons.size())
				break;

			//for going through list of keys of packs
			for (std::vector<Button>::const_iterator itK = (*itP)._buttons.cbegin(); itK != (*itP)._buttons.cend(); ++itK)
			{
				if ((*itK)._index == indexOfKey)
				{
					_packs[indexOfPack]._buttons.erase(itK);
					return;
				}
			}
		}
	}

	void InputMgr::CheckKeys(int key, int action)
	{
		//for going through list of packs
		std::vector<KeyPack>::iterator itP;
		for (itP = _packs.begin(); itP != _packs.end(); ++itP)
		{
			//for going through list of keys of packs
			std::vector<Button>::iterator itK;
			for (itK = (*itP)._buttons.begin(); itK != (*itP)._buttons.end(); ++itK)
				(*itK).Update(key, action);
		}
	}

	/*void InputMgr::AddJoystick(const Joystick& joystick)
	{
		_joysticks.push_back(joystick);
	}

	void InputMgr::SuppJoystick(const Joystick& joystick)
	{
		for (std::vector<Joystick>::iterator it = _joysticks.begin(); it != _joysticks.end(); ++it)
		{
			if ((*it) == joystick)
			{
				_joysticks.erase(it);
				return;
			}
		}
	}

	void InputMgr::ManageJoystick(const Joystick& joystick, int event)
	{
		if (event == GLFW_CONNECTED)
			AddJoystick(joystick);
		else if (event == GLFW_DISCONNECTED)
			SuppJoystick(joystick);
	}

	bool InputMgr::GetJoysticksButtonState(const Joystick& joystick, EGamepadButton button)
	{
		//Update every gamepad

		GLFWgamepadstate state;

		if (glfwGetGamepadState(joystick, &state))
			return state.buttons[button];
		else
			return false;
	}

	float InputMgr::GetJoysticksAxis(const Joystick& joystick, EGamepadAxis axis)
	{
		GLFWgamepadstate state;

		if (glfwGetGamepadState(joystick, &state))
			return state.axes[axis];
		else
			return 0.0f;
	}*/
}