#ifndef _HIERARCHY_H_
#define _HIERARCHY_H_

#include <list>
#include <string>
#include <Node.h>
#include <Inspector.h>
#include <Resources/Scene.h>

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
	void				Update(QXstring name, ImGuiWindowFlags flags, Quantix::Physic::Transform3D* gameComponents, Quantix::Resources::Scene* scene);

	/**
	 * @brief Set the Selectable object
	 * 
	 * @param nodeGlobal std::list<Quantix::Physic::Transform3D*>&
	 * @param node std::list<Quantix::Physic::Transform3D*>&
	 * @param i QXint
	 */
	void				SetSelectable(std::list<Quantix::Physic::Transform3D*>& nodeGlobal, std::list<Quantix::Physic::Transform3D*>::iterator& it);

	/**
	 * @brief Draw Object
	 * 
	 * @param nodeGlobal std::list<Quantix::Physic::Transform3D*>&
	 * @param node std::list<Quantix::Physic::Transform3D*>&
	 * @param scene Scene*
	 */
	void				DrawObject(std::list<Quantix::Physic::Transform3D*>& nodeGlobal, std::list<Quantix::Physic::Transform3D*>& node, Quantix::Resources::Scene* scene);

	/**
	 * @brief Create a Child object
	 * 
	 * @param select QXbool&
	 * @param nodes std::list<Quantix::Physic::Transform3D*>&
	 * @param scene Scene*
	 */
	void				CreateChild(QXbool& select, std::list<Quantix::Physic::Transform3D*>& nodes, Quantix::Resources::Scene* scene);

	void				RemoveObject(QXbool& select, std::list<Quantix::Physic::Transform3D*>& nodes, Quantix::Resources::Scene* scene);

	/**
	 * @brief Rename Menu
	 * 
	 * @param nodes std::list<Quantix::Physic::Transform3D*>&
	 * @param scene Scene*
	 */
	void				MenuRename(std::list<Quantix::Physic::Transform3D*>& nodes, Quantix::Resources::Scene* scene);
	
	/**
	 * @brief Item Menu
	 * 
	 * @param selection QXbool*
	 * @param itemMenu std::list<QXstring>
	 * @param nodes std::list<Quantix::Physic::Transform3D*>&
	 * @param scene Scene*
	 */
	void				MenuItem(QXbool* selection, std::vector<QXstring> itemMenu, std::list<Quantix::Physic::Transform3D*>& nodes, Quantix::Resources::Scene* scene);

	/**
	 * @brief Popup Item Menu
	 * 
	 * @param nodes std::list<Quantix::Physic::Transform3D*>&
	 * @param node Transform3D*
	 * @param scene Scene*
	 */
	QXbool				PopUpMenuItem(std::list<Quantix::Physic::Transform3D*>& nodes, Quantix::Physic::Transform3D* node, Quantix::Resources::Scene* scene);

	/**
	 * @brief Create a Empty Object object
	 * 
	 * @param selection QXbool&
	 * @param node std::list<Quantix::Physic::Transform3D*>&
	 * @param scene Scene*
	 */
	void				CreateEmptyObject(QXbool& selection, std::list<Quantix::Physic::Transform3D*>& node, Quantix::Resources::Scene* scene);

	/**
	 * @brief Create a Item object
	 * 
	 * @param selection QXbool*
	 * @param itemMenu std::list<QXstring>
	 * @param node std::list<Quantix::Physic::Transform3D*>&
	 * @param scene Scene*
	 */
	void				CreateItem(QXbool* selection, std::vector<QXstring> itemMenu, std::list<Quantix::Physic::Transform3D*>& node, Quantix::Resources::Scene* scene);

	/**
	 * @brief Popup Menu
	 * 
	 * @param node std::list<Quantix::Physic::Transform3D*>&
	 * @param scene Scene*
	 */
	void				PopUpMenu(std::list<Quantix::Physic::Transform3D*>& node, Quantix::Resources::Scene* scene);

	/**
	 * @brief Desactivate Previous Inspector
	 * 
	 * @param gameComponents std::list<Quantix::Physic::Transform3D*>&
	 * @param gameComponent Transform3D*
	 */
	void				DesactivatePrevInspector(std::list<Quantix::Physic::Transform3D*>& gameComponents, std::list<Quantix::Physic::Transform3D*>::iterator& gameComponent);


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
