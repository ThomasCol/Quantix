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
#include "Guizmo.h"
#include "Console.h"


namespace fs = std::filesystem;

struct MouseTest
{
	#pragma region Attributes
	bool	MouseCaptured;
	float	DeltaMouseX;
	float	DeltaMouseY;
	float	MouseX;
	float	MouseY;
	#pragma endregion Attributes
};

class Editor
{
public:
	#pragma region Constructors&Destructor
	
	/**
	 * @brief Construct a new Editor object
	 * 
	 */
	Editor() = default;
	
	/**
	 * @brief Construct a new Editor object
	 * 
	 * @param width QXuint
	 * @param height QXuint
	 */
	Editor(QXuint width, QXuint height);
	
	/**
	 * @brief Construct a new Editor object by copy
	 * 
	 * @param editor 
	 */
	Editor(const Editor& editor) = default;
	
	/**
	 * @brief Construct a new Editor object by move
	 * 
	 * @param editor 
	 */
	Editor(Editor&& editor) = default;

	/**
	 * @brief Destroy the Editor object
	 * 
	 */
	~Editor();
	#pragma endregion Constructors&Destructor

	#pragma region Methods
	/**
	 * @brief Init Editor Artifact
	 * 
	 */
	void												InitEditorArtifact();

	/**
	 * @brief Init image
	 * 
	 */
	void												InitImg();

	/**
	 * @brief Init Editor
	 * 
	 */
	void												Init();

	/**
	 * @brief Initialise Editor Dockspace
	 * 
	 */
	void												InitEditor();

	/**
	 * @brief Init ImGui
	 * 
	 */
	void												InitImGui();

	/**
	 * @brief Debug mode for Profiling
	 * 
	 */
	void												DebugMode();

	/**
	 * @brief Update Editor
	 * 
	 */
	void												Update();

	/**
	 * @brief Update Mouse pos for vision of camera
	 * 
	 * @param camera 
	 */
	void												UpdateMouse(Quantix::Core::Components::Camera* camera);

	/**
	 * @brief Update Camera Editor in Scene
	 * 
	 */
	void												CameraUpdateEditor();

	void												MovePlayerController();

	void												MoveFreeCam();

	/**
	 * @brief Update Main Camera in Game
	 * 
	 */
	void												CameraUpdate();

	/**
	 * @brief Retrieve Camera inside scene
	 * 
	 * @param object 
	 */
	void												CheckNewSceneCamera(Quantix::Core::DataStructure::GameObject3D* object);

	/**
	 * @brief Save & Load of Scene 
	 * 
	 */
	void												SaveLoadScene();

	/**
	 * @brief Update Scene
	 * 
	 */
	void												UpdateScene();

	/**
	 * @brief Update Editor
	 * 
	 * @param FBOGame 
	 * @param FBOScene 
	 */
	void												UpdateEditor();

	/**
	 * @brief Draw All Frame
	 * 
	 * @param name 
	 * @param flags 
	 */
	void												Draw(const QXstring& name, ImGuiWindowFlags flags);

	/**
	 * @brief Draw Menu Bar Frame
	 * 
	 */
	void												DrawMenuBar();
	
	/**
	 * @brief Draw Hierarchy Frame
	 * 
	 * @param name 
	 * @param flags 
	 */
	void												DrawHierarchy(const QXstring& name, ImGuiWindowFlags flags);

	QXstring											GetNameOfShader(QXstring shaderPath);

	/**
	 * @brief Draw Shader Frame for PosProcess
	 * 
	 * @param name 
	 * @param flags 
	 */
	void												DrawShader(const QXstring& name, ImGuiWindowFlags flags);

	/**
	 * @brief Simulation Button
	 * 
	 */
	void												Simulation();

	/**
	 * @brief Change State Simulation
	 * 
	 */
	void												ChangeStateSimulation();

	/**
	 * @brief Show Simulation Window
	 * 
	 */
	void												DrawSimulation();

	void												PrintPower();

	/**
	 * @brief Set the scene focus
	 * 
	 */
	void												FocusScene();

	void												MaximizeOnPlay();

	void												ShowCollider();

	/**
	 * @brief Draw Game
	 * 
	 * @param name 
	 * @param flags 
	 */
	void												DrawGame(const QXstring& name, ImGuiWindowFlags flags);

	/**
	 * @brief Draw Scene
	 * 
	 * @param name 
	 * @param flags 
	 */
	void												DrawScene(const QXstring& name, ImGuiWindowFlags flags);

	/**
	 * @brief Draw Window Console
	 * 
	 * @param name 
	 * @param flags 
	 */
	void												DrawConsole(const QXstring& name, ImGuiWindowFlags flags);

	/**
	 * @brief Draw Explorer Console
	 * 
	 * @param name 
	 * @param flags 
	 */
	void												DrawExplorer(const QXstring& name, ImGuiWindowFlags flags);

	/**
	 * @brief Retrieve Camera of Inspector if no camera set
	 * 
	 */
	void												CheckCamera();

	/**
	 * @brief Draw Inspector Console
	 * 
	 * @param name 
	 * @param flags 
	 */
	void												DrawInspector(const QXstring& name, ImGuiWindowFlags flags);

	#pragma region Getters&Setters
	/**
	 * @brief Get the Win object
	 * 
	 * @return Window& 
	 */
	inline Quantix::Core::Platform::Window&				GetWin() { return _win; };

	/**
	 * @brief Get the App object
	 * 
	 * @return Application* 
	 */
	inline Quantix::Core::Platform::Application*		GetApp() const { return _app; };

	/**
	 * @brief Set the Root object
	 * 
	 * @param object 
	 */
	inline void											SetRoot(Quantix::Core::DataStructure::GameObject3D* object) { _root = object; };
	
	/**
	 * @brief Set the Main Camera object
	 * 
	 * @param camera 
	 */
	inline void											SetMainCamera(Quantix::Core::Components::Camera* camera) { _mainCamera = camera; };

	/**
	 * @brief Get the Main Camera object
	 * 
	 * @return Camera* 
	 */
	inline Quantix::Core::Components::Camera*			GetMainCamera() { return _mainCamera; };

	/**
	 * @brief Get the Editor Camera object
	 * 
	 * @return Camera* 
	 */
	inline Quantix::Core::Components::Camera*			GetEditorCamera() { return _cameraEditor; };

	/**
	 * @brief Get the Play object
	 * 
	 * @return QXbool 
	 */
	inline QXbool										GetPlay() const { return _play; };

	/**
	 * @brief Get the Pause object
	 * 
	 * @return QXbool 
	 */
	inline QXbool										GetPause() const { return _pause; };
	#pragma endregion Getters&Setters
	#pragma endregion Methods

	#pragma region Attributes
	MouseTest*															_mouseInput;
	std::vector<Quantix::Core::Components::Light>						_lights;
	#pragma endregion Attributes
private:
	#pragma region Attributes
	Quantix::Core::Platform::Window										_win;
	Quantix::Core::Platform::Application*								_app;
	rttr::library														_lib;
	Quantix::Core::DataStructure::GameObject3D*							_root;
	Quantix::Core::Components::Camera*									_cameraEditor;
	Quantix::Core::Components::Camera*									_mainCamera;
	Quantix::Core::Components::Camera*									_defaultCamera;

	Quantix::Core::Render::RenderFramebuffer							_sceneBuffer;
	Quantix::Core::Render::RenderFramebuffer							_gameBuffer;

	Guizmo																_guizmo;
	Console																_console;
	Docker																_docker;
	Folder																_folder;
	MenuBar																_menuBar;
	Hierarchy															_hierarchy;
	Explorer															_explorer;

	std::map<QXstring, Quantix::Resources::Texture*>					_simImg;
	std::map<QXstring, QXbool>											_simState;
	std::map<QXbool, Quantix::Core::DataStructure::GameObject3D*>		_hasCamera;
	std::map<QXstring, Quantix::Resources::Texture*>					_command;

	QXbool																_play;
	QXbool																_pause;
	QXbool																_sceneFocus;
	QXbool																_gameFocus;
	QXbool																_maximize;
	QXbool																_showCollider;

	ImGuiWindowFlags													_flagsEditor;
	#pragma endregion Attributes
};

#endif // !_EDITOR_H_
