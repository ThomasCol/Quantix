#include "Core/UserEntry/InputManager.h"

#include "Core/Debugger/Logger.h"

namespace Quantix::Core::UserEntry
{
	void InputManager::Update(GLFWwindow* window) noexcept
	{
		QXint state;

		for (QXuint i = 0; i < 121; ++i)
		{
			if (i < 118)
				state = glfwGetKey(window, (QXint)_inputs[i].key);
			else
				state = glfwGetMouseButton(window, (QXint)_inputs[i].key);

			if (_inputs[i].state == (EKeyState)state)
			{
				if (_inputs[i].state == EKeyState::PRESSED)
					_inputs[i].state = EKeyState::DOWN;
				if (_inputs[i].state == EKeyState::RELEASED)
					_inputs[i].state = EKeyState::UP;
			}
			else
			{
				if (_inputs[i].state == EKeyState::UP && state == GLFW_RELEASE)
					continue;
				if (_inputs[i].state == EKeyState::DOWN && state == GLFW_PRESS)
					continue;

				_inputs[i].state = (EKeyState)state;
			}
		}

		QXdouble posX, posY;
		glfwGetCursorPos(window, &posX, &posY);
		_cursorPos = { (QXfloat)posX, (QXfloat)posY };
	}

	EKeyState InputManager::GetKeyState(EKey key) noexcept
	{
		for (QXuint i = 0; i < 121; ++i)
		{
			if (_inputs[i].key == key)
				return _inputs[i].state;
		}

		return EKeyState::UP;
	}
}