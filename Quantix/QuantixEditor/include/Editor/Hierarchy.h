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

	void				DesactivatePrevInspector(std::vector<Node>& nodes, Node node);

	inline Inspector*	GetInspector() const { return _inspector; };

private:
	Inspector* _inspector;
};

#endif // !_HIERARCHY_H_
