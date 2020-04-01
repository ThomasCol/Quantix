#include <imgui.h>
#include <imgui_internal.h>

#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include "Hierarchy.h"
#include "Logger.h"

void Hierarchy::Update(std::string name, ImGuiWindowFlags flags, std::vector<Node>& node)
{
	static int j = 0;
	ImGui::Begin(name.c_str(), NULL, flags);
	{
		for (unsigned int i{ 0 }; i < node.size(); i++)
		{
			if (j == 0)
			{
				Quantix::Core::Debugger::Logger::GetInstance()->SetInfos("Fake GameObject.");
				j++;
			}
			ImGui::Bullet();
			if (ImGui::Selectable(node[i].name.c_str(), node[i].state))
			{
				node[i].state = !node[i].state;
				if (_inspector == nullptr)
					_inspector = new Inspector(node[i]);
				else if (!node[i].state)
					_inspector->SetEnable(false);
				else
					DesactivatePrevInspector(node, node[i]);
			}
		}
	}
	ImGui::End();
}

void Hierarchy::DesactivatePrevInspector(std::vector<Node>& nodes, Node node)
{
	for (unsigned int i{ 0 }; i < nodes.size(); i++)
		if (nodes[i].state && nodes[i].name != node.name)
			nodes[i].state = !nodes[i].state;

	_inspector = new Inspector(node);
}
