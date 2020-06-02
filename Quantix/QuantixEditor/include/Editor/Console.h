#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <vector>
#include <Inspector.h>

class Console
{
public:
	#pragma region Constructors&Destructor
	/**
	 * @brief Construct a new Console object
	 * 
	 */
	Console() noexcept;

	/**
	 * @brief Destroy the Console object
	 *
	 */
	~Console() noexcept;
#pragma endregion Constructors&Destructor

#pragma region Methods
	/**
	 * @brief Initialisation of Console
	 *
	 * @param app
	 */
	void			Init(Quantix::Core::Platform::Application* app) noexcept;

	/**
	 * @brief Print all the Log
	 *
	 */
	void			PrintLog() noexcept;

	/**
	 * @brief User interface of the console
	 *
	 */
	void			ConsoleUI() noexcept;

	/**
	 * @brief Update of the window update
	 *
	 * @param name
	 * @param flags
	 */
	void			Update(const QXstring& name, ImGuiWindowFlags flags) noexcept;
	#pragma endregion Methods

private:
	#pragma region Attributes
	QXuint												_sizeLog;
	std::vector<bool>									_showTypeLog;
	std::vector<Quantix::Resources::Texture*>			_imgTypeLog;
	#pragma endregion Attributes
};

#endif _CONSOLE_H_