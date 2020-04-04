#include "MenuBar.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

//void MenuBar::Update(std::vector<Core::DataStructure::GameComponent*>& object)
//{
//	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(52 / 255, 73 / 255, 94 / 255, 1));
//	if (ImGui::BeginMenuBar())
//	{
//		ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(1, 1, 1, 1));
//		FileButton();
//		EditButton();
//		AssetButton();
//		GameObjectButton(object);
//		ImGui::PopStyleColor();
//		ImGui::EndMenuBar();
//	}
//	ImGui::PopStyleColor();
//}

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

//void MenuBar::CreateGameObject(std::string name, std::vector<Core::DataStructure::GameComponent*>& object, bool& selection)
//{
//	static unsigned int i = 0;
//	if (i == 0)
//		object.push_back(new Core::DataStructure::GameComponent("GameObject"));
//	else
//		object.push_back(new Core::DataStructure::GameComponent("GameObject" + std::to_string(i)));
//	selection = false;
//	i++;
//}

void MenuBar::CreateGameObject(std::string name, std::vector<Node>& object, bool& selection)
{
	static unsigned int i = 0;
	if (i == 0)
		object.push_back({ {}, "GameObject", i, false });
	else
		object.push_back({ {}, "GameObject" + std::to_string(i), i, false });
	selection = false;
	i++;
}

//void MenuBar::CreateObject(bool* selection, std::vector<std::string> objectName, std::vector<Core::DataStructure::GameComponent*>& object)
//{
//	static unsigned int j[2] = { 0, 0 };
//	for (unsigned int i{ 0 }; i < objectName.size(); i++)
//	{
//		if (selection[i])
//		{
//			if (j[i] == 0)
//				object.push_back(new Core::DataStructure::GameObject3D(objectName[i]));
//			else
//				object.push_back(new Core::DataStructure::GameObject3D(objectName[i] + std::to_string(j[i])));
//			selection[i] = false;
//			j[i]++;
//			return;
//		}
//	}
//}

void MenuBar::CreateObject(bool* selection, std::vector<std::string> objectName, std::vector<Node>& object)
{
	static unsigned int j[2] = { 0, 0 };
	for (unsigned int i{ 0 }; i < objectName.size(); i++)
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

//void MenuBar::CreateShapeObject(bool* selection, std::vector<std::string> objectName, std::vector<Core::DataStructure::GameComponent*>& object)
//{
//	static unsigned int j[2] = { 0, 0 };
//	for (unsigned int i{ 0 }; i < objectName.size(); i++)
//	{
//		if (selection[i])
//		{
//			if (j[i] == 0)
//				object.push_back(new Core::DataStructure::GameObject3D(objectName[i]));
//			else
//				object.push_back(new Core::DataStructure::GameObject3D(objectName[i] + std::to_string(j[i])));
//			selection[i] = false;
//			j[i]++;
//			return;
//		}
//	}
//}

void MenuBar::CreateShapeObject(bool* selection, std::vector<std::string> objectName, std::vector<Node>& object)
{
	static unsigned int j[2] = { 0, 0 };
	for (unsigned int i{ 0 }; i < objectName.size(); i++)
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

//void MenuBar::CreateLightObject(bool* selection, std::vector<std::string> objectName, std::vector<Core::DataStructure::GameComponent*>& object)
//{
//	static unsigned int j[2] = { 0, 0 };
//	for (unsigned int i{ 0 }; i < objectName.size(); i++)
//	{
//		if (selection[i])
//		{
//			if (j[i] == 0)
//				object.push_back(new Core::DataStructure::GameObject3D(objectName[i]));
//			else
//				object.push_back(new Core::DataStructure::GameObject3D(objectName[i] + std::to_string(j[i])));
//			selection[i] = false;
//			j[i]++;
//			return;
//		}
//	}
//}

void MenuBar::CreateLightObject(bool* selection, std::vector<std::string> objectName, std::vector<Node>& object)
{
	static unsigned int j[2] = { 0, 0 };
	for (unsigned int i{ 0 }; i < objectName.size(); i++)
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
		static bool selection[2] = { false, false };
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
			static bool selection[2] = { false, false };
			ImGui::Selectable("Material", &selection[0]);
			ImGui::Selectable("Shader", &selection[1]);
			ImGui::EndMenu();
		}
		static bool selection[2] = { false, false };
		ImGui::Selectable("Show in Explorer", &selection[0]);
		ImGui::Selectable("Import Asset", &selection[1]);
		ImGui::EndMenu();
	}
}

//void MenuBar::GameObjectButton(std::vector<Core::DataStructure::GameComponent*>& object)
//{
//	static int id = 0;
//	if (ImGui::BeginMenu("GameObject"))
//	{
//		static bool selection = { false };
//		ImGui::Selectable("Create Empty", &selection);
//		if (selection)
//			CreateGameObject("GameObject", object, selection);
//		if (ImGui::BeginMenu("3D Object"))
//		{
//			static bool selection[2] = { false, false };
//			ImGui::Selectable("Cube", &selection[0]);
//			ImGui::Selectable("Sphere", &selection[1]);
//			CreateShapeObject(selection, { "Cube", "Sphere" }, object);
//			ImGui::EndMenu();
//		}
//		if (ImGui::BeginMenu("Light"))
//		{
//			static bool selection[3] = { false, false, false };
//			ImGui::Selectable("Spot Light", &selection[0]);
//			ImGui::Selectable("Point Light", &selection[1]);
//			ImGui::Selectable("Directional Light", &selection[2]);
//			CreateLightObject(selection, { "Spot Light", "Point Light", "Directional Light" }, object);
//			ImGui::EndMenu();
//		}
//		ImGui::EndMenu();
//	}
//}

void MenuBar::GameObjectButton(std::vector<Node>& object)
{
	static int id = 0;
	if (ImGui::BeginMenu("GameObject"))
	{
		static bool selection = { false };
		ImGui::Selectable("Create Empty", &selection);
		if (selection)
			CreateGameObject("GameObject", object, selection);
		if (ImGui::BeginMenu("3D Object"))
		{
			static bool selection[2] = { false, false };
			ImGui::Selectable("Cube", &selection[0]);
			ImGui::Selectable("Sphere", &selection[1]);
			CreateShapeObject(selection, { "Cube", "Sphere" }, object);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Light"))
		{
			static bool selection[3] = { false, false, false };
			ImGui::Selectable("Spot Light", &selection[0]);
			ImGui::Selectable("Point Light", &selection[1]);
			ImGui::Selectable("Directional Light", &selection[2]);
			CreateLightObject(selection, { "Spot Light", "Point Light", "Directional Light" }, object);
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}
}
