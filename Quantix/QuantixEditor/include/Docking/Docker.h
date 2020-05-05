#ifndef _DOCKER_H_
#define _DOCKER_H_

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <string>
#include <vector>

#include "Type.h"


class Docker
{
public:
	#pragma region Constructors&Destructor
	Docker();
	Docker(const Docker& doc) = default;
	Docker(Docker&& doc) = default;
	~Docker() = default;
	#pragma endregion


	#pragma region Methods
	/**
	 * @brief Init DockSpace
	 * 
	 */
	void								Init();

	/**
	 * @brief Create a Window Editor Dock object
	 * 
	 * @param name 
	 * @param id 
	 * @return QXstring 
	 */
	QXstring							CreateWindowEditorDock(QXstring name, ImGuiID& id);

	#pragma region Getters
	/**
	 * @brief Get the Windows Editor object
	 * 
	 * @return std::vector<QXstring> 
	 */
	inline std::vector<QXstring>		GetWindowsEditor() const { return _winEditor; };

	/**
	 * @brief 
	 * 
	 * @return ImGuiID 
	 */
	inline ImGuiID						GetIDDockspace() const { return _idDocker; };
	#pragma endregion
	#pragma endregion

private:
	#pragma region Attributes
	std::vector<QXstring>				_winEditor;
	ImGuiID								_idDocker;
	#pragma endregion
};

#endif // !_DOCKER_H_