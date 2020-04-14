#ifndef _HIERARCHY_H_
#define _HIERARCHY_H_

#include <vector>
#include <string>
#include <Node.h>
#include <Inspector.h>

class Hierarchy
{
public:
	Hierarchy() = default;
	~Hierarchy() = default;


//	void Update(QXstring name, ImGuiWindowFlags flags, std::vector<Node>& node);
	void Update(std::string name, ImGuiWindowFlags flags, std::vector<Quantix::Physic::Transform3D*>& gameComponents);

	/*void				SetSelectable(std::vector<Node>& nodeGlobal, std::vector<Node>& node, QXint i);
	void				DrawObject(std::vector<Node>& nodeGlobal, std::vector<Node>& node);
	void				CreateChild(QXbool& select, std::vector<Node>& nodes);
	void				MenuRename(std::vector<Node>& nodes);
	void				MenuItem(QXbool* selection, std::vector<QXstring> itemMenu, std::vector<Node>& nodes);
	void				PopUpMenuItem(std::vector<Node>& nodes, Node& node);
	void				CreateEmptyObject(QXbool& selection, std::vector<Node>& node);
	void				CreateItem(QXbool* selection, std::vector<QXstring> itemMenu, std::vector<Node>& node);
	void				PopUpMenu(std::vector<Node>& node);*/

	void				SetSelectable(std::vector<Quantix::Physic::Transform3D*>& nodeGlobal, std::vector<Quantix::Physic::Transform3D*>& node, QXint i);
	void				DrawObject(std::vector<Quantix::Physic::Transform3D*>& nodeGlobal, std::vector<Quantix::Physic::Transform3D*>& node);
	void				CreateChild(QXbool& select, std::vector<Quantix::Physic::Transform3D*>& nodes);
	void				MenuRename(std::vector<Quantix::Physic::Transform3D*>& nodes);
	void				MenuItem(QXbool* selection, std::vector<QXstring> itemMenu, std::vector<Quantix::Physic::Transform3D*>& nodes);
	void				PopUpMenuItem(std::vector<Quantix::Physic::Transform3D*>& nodes, Quantix::Physic::Transform3D* node);
	void				CreateEmptyObject(QXbool& selection, std::vector<Quantix::Physic::Transform3D*>& node);
	void				CreateItem(QXbool* selection, std::vector<QXstring> itemMenu, std::vector<Quantix::Physic::Transform3D*>& node);
	void				PopUpMenu(std::vector<Quantix::Physic::Transform3D*>& node);

	//void				DesactivatePrevInspector(std::vector<Node>& nodes, Node& node);
	void				DesactivatePrevInspector(std::vector<Quantix::Physic::Transform3D*>& gameComponents, Quantix::Physic::Transform3D* gameComponent);


	inline Inspector*	GetInspector() const { return _inspector; };

private:
	Inspector*	_inspector;
	void*		_selected{ nullptr };
};

#endif // !_HIERARCHY_H_
