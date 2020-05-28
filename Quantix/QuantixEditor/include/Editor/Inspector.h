#ifndef _INSPECTOR_H_
#define _INSPECTOR_H_

#include <imgui.h>
#include <imgui_internal.h>

#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include <Type.h>
#include <Core/DataStructure/GameObject3D.h>
#include <Core/Platform/Application.h>

#include <rttr/registration.h>

#define PATHIMG "Other/IconEditor/Simulation/"
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
	Inspector(Quantix::Core::DataStructure::GameComponent* object);

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
	inline void												SetNode(Quantix::Core::DataStructure::GameComponent* object) { _object = object; };

	/**
	 * @brief Set the Object Type object
	 *
	 * @param type3D QXbool
	 */
	inline void												Set3D(QXbool type3D) { _is3D = type3D; };

	/**
	 * @brief Set the Object Type object
	 *
	 * @param type2D QXbool
	 */
	inline void												Set2D(QXbool type2D) { _is2D = type2D; };

	/**
	 * @brief Get the Object Type object
	 *
	 * @Return type3D QXbool
	 */
	inline QXbool											Get3D() { return _is3D; };

	/**
	 * @brief Get the Object Type object
	 *
	 * @Return type2D QXbool
	 */
	inline QXbool											Get2D() { return _is2D; };

	/**
	 * @brief Get the Transform3D object
	 * 
	 * @return Transform3D* 
	 */
	inline Quantix::Physic::Transform3D*					GetTransform3D() { return ((Quantix::Core::DataStructure::GameObject3D*)_object)->GetTransform(); };

	/**
	 * @brief Get the Transform2D object
	 *
	 * @return Transform2D*
	 */
	inline Quantix::Physic::Transform2D*					GetTransform2D() { return ((Quantix::Core::DataStructure::GameObject2D*)_object)->GetTransform(); };

	/**
	 * @brief Get the Game Component object
	 * 
	 * @return Quantix::Core::DataStructure::GameComponent* 
	 */
	inline Quantix::Core::DataStructure::GameComponent*		GetGameComponent() { return _object; };
	#pragma endregion Getters&Setters

	/**
	 * @brief Show Transform 3D
	 * 
	 * @param app 
	 */
	void													ShowTransform3D(Quantix::Core::Platform::Application* app);

	/**
	 * @brief Show Transform 2D
	 * 
	 * @param app 
	 */
	void													ShowTransform2D(Quantix::Core::Platform::Application* app);

	/**
	 * @brief Show Layer Object
	 * 
	 * @param currentProp 
	 * @param inst 
	 */
	void													LayerObject(rttr::property currentProp, rttr::instance inst);

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

	void													ShowBehaviour(std::list<QXstring> componentsName, Quantix::Core::Platform::Application* app);

	void													ShowSoundComponents(std::list<QXstring> componentsName, Quantix::Core::Platform::Application* app);

	void													ShowPhysicsComponents(std::list<QXstring> componentsName, Quantix::Core::Platform::Application* app);

	/**
	 * @brief Add Component
	 * 
	 */
	void													ShowAddComponent(Quantix::Core::Platform::Application* app);

	/**
	 * @brief Show Component
	 * 
	 */
	void													ShowComponent(Quantix::Core::Platform::Application* app);

	/**
	 * @brief Add Component
	 * 
	 */
	void													AddComponent(Quantix::Core::Platform::Application* app);

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
	 * @brief UI for generate deformable mesh
	 * 
	 * @param t 
	 * @param inst 
	 * @param app 
	 */
	void													GenerateDeformableMesh(rttr::type t, rttr::instance inst, Quantix::Core::Platform::Application* app);

	/**
	 * @brief Check Specific class
	 * 
	 * @param t 
	 * @param inst 
	 * @param app 
	 */
	void													CheckSpecClass(rttr::type t, rttr::instance inst, Quantix::Core::Platform::Application* app);

	/**
	 * @brief Show XYZ for flags of Rigid Lock Position/Rotation
	 * 
	 * @param isOpen 
	 * @param name 
	 */
	void													ShowXYZ(QXbool& isOpen, QXstring& name);

	/**
	 * @brief Show flag Rigid Lock for Specific appearance
	 * 
	 * @param inst 
	 * @param currentProp 
	 * @param name 
	 * @return QXbool 
	 */
	QXbool													DrawRigidLock(rttr::instance inst, rttr::property currentProp, QXstring& name);

	/**
	 * @brief Get the Instance object
	 * 
	 * @param inst 
	 * @param t 
	 * @param app 
	 */
	void													GetInstance(rttr::instance inst, rttr::type t, Quantix::Core::Platform::Application* app);

	/**
	 * @brief Show Enum
	 *
	 * @param currentProp
	 * @param inst
	 * @param type
	 */
	void													ShowEnum(rttr::property currentProp, rttr::instance inst);

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
	 * @brief Check Primitive Type
	 * 
	 * @param inst 
	 * @param currentProp 
	 * @param type 
	 * @param app 
	 * @return QXbool 
	 */
	QXbool													CheckPrimitiveType(rttr::instance inst, rttr::property currentProp, rttr::type type, Quantix::Core::Platform::Application* app);

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
	Quantix::Core::DataStructure::GameComponent*			_object;
	QXbool													_enable;
	QXbool													_is3D;
	QXbool													_is2D;
	#pragma endregion Attributes
};

#endif  // !_INSPECTOR_H_
