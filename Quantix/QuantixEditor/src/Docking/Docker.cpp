#include "Docker.h"

Docker::Docker() :
	_winEditor{}
{
}

void Docker::Init()
{
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGuiIO& io = ImGui::GetIO();
	_idDocker = ImGui::GetID("MyDockspace");

	ImGui::DockBuilderRemoveNode(_idDocker); // Clear out existing layout
	ImGui::DockBuilderAddNode(_idDocker); // Add empty node

	ImGuiID dock_main_id = _idDocker; // This variable will track the document node, however we are not using it here as we aren't docking anything into it.
	ImGuiID dock_id_prop = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.20f, NULL, &dock_main_id);
	ImGuiID dock_id_center = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.20f, NULL, &dock_main_id);
	ImGuiID dock_id_scene = ImGui::DockBuilderSplitNode(dock_id_center, ImGuiDir_Up, 0.70f, NULL, &dock_id_center);
	ImGuiID dock_id_log = ImGui::DockBuilderSplitNode(dock_id_center, ImGuiDir_Down, 0.20f, NULL, &dock_id_center);
	ImGuiID dock_id_right = ImGui::DockBuilderSplitNode(dock_id_scene, ImGuiDir_Right, 0.20f, NULL, &dock_id_scene);

	_winEditor.push_back(CreateWindowEditorDock("Console", dock_id_log));
	_winEditor.push_back(CreateWindowEditorDock("Explorer", dock_id_log));
	_winEditor.push_back(CreateWindowEditorDock("Scene", dock_id_scene));
	_winEditor.push_back(CreateWindowEditorDock("Hierarchy", dock_id_prop));
	_winEditor.push_back(CreateWindowEditorDock("Inspector", dock_id_right));

	ImGui::DockBuilderFinish(_idDocker);
}

std::string Docker::CreateWindowEditorDock(std::string name, ImGuiID& id)
{
	ImGui::DockBuilderDockWindow(name.c_str(), id);
	return name;
}
