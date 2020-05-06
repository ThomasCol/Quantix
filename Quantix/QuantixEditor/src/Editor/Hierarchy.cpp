#include <imgui.h>
#include <imgui_internal.h>

#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include "Hierarchy.h"
#include <Core/Debugger/Logger.h>

void Hierarchy::SetSelectable(std::list<Quantix::Physic::Transform3D*>& nodeGlobal, std::list<Quantix::Physic::Transform3D*>::iterator& it)
{
	(*it)->GetObject()->SetIsActive(!(*it)->GetObject()->GetIsActive());
	if (_inspector == nullptr)
		_inspector = new Inspector((*it));
	else if (!(*it)->GetObject()->GetIsActive())
		_inspector->SetEnable(QX_FALSE);
	else
		DesactivatePrevInspector(nodeGlobal, it);
}

void Hierarchy::DrawObject(std::list<Quantix::Physic::Transform3D*>& nodeGlobal, std::list<Quantix::Physic::Transform3D*>& node, Quantix::Resources::Scene* scene)
{
	for (auto it = node.begin(); it != node.end(); ++it)
	{
		ImGui::PushID((*it)->GetObject());
		if ((*it)->GetChilds().size() == 0)
		{
			ImGui::Bullet();
			if (ImGui::Selectable((*it)->GetObject()->GetName().c_str(), (*it)->GetObject()->GetIsActive()))
				SetSelectable(nodeGlobal, it);
		}
		else
		{
			QXbool isOpen = ImGui::TreeNodeEx(&(*it), ImGuiTreeNodeFlags_Selected, (*it)->GetObject()->GetName().c_str());
			if (ImGui::IsItemClicked(0))
				SetSelectable(nodeGlobal, it);
			if (isOpen)
			{
				DrawObject(nodeGlobal, (*it)->GetChilds(), scene);
				ImGui::TreePop();
			}
		}
		if (PopUpMenuItem(nodeGlobal, (*it), scene))
		{
			ImGui::PopID();
			break;
		}
		ImGui::PopID();

	}
	PopUpMenu(node, scene);
}

void Hierarchy::Update(QXstring name, ImGuiWindowFlags flags, Quantix::Physic::Transform3D* node, Quantix::Resources::Scene* scene)
{
	ImGui::Begin(name.c_str(), NULL, flags);
	{
		if (ImGui::TreeNodeEx(&node, ImGuiTreeNodeFlags_DefaultOpen, "World Scene"))
		{
			if (node->GetChilds().size() > 0)
				DrawObject(node->GetChilds(), node->GetChilds(), scene);
			ImGui::TreePop();
		}
	}
	ImGui::End();
}

void Hierarchy::CreateChild(QXbool& select, std::list<Quantix::Physic::Transform3D*>& nodes, Quantix::Resources::Scene* scene)
{
	for (auto it = nodes.begin(); it != nodes.end(); ++it)
	{
		if ((*it)->GetChilds().size() != 0)
			CreateChild(select, (*it)->GetChilds(), scene);

		if ((*it)->GetObject() == _selected)
		{
			if ((*it)->GetChilds().size() == 0)
			{
				scene->AddGameObject("GameObject", (*it)->GetObject());
			}
			else
			{
				std::string name = "GameObject" + std::to_string((QXuint)(*it)->GetChilds().size());
				scene->AddGameObject(name, (*it)->GetObject());
			}

			select = false;
			_selected = nullptr;
			ImGui::CloseCurrentPopup();
		}
	}
}

void Hierarchy::RemoveObject(QXbool& select, std::list<Quantix::Physic::Transform3D*>& nodes, Quantix::Resources::Scene* scene)
{
	for (auto it = nodes.begin(); it != nodes.end();)
	{
		if ((*it)->GetChilds().size() != 0)
			RemoveObject(select, (*it)->GetChilds(), scene);

		if ((*it)->GetObject() == _selected)
		{
			for (QXuint i = 0; i < (*it)->GetObject()->GetComponents().size(); i++)
				(*it)->GetObject()->RemoveComponent((*it)->GetObject()->GetComponents()[i]);
			for (QXuint i = 0; i < (*it)->GetObject()->GetBehaviours().size(); i++)
				(*it)->GetObject()->RemoveBehaviour((*it)->GetObject()->GetBehaviours()[i]);
			it = nodes.erase(it);
			_selected = nullptr;
			select = false;
			ImGui::CloseCurrentPopup();
		}
		else
			++it;
	}
}

void Hierarchy::MenuRename(std::list<Quantix::Physic::Transform3D*>& nodes, Quantix::Resources::Scene* scene)
{
	for (auto it = nodes.begin(); it != nodes.end(); ++it)
	{
		if ((*it)->GetChilds().size() != 0)
		{
			std::list<Quantix::Physic::Transform3D*> child = (*it)->GetChilds();
			MenuRename(child, scene);
		}

		if ((*it)->GetObject() == _selected)
		{
			QXstring name;
			QXchar currName[64];

			memcpy(currName, (*it)->GetObject()->GetName().c_str(), (*it)->GetObject()->GetName().size() + 1);
			if (ImGui::InputText("##Input", currName, IM_ARRAYSIZE(currName), ImGuiInputTextFlags_EnterReturnsTrue))
			{
				scene->GetGameObject((*it)->GetObject()->GetName())->SetName(currName);
				if (_inspector != nullptr)
					_inspector->SetNode((*it));
				_selected = nullptr;
				ImGui::CloseCurrentPopup();
			}
		}
	}
}

void Hierarchy::MenuItem(QXbool* selection, std::vector<QXstring> itemMenu, std::list<Quantix::Physic::Transform3D*>& nodes, Quantix::Resources::Scene* scene)
{
	for (QXuint i{ 0 }; i < itemMenu.size(); i++)
	{
		if (selection[i])
		{
			if (itemMenu[i] == "Create Child")
				CreateChild(selection[i], nodes, scene);
			else if (itemMenu[i] == "Remove")
				RemoveObject(selection[i], nodes, scene);
		}
	}
}

QXbool Hierarchy::PopUpMenuItem(std::list<Quantix::Physic::Transform3D*>& nodes, Quantix::Physic::Transform3D* node, Quantix::Resources::Scene* scene)
{
	static QXbool isRemoved= QX_FALSE;
	if (ImGui::BeginPopupContextItem("Context Item"))
	{
		if (_selected == nullptr)
			_selected = node->GetObject();
		else
		{
			static QXbool selection[2] = { false, false };
			ImGui::Selectable("Create Child", &selection[0]);
			ImGui::Selectable("Remove", &selection[1]);
			if (selection[1])
				isRemoved = QX_TRUE;
			MenuRename(nodes, scene);
			MenuItem(selection, { "Create Child", "Remove" }, nodes, scene);
		}
		ImGui::EndPopup();
	}
	if (isRemoved)
	{
		isRemoved = QX_FALSE;
		return QX_TRUE;
	}
	return QX_FALSE;
}

void Hierarchy::CreateEmptyObject(QXbool& selection, std::list<Quantix::Physic::Transform3D*>& node, Quantix::Resources::Scene* scene)
{
	if (selection)
	{
		if (node.size() == 0)
		{
			scene->AddGameObject("GameObject");
		}
		else
		{
			std::string name = "GameObject" + std::to_string((QXuint)node.size());
			scene->AddGameObject(name);
		}
		selection = false;
	}
}

void Hierarchy::CreateItem(QXbool* selection, std::vector<QXstring> itemMenu, std::list<Quantix::Physic::Transform3D*>& node, Quantix::Resources::Scene* scene)
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

void Hierarchy::PopUpMenu(std::list<Quantix::Physic::Transform3D*>& node, Quantix::Resources::Scene* scene)
{
	if (ImGui::BeginPopupContextWindow("Context Menu", 1, false))
	{
		static QXbool selection[1] = { false };
		ImGui::Selectable("Create Empty", &selection[0]);
		CreateItem(selection, { "Create Empty" }, node, scene);
		ImGui::EndPopup();
	}
}

void Hierarchy::DesactivatePrevInspector(std::list<Quantix::Physic::Transform3D*>& nodes, std::list<Quantix::Physic::Transform3D*>::iterator& node)
{
	for (auto it = nodes.begin(); it != nodes.end(); ++it)
	{
		if ((*it)->GetChilds().size() > 0)
			DesactivatePrevInspector((*it)->GetChilds(), node);
		if ((*it)->GetChilds().size() == 0)
		{
			if ((*it)->GetObject() != (*node)->GetObject() && (*it)->GetObject()->GetIsActive())
				(*it)->GetObject()->SetIsActive(!(*it)->GetObject()->GetIsActive());
		}
		if ((*it)->GetObject() == (*node)->GetObject() && (*it)->GetObject()->GetName() == (*node)->GetObject()->GetName())
			_inspector = new Inspector((*node));
	}
}