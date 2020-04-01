#ifndef _DOCKER_H_
#define _DOCKER_H_

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include <string>
#include <vector>


class Docker
{
public:
	Docker();
	Docker(const Docker& doc) = default;
	Docker(Docker&& doc) = default;
	~Docker() = default;

	void								Init();

	std::string							CreateWindowEditorDock(std::string name, ImGuiID& id);

	inline std::vector<std::string>		GetWindowsEditor() const { return _winEditor; };
	inline ImGuiID						GetIDDockspace() const { return _idDocker; };

private:
	std::vector<std::string>			_winEditor;
	ImGuiID								_idDocker;
};

#endif // !_DOCKER_H_