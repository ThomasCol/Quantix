#include "MenuBar.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

void MenuBar::Update(std::vector<Node>& object)
{
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(52 / 255, 73 / 255, 94 / 255, 1));
	if (ImGui::BeginMenuBar())
	{
		ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(1, 1, 1, 1));
		FileButton();
		EditButton();
		AssetButton();
		GameObjectButton(object);
		ImGui::PopStyleColor();
		ImGui::EndMenuBar();
	}
	ImGui::PopStyleColor();
}

void MenuBar::CreateGameObject(QXstring name, std::vector<Node>& object, QXbool& selection)
{
	static QXuint i = 0;
	if (i == 0)
		object.push_back({ {}, "GameObject", i, false });
	else
		object.push_back({ {}, "GameObject" + std::to_string(i), i, false });
	selection = false;
	i++;
}

void MenuBar::CreateObject(QXbool* selection, std::vector<QXstring> objectName, std::vector<Node>& object)
{
	static QXuint j[2] = { 0, 0 };
	for (QXuint i{ 0 }; i < objectName.size(); i++)
	{
		if (selection[i])
		{
			if (j[i] == 0)
				object.push_back({ {}, objectName[i], j[i], false });
			else
				object.push_back({ {}, objectName[i] + std::to_string(j[i]), j[i], false });
			selection[i] = false;
			j[i]++;
			return;
		}
	}
}

void MenuBar::CreateShapeObject(QXbool* selection, std::vector<QXstring> objectName, std::vector<Node>& object)
{
	static QXuint j[2] = { 0, 0 };
	for (QXuint i{ 0 }; i < objectName.size(); i++)
	{
		if (selection[i])
		{
			if (j[i] == 0)
				object.push_back({ {}, objectName[i], j[i], false });
			else
				object.push_back({ {}, objectName[i] + std::to_string(j[i]), j[i], false });
			selection[i] = false;
			j[i]++;
			return;
		}
	}
}

void MenuBar::CreateLightObject(QXbool* selection, std::vector<QXstring> objectName, std::vector<Node>& object)
{
	static QXuint j[2] = { 0, 0 };
	for (QXuint i{ 0 }; i < objectName.size(); i++)
	{
		if (selection[i])
		{
			if (j[i] == 0)
				object.push_back({ {}, objectName[i], j[i], false });
			else
				object.push_back({ {}, objectName[i] + std::to_string(j[i]), j[i], false });
			selection[i] = false;
			j[i]++;
			return;
		}
	}
}

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
		ImGui::Selectable("Show in Explorer", &selection[0]);
		ImGui::Selectable("Import Asset", &selection[1]);
		ImGui::EndMenu();
	}
}

void MenuBar::GameObjectButton(std::vector<Node>& object)
{
	static QXint id = 0;
	if (ImGui::BeginMenu("GameObject"))
	{
		static QXbool selection = { false };
		ImGui::Selectable("Create Empty", &selection);
		if (selection)
			CreateGameObject("GameObject", object, selection);
		if (ImGui::BeginMenu("3D Object"))
		{
			static QXbool selection[2] = { false, false };
			ImGui::Selectable("Cube", &selection[0]);
			ImGui::Selectable("Sphere", &selection[1]);
			CreateShapeObject(selection, { "Cube", "Sphere" }, object);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Light"))
		{
			static QXbool selection[3] = { false, false, false };
			ImGui::Selectable("Spot Light", &selection[0]);
			ImGui::Selectable("Point Light", &selection[1]);
			ImGui::Selectable("Directional Light", &selection[2]);
			CreateLightObject(selection, { "Spot Light", "Point Light", "Directional Light" }, object);
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}
}
