#ifndef _MENUBAR_H_
#define _MENUBAR_H_

#include <Core/Platform/Application.h>
#include <Core/DataStructure/GameObject3D.h>

#include <vector>
#include <string>

#include "Type.h"

class MenuBar
{
public:
	MenuBar() = default;
	MenuBar(const MenuBar& menu) = default;
	MenuBar(MenuBar&& menu) = default;
	~MenuBar() = default;

	void Update(std::vector<Quantix::Physic::Transform3D*>& object, Quantix::Core::Platform::Application* app);
	void CreateGameObject(std::string name, std::vector<Quantix::Physic::Transform3D*>& object, bool& selection, Quantix::Core::Platform::Application* app);
	void CreateObject(bool* selection, std::vector<std::string> objectName, std::vector<Quantix::Physic::Transform3D*>& object, Quantix::Core::Platform::Application* app);
	void CreateShapeObject(bool* selection, std::vector<std::string> objectName, std::vector<Quantix::Physic::Transform3D*>& object, Quantix::Core::Platform::Application* app);
	void CreateLightObject(bool* selection, std::vector<std::string> objectName, std::vector<Quantix::Physic::Transform3D*>& object, Quantix::Core::Platform::Application* app);

	void FileButton();
	void EditButton();
	void AssetButton();
	void GameObjectButton(std::vector<Quantix::Physic::Transform3D*>& object, Quantix::Core::Platform::Application* app);

private:

};

#endif // !_MENUBAR_H_