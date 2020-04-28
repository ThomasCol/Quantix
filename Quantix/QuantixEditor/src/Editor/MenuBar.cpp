#include "MenuBar.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <filesystem>

#define DEFAULTPATH "media"

void MenuBar::FileButton()
{
	if (ImGui::BeginMenu("File"))
	{
		static bool selection[3] = { false, false, false };
		ImGui::Selectable("New Project", &selection[0]);
		ImGui::Selectable("Save", &selection[1]);
		ImGui::Selectable("Save As", &selection[2]);
		ImGui::EndMenu();
	}
}

void MenuBar::EditButton()
{
	if (ImGui::BeginMenu("Edit"))
	{
		static QXbool selection[2] = { false, false };
		ImGui::Selectable("Project Settings", &selection[0]);
		ImGui::Selectable("Preferences", &selection[1]);
		ImGui::EndMenu();
	}
}

void MenuBar::OpenExplorer(QXbool selection)
{
	if (selection)
	{
		QXstring cmd = "explorer ";
		cmd += std::filesystem::current_path().string() + "\\" + DEFAULTPATH;
		std::cout << cmd << std::endl;
		system(cmd.c_str());
	}
}

void MenuBar::AssetButton()
{
	if (ImGui::BeginMenu("Asset"))
	{
		if (ImGui::BeginMenu("Create"))
		{
			static QXbool selection[2] = { false, false };
			ImGui::Selectable("Material", &selection[0]);
			ImGui::Selectable("Shader", &selection[1]);
			ImGui::EndMenu();
		}
		static QXbool selection[2] = { false, false };
		if (ImGui::Selectable("Show in Explorer", &selection[0]))
			OpenExplorer(true);
		ImGui::Selectable("Import Asset", &selection[1]);
		ImGui::EndMenu();
	}
}

void MenuBar::Update(Quantix::Core::Platform::Application* app)
{
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(52 / 255, 73 / 255, 94 / 255, 1));
	if (ImGui::BeginMenuBar())
	{
		ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(1, 1, 1, 1));
		FileButton();
		EditButton();
		AssetButton();
		GameObjectButton(app);
		ImGui::PopStyleColor();
		ImGui::EndMenuBar();
	}
	ImGui::PopStyleColor();
}

void MenuBar::CreateGameObject(QXstring name, QXbool& selection, Quantix::Core::Platform::Application* app)
{
	static QXuint i = 0;
	if (i == 0)
		app->scene->AddGameObject("GameObject");
	else
		app->scene->AddGameObject("GameObject" + std::to_string(i));
	selection = false;
	i++;
}

void MenuBar::CreateObject(QXbool* selection, std::vector<QXstring> objectName, Quantix::Core::Platform::Application* app)
{
	static QXuint j[2] = { 0, 0 };
	for (QXuint i{ 0 }; i < objectName.size(); i++)
	{
		if (selection[i])
		{
			if (j[i] == 0)
				app->scene->AddGameObject(objectName[i]);
			else
				app->scene->AddGameObject(objectName[i] + std::to_string(j[i]));
			selection[i] = false;
			j[i]++;
			return;
		}
	}
}

void MenuBar::CreateShapeObject(QXbool* selection, std::vector<QXstring> objectName, Quantix::Core::Platform::Application* app)
{
	static QXuint j[2] = { 0, 0 };
	for (QXuint i{ 0 }; i < objectName.size(); i++)
	{
		if (selection[i])
		{
			Quantix::Core::DataStructure::GameObject3D* obj;
			if (j[i] == 0)
				obj = app->scene->AddGameObject(objectName[i]);
			else
				obj = app->scene->AddGameObject(objectName[i] + std::to_string(j[i]));
			
			obj->AddComponent<Quantix::Core::Components::Mesh>();
			Quantix::Core::Components::Mesh* mesh = obj->GetComponent<Quantix::Core::Components::Mesh>();
			if (i == 0)
				mesh = app->manager.CreateMesh(mesh, "../QuantixEngine/Media/Mesh/cube.obj");
			else
				mesh = app->manager.CreateMesh(mesh, "../QuantixEngine/Media/Mesh/sphere.obj");

			selection[i] = false;
			j[i]++;
			return;
		}
	}
}

void MenuBar::CreateComponentLight(Quantix::Core::DataStructure::GameObject3D* obj, std::vector<QXstring> objectName, QXuint i)
{
	obj->AddComponent<Quantix::Core::Components::Light>();
	Quantix::Core::Components::Light* light = obj->GetComponent<Quantix::Core::Components::Light>();
	if (objectName[i] == "Spot Light")
		light->type = Quantix::Core::Components::ELightType::SPOT;
	if (objectName[i] == "Point Light")
		light->type = Quantix::Core::Components::ELightType::POINT;
	if (objectName[i] == "Directional Light")
		light->type = Quantix::Core::Components::ELightType::DIRECTIONAL;
	light->position = obj->GetTransform()->GetPosition();
}

void MenuBar::CreateLightObject(QXbool* selection, std::vector<QXstring> objectName, Quantix::Core::Platform::Application* app)
{
	static QXuint j[2] = { 0, 0 };
	for (QXuint i{ 0 }; i < objectName.size(); i++)
	{
		if (selection[i])
		{
			Quantix::Core::DataStructure::GameObject3D* obj;
			if (j[i] == 0)
				obj = app->scene->AddGameObject(objectName[i]);
			else
				obj = app->scene->AddGameObject(objectName[i] + std::to_string(j[i]));
			CreateComponentLight(obj, objectName, i);
			selection[i] = false;
			j[i]++;
			return;
		}
	}
}

void MenuBar::GameObjectButton(Quantix::Core::Platform::Application* app)
{
	static QXint id = 0;
	if (ImGui::BeginMenu("GameObject"))
	{
		static QXbool selection = { false };
		ImGui::Selectable("Create Empty", &selection);
		if (selection)
			CreateGameObject("GameObject", selection, app);
		if (ImGui::BeginMenu("3D Object"))
		{
			static QXbool selection[2] = { false, false };
			ImGui::Selectable("Cube", &selection[0]);
			ImGui::Selectable("Sphere", &selection[1]);
			CreateShapeObject(selection, { "Cube", "Sphere" }, app);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Light"))
		{
			static QXbool selection[3] = { false, false, false };
			ImGui::Selectable("Spot Light", &selection[0]);
			ImGui::Selectable("Point Light", &selection[1]);
			ImGui::Selectable("Directional Light", &selection[2]);
			CreateLightObject(selection, { "Spot Light", "Point Light", "Directional Light" }, app);
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}
}
