#ifndef _HIERARCHY_H_
#define _HIERARCHY_H_

#include <list>
#include <string>
#include <Inspector.h>
#include <Core/Platform/Application.h>

class Hierarchy
{
public:
	#pragma region Constructors&Destructor
	/**
	 * @brief Construct a new Hierarchy object
	 * 
	 */
	Hierarchy() = default;
	
	/**
	 * @brief Destroy the Hierarchy object
	 * 
	 */
	~Hierarchy() = default;
	#pragma endregion Constructors&Destructor

	#pragma region Methods
	/**
	 * @brief Update
	 * 
	 * @param name QXstring
	 * @param flags ImGuiWindowFlags
	 * @param gameComponents Transform3D
	 * @param scene Scene*
	 */
	void				Update(QXstring name, ImGuiWindowFlags flags, Quantix::Physic::Transform3D* gameComponents, Quantix::Core::Platform::Application* app);

	/**
	 * @brief Draw Object
	 * 
	 * @param nodeGlobal std::list<Quantix::Physic::Transform3D*>&
	 * @param node std::list<Quantix::Physic::Transform3D*>&
	 * @param scene Scene*
	 */
	void				DrawObject(std::list<Quantix::Physic::Transform3D*>& nodeGlobal, std::list<Quantix::Physic::Transform3D*>& node, Quantix::Core::Platform::Application* app);

	void				DrawGameComponent(Quantix::Core::Platform::Application* app);

	void				DrawObject2D(std::list<Quantix::Physic::Transform2D*>& nodeGlobal, std::list<Quantix::Physic::Transform2D*>& node, Quantix::Core::Platform::Application* app);

	void				DesactiveAllNodes(void* ptr, Quantix::Core::Platform::Application* app);

	/**
	 * @brief Create a Child object
	 * 
	 * @param select QXbool&
	 * @param nodes std::list<Quantix::Physic::Transform3D*>&
	 * @param scene Scene*
	 */
	void				CreateChild(QXbool& select, std::list<Quantix::Physic::Transform3D*>& nodes, Quantix::Core::Platform::Application* app);

	void				RemoveObject(QXbool& select, std::list<Quantix::Physic::Transform3D*>& nodes, Quantix::Core::Platform::Application* app);

	void				RemoveObject2D(QXbool& select, std::list<Quantix::Physic::Transform2D*>& nodes, Quantix::Core::Platform::Application* app);

	void				RemoveGC(QXbool& select, std::list<Quantix::Core::DataStructure::GameComponent*>& nodes, Quantix::Core::Platform::Application* app);

	QXstring			Rename(const QXchar* name, QXsizei size);

	QXbool				PopUpMenuItem2D(std::list<Quantix::Physic::Transform2D*>& nodes, Quantix::Physic::Transform2D* node, Quantix::Core::Platform::Application* app);

	/**
	 * @brief Popup Item Menu
	 * 
	 * @param nodes std::list<Quantix::Physic::Transform3D*>&
	 * @param node Transform3D*
	 * @param scene Scene*
	 */
	QXbool				PopUpMenuItem(std::list<Quantix::Physic::Transform3D*>& nodes, Quantix::Physic::Transform3D* node, Quantix::Core::Platform::Application* app);

	QXbool				PopUpMenuItemGC(Quantix::Core::DataStructure::GameComponent* node, Quantix::Core::Platform::Application* app);


	/**
	 * @brief Create a Empty GameComponent object
	 *
	 * @param selection QXbool&
	 * @param node std::list<Quantix::Physic::Transform3D*>&
	 * @param scene Scene*
	 */
	void				CreateGameComponent(QXbool& selection, Quantix::Core::Platform::Application* app);

	/**
	 * @brief Create a Empty Object 3D object
	 * 
	 * @param selection QXbool&
	 * @param node std::list<Quantix::Physic::Transform3D*>&
	 * @param scene Scene*
	 */
	void				CreateEmptyObject3D(QXbool& selection, Quantix::Core::Platform::Application* app);

	/**
	 * @brief Create a Cube object
	 *
	 * @param selection QXbool&
	 * @param node std::list<Quantix::Physic::Transform3D*>&
	 * @param scene Scene*
	 */
	void				CreateCube(QXbool& selection, Quantix::Core::Platform::Application* app);

	/**
	 * @brief Create a Sphere object
	 *
	 * @param selection QXbool&
	 * @param node std::list<Quantix::Physic::Transform3D*>&
	 * @param scene Scene*
	 */
	void				CreateSphere(QXbool& selection, Quantix::Core::Platform::Application* app);

	/**
	 * @brief Create a Capsule object
	 *
	 * @param selection QXbool&
	 * @param node std::list<Quantix::Physic::Transform3D*>&
	 * @param scene Scene*
	 */
	void				CreateCapsule(QXbool& selection, Quantix::Core::Platform::Application* app);

	/**
	 * @brief Create a Empty Object 2D object
	 *
	 * @param selection QXbool&
	 * @param node std::list<Quantix::Physic::Transform3D*>&
	 * @param scene Scene*
	 */
	void				CreateEmptyObject2D(QXbool& selection, Quantix::Core::Platform::Application* app);

	/**
	 * @brief Popup Menu
	 * 
	 * @param node std::list<Quantix::Physic::Transform3D*>&
	 * @param scene Scene*
	 */
	void				PopUpMenu(Quantix::Core::Platform::Application* app);
	#pragma region Getter
	/**
	 * @brief Get the Inspector object
	 * 
	 * @return Inspector* 
	 */
	inline Inspector*	GetInspector() { return _inspector; };
	#pragma endregion Getter
	#pragma endregion Methods

private:
	#pragma region Attributes
	Inspector*				_inspector;
	void*					_selected{ nullptr };
	#pragma endregion Attributes
};

#endif // !_HIERARCHY_H_
