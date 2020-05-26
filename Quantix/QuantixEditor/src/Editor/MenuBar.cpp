#include "MenuBar.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <filesystem>
#include <Physic/PhysicHandler.h>

#define DEFAULTPATH "media"

void MenuBar::LoadScene(Quantix::Core::Platform::Application* app)
{
	Quantix::Physic::PhysicHandler::GetInstance()->CleanScene();
	app->newScene = app->manager.LoadScene("../QuantixEngine/Media/scene.quantix");
	app->sceneChange = true;
}

void MenuBar::FileButton(Quantix::Core::Platform::Application* app)
{
	if (ImGui::BeginMenu("File"))
	{
		static bool selection[2] = { QX_FALSE, QX_FALSE };
		if (ImGui::Selectable("Save Scene", &selection[1]))
			app->manager.SaveScene(app->scene);
		if (ImGui::Selectable("Load Scene", &selection[2]))
			LoadScene(app);
		ImGui::EndMenu();
	}
}

void MenuBar::PhysXSettings()
{
	ImGui::GetStyle().WindowRounding = 8.f;
	if (ImGui::Begin("PhysX Settings", &_winPhysX, ImGuiWindowFlags_NoCollapse))
	{
		rttr::instance inst(Quantix::Physic::PhysicHandler::GetInstance());
		for (auto it = Quantix::Physic::PhysicHandler::GetInstance()->get_type().get_properties().begin(); it != Quantix::Physic::PhysicHandler::GetInstance()->get_type().get_properties().end(); ++it)
		{
			rttr::property currentProp = *(it);
			ImGui::PushID(currentProp.get_name().to_string().c_str());
			QXbool enable = currentProp.get_value(inst).to_bool();
			ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(300.f); ImGui::Checkbox("", &enable);
			currentProp.set_value(inst, enable);
			ImGui::PopID();
		}
		ImGui::End();
	}
	else
		_winPhysX = QX_FALSE;
	ImGui::GetStyle().WindowRounding = 0.f;
}

void MenuBar::PostProcessSettings(Quantix::Core::Platform::Application* app)
{
	ImGui::GetStyle().WindowRounding = 8.f;
	if (ImGui::Begin("PostProcess Settings", &_postProcess, ImGuiWindowFlags_NoCollapse))
	{
		std::vector<Quantix::Core::Render::PostProcess::PostProcessEffect*> effect = app->renderer.GetEffects();
		for (QXsizei i = 0; i < effect.size(); i++)
		{
			ImGui::PushID(i);
			ImGui::Text(effect[i]->name.c_str()); ImGui::SameLine(300.f); ImGui::Checkbox("", &effect[i]->enable);
			ImGui::PopID();
		}
		ImGui::End();
	}
	else
		_postProcess = QX_FALSE;
	ImGui::GetStyle().WindowRounding = 0.f;
}

void MenuBar::Settings(QXbool* selection)
{
	if (selection[0])
	{
		_winPhysX = !_winPhysX;
		selection[0] = QX_FALSE;
	}
	if (selection[1])
	{
		_postProcess = !_postProcess;
		selection[1] = QX_FALSE;
	}
}

void MenuBar::EditButton()
{
	if (ImGui::BeginMenu("Edit"))
	{
		static QXbool selection[2] = { QX_FALSE, QX_FALSE };
		ImGui::Selectable("PhysX Settings", &selection[0]);
		ImGui::Selectable("PostProcess Settings", &selection[1]);
		Settings(selection);
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
			static QXbool selection[2] = { QX_FALSE, QX_FALSE };
			ImGui::Selectable("Material", &selection[0]);
			ImGui::Selectable("Shader", &selection[1]);
			ImGui::EndMenu();
		}
		static QXbool selection[2] = { QX_FALSE, QX_FALSE };
		if (ImGui::Selectable("Show in Explorer", &selection[0]))
			OpenExplorer(QX_TRUE);
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
		FileButton(app);
		EditButton();
		AssetButton();
		GameObjectButton(app);
		ImGui::PopStyleColor();
		ImGui::EndMenuBar();
	}
	ImGui::PopStyleColor();
	if (_winPhysX)
		PhysXSettings();
	if (_postProcess)
		PostProcessSettings(app);
}

void MenuBar::CreateGameObject(QXstring name, QXbool& selection, Quantix::Core::Platform::Application* app)
{
	static QXuint i = 0;
	if (i == 0)
		app->scene->AddGameObject("GameObject");
	else
		app->scene->AddGameObject("GameObject" + std::to_string(i));
	selection = QX_FALSE;
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
			selection[i] = QX_FALSE;
			j[i]++;
			return;
		}
	}
}

void MenuBar::CreateShapeObject(QXbool* selection, std::vector<QXstring> objectName, Quantix::Core::Platform::Application* app)
{
	static QXuint j[3] = { 0, 0, 0 };
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
			mesh->Init(obj);
			if (i == 0)
				mesh = app->manager.CreateMesh(mesh, "media/Mesh/cube.obj");
			else if (i == 1)
				mesh = app->manager.CreateMesh(mesh, "media/Mesh/sphere.obj");
			else
				mesh = app->manager.CreateMesh(mesh, "media/Mesh/capsule.obj");

			selection[i] = QX_FALSE;
			j[i]++;
			return;
		}
	}
}

void MenuBar::CreateComponentLight(Quantix::Core::DataStructure::GameObject3D* obj, std::vector<QXstring> objectName, QXuint i)
{
	obj->AddComponent<Quantix::Core::Components::Light>();
	Quantix::Core::Components::Light* light = obj->GetComponent<Quantix::Core::Components::Light>();
	light->Init(obj);
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
			selection[i] = QX_FALSE;
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
		static QXbool selection = { QX_FALSE };
		ImGui::Selectable("Create Empty", &selection);
		if (selection)
			CreateGameObject("GameObject", selection, app);
		if (ImGui::BeginMenu("3D Object"))
		{
			static QXbool selection[3] = { QX_FALSE, QX_FALSE };
			ImGui::Selectable("Cube", &selection[0]);
			ImGui::Selectable("Sphere", &selection[1]);
			ImGui::Selectable("Capsule", &selection[2]);
			CreateShapeObject(selection, { "Cube", "Sphere", "Capsule" }, app);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Light"))
		{
			static QXbool selection[3] = { QX_FALSE, QX_FALSE, QX_FALSE };
			ImGui::Selectable("Spot Light", &selection[0]);
			ImGui::Selectable("Point Light", &selection[1]);
			ImGui::Selectable("Directional Light", &selection[2]);
			CreateLightObject(selection, { "Spot Light", "Point Light", "Directional Light" }, app);
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}
}
