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
	Console();

	/**
	 * @brief Destroy the Console object
	 * 
	 */
	~Console();
	#pragma endregion Constructors&Destructor

	#pragma region Methods
	/**
	 * @brief Initialisation of Console
	 * 
	 * @param app 
	 */
	void			Init(Quantix::Core::Platform::Application* app);

	/**
	 * @brief Print all the Log
	 * 
	 */
	void			PrintLog();

	/**
	 * @brief User interface of the console
	 * 
	 */
	void			ConsoleUI();

	/**
	 * @brief Update of the window update
	 * 
	 * @param name 
	 * @param flags 
	 */
	void			Update(const QXstring& name, ImGuiWindowFlags flags);
	#pragma endregion Methods

private:
	#pragma region Attributes
	QXuint												_sizeLog;
	std::vector<bool>									_showTypeLog;
	std::vector<Quantix::Resources::Texture*>			_imgTypeLog;
	#pragma endregion Attributes
};

#endif _CONSOLE_H_