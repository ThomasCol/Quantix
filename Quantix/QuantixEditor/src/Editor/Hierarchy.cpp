#include <imgui.h>
#include <imgui_internal.h>

#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include "Hierarchy.h"
#include <Core/Debugger/Logger.h>

void Hierarchy::SetSelectable(std::vector<std::shared_ptr<Quantix::Physic::Transform3D>>& nodeGlobal, std::vector<std::shared_ptr<Quantix::Physic::Transform3D>>& node, QXint i)
{
	node[i]->GetObject()->SetIsActive(!node[i]->GetObject()->GetIsActive());
	if (_inspector == nullptr)
		_inspector = new Inspector(node[i]);
	else if (!node[i]->GetObject()->GetIsActive())
		_inspector->SetEnable(false);
	else
		DesactivatePrevInspector(nodeGlobal, node[i]);
}

void Hierarchy::DrawObject(std::vector<std::shared_ptr<Quantix::Physic::Transform3D>>& nodeGlobal, std::vector<std::shared_ptr<Quantix::Physic::Transform3D>>& node, Quantix::Resources::Scene* scene)
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
		if (node[i]->GetChilds().size() == 0)
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
				DrawObject(nodeGlobal, node[i]->GetChilds(), scene);
				ImGui::TreePop();
			}
		}
		PopUpMenuItem(nodeGlobal, node[i], scene);
		ImGui::PopID();
	}
	PopUpMenu(node, scene);
}

void Hierarchy::Update(QXstring name, ImGuiWindowFlags flags, std::shared_ptr<Quantix::Physic::Transform3D> node, Quantix::Resources::Scene* scene)
{
	ImGui::Begin(name.c_str(), NULL, flags);
	{
		if (ImGui::TreeNodeEx(&node, ImGuiTreeNodeFlags_Selected, "World Scene"))
		{
			if (node->GetChilds().size() > 0)
				DrawObject(node->GetChilds(), node->GetChilds(), scene);
			ImGui::TreePop();
		}
	}
	ImGui::End();
}

void Hierarchy::CreateChild(QXbool& select, std::vector<std::shared_ptr<Quantix::Physic::Transform3D>>& nodes, Quantix::Resources::Scene* scene)
{
	for (QXuint i = 0; i < nodes.size(); i++)
	{
		if (nodes[i]->GetChilds().size() != 0)
			CreateChild(select, nodes[i]->GetChilds(), scene);

		if (nodes[i] == _selected)
		{
			if (nodes.size() == 0)
				scene->AddGameObject("GameObject");
			else
				scene->AddGameObject("GameObject" + std::to_string((QXuint)nodes[i]->GetChilds().size()), nodes[i]->GetObject()->GetName());

			select = false;
			_selected = nullptr;
			ImGui::CloseCurrentPopup();
		}
	}
}

void Hierarchy::MenuRename(std::vector<std::shared_ptr<Quantix::Physic::Transform3D>>& nodes, Quantix::Resources::Scene* scene)
{
	for (QXuint i = 0; i < nodes.size(); i++)
	{
		if (nodes[i]->GetChilds().size() != 0)
		{
			std::vector<std::shared_ptr<Quantix::Physic::Transform3D>> child = nodes[i]->GetChilds();
			MenuRename(child, scene);
		}

		if (nodes[i] == _selected)
		{
			QXstring name;
			QXchar currName[64];

			memcpy(currName, nodes[i]->GetObject()->GetName().c_str(), nodes[i]->GetObject()->GetName().size() + 1);
			if (ImGui::InputText("##Input", currName, IM_ARRAYSIZE(currName), ImGuiInputTextFlags_EnterReturnsTrue))
			{
				scene->GetGameObject(nodes[i]->GetObject()->GetName())->SetName(currName);
				if (_inspector != nullptr)
					_inspector->SetNode(nodes[i]);
				_selected = nullptr;
				ImGui::CloseCurrentPopup();
			}
		}
	}
}

void Hierarchy::MenuItem(QXbool* selection, std::vector<QXstring> itemMenu, std::vector<std::shared_ptr<Quantix::Physic::Transform3D>>& nodes, Quantix::Resources::Scene* scene)
{
	for (QXuint i{ 0 }; i < itemMenu.size(); i++)
	{
		if (selection[i])
		{
			if (itemMenu[i] == "Create Child")
				CreateChild(selection[i], nodes, scene);
		}
	}
}

void Hierarchy::PopUpMenuItem(std::vector<std::shared_ptr<Quantix::Physic::Transform3D>>& nodes, std::shared_ptr<Quantix::Physic::Transform3D> node, Quantix::Resources::Scene* scene)
{
	if (ImGui::BeginPopupContextItem("Context Item"))
	{
		if (_selected == nullptr)
			_selected = node;
		else
		{
			static QXbool selection[1] = { false };
			ImGui::Selectable("Create Child", &selection[0]);
			MenuRename(nodes, scene);
			MenuItem(selection, { "Create Child" }, nodes, scene);
		}
		ImGui::EndPopup();
	}
}

void Hierarchy::CreateEmptyObject(QXbool& selection, std::vector<std::shared_ptr<Quantix::Physic::Transform3D>>& node, Quantix::Resources::Scene* scene)
{
	if (selection)
	{
		if (node.size() == 0)
			scene->AddGameObject("GameObject");
		else
			scene->AddGameObject("GameObject" + std::to_string((QXuint)node.size()));
		selection = false;
	}
}

void Hierarchy::CreateItem(QXbool* selection, std::vector<QXstring> itemMenu, std::vector<std::shared_ptr<Quantix::Physic::Transform3D>>& node, Quantix::Resources::Scene* scene)
{
	for (QXuint i{ 0 }; i < itemMenu.size(); i++)
	{
		if (selection[i])
		{
			if (itemMenu[i] == "Create Empty")
				CreateEmptyObject(selection[i], node, scene);
		}
	}
}

void Hierarchy::PopUpMenu(std::vector<std::shared_ptr<Quantix::Physic::Transform3D>>& node, Quantix::Resources::Scene* scene)
{
	if (ImGui::BeginPopupContextWindow("Context Menu", 1, false))
	{
		static QXbool selection[1] = { false };
		ImGui::Selectable("Create Empty", &selection[0]);
		CreateItem(selection, { "Create Empty" }, node, scene);
		ImGui::EndPopup();
	}
}

void Hierarchy::DesactivatePrevInspector(std::vector<std::shared_ptr<Quantix::Physic::Transform3D>>& nodes, std::shared_ptr<Quantix::Physic::Transform3D> node)
{
	for (QXuint i{ 0 }; i < nodes.size(); i++)
	{
		if (nodes[i]->GetChilds().size() > 0)
			DesactivatePrevInspector(nodes[i]->GetChilds(), node);
		if (nodes[i]->GetChilds().size() == 0)
		{
			if (nodes[i]->GetObject() != node->GetObject() && nodes[i]->GetObject()->GetIsActive())
				nodes[i]->GetObject()->SetIsActive(!nodes[i]->GetObject()->GetIsActive());
		}
		if (nodes[i]->GetObject() == node->GetObject() && nodes[i]->GetObject()->GetName() == node->GetObject()->GetName())
			_inspector = new Inspector(node);
	}
}