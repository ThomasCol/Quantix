#include "MenuBar.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <filesystem>
#include <Core/Physic/PhysicHandler.h>

#define DEFAULTPATH "media"

void MenuBar::LoadScene(Quantix::Core::Platform::Application* app) noexcept
{
	Quantix::Core::Physic::PhysicHandler::GetInstance()->CleanScene();
	app->newScene = app->manager.LoadScene("../QuantixEngine/Media/scene.quantix");
	app->sceneChange = true;
}

void MenuBar::FileButton(Quantix::Core::Platform::Application* app) noexcept
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

void MenuBar::PhysXSettings() noexcept
{
	ImGui::GetStyle().WindowRounding = 8.f;
	if (ImGui::Begin("PhysX Settings", &_winPhysX, ImGuiWindowFlags_NoCollapse))
	{
		rttr::instance inst(Quantix::Core::Physic::PhysicHandler::GetInstance());
		for (auto it = Quantix::Core::Physic::PhysicHandler::GetInstance()->get_type().get_properties().begin(); it != Quantix::Core::Physic::PhysicHandler::GetInstance()->get_type().get_properties().end(); ++it)
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

Math::QXvec4 MenuBar::GetMatrixLineColorCorrection(QXint i, Math::QXmat4 mat) noexcept
{
	Math::QXvec4 rgba;
	for (QXint j = 0; j < 4; j++)
		rgba[j] = mat.array[i * 4 + j];
	return rgba;
}

void MenuBar::SetMatrixLineColorCorrection(QXint i, Math::QXmat4& mat, Math::QXvec4 rgba) noexcept
{
	for (QXint j = 0; j < 4; j++)
		mat.array[i * 4 + j] = rgba[j];
}

void MenuBar::CheckPrimitiveType(rttr::instance inst, rttr::property currentProp, rttr::type type, Quantix::Core::Platform::Application* app) noexcept
{
	if (type == rttr::type::get<QXbool>())
	{
		QXbool enable = currentProp.get_value(inst).to_bool();
		ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(165.f); ImGui::Checkbox("", &enable);
		currentProp.set_value(inst, enable);
	}
	else if (type == rttr::type::get<QXfloat>())
	{
		rttr::variant data = currentProp.get_metadata("Description");
		QXfloat value = currentProp.get_value(inst).to_float();
		ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(165.f);
		if (data.is_valid())
			ImGui::DragFloat("", &value, 0.02f, 0.f);
		else
			ImGui::DragFloat("", &value, 0.02f, 0.f, 1.f);
		currentProp.set_value(inst, value);
	}
	else if (type == rttr::type::get<QXuint>())
	{
		QXint value = currentProp.get_value(inst).to_uint32();
		ImGui::Text(currentProp.get_name().to_string().c_str()); ImGui::SameLine(165.f); ImGui::InputInt("", &value);
		currentProp.set_value(inst, (QXuint)value);
	}
	else if (type.is_array())
	{
		if (ImGui::TreeNode(currentProp.get_name().to_string().c_str()))
		{
			QXfloat value[5];
			for (QXuint i = 0; i < 5; i++)
			{
				ImGui::PushID(&value[i]);
				value[i] = currentProp.get_value(inst).create_sequential_view().get_value(i).to_float();
				QXstring name = "Weight" + std::to_string(i);
				ImGui::Text(name.c_str()); ImGui::SameLine(165.f); ImGui::DragFloat("", &value[i], 0.02f, 0.f, 1.f);
				ImGui::PopID();
			}
			currentProp.set_value(inst, value);
			ImGui::TreePop();
		}
	}
	else if (type == rttr::type::get<Math::QXmat4>())
	{
		Math::QXmat4 value = currentProp.get_value(inst).get_value<Math::QXmat4>();
		if (ImGui::TreeNode(currentProp.get_name().to_string().c_str()))
		{
			for (QXint i = 0; i < 3; i++)
			{
				ImGui::PushID(i);
				Math::QXvec4 correction = GetMatrixLineColorCorrection(i, value);

				QXstring name = "Correction " + std::to_string(i);
				ImGui::Text(name.c_str()); ImGui::SameLine(165.f); ImGui::ColorEdit4("", correction.e);

				SetMatrixLineColorCorrection(i, value, correction);
				ImGui::PopID();
			}
			currentProp.set_value(inst, value);

			ImGui::TreePop();
		}
	}
}

void MenuBar::PostProcessSettings(Quantix::Core::Platform::Application* app) noexcept
{
	ImGui::GetStyle().WindowRounding = 8.f;
	if (ImGui::Begin("PostProcess Settings", &_postProcess, ImGuiWindowFlags_NoCollapse))
	{
		rttr::array_range postProcess = rttr::type::get<Quantix::Core::Render::PostProcess::PostProcessEffect>().get_derived_classes();
		std::list<QXstring> postProcessName;
		std::vector<Quantix::Core::Render::PostProcess::PostProcessEffect*> effect = app->renderer.GetEffects();

		for (auto it : postProcess)
			postProcessName.push_back(it.get_name().to_string());
		postProcessName.sort();

		for (auto it = postProcessName.begin(); it != postProcessName.end(); ++it)
		{
			for (auto itPostProcess = postProcess.begin(); itPostProcess != postProcess.end(); ++itPostProcess)
			{
				if (itPostProcess->get_name().to_string() == (*it))
				{
					for (QXsizei i = 0; i < effect.size(); i++)
					{
						if (effect[i]->name == itPostProcess->get_name().to_string())
						{
							ImGui::PushID((QXint)i);
							if (ImGui::TreeNode(effect[i]->name.c_str()))
							{
								for (auto itProp = itPostProcess->get_properties().begin(); itProp != itPostProcess->get_properties().end(); ++itProp)
								{
									ImGui::PushID(itProp->get_name().to_string().c_str());
									rttr::property currentProp = *(itProp);
									rttr::type type = currentProp.get_type();
									CheckPrimitiveType(effect[i], currentProp, type, app);
									ImGui::PopID();
								}
								ImGui::TreePop();
							}
							ImGui::PopID();
							break;
						}
					}
					break;
				}
			}
		}
		ImGui::End();
	}
	else
		_postProcess = QX_FALSE;
	ImGui::GetStyle().WindowRounding = 0.f;
}

void MenuBar::Settings(QXbool* selection) noexcept
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

void MenuBar::EditButton() noexcept
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

void MenuBar::OpenExplorer(QXbool selection) noexcept
{
	if (selection)
	{
		QXstring cmd = "explorer ";
		cmd += std::filesystem::current_path().string() + "\\" + DEFAULTPATH;
		std::cout << cmd << std::endl;
		system(cmd.c_str());
	}
}

void MenuBar::AssetButton() noexcept
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

void MenuBar::Update(Quantix::Core::Platform::Application* app) noexcept
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

void MenuBar::CreateGameObject(QXstring name, QXbool& selection, Quantix::Core::Platform::Application* app) noexcept
{
	static QXuint i = 0;
	if (i == 0)
		app->scene->AddGameObject("GameObject");
	else
		app->scene->AddGameObject("GameObject" + std::to_string(i));
	selection = QX_FALSE;
	i++;
}

void MenuBar::CreateObject(QXbool* selection, std::vector<QXstring> objectName, Quantix::Core::Platform::Application* app) noexcept
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

void MenuBar::CreateShapeObject(QXbool* selection, std::vector<QXstring> objectName, Quantix::Core::Platform::Application* app) noexcept
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

void MenuBar::CreateComponentLight(Quantix::Core::DataStructure::GameObject3D* obj, std::vector<QXstring> objectName, QXuint i) noexcept
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

void MenuBar::CreateLightObject(QXbool* selection, std::vector<QXstring> objectName, Quantix::Core::Platform::Application* app) noexcept
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

void MenuBar::GameObjectButton(Quantix::Core::Platform::Application* app) noexcept
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
