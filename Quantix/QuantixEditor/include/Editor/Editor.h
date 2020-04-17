#ifndef _EDITOR_H_
#define _EDITOR_H_

#include <rttr/library.h>
#include <map>
#include <cstdlib>
#include <Core/Platform/Application.h>

#include "Window.h"
#include "Docker.h"
#include "MenuBar.h"
#include "Hierarchy.h"
#include "Explorer.h"

namespace fs = std::filesystem;

struct MouseTest
{
	bool	MouseCaptured;
	float	DeltaMouseX;
	float	DeltaMouseY;
	float	MouseX;
	float	MouseY;
};

class Editor
{
public:
	Editor() = default;
	Editor(QXuint width, QXuint height);
	Editor(const Editor& editor) = default;
	Editor(Editor&& editor) = default;
	~Editor();

	void												Init();
	void												InitImGui();
	void												Update(QXuint FBO);

	void												Draw(const QXstring& name, ImGuiWindowFlags flags);
	void												DrawMenuBar();
	void												DrawHierarchy(const QXstring& name, ImGuiWindowFlags flags);
	void												Simulation();
	void												DrawSimulation();
	void												DrawScene(const QXstring& name, ImGuiWindowFlags flags);

	void												PrintLog();

	void												DrawConsole(const QXstring& name, ImGuiWindowFlags flags);
	void												DrawExplorer(const QXstring& name, ImGuiWindowFlags flags);
	void												DrawInspector(const QXstring& name, ImGuiWindowFlags flags);

	inline Quantix::Core::Platform::Window&				GetWin() { return _win; };
	inline Quantix::Core::Platform::Application*		GetApp() const { return _app; };
	inline void											SetObject(Quantix::Physic::Transform3D* object) { _graph3D = object; };


	MouseTest*											_mouseInput;
private:
	Quantix::Core::Platform::Window						_win;
	Quantix::Core::Platform::Application*				_app;
	rttr::library										_lib;
	Quantix::Physic::Transform3D*						_graph3D;

	Docker												_docker;
	Folder												_folder;
	MenuBar												_menuBar;
	Hierarchy											_hierarchy;
	Explorer											_explorer;

	std::vector<Quantix::Resources::Texture*>			_simImg;
	std::vector<QXbool>									_simState;
	std::vector<Node>									_object;
	//std::vector<Core::DataStructure::GameComponent*>	_gameComponent;

	QXuint												_fbo;
	ImGuiWindowFlags									_flagsEditor;
};

#endif // !_EDITOR_H_