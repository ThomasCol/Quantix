#include <imgui.h>
#include <imgui_internal.h>

#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include "Hierarchy.h"
#include <Core/Debugger/Logger.h>

Hierarchy::~Hierarchy() noexcept
{
	delete _inspector;
}

void Hierarchy::DrawObject(std::list<Quantix::Core::Physic::Transform3D*>& nodeGlobal, std::list<Quantix::Core::Physic::Transform3D*>& node, Quantix::Core::Platform::Application* app) noexcept
{
	for (auto it = node.begin(); it != node.end(); ++it)
	{
		ImGui::PushID((*it)->GetObject());
		if ((*it)->GetChilds().size() == 0)
		{
			ImGui::Bullet();
			if (ImGui::Selectable((*it)->GetObject()->GetName().c_str(), (*it)->GetObject()->GetIsActive()))
			{
				(*it)->GetObject()->SetIsActive(QX_TRUE);
				if (_inspector)
					delete _inspector;
				_inspector = new Inspector((*it)->GetObject());
				_inspector->Set3D(QX_TRUE);
				DesactiveAllNodes((*it), app);
			}
		}
		else
		{
			QXbool isOpen = ImGui::TreeNodeEx(&(*it), ImGuiTreeNodeFlags_Selected, (*it)->GetObject()->GetName().c_str());
			if (ImGui::IsItemClicked(0))
			{
				(*it)->GetObject()->SetIsActive(QX_TRUE);
				if (_inspector)
					delete _inspector;
				_inspector = new Inspector((*it)->GetObject());
				_inspector->Set3D(QX_TRUE);
				DesactiveAllNodes((*it), app);
			}
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

void Hierarchy::DrawObject2D(std::list<Quantix::Core::Physic::Transform2D*>& nodeGlobal, std::list<Quantix::Core::Physic::Transform2D*>& node, Quantix::Core::Platform::Application* app) noexcept
{
	for (auto it = node.begin(); it != node.end(); ++it)
	{
		ImGui::PushID((*it)->GetObject());
		if ((*it)->GetChilds().size() == 0)
		{
			ImGui::Bullet();
			if (ImGui::Selectable((*it)->GetObject()->GetName().c_str(), (*it)->GetObject()->GetIsActive()))
			{
				(*it)->GetObject()->SetIsActive(QX_TRUE);
				if (_inspector)
					delete _inspector;
				_inspector = new Inspector((*it)->GetObject());
				_inspector->Set2D(QX_TRUE);
				DesactiveAllNodes((*it), app);
			}
		}
		else
		{
			QXbool isOpen = ImGui::TreeNodeEx(&(*it), ImGuiTreeNodeFlags_Selected, (*it)->GetObject()->GetName().c_str());
			if (ImGui::IsItemClicked(0))
			{
				(*it)->GetObject()->SetIsActive(QX_TRUE);
				if (_inspector)
					delete _inspector;
				_inspector = new Inspector((*it)->GetObject());
				_inspector->Set2D(QX_TRUE);
				DesactiveAllNodes((*it), app);
			}
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

void Hierarchy::DesactiveAllNodes(void* ptr, Quantix::Core::Platform::Application* app) noexcept
{
	for (auto it = app->scene->GetGameComponents().begin(); it != app->scene->GetGameComponents().end(); ++it)
	{
		if ((*it) != ptr)
			(*it)->SetIsActive(QX_FALSE);
	}
	for (QXuint i = 0; i < app->scene->GetGameObjects2D().size(); i++)
	{
		if (app->scene->GetGameObjects2D()[i]->GetTransform() != ptr)
			app->scene->GetGameObjects2D()[i]->SetIsActive(QX_FALSE);
	}
	for (QXuint i = 0; i < app->scene->GetGameObjects3D().size(); i++)
	{
		if (app->scene->GetGameObjects3D()[i]->GetTransform() != ptr)
			app->scene->GetGameObjects3D()[i]->SetIsActive(QX_FALSE);
	}
}

void Hierarchy::DrawGameComponent(Quantix::Core::Platform::Application* app) noexcept
{
	for (auto it = app->scene->GetGameComponents().begin(); it != app->scene->GetGameComponents().end(); ++it)
	{
		ImGui::PushID((*it));
		ImGui::Bullet();
		if (ImGui::Selectable((*it)->GetName().c_str(), (*it)->GetIsActive()))
		{
			(*it)->SetIsActive(QX_TRUE);
			if (_inspector)
				delete _inspector;
			_inspector = new Inspector((*it));
			DesactiveAllNodes((*it), app);
		}
		if (PopUpMenuItemGC((*it), app))
		{
			ImGui::PopID();
			break;
		}
		ImGui::PopID();
	}
}

void Hierarchy::Update(QXstring name, ImGuiWindowFlags flags, Quantix::Core::Physic::Transform3D* node, Quantix::Core::Platform::Application* app) noexcept
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

void Hierarchy::CreateChild(QXbool& select, std::list<Quantix::Core::Physic::Transform3D*>& nodes, Quantix::Core::Platform::Application* app) noexcept
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

void Hierarchy::RemoveObject(QXbool& select, std::list<Quantix::Core::Physic::Transform3D*>& nodes, Quantix::Core::Platform::Application* app) noexcept
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

void Hierarchy::RemoveObject2D(QXbool& select, std::list<Quantix::Core::Physic::Transform2D*>& nodes, Quantix::Core::Platform::Application* app) noexcept
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

void Hierarchy::RemoveGC(QXbool& select, std::list<Quantix::Core::DataStructure::GameComponent*>& nodes, Quantix::Core::Platform::Application* app) noexcept
{
	for (auto it = nodes.begin(); it != nodes.end();)
	{
		if ((*it) == _selected)
		{
			for (QXuint i = 0; i < (*it)->GetComponents().size(); i++)
				(*it)->RemoveComponent((*it)->GetComponents()[i]);
			it = nodes.erase(it);
			_selected = nullptr;
			select = false;
			ImGui::CloseCurrentPopup();
		}
		else
			++it;
	}
}

QXstring Hierarchy::Rename(const QXchar* name, QXsizei size) noexcept
{
	QXchar currName[64];

	memcpy(currName, name, size);
	if (ImGui::InputText("##Input", currName, IM_ARRAYSIZE(currName), ImGuiInputTextFlags_EnterReturnsTrue))
		return currName;
	return "";
}

QXbool Hierarchy::PopUpMenuItem2D(std::list<Quantix::Core::Physic::Transform2D*>& nodes, Quantix::Core::Physic::Transform2D* node, Quantix::Core::Platform::Application* app) noexcept
{
	QXbool isRemoved = QX_FALSE;
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
			{
				RemoveObject2D(selection[1], nodes, app);
				isRemoved = QX_TRUE;
			}
		}
		ImGui::EndPopup();
	}
	return isRemoved;
}

QXbool Hierarchy::PopUpMenuItem(std::list<Quantix::Core::Physic::Transform3D*>& nodes, Quantix::Core::Physic::Transform3D* node, Quantix::Core::Platform::Application* app) noexcept
{
	QXbool isRemoved = QX_FALSE;
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
			{
				RemoveObject(selection, nodes, app);
				isRemoved = QX_TRUE;
			}
		}
		ImGui::EndPopup();
	}
	return isRemoved;
}

QXbool Hierarchy::PopUpMenuItemGC(Quantix::Core::DataStructure::GameComponent* node, Quantix::Core::Platform::Application* app) noexcept
{
	QXbool isRemoved = QX_FALSE;
	if (ImGui::BeginPopupContextItem("Context Item GC"))
	{
		if (_selected == nullptr)
			_selected = node;
		else
		{
			static QXbool selection = QX_FALSE;
			if (ImGui::Selectable("Remove", &selection))
			{
				RemoveGC(selection, app->scene->GetGameComponents(), app);
				isRemoved = QX_TRUE;
			}
		}
		ImGui::EndPopup();
	}
	return isRemoved;
}

void Hierarchy::CreateGameComponent(QXbool& selection, Quantix::Core::Platform::Application* app) noexcept
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

void Hierarchy::CreateEmptyObject3D(QXbool& selection, Quantix::Core::Platform::Application* app) noexcept
{
	if (selection)
	{
		QXuint value = 0;
		if (_selected)
			value = (QXuint)((Quantix::Core::Physic::Transform3D*)_selected)->GetChilds().size();
		else
			value = (QXuint)app->scene->GetRoot()->GetTransform()->GetChilds().size();
		if (value == 0)
		{
			app->scene->AddGameObject("GameObject", (Quantix::Core::Physic::Transform3D*)_selected);
		}
		else
		{
			std::string name = "GameObject" + std::to_string(value);
			app->scene->AddGameObject(name, (Quantix::Core::Physic::Transform3D*)_selected);
		}
		_selected = nullptr;
		selection = false;
	}
}

void Hierarchy::CreateCube(QXbool& selection, Quantix::Core::Platform::Application* app) noexcept
{
	if (selection)
	{
		Quantix::Core::DataStructure::GameObject3D* obj;
		QXuint value = 0;
		if (_selected)
			value = (QXuint)((Quantix::Core::Physic::Transform3D*)_selected)->GetChilds().size();
		else
			value = (QXuint)app->scene->GetRoot()->GetTransform()->GetChilds().size();
		if (value == 0)
		{
			obj = app->scene->AddGameObject("Cube", (Quantix::Core::Physic::Transform3D*)_selected);
		}
		else
		{
			QXstring name = "Cube" + std::to_string(value);
			obj = app->scene->AddGameObject(name, (Quantix::Core::Physic::Transform3D*)_selected);
		}
		obj->AddComponent<Quantix::Core::Components::Mesh>();
		Quantix::Core::Components::Mesh* mesh = obj->GetComponent<Quantix::Core::Components::Mesh>();
		mesh->Init(obj);
		mesh = app->manager.CreateMesh(mesh, "media/Mesh/cube.obj");

		_selected = nullptr;
		selection = false;
	}
}

void Hierarchy::CreateSphere(QXbool& selection, Quantix::Core::Platform::Application* app) noexcept
{
	if (selection)
	{
		Quantix::Core::DataStructure::GameObject3D* obj;
		QXuint value = 0;
		if (_selected)
			value = (QXuint)((Quantix::Core::Physic::Transform3D*)_selected)->GetChilds().size();
		else
			value = (QXuint)app->scene->GetRoot()->GetTransform()->GetChilds().size();
		if (value == 0)
		{
			obj = app->scene->AddGameObject("Sphere", (Quantix::Core::Physic::Transform3D*)_selected);
		}
		else
		{
			QXstring name = "Sphere" + std::to_string(value);
			obj = app->scene->AddGameObject(name, (Quantix::Core::Physic::Transform3D*)_selected);
		}
		obj->AddComponent<Quantix::Core::Components::Mesh>();
		Quantix::Core::Components::Mesh* mesh = obj->GetComponent<Quantix::Core::Components::Mesh>();
		mesh->Init(obj);
		mesh = app->manager.CreateMesh(mesh, "media/Mesh/sphere.obj");

		_selected = nullptr;
		selection = false;
	}
}

void Hierarchy::CreateCapsule(QXbool& selection, Quantix::Core::Platform::Application* app) noexcept
{
	if (selection)
	{
		Quantix::Core::DataStructure::GameObject3D* obj;
		QXuint value = 0;
		if (_selected)
			value = (QXuint)((Quantix::Core::Physic::Transform3D*)_selected)->GetChilds().size();
		else
			value = (QXuint)app->scene->GetRoot()->GetTransform()->GetChilds().size();
		if (value == 0)
		{
			obj = app->scene->AddGameObject("Capsule", (Quantix::Core::Physic::Transform3D*)_selected);
		}
		else
		{
			QXstring name = "Capsule" + std::to_string(value);
			obj = app->scene->AddGameObject(name, (Quantix::Core::Physic::Transform3D*)_selected);
		}
		obj->AddComponent<Quantix::Core::Components::Mesh>();
		Quantix::Core::Components::Mesh* mesh = obj->GetComponent<Quantix::Core::Components::Mesh>();
		mesh->Init(obj);
		mesh = app->manager.CreateMesh(mesh, "media/Mesh/capsule.obj");

		_selected = nullptr;
		selection = false;
	}
}

void Hierarchy::CreateEmptyObject2D(QXbool& selection, Quantix::Core::Platform::Application* app) noexcept
{
	if (selection)
	{
		QXuint value = 0;
		if (_selected)
			value = (QXuint)((Quantix::Core::Physic::Transform2D*)_selected)->GetChilds().size();
		else
			value = (QXuint)app->scene->GetRoot2D()->GetTransform()->GetChilds().size();
		if (value == 0)
		{
			app->scene->AddGameObject2D("GameObject", (Quantix::Core::Physic::Transform2D*)_selected);
		}
		else
		{
			std::string name = "GameObject" + std::to_string(value);
			app->scene->AddGameObject2D(name, (Quantix::Core::Physic::Transform2D*)_selected);
		}
		_selected = nullptr;
		selection = false;
	}
}

void Hierarchy::PopUpMenu(Quantix::Core::Platform::Application* app) noexcept
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
