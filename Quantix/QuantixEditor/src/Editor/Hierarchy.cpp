#include <imgui.h>
#include <imgui_internal.h>

#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include "Hierarchy.h"
#include "Logger.h"

void Hierarchy::SetSelectable(std::vector<Node>& nodeGlobal, std::vector<Node>& node, QXint i)
{
	node[i].state = !node[i].state;
	if (_inspector == nullptr)
		_inspector = new Inspector(node[i]);
	else if (!node[i].state)
		_inspector->SetEnable(false);
	else
		DesactivatePrevInspector(nodeGlobal, node[i]);
}

void Hierarchy::DrawObject(std::vector<Node>& nodeGlobal, std::vector<Node>& node)
{
	static QXint j = 0;
	for (QXuint i{ 0 }; i < node.size(); i++)
	{
		if (j == 0)
		{
			Quantix::Core::Debugger::Logger::GetInstance()->SetInfo("Fake GameObject.");
			j++;
		}
		ImGui::PushID(&node[i]);
		if (node[i].child.size() == 0)
		{
			ImGui::Bullet();
			if (ImGui::Selectable(node[i].name.c_str(), node[i].state))
				SetSelectable(nodeGlobal, node, i);
		}
		else
		{
			QXbool isOpen = ImGui::TreeNodeEx(&node[i], ImGuiTreeNodeFlags_Selected, node[i].name.c_str());
			if (ImGui::IsItemClicked(0))
				SetSelectable(nodeGlobal, node, i);
			if (isOpen)
			{
				DrawObject(nodeGlobal, node[i].child);
				ImGui::TreePop();
			}
		}
		PopUpMenuItem(nodeGlobal, node[i]);
		ImGui::PopID();
	}
	PopUpMenu(node);
}

void Hierarchy::Update(QXstring name, ImGuiWindowFlags flags, std::vector<Node>& node)
{
	ImGui::Begin(name.c_str(), NULL, flags);
	{
		DrawObject(node, node);
	}
	ImGui::End();
}

void Hierarchy::CreateChild(QXbool& select, std::vector<Node>& nodes)
{
	for (QXuint i = 0; i < nodes.size(); i++)
	{
		if (nodes[i].child.size() != 0)
			CreateChild(select, nodes[i].child);

		if (&nodes[i] == _selected)
		{
			if (nodes[i].child.size() == 0)
				nodes[i].child.push_back({ {}, "GameObject", (QXuint)nodes[i].child.size(), false });
			else
				nodes[i].child.push_back({ {}, "GameObject" + std::to_string((QXuint)nodes[i].child.size()), (QXuint)nodes[i].child.size(), false });
			select = false;
			_selected = nullptr;
			ImGui::CloseCurrentPopup();
		}
	}
}

void Hierarchy::MenuRename(std::vector<Node>& nodes)
{
	for (QXuint i = 0; i < nodes.size(); i++)
	{
		if (nodes[i].child.size() != 0)
			MenuRename(nodes[i].child);

		if (&nodes[i] == _selected)
		{
			QXstring name;
			QXchar currName[64];

			memcpy(currName, nodes[i].name.c_str(), nodes[i].name.size() + 1);
			if (ImGui::InputText("##Input", currName, IM_ARRAYSIZE(currName), ImGuiInputTextFlags_EnterReturnsTrue))
			{
				nodes[i].name = currName;
				_inspector->SetNode(nodes[i]);
				_selected = nullptr;
				ImGui::CloseCurrentPopup();
			}
		}
	}
}

void Hierarchy::MenuItem(QXbool* selection, std::vector<QXstring> itemMenu, std::vector<Node>& nodes)
{
	for (QXuint i{ 0 }; i < itemMenu.size(); i++)
	{
		if (selection[i])
		{
			if (itemMenu[i] == "Create Child")
				CreateChild(selection[i], nodes);
		}
	}
}

void Hierarchy::PopUpMenuItem(std::vector<Node>& nodes, Node& node)
{
	if (ImGui::BeginPopupContextItem("Context Item"))
	{
		if (_selected == nullptr)
			_selected = &node;
		else
		{ 
			static QXbool selection[1] = { false };
			ImGui::Selectable("Create Child", &selection[0]);
			MenuRename(nodes);
			MenuItem(selection, { "Create Child" }, nodes);
		}
		ImGui::EndPopup();
	}
}

void Hierarchy::CreateEmptyObject(QXbool& selection, std::vector<Node>& node)
{
	if (selection)
	{
		if (node.size() == 0)
			node.push_back({ {}, "GameObject", 0, false });
		else
			node.push_back({ {}, "GameObject" + std::to_string((QXuint)node.size()), (QXuint)node.size(), false });
		selection = false;
	}
}

void Hierarchy::CreateItem(QXbool* selection, std::vector<QXstring> itemMenu, std::vector<Node>& node)
{
	for (QXuint i{ 0 }; i < itemMenu.size(); i++)
	{
		if (selection[i])
		{
			if (itemMenu[i] == "Create Empty")
				CreateEmptyObject(selection[i], node);
		}
	}
}

void Hierarchy::PopUpMenu(std::vector<Node>& node)
{
	if (ImGui::BeginPopupContextWindow("Context Menu", 1, false))
	{
		static QXbool selection[1] = { false };
		ImGui::Selectable("Create Empty", &selection[0]);
		CreateItem(selection, {"Create Empty"}, node);
		ImGui::EndPopup();
	}
}

void Hierarchy::DesactivatePrevInspector(std::vector<Node>& nodes, Node& node)
{
	for (QXuint i{ 0 }; i < nodes.size(); i++)
	{
		if (nodes[i].child.size() > 0)
			DesactivatePrevInspector(nodes[i].child, node);
		if (nodes[i].child.size() == 0)
		{
			if (&nodes[i] != &node && nodes[i].state)
				nodes[i].state = !nodes[i].state;
		}
		if (&nodes[i] == &node && nodes[i].name == node.name)
			_inspector = new Inspector(node);
	}
}

//void Hierarchy::Update(std::string name, ImGuiWindowFlags flags, std::vector<Core::DataStructure::GameComponent*>& node)
//{
//	static int j = 0;
//	ImGui::Begin(name.c_str(), NULL, flags);
//	{
//		for (unsigned int i{ 0 }; i < node.size(); i++)
//		{
//			if (j == 0)
//			{
//				Quantix::Core::Debugger::Logger::GetInstance()->SetInfo("Fake GameObject.");
//				j++;
//			}
//			ImGui::Bullet();
//			if (ImGui::Selectable(node[i]->GetName().c_str(), node[i]->GetIsActive()))
//			{
//				node[i]->SetIsActive(!node[i]->GetIsActive());
//				if (_inspector == nullptr)
//					_inspector = new Inspector(node[i]);
//				else if (!node[i]->GetIsActive())
//					_inspector->SetEnable(false);
//				else
//					DesactivatePrevInspector(node, node[i]);
//			}
//		}
//	}
//	ImGui::End();
//}

//void Hierarchy::DesactivatePrevInspector(std::vector<Core::DataStructure::GameComponent*>& gameComponents, Core::DataStructure::GameComponent* gameComponent)
//{
//	for (unsigned int i{ 0 }; i < gameComponents.size(); i++)
//		if (gameComponents[i]->GetIsActive() && gameComponents[i]->GetName() != gameComponent->GetName())
//			gameComponents[i]->SetIsActive(!gameComponents[i]->GetIsActive());
//
//	_inspector = new Inspector(gameComponent);
//}
