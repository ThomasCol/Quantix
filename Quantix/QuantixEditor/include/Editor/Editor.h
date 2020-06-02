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
	Editor(QXuint width, QXuint height) noexcept;
	
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
	~Editor() noexcept;
	#pragma endregion Constructors&Destructor

	#pragma region Methods
	/**
	 * @brief Init Editor Artifact
	 * 
	 */
	void												InitEditorArtifact() noexcept;

	/**
	 * @brief Init image
	 * 
	 */
	void												InitImg() noexcept;

	/**
	 * @brief Init Editor
	 * 
	 */
	void												Init() noexcept;

	/**
	 * @brief Initialise Editor Dockspace
	 * 
	 */
	void												InitEditor() noexcept;

	/**
	 * @brief Init ImGui
	 *
	 */
	void												InitImGui() noexcept;

	/**
	 * @brief Debug mode for Profiling
	 *
	 */
	void												DebugMode() noexcept;

	/**
	 * @brief Update Editor
	 *
	 */
	void												Update() noexcept;

	/**
	 * @brief Update Mouse pos for vision of camera
	 *
	 * @param camera
	 */
	void												UpdateMouse(Quantix::Core::Components::Camera* camera) noexcept;

	/**
	 * @brief Update Camera Editor in Scene
	 *
	 */
	void												CameraUpdateEditor() noexcept;

	/**
	 * @brief Move Player Controller
	 *
	 */
	void												MovePlayerController() noexcept;

	/**
	 * @brief Move free camera
	 *
	 */
	void												MoveFreeCam() noexcept;

	/**
	 * @brief Update Main Camera in Game
	 *
	 */
	void												CameraUpdate() noexcept;

	/**
	 * @brief Retrieve Camera inside scene
	 *
	 * @param object
	 */
	void												CheckNewSceneCamera(Quantix::Core::DataStructure::GameObject3D* object) noexcept;

	/**
	 * @brief Save & Load of Scene
	 *
	 */
	void												SaveLoadScene() noexcept;

	/**
	 * @brief Update Scene
	 *
	 */
	void												UpdateScene() noexcept;

	/**
	 * @brief Update Editor
	 *
	 * @param FBOGame
	 * @param FBOScene
	 */
	void												UpdateEditor() noexcept;

	/**
	 * @brief Draw All Frame
	 *
	 * @param name
	 * @param flags
	 */
	void												Draw(const QXstring& name, ImGuiWindowFlags flags) noexcept;

	/**
	 * @brief Draw Menu Bar Frame
	 *
	 */
	void												DrawMenuBar() noexcept;

	/**
	 * @brief Draw Hierarchy Frame
	 *
	 * @param name
	 * @param flags
	 */
	void												DrawHierarchy(const QXstring& name, ImGuiWindowFlags flags) noexcept;

	/**
	 * @brief Get the Name Of Shader object
	 *
	 * @param shaderPath
	 * @return QXstring
	 */
	QXstring											GetNameOfShader(QXstring shaderPath) noexcept;

	/**
	 * @brief Draw Shader Frame for PosProcess
	 *
	 * @param name
	 * @param flags
	 */
	void												DrawShader(const QXstring& name, ImGuiWindowFlags flags) noexcept;

	/**
	 * @brief Simulation Button
	 *
	 */
	void												Simulation() noexcept;

	/**
	 * @brief Change State Simulation
	 *
	 */
	void												ChangeStateSimulation() noexcept;

	/**
	 * @brief Show Simulation Window
	 *
	 */
	void												DrawSimulation() noexcept;

	/**
	 * @brief UI of Power
	 *
	 */
	void												PrintPower() noexcept;

	/**
	 * @brief Set the scene focus
	 *
	 */
	void												FocusScene() noexcept;

	/**
	 * @brief Maximize window game on play
	 *
	 */
	void												MaximizeOnPlay() noexcept;

	/**
	 * @brief Change boolean to show collider
	 *
	 */
	void												ShowCollider() noexcept;

	/**
	 * @brief Draw Game
	 *
	 * @param name
	 * @param flags
	 */
	void												DrawGame(const QXstring& name, ImGuiWindowFlags flags) noexcept;

	/**
	 * @brief Draw Scene
	 *
	 * @param name
	 * @param flags
	 */
	void												DrawScene(const QXstring& name, ImGuiWindowFlags flags) noexcept;

	/**
	 * @brief Draw Window Console
	 *
	 * @param name
	 * @param flags
	 */
	void												DrawConsole(const QXstring& name, ImGuiWindowFlags flags) noexcept;

	/**
	 * @brief Draw Explorer Console
	 *
	 * @param name
	 * @param flags
	 */
	void												DrawExplorer(const QXstring& name, ImGuiWindowFlags flags) noexcept;

	/**
	 * @brief Retrieve Camera of Inspector if no camera set
	 *
	 */
	void												CheckCamera() noexcept;

	/**
	 * @brief Draw Inspector Console
	 *
	 * @param name
	 * @param flags
	 */
	void												DrawInspector(const QXstring& name, ImGuiWindowFlags flags) noexcept;

#pragma region Getters&Setters
	/**
	 * @brief Get the Win object
	 *
	 * @return Window&
	 */
	inline Quantix::Core::Platform::Window&				GetWin() noexcept { return _win; };

	/**
	 * @brief Get the App object
	 *
	 * @return Application*
	 */
	inline Quantix::Core::Platform::Application*		GetApp() const noexcept { return _app; };

	/**
	 * @brief Set the Root object
	 *
	 * @param object
	 */
	inline void											SetRoot(Quantix::Core::DataStructure::GameObject3D* object) noexcept { _root = object; };

	/**
	 * @brief Set the Main Camera object
	 *
	 * @param camera
	 */
	inline void											SetMainCamera(Quantix::Core::Components::Camera* camera) noexcept { _mainCamera = camera; };

	/**
	 * @brief Get the Main Camera object
	 *
	 * @return Camera*
	 */
	inline Quantix::Core::Components::Camera*			GetMainCamera() noexcept { return _mainCamera; };

	/**
	 * @brief Get the Editor Camera object
	 *
	 * @return Camera*
	 */
	inline Quantix::Core::Components::Camera*			GetEditorCamera() noexcept { return _cameraEditor; };

	/**
	 * @brief Get the Play object
	 *
	 * @return QXbool
	 */
	inline QXbool										GetPlay() const noexcept { return _play; };

	/**
	 * @brief Get the Pause object
	 *
	 * @return QXbool
	 */
	inline QXbool										GetPause()const noexcept { return _pause; };
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
