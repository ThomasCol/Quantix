#include <imgui.h>
#include <imgui_internal.h>

#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include "Hierarchy.h"
#include <Core/Debugger/Logger.h>

void Hierarchy::SetSelectable(std::vector<Quantix::Physic::Transform3D*>& nodeGlobal, std::vector<Quantix::Physic::Transform3D*>& node, QXint i)
{
	node[i]->GetObject()->SetIsActive(!node[i]->GetObject()->GetIsActive());
	if (_inspector == nullptr)
		_inspector = new Inspector(node[i]);
	else if (!node[i]->GetObject()->GetIsActive())
		_inspector->SetEnable(false);
	else
		DesactivatePrevInspector(nodeGlobal, node[i]);
}

void Hierarchy::DrawObject(std::vector<Quantix::Physic::Transform3D*>& nodeGlobal, std::vector<Quantix::Physic::Transform3D*>& node)
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
		if (node[i]->GetChild().size() == 0)
		{
			ImGui::Bullet();
			if (ImGui::Selectable(node[i]->GetObject()->GetName().c_str(), node[i]->GetObject()->GetIsActive()))
				SetSelectable(nodeGlobal, node, i);
		}
		else
		{
			QXbool isOpen = ImGui::TreeNodeEx(&node[i], ImGuiTreeNodeFlags_Selected, node[i]->GetObject()->GetName().c_str());
			if (ImGui::IsItemClicked(0))
				SetSelectable(nodeGlobal, node, i);
			if (isOpen)
			{
				DrawObject(nodeGlobal, node[i]->GetChild());
				ImGui::TreePop();
			}
		}
		PopUpMenuItem(nodeGlobal, node[i]);
		ImGui::PopID();
	}
	PopUpMenu(node);
}

void Hierarchy::Update(QXstring name, ImGuiWindowFlags flags, Quantix::Physic::Transform3D* node)
{
	ImGui::Begin(name.c_str(), NULL, flags);
	{
		if (ImGui::TreeNodeEx(&node, ImGuiTreeNodeFlags_Selected, "World Scene"))
		{
			if (node->GetChild().size() > 0)
				DrawObject(node->GetChild(), node->GetChild());
			ImGui::TreePop();
		}
	}
	ImGui::End();
}

void Hierarchy::CreateChild(QXbool& select, std::vector<Quantix::Physic::Transform3D*>& nodes)
{
	for (QXuint i = 0; i < nodes.size(); i++)
	{
		if (nodes[i]->GetChild().size() != 0)
			CreateChild(select, nodes[i]->GetChild());

		if (&nodes[i] == _selected)
		{
			if (nodes[i]->GetChild().size() == 0)
			{
				nodes[i]->GetChild().push_back(new Quantix::Physic::Transform3D());
				nodes.back()->SetObject(new Quantix::Core::DataStructure::GameObject3D("GameObject"));
			}
			else
			{
				nodes[i]->GetChild().push_back(new Quantix::Physic::Transform3D());
				nodes.back()->SetObject(new Quantix::Core::DataStructure::GameObject3D("GameObject" + std::to_string((QXuint)nodes[i]->GetChild().size())));
			}
			select = false;
			_selected = nullptr;
			ImGui::CloseCurrentPopup();
		}
	}
}

void Hierarchy::MenuRename(std::vector<Quantix::Physic::Transform3D*>& nodes)
{
	for (QXuint i = 0; i < nodes.size(); i++)
	{
		if (nodes[i]->GetChild().size() != 0)
		{
			std::vector<Quantix::Physic::Transform3D*> child = nodes[i]->GetChild();
			MenuRename(child);
		}

		if (&nodes[i] == _selected)
		{
			QXstring name;
			QXchar currName[64];

			memcpy(currName, nodes[i]->GetObject()->GetName().c_str(), nodes[i]->GetObject()->GetName().size() + 1);
			if (ImGui::InputText("##Input", currName, IM_ARRAYSIZE(currName), ImGuiInputTextFlags_EnterReturnsTrue))
			{
				nodes[i]->GetObject()->GetName() = currName;
				_inspector->SetNode(nodes[i]);
				_selected = nullptr;
				ImGui::CloseCurrentPopup();
			}
		}
	}
}

void Hierarchy::MenuItem(QXbool* selection, std::vector<QXstring> itemMenu, std::vector<Quantix::Physic::Transform3D*>& nodes)
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

void Hierarchy::PopUpMenuItem(std::vector<Quantix::Physic::Transform3D*>& nodes, Quantix::Physic::Transform3D* node)
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

void Hierarchy::CreateEmptyObject(QXbool& selection, std::vector<Quantix::Physic::Transform3D*>& node)
{
	if (selection)
	{
		if (node.size() == 0)
		{
			node.push_back(new Quantix::Physic::Transform3D());
			node.back()->SetObject(new Quantix::Core::DataStructure::GameObject3D("GameObject"));
		}
		else
		{
			node.push_back(new Quantix::Physic::Transform3D());
			node.back()->SetObject(new Quantix::Core::DataStructure::GameObject3D("GameObject" + std::to_string((QXuint)node.size())));
		}
		selection = false;
	}
}

void Hierarchy::CreateItem(QXbool* selection, std::vector<QXstring> itemMenu, std::vector<Quantix::Physic::Transform3D*>& node)
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

void Hierarchy::PopUpMenu(std::vector<Quantix::Physic::Transform3D*>& node)
{
	if (ImGui::BeginPopupContextWindow("Context Menu", 1, false))
	{
		static QXbool selection[1] = { false };
		ImGui::Selectable("Create Empty", &selection[0]);
		CreateItem(selection, { "Create Empty" }, node);
		ImGui::EndPopup();
	}
}

void Hierarchy::DesactivatePrevInspector(std::vector<Quantix::Physic::Transform3D*>& nodes, Quantix::Physic::Transform3D* node)
{
	for (QXuint i{ 0 }; i < nodes.size(); i++)
	{
		if (nodes[i]->GetChild().size() > 0)
			DesactivatePrevInspector(nodes[i]->GetChild(), node);
		if (nodes[i]->GetChild().size() == 0)
		{
			if (&nodes[i] != &node && nodes[i]->GetObject()->GetIsActive())
				nodes[i]->GetObject()->SetIsActive(!nodes[i]->GetObject()->GetIsActive());
		}
		if (&nodes[i] == &node && nodes[i]->GetObject()->GetName() == node->GetObject()->GetName())
			_inspector = new Inspector(node);
	}
}