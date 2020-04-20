#ifndef _EDITOR_H_
#define _EDITOR_H_

#include <rttr/library.h>
#include <map>
#include <cstdlib>
#include <Core/Platform/Application.h>
#include <Core/DataStructure/GameObject3D.h>

#include "Window.h"
#include "Docker.h"
#include "MenuBar.h"
#include "Hierarchy.h"
#include "Explorer.h"
#include <imGuizmo.h>


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
	void												ShowGuizmoObject(Quantix::Physic::Transform3D* transform);
	void												DrawGuizmo();
	void												DrawScene(const QXstring& name, ImGuiWindowFlags flags);

	void												PrintLog();

	void												DrawConsole(const QXstring& name, ImGuiWindowFlags flags);
	void												DrawExplorer(const QXstring& name, ImGuiWindowFlags flags);
	void												DrawInspector(const QXstring& name, ImGuiWindowFlags flags);

	inline Quantix::Core::Platform::Window&				GetWin() { return _win; };
	inline Quantix::Core::Platform::Application*		GetApp() const { return _app; };
	inline void											SetRoot(Quantix::Core::DataStructure::GameObject3D* object) { _root = object; };
	inline void											SetMainCamera(Quantix::Core::Components::Camera* camera) { _mainCamera = camera; };

	MouseTest*											_mouseInput;
private:
	Quantix::Core::Platform::Window						_win;
	Quantix::Core::Platform::Application*				_app;
	rttr::library										_lib;
	Quantix::Core::DataStructure::GameObject3D*			_root;
	Quantix::Core::Components::Camera*					_mainCamera;

	Docker												_docker;
	Folder												_folder;
	MenuBar												_menuBar;
	Hierarchy											_hierarchy;
	Explorer											_explorer;

	std::map<QXstring, Quantix::Resources::Texture*>	_simImg;
	std::map<QXstring, QXbool>							_simState;

	QXuint												_fbo;
	ImGuizmo::OPERATION									_guizmoType;
	ImGuiWindowFlags									_flagsEditor;
};

#endif // !_EDITOR_H_
