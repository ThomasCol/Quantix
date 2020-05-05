#ifndef _INSPECTOR_H_
#define _INSPECTOR_H_

#include <imgui.h>
#include <imgui_internal.h>

#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include <Type.h>
#include <Node.h>
#include <Core/DataStructure/GameObject3D.h>
#include <Core/Platform/Application.h>

#include <rttr/registration.h>

#include "Type.h"

#define PATHIMG "media/IconEditor/Simulation/"
#define PNG ".png"

class Inspector
{
public:
	#pragma region Constructors&Destructor
	/**
	 * @brief Construct a new Inspector object
	 * 
	 */
	Inspector() = default;

	/**
	 * @brief Construct a new Inspector object
	 * 
	 * @param transform 
	 */
	Inspector(Quantix::Physic::Transform3D* transform);

	/**
	 * @brief Construct a new Inspector object
	 * 
	 * @param inspector 
	 */
	Inspector(const Inspector& inspector) = default;

	/**
	 * @brief Construct a new Inspector object
	 * 
	 * @param inspector 
	 */
	Inspector(Inspector&& inspector) = default;

	/**
	 * @brief Destroy the Inspector object
	 * 
	 */
	~Inspector() = default;
	#pragma endregion Constructors&Destructor

	#pragma region Methods
	#pragma region Getters&Setters
	/**
	 * @brief Set the Enable object
	 * 
	 * @param enable QXbool
	 */
	inline void												SetEnable(QXbool enable) { _enable = enable; };

	/**
	 * @brief Set the Node object
	 * 
	 * @param transform Quantix::Physic::Transform3D*
	 */
	inline void												SetNode(Quantix::Physic::Transform3D* transform) { _transform = transform; };

	/**
	 * @brief Get the Transform object
	 * 
	 * @return Transform3D* 
	 */
	inline Quantix::Physic::Transform3D*					GetTransform() { return _transform; };
	#pragma endregion Getters&Setters

	/**
	 * @brief Update
	 * 
	 * @param win Window&
	 * @param app Application*
	 */
	void													Update(Quantix::Core::Platform::Window& win, Quantix::Core::Platform::Application* app);

	/**
	 * @brief Popup Menu Item
	 * 
	 * @param component Component*
	 */
	void													PopUpMenuItem(Quantix::Core::DataStructure::Component* component);

	/**
	 * @brief Show Component
	 * 
	 */
	void													ShowComponent();

	/**
	 * @brief Add Component
	 * 
	 */
	void													AddComponent();

	/**
	 * @brief Show Material Path
	 * 
	 * @param inst 
	 * @param currentProp 
	 * @param app 
	 */
	void													DrawMaterialPath(rttr::instance inst, rttr::property currentProp, Quantix::Core::Platform::Application* app);

	/**
	 * @brief Show Model Path
	 * 
	 * @param inst 
	 * @param currentProp 
	 * @param app 
	 */
	void													DrawModelPath(rttr::instance inst, rttr::property currentProp, Quantix::Core::Platform::Application* app);

	/**
	 * @brief Show Texture Path
	 * 
	 * @param inst 
	 * @param currentProp 
	 * @param app 
	 */
	void													DrawMTexturePath(rttr::instance inst, rttr::property currentProp, Quantix::Core::Platform::Application* app);

	/**
	 * @brief Show Sound Path of SoundEmitter
	 * 
	 * @param inst 
	 * @param t 
	 * @param currentProp 
	 * @param app 
	 */
	void													DrawSoundEmitterPath(rttr::instance inst, rttr::type t, rttr::property currentProp, Quantix::Core::Platform::Application* app);

	/**
	 * @brief Set the Attributes Listener object
	 * 
	 * @param inst 
	 * @param t 
	 */
	void													SetAttributesListener(rttr::instance inst, rttr::type t);

	/**
	 * @brief Set the Sound object
	 * 
	 * @param inst 
	 * @param t 
	 * @param currentProp 
	 * @param app 
	 */
	void													SetSound(rttr::instance inst, rttr::type t, rttr::property currentProp, Quantix::Core::Platform::Application* app);

	/**
	 * @brief Get the Instance object
	 * 
	 * @param inst 
	 * @param t 
	 * @param app 
	 */
	void													GetInstance(rttr::instance inst, rttr::type t, Quantix::Core::Platform::Application* app);

	/**
	 * @brief Show Light Enum
	 * 
	 * @param currentProp 
	 * @param inst 
	 * @param type 
	 */
	void													ShowLightEnum(rttr::property currentProp, rttr::instance inst, rttr::type type);

	/**
	 * @brief Show Sound Mode Enum
	 * 
	 * @param currentProp 
	 * @param inst 
	 * @param type 
	 */
	void													ShowSoundModeEnum(rttr::property currentProp, rttr::instance inst, rttr::type type);

	/**
	 * @brief Look Type of Instance or Property
	 * 
	 * @param inst 
	 * @param type 
	 * @param currentProp 
	 * @param app 
	 */
	void													LookType(rttr::instance inst, rttr::type type, rttr::property currentProp, Quantix::Core::Platform::Application* app);

	/**
	 * @brief Draw Variable
	 * 
	 * @param inst 
	 * @param currentProp 
	 * @param type 
	 * @param app 
	 */
	void													DrawVariable(rttr::instance inst, rttr::property currentProp, rttr::type type, Quantix::Core::Platform::Application* app);
	#pragma endregion Methods

private:
	#pragma region Attributes
	Quantix::Physic::Transform3D*							_transform;
	QXbool													_enable;
	#pragma endregion Attributes
};

#endif // !_INSPECTOR_H_
