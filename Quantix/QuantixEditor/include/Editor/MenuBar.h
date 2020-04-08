#ifndef _MENUBAR_H_
#define _MENUBAR_H_

#include <Core/DataStructure/GameObject3D.h>

#include <vector>
#include <string>
#include <Node.h>

#include "Type.h"

class MenuBar
{
public:
	MenuBar() = default;
	MenuBar(const MenuBar& menu) = default;
	MenuBar(MenuBar&& menu) = default;
	~MenuBar() = default;

	void Update(std::vector<Node>& object);
	void CreateGameObject(QXstring name, std::vector<Node>& object, QXbool& selection);
	void CreateObject(QXbool* selection, std::vector<QXstring> objectName, std::vector<Node>& object);
	void CreateShapeObject(QXbool* selection, std::vector<QXstring> objectName, std::vector<Node>& object);
	void CreateLightObject(QXbool* selection, std::vector<QXstring> objectName, std::vector<Node>& object);
	/*void Update(std::vector<Core::DataStructure::GameComponent*>& object);
	void CreateGameObject(std::string name, std::vector<Core::DataStructure::GameComponent*>& object, bool& selection);
	void CreateObject(bool* selection, std::vector<std::string> objectName, std::vector<Core::DataStructure::GameComponent*>& object);
	void CreateShapeObject(bool* selection, std::vector<std::string> objectName, std::vector<Core::DataStructure::GameComponent*>& object);
	void CreateLightObject(bool* selection, std::vector<std::string> objectName, std::vector<Core::DataStructure::GameComponent*>& object);*/

	void FileButton();
	void EditButton();
	void AssetButton();
	void GameObjectButton(std::vector<Node>& object);
	//void GameObjectButton(std::vector<Core::DataStructure::GameComponent*>& object);

private:

};

#endif // !_MENUBAR_H_