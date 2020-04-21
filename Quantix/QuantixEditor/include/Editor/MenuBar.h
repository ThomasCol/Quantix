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

	void Update(Quantix::Core::Platform::Application* app);
	void CreateGameObject(std::string name, bool& selection, Quantix::Core::Platform::Application* app);
	void CreateObject(bool* selection, std::vector<std::string> objectName, Quantix::Core::Platform::Application* app);
	void CreateShapeObject(bool* selection, std::vector<std::string> objectName, Quantix::Core::Platform::Application* app);
	void CreateComponentLight(Quantix::Core::DataStructure::GameObject3D* obj, std::vector<QXstring> objectName, QXuint i);
	void CreateLightObject(bool* selection, std::vector<std::string> objectName, Quantix::Core::Platform::Application* app);

	void FileButton();
	void EditButton();
	void AssetButton();
	void GameObjectButton(Quantix::Core::Platform::Application* app);

private:

};

#endif // !_MENUBAR_H_