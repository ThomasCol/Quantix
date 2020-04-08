#ifndef _EDITOR_H_
#define _EDITOR_H_

#include <Core/Platform/Application.h>
#include <map>
#include <cstdlib>

#include "Window.h"
#include "Docker.h"
#include "MenuBar.h"
#include "Hierarchy.h"
#include "Explorer.h"

namespace fs = std::filesystem;

class Editor
{
public:
	Editor() = default;
	Editor(QXuint width, QXuint height);
	Editor(const Editor& editor) = default;
	Editor(Editor&& editor) = default;
	~Editor();

	QXbool												Init();
	void												Update(QXuint FBO);

	void												Draw(QXstring name, ImGuiWindowFlags flags);
	void												DrawMenuBar();
	void												DrawHierarchy(QXstring name, ImGuiWindowFlags flags);
	void												Simulation();
	void												DrawSimulation();
	void												DrawScene(QXstring name, ImGuiWindowFlags flags);

	void												PrintLog();

	void												DrawConsole(QXstring name, ImGuiWindowFlags flags);
	void												DrawExplorer(QXstring name, ImGuiWindowFlags flags);
	void												DrawInspector(QXstring name, ImGuiWindowFlags flags);

	inline Quantix::Core::Platform::Window&				GetWin() { return _win; };
	inline Quantix::Core::Platform::Application*		GetApp() const { return _app; };


private:
	Quantix::Core::Platform::Window						_win;
	Quantix::Core::Platform::Application*				_app;
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
	QXbool												_init;
	ImGuiWindowFlags									_flagsEditor;
};

#endif // !_EDITOR_H_