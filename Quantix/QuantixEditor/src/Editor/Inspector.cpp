#include "Inspector.h"

Inspector::Inspector(Node node) :
	_node { node },
	_enable { true }
{
}

/*Inspector::Inspector(Core::DataStructure::GameComponent* gc) :
	_gc{ gc },
	_enable{ true }
{
}*/

void Inspector::Update()
{
	if (_enable)
	{
		ImGui::Text("Name: %s", _node.name.c_str());

		if (ImGui::TreeNodeEx("Transform", ImGuiTreeNodeFlags_Framed))
		{
			static float	pos[3] = { 0, 0, 0 };
			static float	rot[3] = { 0, 0, 0 };
			static float	scale[3] = { 1, 1, 1 };
			ImGui::DragFloat3("Position", pos, -3000.f, 3000.f);
			ImGui::DragFloat3("Rotation", rot, -3000.f, 3000.f);
			ImGui::DragFloat3("Scale", scale, 0.f, 100.f);
			ImGui::TreePop();
		}

		if (ImGui::TreeNodeEx("Component", ImGuiTreeNodeFlags_Framed))
		{
			ImGui::Text("Component1");
			ImGui::Text("Component2");
			ImGui::Text("Component3");
			ImGui::TreePop();
		}
	}
}
