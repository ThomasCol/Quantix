#ifndef _HIERARCHY_H_
#define _HIERARCHY_H_

#include <vector>
#include <string>
#include <Node.h>
#include <Inspector.h>
#include <Resources/Scene.h>

class Hierarchy
{
public:
	Hierarchy() = default;
	~Hierarchy() = default;

	void				Update(std::string name, ImGuiWindowFlags flags, std::shared_ptr<Quantix::Physic::Transform3D> gameComponents, Quantix::Resources::Scene* scene);

	void				SetSelectable(std::vector<std::shared_ptr<Quantix::Physic::Transform3D>>& nodeGlobal, std::vector<std::shared_ptr<Quantix::Physic::Transform3D>>& node, QXint i);
	void				DrawObject(std::vector<std::shared_ptr<Quantix::Physic::Transform3D>>& nodeGlobal, std::vector<std::shared_ptr<Quantix::Physic::Transform3D>>& node, Quantix::Resources::Scene* scene);
	void				CreateChild(QXbool& select, std::vector<std::shared_ptr<Quantix::Physic::Transform3D>>& nodes, Quantix::Resources::Scene* scene);
	void				MenuRename(std::vector<std::shared_ptr<Quantix::Physic::Transform3D>>& nodes, Quantix::Resources::Scene* scene);
	void				MenuItem(QXbool* selection, std::vector<QXstring> itemMenu, std::vector<std::shared_ptr<Quantix::Physic::Transform3D>>& nodes, Quantix::Resources::Scene* scene);
	void				PopUpMenuItem(std::vector<std::shared_ptr<Quantix::Physic::Transform3D>>& nodes, std::shared_ptr<Quantix::Physic::Transform3D> node, Quantix::Resources::Scene* scene);
	void				CreateEmptyObject(QXbool& selection, std::vector<std::shared_ptr<Quantix::Physic::Transform3D>>& node, Quantix::Resources::Scene* scene);
	void				CreateItem(QXbool* selection, std::vector<QXstring> itemMenu, std::vector<std::shared_ptr<Quantix::Physic::Transform3D>>& node, Quantix::Resources::Scene* scene);
	void				PopUpMenu(std::vector<std::shared_ptr<Quantix::Physic::Transform3D>>& node, Quantix::Resources::Scene* scene);

	void				DesactivatePrevInspector(std::vector<std::shared_ptr<Quantix::Physic::Transform3D>>& gameComponents, std::shared_ptr<Quantix::Physic::Transform3D> gameComponent);


	inline Inspector*	GetInspector() { return _inspector; };

private:
	Inspector*				_inspector;
	std::shared_ptr<void>	_selected{ nullptr };
};

#endif // !_HIERARCHY_H_
