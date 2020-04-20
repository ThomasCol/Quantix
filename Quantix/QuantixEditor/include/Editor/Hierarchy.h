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

	void				Update(std::string name, ImGuiWindowFlags flags, Quantix::Physic::Transform3D* gameComponents);

	void				SetSelectable(std::vector<Quantix::Physic::Transform3D*>& nodeGlobal, std::vector<Quantix::Physic::Transform3D*>& node, QXint i);
	void				DrawObject(std::vector<Quantix::Physic::Transform3D*>& nodeGlobal, std::vector<Quantix::Physic::Transform3D*>& node);
	void				CreateChild(QXbool& select, std::vector<Quantix::Physic::Transform3D*>& nodes);
	void				MenuRename(std::vector<Quantix::Physic::Transform3D*>& nodes);
	void				MenuItem(QXbool* selection, std::vector<QXstring> itemMenu, std::vector<Quantix::Physic::Transform3D*>& nodes);
	void				PopUpMenuItem(std::vector<Quantix::Physic::Transform3D*>& nodes, Quantix::Physic::Transform3D* node);
	void				CreateEmptyObject(QXbool& selection, std::vector<Quantix::Physic::Transform3D*>& node);
	void				CreateItem(QXbool* selection, std::vector<QXstring> itemMenu, std::vector<Quantix::Physic::Transform3D*>& node);
	void				PopUpMenu(std::vector<Quantix::Physic::Transform3D*>& node);

	void				DesactivatePrevInspector(std::vector<Quantix::Physic::Transform3D*>& gameComponents, Quantix::Physic::Transform3D* gameComponent);


	inline Inspector*	GetInspector() { return _inspector; };

private:
	Inspector*	_inspector;
	void*		_selected{ nullptr };
};

#endif // !_HIERARCHY_H_
