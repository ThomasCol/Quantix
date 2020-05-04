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

	void												InitImg();
	void												Init();
	void												InitImGui();
	void												Update(QXuint FBOGame, QXuint FBOScene);

	void												Draw(const QXstring& name, ImGuiWindowFlags flags);
	void												DrawMenuBar();
	void												DrawHierarchy(const QXstring& name, ImGuiWindowFlags flags);
	void												DrawShader(const QXstring& name, ImGuiWindowFlags flags);
	void												Simulation();
	void												ChangeStateSimulation();
	void												ChangeGuizmoOperation(QXuint index);
	void												LocalWorldGuizmo(QXint pos);
	void												GuizmoUI();
	void												DrawSimulation();
	void												MoveObject(Quantix::Physic::Transform3D* transform, Math::QXmat4& matrix, Math::QXmat4& matrixTmp);
	void												ShowGuizmoObject(Quantix::Physic::Transform3D* transform);
	void												DrawGuizmo();
	void												FocusScene();
	void												DrawGame(const QXstring& name, ImGuiWindowFlags flags);
	void												DrawScene(const QXstring& name, ImGuiWindowFlags flags);

	void												PrintLog();

	void												ConsoleUI();

	void												DrawConsole(const QXstring& name, ImGuiWindowFlags flags);
	void												DrawExplorer(const QXstring& name, ImGuiWindowFlags flags);
	void												DrawInspector(const QXstring& name, ImGuiWindowFlags flags);

	inline Quantix::Core::Platform::Window&				GetWin() { return _win; };
	inline Quantix::Core::Platform::Application*		GetApp() const { return _app; };
	inline void											SetRoot(Quantix::Core::DataStructure::GameObject3D* object) { _root = object; };
	inline void											SetMainCamera(Quantix::Core::Components::Camera* camera) { _mainCamera = camera; };
	inline Quantix::Core::Components::Camera*			GetMainCamera() { return _mainCamera; };
	inline Quantix::Core::Components::Camera*			GetEditorCamera() { return _cameraEditor; };
	inline QXbool										GetPlay() const { return _play; };
	inline QXbool										GetPause() const { return _pause; };

	MouseTest*											_mouseInput;
private:
	Quantix::Core::Platform::Window						_win;
	Quantix::Core::Platform::Application*				_app;
	rttr::library										_lib;
	Quantix::Core::DataStructure::GameObject3D*			_root;
	Quantix::Core::Components::Camera*					_cameraEditor;
	Quantix::Core::Components::Camera*					_mainCamera;
	Quantix::Core::Components::Camera*					_defaultCamera;

	Docker												_docker;
	Folder												_folder;
	MenuBar												_menuBar;
	Hierarchy											_hierarchy;
	Explorer											_explorer;

	std::map<QXstring, Quantix::Resources::Texture*>	_simImg;
	std::map<QXstring, QXbool>							_simState;
	QXbool												_play;
	QXbool												_pause;
	QXbool												_activateFocus;

	QXuint												_fboScene;
	QXuint												_fboGame;
	std::vector<bool>									_showTypeLog;
	std::vector<Quantix::Resources::Texture*>			_imgTypeLog;
	std::vector<Quantix::Resources::Texture*>			_imgGuizmo;
	ImGuizmo::OPERATION									_guizmoType;
	ImGuizmo::MODE										_guizmoMode;
	QXuint												_sizeLog;
	ImGuiWindowFlags									_flagsEditor;
};

#endif // !_EDITOR_H_
