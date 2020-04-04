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


	void Update(std::string name, ImGuiWindowFlags flags, std::vector<Node>& node);
//	void Update(std::string name, ImGuiWindowFlags flags, std::vector<Core::DataStructure::GameComponent*>& gameComponents);

	void				SetSelectable(std::vector<Node>& nodeGlobal, std::vector<Node>& node, int i);
	void				DrawObject(std::vector<Node>& nodeGlobal, std::vector<Node>& node);
	void				CreateChild(bool& select, std::vector<Node>& nodes);
	void				MenuRename(std::vector<Node>& nodes);
	void				MenuItem(bool* selection, std::vector<std::string> itemMenu, std::vector<Node>& nodes);
	void				PopUpMenuItem(std::vector<Node>& nodes, Node& node);
	void				CreateEmptyObject(bool& selection, std::vector<Node>& node);
	void				CreateItem(bool* selection, std::vector<std::string> itemMenu, std::vector<Node>& node);
	void				PopUpMenu(std::vector<Node>& node);

	void				DesactivatePrevInspector(std::vector<Node>& nodes, Node& node);
//	void				DesactivatePrevInspector(std::vector<Core::DataStructure::GameComponent*>& gameComponents, Core::DataStructure::GameComponent* gameComponent);


	inline Inspector*	GetInspector() const { return _inspector; };

private:
	Inspector*	_inspector;
	void*		_selected{ nullptr };
};

#endif // !_HIERARCHY_H_
