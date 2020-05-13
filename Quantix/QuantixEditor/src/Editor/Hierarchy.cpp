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
	{
		_inspector = new Inspector((*it)->GetObject());
		_inspector->Set3D(QX_TRUE);
	}
	else if (!(*it)->GetObject()->GetIsActive())
		_inspector->SetEnable(QX_FALSE);
	else
		DesactivatePrevInspector(nodeGlobal, it);
}

void Hierarchy::SetSelectable2D(std::list<Quantix::Physic::Transform2D*>& nodeGlobal, std::list<Quantix::Physic::Transform2D*>::iterator& it)
{
	(*it)->GetObject()->SetIsActive(!(*it)->GetObject()->GetIsActive());
	if (_inspector == nullptr)
	{
		_inspector = new Inspector((*it)->GetObject());
		_inspector->Set2D(QX_TRUE);
	}
	else if (!(*it)->GetObject()->GetIsActive())
		_inspector->SetEnable(QX_FALSE);
	else
		DesactivatePrevInspector2D(nodeGlobal, it);
}

void Hierarchy::DrawObject(std::list<Quantix::Physic::Transform3D*>& nodeGlobal, std::list<Quantix::Physic::Transform3D*>& node, Quantix::Core::Platform::Application* app)
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
				DrawObject(nodeGlobal, (*it)->GetChilds(), app);
				ImGui::TreePop();
			}
		}
		if (PopUpMenuItem(nodeGlobal, (*it), app))
		{
			ImGui::PopID();
			break;
		}
		ImGui::PopID();
	}
}

void Hierarchy::DrawObject2D(std::list<Quantix::Physic::Transform2D*>& nodeGlobal, std::list<Quantix::Physic::Transform2D*>& node, Quantix::Core::Platform::Application* app)
{
	for (auto it = node.begin(); it != node.end(); ++it)
	{
		ImGui::PushID((*it)->GetObject());
		if ((*it)->GetChilds().size() == 0)
		{
			ImGui::Bullet();
			if (ImGui::Selectable((*it)->GetObject()->GetName().c_str(), (*it)->GetObject()->GetIsActive()))
				SetSelectable2D(nodeGlobal, it);
		}
		else
		{
			QXbool isOpen = ImGui::TreeNodeEx(&(*it), ImGuiTreeNodeFlags_Selected, (*it)->GetObject()->GetName().c_str());
			if (ImGui::IsItemClicked(0))
				SetSelectable2D(nodeGlobal, it);
			if (isOpen)
			{
				DrawObject2D(nodeGlobal, (*it)->GetChilds(), app);
				ImGui::TreePop();
			}
		}
		if (PopUpMenuItem2D(nodeGlobal, (*it), app))
		{
			ImGui::PopID();
			break;
		}
		ImGui::PopID();

	}
}

void Hierarchy::DrawGameComponent(Quantix::Core::Platform::Application* app)
{
	for (auto it = app->scene->GetGameComponents().begin(); it != app->scene->GetGameComponents().end(); ++it)
	{
		ImGui::PushID((*it));
		ImGui::Bullet();
		if (ImGui::Selectable((*it)->GetName().c_str(), (*it)->GetIsActive()))
			_inspector = new Inspector((*it));
		if (PopUpMenuItemGC((*it), app))
		{
			ImGui::PopID();
			break;
		}
		ImGui::PopID();

	}
}

void Hierarchy::Update(QXstring name, ImGuiWindowFlags flags, Quantix::Physic::Transform3D* node, Quantix::Core::Platform::Application* app)
{
	ImGui::Begin(name.c_str(), NULL, flags);
	{
		if (ImGui::TreeNodeEx(&node, ImGuiTreeNodeFlags_DefaultOpen, "World Scene"))
		{
			if (node->GetChilds().size() > 0)
				DrawObject(node->GetChilds(), node->GetChilds(), app);
			if (app->scene->GetRoot2D()->GetTransform()->GetChilds().size() > 0)
				DrawObject2D(app->scene->GetRoot2D()->GetTransform()->GetChilds(), app->scene->GetRoot2D()->GetTransform()->GetChilds(), app);
			if (app->scene->GetGameComponents().size() > 0)
				DrawGameComponent(app);
			PopUpMenu(app);
			ImGui::TreePop();
		}
	}
	ImGui::End();
}

void Hierarchy::CreateChild(QXbool& select, std::list<Quantix::Physic::Transform3D*>& nodes, Quantix::Core::Platform::Application* app)
{
	for (auto it = nodes.begin(); it != nodes.end(); ++it)
	{
		if ((*it)->GetChilds().size() != 0)
			CreateChild(select, (*it)->GetChilds(), app);

		if ((*it)->GetObject() == _selected)
		{
			if ((*it)->GetChilds().size() == 0)
			{
				app->scene->AddGameObject("GameObject", (*it)->GetObject());
			}
			else
			{
				std::string name = "GameObject" + std::to_string((QXuint)(*it)->GetChilds().size());
				app->scene->AddGameObject(name, (*it)->GetObject());
			}

			select = false;
			_selected = nullptr;
			ImGui::CloseCurrentPopup();
		}
	}
}

void Hierarchy::RemoveObject(QXbool& select, std::list<Quantix::Physic::Transform3D*>& nodes, Quantix::Core::Platform::Application* app)
{
	for (auto it = nodes.begin(); it != nodes.end();)
	{
		if ((*it)->GetChilds().size() != 0)
			RemoveObject(select, (*it)->GetChilds(), app);

		if ((*it)->GetObject() == _selected)
		{
			for (QXuint i = 0; i < (*it)->GetObject()->GetComponents().size(); i++)
				(*it)->GetObject()->RemoveComponent((*it)->GetObject()->GetComponents()[i]);
			it = nodes.erase(it);
			_selected = nullptr;
			select = false;
			ImGui::CloseCurrentPopup();
		}
		else
			++it;
	}
}

void Hierarchy::RemoveObject2D(QXbool& select, std::list<Quantix::Physic::Transform2D*>& nodes, Quantix::Core::Platform::Application* app)
{
	for (auto it = nodes.begin(); it != nodes.end();)
	{
		if ((*it)->GetChilds().size() != 0)
			RemoveObject2D(select, (*it)->GetChilds(), app);

		if ((*it)->GetObject() == _selected)
		{
			for (QXuint i = 0; i < (*it)->GetObject()->GetComponents().size(); i++)
				(*it)->GetObject()->RemoveComponent((*it)->GetObject()->GetComponents()[i]);
			it = nodes.erase(it);
			_selected = nullptr;
			select = false;
			ImGui::CloseCurrentPopup();
		}
		else
			++it;
	}
}

void Hierarchy::RemoveGC(QXbool& select, std::list<Quantix::Core::DataStructure::GameComponent*>& nodes, Quantix::Core::Platform::Application* app)
{
	for (auto it = nodes.begin(); it != nodes.end();)
	{
		if ((*it) == _selected)
		{
			for (QXuint i = 0; i < (*it)->GetComponents().size(); i++)
				(*it)->RemoveComponent((*it)->GetComponents()[i]);
			it = nodes.erase(it);
			_selected = nullptr;
			ImGui::CloseCurrentPopup();
		}
		else
			++it;
	}
}

QXstring Hierarchy::Rename(const QXchar* name, QXsizei size)
{
	QXchar currName[64];

	memcpy(currName, name, size);
	if (ImGui::InputText("##Input", currName, IM_ARRAYSIZE(currName), ImGuiInputTextFlags_EnterReturnsTrue))
		return currName;
	return "";
}

void Hierarchy::MenuRename(std::list<Quantix::Physic::Transform3D*>& nodes, Quantix::Core::Platform::Application* app)
{
	for (auto it = nodes.begin(); it != nodes.end(); ++it)
	{
		if ((*it)->GetChilds().size() != 0)
		{
			std::list<Quantix::Physic::Transform3D*> child = (*it)->GetChilds();
			MenuRename(child, app);
		}

		if ((*it)->GetObject() == _selected)
		{
			QXstring name = Rename((*it)->GetObject()->GetName().c_str(), (*it)->GetObject()->GetName().size() + 1);
			if (name != "")
			{
				app->scene->GetGameObject((*it)->GetObject()->GetName())->SetName(name);
				if (_inspector != nullptr)
					_inspector->SetNode((*it)->GetObject());
				_selected = nullptr;
				ImGui::CloseCurrentPopup();
			}

		}
	}
}

void Hierarchy::MenuRename2D(std::list<Quantix::Physic::Transform2D*>& nodes, Quantix::Core::Platform::Application* app)
{
	for (auto it = nodes.begin(); it != nodes.end(); ++it)
	{
		if ((*it)->GetChilds().size() != 0)
		{
			std::list<Quantix::Physic::Transform2D*> child = (*it)->GetChilds();
			MenuRename2D(child, app);
		}

		if ((*it)->GetObject() == _selected)
		{
			QXstring name = Rename((*it)->GetObject()->GetName().c_str(), (*it)->GetObject()->GetName().size() + 1);
			if (name != "")
			{
				app->scene->GetGameObject((*it)->GetObject()->GetName())->SetName(name);
				if (_inspector != nullptr)
					_inspector->SetNode((*it)->GetObject());
				_selected = nullptr;
				ImGui::CloseCurrentPopup();
			}

		}
	}
}

QXbool Hierarchy::PopUpMenuItem2D(std::list<Quantix::Physic::Transform2D*>& nodes, Quantix::Physic::Transform2D* node, Quantix::Core::Platform::Application* app)
{
	static QXbool isRemoved = QX_FALSE;
	if (ImGui::BeginPopupContextItem("Context Item 2D"))
	{
		if (_selected == nullptr)
			_selected = node->GetObject();
		else
		{
			static QXbool selection[2] = { QX_FALSE, QX_FALSE };
			if (ImGui::Selectable("Create Empty", &selection[0]))
				CreateEmptyObject2D(selection[0], app);
			if (ImGui::Selectable("Remove", &selection[1]))
				RemoveObject2D(selection[1], nodes, app);
			if (selection[1])
				isRemoved = QX_TRUE;
			MenuRename2D(nodes, app);
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

QXbool Hierarchy::PopUpMenuItem(std::list<Quantix::Physic::Transform3D*>& nodes, Quantix::Physic::Transform3D* node, Quantix::Core::Platform::Application* app)
{
	static QXbool isRemoved = QX_FALSE;
	if (ImGui::BeginPopupContextItem("Context Item 3D"))
	{
		if (_selected == nullptr)
			_selected = node->GetObject();
		else
		{
			if (ImGui::BeginMenu("GameObject3D"))
			{
				static QXbool selection3D[4] = { QX_FALSE, QX_FALSE, QX_FALSE, QX_FALSE };
				if (ImGui::Selectable("Create Empty", &selection3D[0]))
					CreateEmptyObject3D(selection3D[0], app);
				if (ImGui::Selectable("Cube", &selection3D[1]))
					CreateCube(selection3D[1], app);
				if (ImGui::Selectable("Sphere", &selection3D[2]))
					CreateSphere(selection3D[2], app);
				if (ImGui::Selectable("Capsule", &selection3D[3]))
					CreateCapsule(selection3D[3], app);

				ImGui::EndMenu();
			}
			static QXbool selection = QX_FALSE;
			if (ImGui::Selectable("Remove", &selection))
				RemoveObject(selection, nodes, app);
			if (selection)
				isRemoved = QX_TRUE;
			MenuRename(nodes, app);
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

QXbool Hierarchy::PopUpMenuItemGC(Quantix::Core::DataStructure::GameComponent* node, Quantix::Core::Platform::Application* app)
{
	static QXbool isRemoved = QX_FALSE;
	if (ImGui::BeginPopupContextItem("Context Item GC"))
	{
		if (_selected == nullptr)
			_selected = node;
		else
		{
			static QXbool selection = QX_FALSE;
			if (ImGui::Selectable("Remove", &selection))
				RemoveGC(selection, app->scene->GetGameComponents(), app);
			if (selection)
			{
				isRemoved = QX_TRUE;
				selection = QX_FALSE;
			}
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

void Hierarchy::CreateGameComponent(QXbool& selection, Quantix::Core::Platform::Application* app)
{
	if (selection)
	{
		if (app->scene->GetGameComponents().size() == 0)
		{
			app->scene->AddGameComponent("GameComponent", (Quantix::Core::DataStructure::GameComponent*)_selected);
		}
		else
		{
			std::string name = "GameComponent" + std::to_string((QXuint)app->scene->GetGameComponents().size());
			app->scene->AddGameComponent(name, (Quantix::Core::DataStructure::GameComponent*)_selected);
		}
		_selected = nullptr;
		selection = false;
	}
}

void Hierarchy::CreateEmptyObject3D(QXbool& selection, Quantix::Core::Platform::Application* app)
{
	if (selection)
	{
		QXuint value = 0;
		if (_selected)
			value = ((Quantix::Physic::Transform3D*)_selected)->GetChilds().size();
		else
			value = app->scene->GetRoot()->GetTransform()->GetChilds().size();
		if (value == 0)
		{
			app->scene->AddGameObject("GameObject", (Quantix::Physic::Transform3D*)_selected);
		}
		else
		{
			std::string name = "GameObject" + std::to_string((QXuint)app->scene->GetRoot()->GetTransform()->GetChilds().size());
			app->scene->AddGameObject(name, (Quantix::Physic::Transform3D*)_selected);
		}
		_selected = nullptr;
		selection = false;
	}
}

void Hierarchy::CreateCube(QXbool& selection, Quantix::Core::Platform::Application* app)
{
	if (selection)
	{
		Quantix::Core::DataStructure::GameObject3D* obj;
		QXuint value = 0;
		if (_selected)
			value = ((Quantix::Physic::Transform3D*)_selected)->GetChilds().size();
		else
			value = app->scene->GetRoot()->GetTransform()->GetChilds().size();
		if (value == 0)
		{
			obj = app->scene->AddGameObject("Cube", (Quantix::Physic::Transform3D*)_selected);
		}
		else
		{
			QXstring name = "Cube" + std::to_string((QXuint)app->scene->GetRoot()->GetTransform()->GetChilds().size());
			obj = app->scene->AddGameObject(name, (Quantix::Physic::Transform3D*)_selected);
		}
		obj->AddComponent<Quantix::Core::Components::Mesh>();
		Quantix::Core::Components::Mesh* mesh = obj->GetComponent<Quantix::Core::Components::Mesh>();
		mesh->Init(obj);
		mesh = app->manager.CreateMesh(mesh, "media/Mesh/cube.obj");

		_selected = nullptr;
		selection = false;
	}
}

void Hierarchy::CreateSphere(QXbool& selection, Quantix::Core::Platform::Application* app)
{
	if (selection)
	{
		Quantix::Core::DataStructure::GameObject3D* obj;
		QXuint value = 0;
		if (_selected)
			value = ((Quantix::Physic::Transform3D*)_selected)->GetChilds().size();
		else
			value = app->scene->GetRoot()->GetTransform()->GetChilds().size();
		if (value == 0)
		{
			obj = app->scene->AddGameObject("Sphere", (Quantix::Physic::Transform3D*)_selected);
		}
		else
		{
			QXstring name = "Sphere" + std::to_string((QXuint)app->scene->GetRoot()->GetTransform()->GetChilds().size());
			obj = app->scene->AddGameObject(name, (Quantix::Physic::Transform3D*)_selected);
		}
		obj->AddComponent<Quantix::Core::Components::Mesh>();
		Quantix::Core::Components::Mesh* mesh = obj->GetComponent<Quantix::Core::Components::Mesh>();
		mesh->Init(obj);
		mesh = app->manager.CreateMesh(mesh, "media/Mesh/sphere.obj");

		_selected = nullptr;
		selection = false;
	}
}

void Hierarchy::CreateCapsule(QXbool& selection, Quantix::Core::Platform::Application* app)
{
	if (selection)
	{
		Quantix::Core::DataStructure::GameObject3D* obj;
		QXuint value = 0;
		if (_selected)
			value = ((Quantix::Physic::Transform3D*)_selected)->GetChilds().size();
		else
			value = app->scene->GetRoot()->GetTransform()->GetChilds().size();
		if (value == 0)
		{
			obj = app->scene->AddGameObject("Capsule", (Quantix::Physic::Transform3D*)_selected);
		}
		else
		{
			QXstring name = "Capsule" + std::to_string((QXuint)app->scene->GetRoot()->GetTransform()->GetChilds().size());
			obj = app->scene->AddGameObject(name, (Quantix::Physic::Transform3D*)_selected);
		}
		obj->AddComponent<Quantix::Core::Components::Mesh>();
		Quantix::Core::Components::Mesh* mesh = obj->GetComponent<Quantix::Core::Components::Mesh>();
		mesh->Init(obj);
		mesh = app->manager.CreateMesh(mesh, "media/Mesh/capsule.obj");

		_selected = nullptr;
		selection = false;
	}
}

void Hierarchy::CreateEmptyObject2D(QXbool& selection, Quantix::Core::Platform::Application* app)
{
	if (selection)
	{
		QXuint value = 0;
		if (_selected)
			value = ((Quantix::Physic::Transform2D*)_selected)->GetChilds().size();
		else
			value = app->scene->GetRoot2D()->GetTransform()->GetChilds().size();
		if (value == 0)
		{
			app->scene->AddGameObject2D("GameObject", (Quantix::Physic::Transform2D*)_selected);
		}
		else
		{
			std::string name = "GameObject" + std::to_string((QXuint)app->scene->GetRoot2D()->GetTransform()->GetChilds().size());
			app->scene->AddGameObject2D(name, (Quantix::Physic::Transform2D*)_selected);
		}
		_selected = nullptr;
		selection = false;
	}
}

void Hierarchy::PopUpMenu(Quantix::Core::Platform::Application* app)
{
	if (ImGui::BeginPopupContextWindow("Context Menu", 1, false))
	{
		static QXbool selection = QX_FALSE;

		if (ImGui::Selectable("Game Component", &selection))
			CreateGameComponent(selection, app);
		if (ImGui::BeginMenu("GameObject3D"))
		{
			static QXbool selection3D[4] = { QX_FALSE, QX_FALSE, QX_FALSE, QX_FALSE };
			if (ImGui::Selectable("Create Empty", &selection3D[0]))
				CreateEmptyObject3D(selection3D[0], app);
			if (ImGui::Selectable("Cube", &selection3D[1]))
				CreateCube(selection3D[1], app);
			if (ImGui::Selectable("Sphere", &selection3D[2]))
				CreateSphere(selection3D[2], app);
			if (ImGui::Selectable("Capsule", &selection3D[3]))
				CreateCapsule(selection3D[3], app);
			
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("GameObject2D"))
		{
			static QXbool selection2D = QX_FALSE;
			if (ImGui::Selectable("Create Empty", &selection2D))
				CreateEmptyObject2D(selection2D, app);
			ImGui::EndMenu();
		}
		ImGui::EndPopup();
	}
}

void Hierarchy::DesactivatePrevInspector2D(std::list<Quantix::Physic::Transform2D*>& nodes, std::list<Quantix::Physic::Transform2D*>::iterator& node)
{
	for (auto it = nodes.begin(); it != nodes.end(); ++it)
	{
		if ((*it)->GetChilds().size() > 0)
			DesactivatePrevInspector2D((*it)->GetChilds(), node);
		if ((*it)->GetChilds().size() == 0)
		{
			if ((*it)->GetObject() != (*node)->GetObject() && (*it)->GetObject()->GetIsActive())
				(*it)->GetObject()->SetIsActive(!(*it)->GetObject()->GetIsActive());
		}
		if ((*it)->GetObject() == (*node)->GetObject() && (*it)->GetObject()->GetName() == (*node)->GetObject()->GetName())
		{
			_inspector = new Inspector((*node)->GetObject());
			_inspector->Set2D(QX_TRUE);
		}
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
		{
			_inspector = new Inspector((*node)->GetObject());
			_inspector->Set3D(QX_TRUE);
		}
	}
}